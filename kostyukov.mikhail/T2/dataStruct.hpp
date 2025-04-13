#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP
#include <iostream>
#include <string>

namespace kostyukov
{
  struct DataStruct
  {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
  };

  std::istream &operator>>(std::istream &in, DataStruct &dest);
  std::ostream &operator<<(std::ostream &out, const DataStruct &dest);
  bool comparator(const DataStruct &lhs, const DataStruct &rhs);

  struct UllIO
  {
    unsigned long long &ref;
    enum Format { BIN, HEX } format;
    explicit UllIO(unsigned long long &num, Format fmt) : ref(num), format(fmt) {}
  };
  struct StringIO
  {
    std::string &ref;
  };
  struct DelimiterIO
  {
    char expected;
  };

  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
  std::istream &operator>>(std::istream &in, UllIO &&dest);
  std::ostream &operator<<(std::ostream &out, const UllIO &&dest);
  std::ostream &operator<<(std::ostream &out, const StringIO &&dest);
}
#endif
