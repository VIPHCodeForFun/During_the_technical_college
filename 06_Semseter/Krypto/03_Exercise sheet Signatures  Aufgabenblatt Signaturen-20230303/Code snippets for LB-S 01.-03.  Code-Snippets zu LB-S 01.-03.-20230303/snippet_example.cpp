unsigned char hash[crypto_hash_sha512_BYTES];
/* TODO: Calculate hash as usual */
mpz_class hash_value;
libsodium_to_GMP(hash, hash_value);