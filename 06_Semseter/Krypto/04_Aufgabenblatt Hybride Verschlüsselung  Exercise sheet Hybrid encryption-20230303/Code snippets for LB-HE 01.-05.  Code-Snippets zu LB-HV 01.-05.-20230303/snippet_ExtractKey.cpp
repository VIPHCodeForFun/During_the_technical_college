#include <sstream>

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
