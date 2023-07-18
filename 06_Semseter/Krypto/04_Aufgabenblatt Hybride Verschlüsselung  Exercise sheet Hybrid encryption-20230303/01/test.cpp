#include <iostream>
#include <gmpxx.h>  // https://gmplib.org/manual/
#include <sodium.h>
#include "dbghelp.h"

#include <iomanip>	// std::setw(2)
#include <sstream>
#include <string>

std::string ExtractKey(const mpz_class &g_xy_mod_p)
{
    mpz_class two_256;
    mpz_ui_pow_ui(two_256.get_mpz_t(), 2, 256);
    mpz_class g_xy_short;
    mpz_mod(g_xy_short.get_mpz_t(), g_xy_mod_p.get_mpz_t(), two_256.get_mpz_t());
    std::stringstream s;
    s << std::hex << g_xy_short << std::endl;
    return s.str();
}

bool HexStringToArray(const std::string &hex_string, unsigned char array[], const size_t array_size)
{
    if (hex_string.length() != 2 * array_size)
        return false;
    for (size_t i = 0; i < array_size; i++)
    {
        const std::string str_part(hex_string.c_str() + 2 * i, 2); //Process 2 characters (one byte) at a time
        try
        {
            const auto byte = std::stoul(str_part, nullptr, 16);
            array[i] = byte;
        }
        catch (...)
        {
            return false;
        }
    }
    return true;
}

const char * const g_as_text = "\
  f7e1a085d69b3ddecbbcab5c36b857b97994afbbfa3aea82f\
  9574c0b3d0782675159578ebad4594fe67107108180b44916\
  7123e84c281613b7cf09328cc8a6e13c167a8b547c8d28e0a\
  3ae1e2bb3a675916ea37f0bfa213562f1fb627a01243bcca4\
  f1bea8519089a883dfe15ae59f06928b665e807b552564014\
  c3bfecf492a";
const mpz_class G(g_as_text, 16);

const char * const p_as_text = "\
  fd7f53811d75122952df4a9c2eece4e7f611b7523cef4400c\
  31e3f80b6512669455d402251fb593d8d58fabfc5f5ba30f6\
  cb9b556cd7813b801d346ff26660b76b9950a5a49f9fe8047\
  b1022c24fbba9d7feb7c61bf83b57e7c6a8a6150f04fb83f6\
  d3c51ec3023554135a169132f675f3ae2b61d72aeff222031\
  99dd14801c7";
const mpz_class P(p_as_text, 16);

