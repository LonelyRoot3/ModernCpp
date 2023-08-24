#include <climits>
#include <iostream>
#include <limits>
#include <string>

int main() {
  // 1, 将32位数左移16位

  // // 输出 0
  // std::cout << (65536 << 16) << std::endl;
  // // 输出 4294967296
  // std::cout << (65536LL << 16) << std::endl;

  // 2, numeric_limits
  // std::cout << "long long: " << std::numeric_limits<long long>::max() << ", "
  //           << std::numeric_limits<long long>::min() << std::endl;

  // std::cout << "int64_t: " << std::numeric_limits<int64_t>::max() << ", "
  //           << std::numeric_limits<int64_t>::min() << std::endl;

  // std::cout << "long: " << std::numeric_limits<long>::max() << ", "
  //           << std::numeric_limits<long>::min() << std::endl;

  // 3, utf-8, utf-16, utf-32 (Unicode Transfer Format)
  // 3.1 字符
  char utf8c = u8'a';
  char16_t utf16c = u'a';
  char32_t utf32c = U'a';
  std::cout << utf8c << "\t" << utf16c << "\t" << utf32c << std::endl;

  char16_t utf16c_2 = u'好';
  char32_t utf32c_2 = U'好';
  std::cout << std::hex << utf16c_2 << "\t" << std::hex << utf32c_2
            << std::endl;

  char* abc_p = (char*)&utf16c_2;
  std::cout << std::hex << (int)abc_p[0] << "\t" << std::hex << (int)abc_p[1]
            << std::endl;

  // 3.2 字符串
  char utf8[] = u8"好";
  char16_t utf16[] = u"你好世界";
  char32_t utf32[] = U"你好世界";

  for (std::size_t i = 0u; i < sizeof(utf8); ++i) {
    std::cout << std::hex << (int)utf8[i] << "\t";
  }
  std::cout << std::endl;

  for (std::size_t i = 0u; i < sizeof(utf16) / sizeof(char16_t); ++i) {
    // std::cout << std::hex << (int)utf16[i] << "\t";
    std::cout << utf16[i] << "\t";
    // std::printf("%c\t", utf16[i]);
  }
  std::cout << std::endl;

  return 0;
}
