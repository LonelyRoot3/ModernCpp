#include <iostream>
#include <string>
#include <type_traits>

class Trivial {
 public:
  Trivial() = default;
  Trivial(int n) : i(n), j(n) {}
  // Trivial& operator=(const Trivial&) = delete;
  void Show() { std::cout << i << "," << j << std::endl; }

 private:
  int i, j;
};

int main() {
  Trivial a(5);
  Trivial b;
  // 自定义构造函数只会抑制默认构造函数的合成，不会抑制默认赋值操作符的合成
  b = a;
  b.Show();

  std::cout << "is_trivial: " << std::is_trivial<Trivial>::value << std::endl;
}