int main( const int argc, const char * const argv [] )
{
    /* Error Abfrage */
    if ( sodium_init() == -1 )
    {
        return 1;
    }

    /* ServerGeneratePartialKey */
    if ( std::string(argv[1]) == "ServerGeneratePartialKey" && argc == 2 )
    {
        int seed = 1000; // !!! time(nullptr));
        gmp_randstate_t rnd_state;
        gmp_randinit_default(rnd_state);
        gmp_randseed_ui(rnd_state,seed);
        // Erzeuge random Wert für x
        mpz_class x(0);
        mpz_urandomm(x.get_mpz_t(), rnd_state, P.get_mpz_t());

        /* Berechnung von S */
        mpz_class S(0);
        mpz_powm(S.get_mpz_t(),  G.get_mpz_t(), x.get_mpz_t(),  P.get_mpz_t());

        std::cout << "x: " << x.get_mpz_t() << std::endl;
        std::cout << "S: " << S.get_mpz_t() << std::endl;
        return 0;
    }

    /* ClientGeneratePartialKey */
    if ( std::string(argv[1]) == "ClientGeneratePartialKey" && argc == 2 )
    {
        int seed = time(nullptr);
        gmp_randstate_t rnd_state;
        gmp_randinit_default(rnd_state);
        gmp_randseed_ui(rnd_state,seed);
        // Erzeuge random Wert für y
        mpz_class y(0);
        mpz_urandomm(y.get_mpz_t(), rnd_state, P.get_mpz_t());

        /* Berechnung von C */
        mpz_class C(0);
        mpz_powm(C.get_mpz_t(),  G.get_mpz_t(), y.get_mpz_t(),  P.get_mpz_t());

        std::cout << "y: " << y.get_mpz_t() << std::endl;
        std::cout << "C: " << C.get_mpz_t() << std::endl;
        return 0;
    }

    /* ServerGenerateSessionKey */
    if ( std::string(argv[1]) == "ServerGenerateSessionKey" && argc == 4 )
    {
        mpz_class C(argv[2]);
        mpz_class x(argv[3]);
        mpz_class g_xy_mod_p(0);

        mpz_powm(g_xy_mod_p.get_mpz_t(), C.get_mpz_t(), x.get_mpz_t(), P.get_mpz_t());
        std::string k = ExtractKey(g_xy_mod_p);

        std::cout << k << std::endl;
        return 0;
    }

    /* ClientGenerateSessionKey */
    if ( std::string(argv[1]) == "ClientGenerateSessionKey" && argc == 4 )
    {
        mpz_class S(argv[2]);
        mpz_class x(argv[3]);
        mpz_class g_xy_mod_p(0);

        mpz_powm(g_xy_mod_p.get_mpz_t(), S.get_mpz_t(), x.get_mpz_t(), P.get_mpz_t());
        std::string k = ExtractKey(g_xy_mod_p);

        std::cout << k << std::endl;
        return 0;
    }

    /* ServerEncrypt */
    // Console: ServerEncrypt Nachricht Sitzungsschlüssel
    if ( std::string(argv[1]) == "ServerEncrypt" && argc == 4 )
    {
        /* Nachricht zu unsiged char* convertieren */
        std::string strMessage = argv[2];
        int messageLen = strMessage.length();
        unsigned char* message = (unsigned char*)strMessage.c_str();

        /* Hex Schlüssel in u char Schlüssel convertieren */
        std::string hexSessionKey = argv[3];
        unsigned int sessionKeyLen = (hexSessionKey.length()) / 2;
        unsigned char sessionKey[sessionKeyLen];
        HexStringToArray(hexSessionKey, sessionKey, sessionKeyLen);

        /* Verschlüsseln mit AES256-GCM */
        // https://doc.libsodium.org/secret-key_cryptography/aead/aes-256-gcm
        unsigned char nonce[crypto_aead_aes256gcm_NPUBBYTES] = {0};
        unsigned char ciphertext[messageLen + crypto_aead_aes256gcm_ABYTES];
        unsigned long long ciphertext_len;

        crypto_aead_aes256gcm_encrypt(ciphertext, &ciphertext_len,
                                      message, messageLen,
                                      nullptr, 0, NULL,
                                      nonce,
                                      sessionKey);

        /* Ausgabe in HEX */
        for ( int i = 0; i < (int)ciphertext_len; i++)
        {
            std::cout <<  std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(ciphertext[i]);
        }
        std::cout << std::endl;

        return 0;
    }

    /* ClientDecrypt */
    // Console: ClientDecrypt, verschlüsselte Nachricht, Sitzungsschlüssel
    if ( std::string(argv[1]) == "ClientDecrypt" && argc == 4 )
    {
        /* Hex verschlüsselte Nachricht in u char verschlüsselte Nachricht convertieren */
        std::string hexCiphertMessage = argv[2];
        unsigned int ciphertMessageLen = (hexCiphertMessage.length()) / 2;
        unsigned char ciphertMessage[ciphertMessageLen];
        HexStringToArray(hexCiphertMessage, ciphertMessage, ciphertMessageLen);

        /* Hex Schlüssel in u char Schlüssel convertieren */
        std::string hexSessionKey = argv[3];
        unsigned int sessionKeyLen = (hexSessionKey.length() ) / 2;
        unsigned char sessionKey[sessionKeyLen];
        HexStringToArray(hexSessionKey, sessionKey, sessionKeyLen);

        /* Entschlüsseln */
        unsigned char nonce[crypto_aead_aes256gcm_NPUBBYTES] = {0};
        unsigned char decrypted[ciphertMessageLen];
        unsigned long long decrypted_len;

        if (ciphertMessageLen < crypto_aead_aes256gcm_ABYTES || crypto_aead_aes256gcm_decrypt(decrypted, &decrypted_len,
                NULL,
                ciphertMessage, ciphertMessageLen,
                nullptr, 0,
                nonce,
                sessionKey) != 0)
        {
            std::cout << "Fehler !" << std::endl;
            return 666;
        }
        std::cout << decrypted << std::endl;

        return 0;
    }

    std::cout << "Nichts ist passiert :)" << std::endl;
    return 10;
}

