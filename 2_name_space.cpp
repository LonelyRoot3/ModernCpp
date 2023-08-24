#include <iostream>
#include <string>

namespace Parent {
namespace Child1 {
void foo() { std::cout << "Child1::foo()" << std::endl; }
}  // namespace Child1

inline namespace Child2 {
void foo() { std::cout << "Child2::foo()" << std::endl; }
}  // namespace Child2
}  // namespace Parent

int main() {
  Parent::Child1::foo();
  Parent::foo();
  return 0;
}
