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
