#include <iostream>
#include <cstdio>
#include <termios.h>
#include <unistd.h>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/rsa.h>
#include <gmpxx.h>

static termios DisableEcho()
{
  termios t_old, t_new;
  tcgetattr(STDIN_FILENO, &t_old);
  t_new = t_old;
  t_new.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &t_new);
  return t_old;
}

static void EnableEcho(const termios &old)
{
  tcsetattr(STDIN_FILENO, TCSANOW, &old);
}

static int ProvidePassword(char* buf, int size, int rwflag, void*)
{
  if (rwflag != 0)
    return -1;
  std::cout << "Please enter passphrase: ";
  std::string s;
  const termios old = DisableEcho();
  std::cin >> s;
  EnableEcho(old);
  std::cout << std::endl;
  strncpy(buf, s.c_str(), size);
  return static_cast<int>(s.length());
}

static void ConvertBigNum(const BIGNUM * const value, mpz_class &converted_value)
{
  char * const decimal_value = BN_bn2dec(value);
  converted_value.set_str(decimal_value, 10);
  OPENSSL_free(decimal_value);
}

bool ReadPrivateKeyFromFile(const char * const pem_filename, mpz_class &d, mpz_class &N)
{
  FILE * const fp = fopen(pem_filename, "r");
  if(!fp)
  {
    std::cerr << "File " << pem_filename << " not found" << std::endl;
    return false;
  }
  RSA * const key = PEM_read_RSAPrivateKey(fp, nullptr, ProvidePassword, nullptr);
  fclose(fp);
  if (!key)
  {
    std::cerr << "An error occurred while reading the RSA private key file" << std::endl;
    return false;
  }
  const BIGNUM *big_n, *big_e, *big_d;
  RSA_get0_key(key, &big_n, &big_e, &big_d);
  if (!big_n || !big_d)
  {
    std::cerr << "n or d is null" << std::endl;
    return false;
  }
  ConvertBigNum(big_n, N);
  ConvertBigNum(big_d, d);
  return true;
}

bool ReadPublicKeyFromFile(const char * const crt_filename, mpz_class &e, mpz_class &N)
{
  FILE * const fp = fopen(crt_filename, "r");
  if(!fp)
  {
    std::cerr << "File " << crt_filename << " not found" << std::endl;
    return false;
  }
  const X509 * const certificate = PEM_read_X509(fp, nullptr, nullptr, nullptr);
  fclose(fp);
  if (!certificate)
  {
    std::cerr << "An error occurred while reading the certificate" << std::endl;
    return false;
  }
  EVP_PKEY * const pkey = X509_get0_pubkey(certificate);
  //cout << "PK bits: " << EVP_PKEY_bits(pkey) << endl;
  const RSA * const key = EVP_PKEY_get1_RSA(pkey);
  if (!key)
  {
    std::cerr << "Public key is not an RSA key" << std::endl;
    return false;
  }
  const BIGNUM *big_n, *big_e, *big_d;
  RSA_get0_key(key, &big_n, &big_e, &big_d);
  if (!big_n || !big_e)
  {
    std::cerr << "n or e is null" << std::endl;
    return false;
  }
  ConvertBigNum(big_n, N);
  ConvertBigNum(big_e, e);
  return true;
}

