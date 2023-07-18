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