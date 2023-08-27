#include <iostream>
#include <string>
template <typename T1, typename T2>
auto sum(T1 t1, T2 t2) -> decltype(t1 + t2) {
  return t1 + t2;
};

int main() {
  std::cout << sum(1, 3.5) << std::endl;
  return 0;
}