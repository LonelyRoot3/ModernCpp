#include <iostream>
#include <string>

struct Point {
  int x;
  int y;
  int z;
};

int main() {
  int x = 999;
  const int y = 0;
  const int z = 99;
  char c1 = x;  // 无警告
  char c2{x};  // warning: narrowing conversion of ‘x’ from ‘int’ to ‘char’
  char c3{z};
  double d{x};  // narrowing conversion of ‘x’ from ‘int’ to ‘double’
  double d2{y};  // 无警告,因为0可以被精确表示

  std::cout << c1 << ", " << c2 << "," << c3 << "," << d << "," << d2
            << std::endl;

  Point p{.y = 3, .z = 2};

  std::cout << p.x << "," << p.y << "," << p.z << std::endl;

  return 0;
}