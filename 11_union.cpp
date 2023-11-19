#include <iostream>
#include <string>
#include <vector>

union U {
  int x1;
  float x2;
};

union U2 {
  U2() : x3() {}
  ~U2() { x3.~basic_string(); }
  int x1;
  float x2;
  std::string x3;
  std::vector<int> x4;
};

union U3 {
  U3() {}
  ~U3() {}
  int x1;
  float x2;
  std::string x3;
  std::vector<int> x4;
};

int main() {
  U u;
  u.x1 = 5;
  std::cout << u.x1 << ", " << u.x2 << std::endl;

  u.x2 = 5.0;
  std::cout << u.x1 << ", " << u.x2 << std::endl;

  std::cout << sizeof(u) << std::endl;

  U2 u2;
  std::cout << sizeof(u2) << std::endl;
  u2.x3 = "Hello, world!\n";
  std::cout << sizeof(u2) << std::endl;

  // u2.x4.push_back(5);
  U3 u3;
  // placement new, 指定内存地址 + 构造函数
  new (&u3.x3) std::string("Hello, world!");  // 自己构造
  std::cout << u3.x3 << std::endl;
  std::cout << u3.x1 << std::endl;
  u3.x3.~basic_string();  // 自己析构

  new (&u3.x4) std::vector<int>;
  u3.x4.push_back(5);
  std::cout << u3.x4[0] << std::endl;
  u3.x4.~vector();
  return 0;
}