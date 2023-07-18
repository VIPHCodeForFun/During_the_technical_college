#include <iostream>
#include <string.h>
#include <iomanip>
#include <sodium.h>

#include <string>

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

int main(const int argc, const char * const argv[])
{
    if (sodium_init() == -1)
    {
        std::cout << "sodium_init() failed " << std::endl;
        return 1;
    }

    /* --------- SIGN --------- */
    if(std::string(argv[1]) == "Sign" && argc == 3 )
    {
        const char * const message = argv[2];
        const size_t message_length = strlen(message);

        /* Private und public Key */
        unsigned char pk[crypto_sign_PUBLICKEYBYTES];
        unsigned char sk[crypto_sign_SECRETKEYBYTES];
        crypto_sign_keypair(pk, sk);

        /* Sign */
        unsigned char signed_message[crypto_sign_BYTES + message_length];
        unsigned long long signed_message_len;
        crypto_sign(signed_message, &signed_message_len, (unsigned char *)message, message_length, sk);

        /* Ausgabe */
        std::cout << "Signed message: " << std::hex;
        for (size_t i = 0; i < signed_message_len; i++)
        {
            std::cout << std::setw(2) << std::setfill('0') << static_cast<int>(signed_message[i]);
        }
        std::cout << std::endl;
        std::cout << "Public key: " << std::hex;
        for (size_t i = 0; i < ( sizeof(pk) / sizeof(unsigned char) ); i++)
        {
            std::cout << std::setw(2) << std::setfill('0') << static_cast<int>(pk[i]);
        }
        std::cout << std::endl;
    }

    /* --------- VERIFY --------- */
    else if(std::string(argv[1]) == "Verify" && argc == 4 )
    {
        /* Convertirung imput von Hex zu unsigned char Array */
        std::string hex_signed_message(argv[2]);
        size_t signed_message_len = (hex_signed_message.length()) / 2;
        unsigned char signed_message[signed_message_len];
        HexStringToArray(hex_signed_message, signed_message, signed_message_len);

        std::string hex_pk(argv[3]);
        size_t pk_len = (hex_pk.length()) / 2;
        unsigned char pk[pk_len];
        HexStringToArray(hex_pk, pk, pk_len);

        /* Vergleich der Signatur */
        unsigned char unsigned_message[signed_message_len - crypto_sign_BYTES];
        unsigned long long unsigned_message_len;
        if (crypto_sign_open(unsigned_message, &unsigned_message_len, signed_message, signed_message_len, pk) != 0)
        {
            /* incorrect signature! */
			std::cout << "Signature invalid." << std:: endl;
        }
        else
        {
        	std::cout << "Signature valid." << std:: endl;
        }
    }
    return 0;
}


