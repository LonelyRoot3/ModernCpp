#include <iostream>
#include <string>

class Base {
 public:
  virtual void f() { std::cout << "Base::f()" << std::endl; }
};

class Derived : public Base {
 public:
  void f() override { std::cout << "Derived::f()" << std::endl; }
};

template <auto N>
void f() {
  std::cout << N << std::endl;
}

int main() {
  auto i{5};
  auto i2 = {5};  // 被推导为std::initializer_list <int>
  // auto j{5, 6};  // 编译不过
  auto k = {5, 6};  // 被推导为std::initializer_list <int>
  // auto k2 = {5, 6.0};  // 编译不过，初始化列表里的成员类型不一致，无法推导
  std::cout << i << *i2.begin() << std::endl;
  std::cout << *k.begin() << std::endl;

  Base* d = new Derived();
  auto b1 = *d;
  b1.f();  // Base::f()

  auto b2 = d;
  b2->f();  // Derived::f()

  auto& b3 = *d;
  b3.f();  // Derived::f()

  // auto 形参的lambda表达式
  // 这不比模板好用？！
  auto Add = [](auto a1, auto a2) { return a1 + a2; };
  auto ret_value = Add(5, 5.0);
  std::cout << ret_value << std::endl;

  // auto 用作非类型模板形参
  f<5>();
  // f<5.0>(); // 非类型模板形参必须是整型
}