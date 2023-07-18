#include <iostream>
#include <gmpxx.h>
#include <sodium.h>
#include "dbghelp.h"
#include "certhelp.h"

#include <iomanip> // std::setw(2)


template <size_t N> //Number of bytes (array size)
void libsodium_to_GMP(const unsigned char (&libsodium_value)[N], mpz_class &GMP_value)
{
  GMP_value = 0;
  for (const auto &libsodium_byte : libsodium_value)
  {
    GMP_value *= 256;
    GMP_value += libsodium_byte;
  }
}


int main(const int argc, const char * const argv [])
{
    if (sodium_init() == -1)
        return 1;

    if (argc < 2)
    {
        std::cerr << "Description: " << std::endl;
        std::cerr << "Usage: " << argv[0] << std::endl;
        return 2;
    }

    /* ServerReadPublicKey cert.crt */
    if ( std::string(argv[1]) == "ServerReadPublicKey" && argc == 3 )
    {
        mpz_class e(0);
        mpz_class N(0);
        ReadPublicKeyFromFile(argv[2], e, N);
        std::cout << "Public key: (" << e << ", " << N << ")" << std::endl;
    }

    /* ClientReadPrivateKey key.pem */
    if ( std::string(argv[1]) == "ClientReadPrivateKey" && argc == 3 )
    {
        // ReadPrivateKeyFromFile(const char * const pem_filename, mpz_class &d, mpz_class &N);
        mpz_class d(0);
        mpz_class N(0);
        ReadPrivateKeyFromFile(argv[2], d, N);
        std::cout << "Private key: (" << d << ", " << N << ")" << std::endl;
    }

    /* ServerCreateChallenge 65537 7059515099399582[...] */
    if ( std::string(argv[1]) == "ServerCreateChallenge" && argc == 4)
    {
        mpz_class e (argv[2]);
        mpz_class N (argv[3]);

        /* random nummer r zwischen 0 und N-1 */
        int seed = time(nullptr);
        gmp_randstate_t rnd_state;
        gmp_randinit_default(rnd_state);
        gmp_randseed_ui(rnd_state,seed);
        mpz_class random(0);
        mpz_urandomm(random.get_mpz_t(), rnd_state, N.get_mpz_t() );

        /*  Berechnung der Ent/Verschlüsselung  -> c := Epk(r) <=> c ≡ m^e (mod N). */
        mpz_class c (0);
        mpz_powm(c.get_mpz_t(),  random.get_mpz_t(), e.get_mpz_t(),  N.get_mpz_t());

        std::cout << "Challenge: " << c << std::endl;
        std::cout << "Random number: " << random << std::endl;
    }

    /* ClientCreateResponse 4766680102085249[...] 4697366898921479[...] 7059515099399582[...] */
    if ( std::string(argv[1]) == "ClientCreateResponse" && argc == 5)
    {
        mpz_class c(argv[2]);
        mpz_class  d(argv[3]);
        mpz_class N(argv[4]);

        /* Entschlüsselung m ≡ c^d (mod N). */
        mpz_class m (0);
        mpz_powm(m.get_mpz_t(),  c.get_mpz_t(), d.get_mpz_t(),  N.get_mpz_t());

        /* h := H(Dsk(c)) = h:= H(m) */
        std::string mStr = m.get_str();
        unsigned char hash[crypto_hash_sha512_BYTES];
        crypto_hash_sha512(hash, reinterpret_cast<const unsigned char*>(mStr.data()), mStr.length());

        /* Convertierung zu mpz_class */
		mpz_class hash_value;

		/* Ausgabe */
  		libsodium_to_GMP(hash,hash_value);
 	 	std::cout << hash_value << std::endl;
    }

    /* ServerVerifyResponse 1262648800327937[...] 6688689096349587[...] */
    if ( std::string(argv[1]) == "ServerVerifyResponse" && argc == 4)
    {
        std::string h(argv[2]);
        std::string r(argv[3]);

        /* berechne h′ := H(r) mit der tats¨achlichen Response h. s*/
        unsigned char hash[crypto_hash_sha512_BYTES];
        crypto_hash_sha512(hash, reinterpret_cast<const unsigned char*>(r.data()), r.length());

        /* Convertierung zu mpz_class */
		mpz_class mpz_h(h);

		mpz_class hash_value;
  		libsodium_to_GMP(hash,hash_value);

		/* Vergleiche h und h'*/
        if( mpz_h == hash_value)
        {
            std::cout << "Authenticated successfully" << std::endl;
        }
        else
        {
            std::cout << "Authentication failed" << std::endl;
        }
    }
    return 0;
}
