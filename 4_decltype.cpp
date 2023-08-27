#include <iostream>
#include <string>

class Apple {
  std::string name;
  double weight;
  int color;
};

template <typename T1, typename T2>
auto sum(T1 a1, T2 a2) -> decltype(a1 + a2) {
  return (a1 + a2);
}

int main() {
  // typeid
  int x1 = 0;
  double x2 = 5.5;
  Apple apple;
  int arr[10];

  decltype(arr) arr2;
  decltype(sum<int, double>) sum_2;
  decltype(&sum<int, double>) sum_3 = &sum<int, double>;
  decltype(auto) sum_4 = &sum<int, double>;
  auto sum_5 = &sum<int, double>;

  std::cout << typeid(x1).name() << std::endl;     // i
  std::cout << typeid(x2).name() << std::endl;     // d
  std::cout << typeid(apple).name() << std::endl;  // 5Apple0
  std::cout << typeid(arr).name() << std::endl;    // A10_i
  std::cout << typeid(arr2).name() << std::endl;  // A10_i, 不会退化成指针a
  std::cout << sum(1, 2.7) << std::endl;
  std::cout << typeid(sum_2).name() << std::endl;
  std::cout << typeid(sum_3).name() << std::endl;
  std::cout << typeid(sum_4).name() << std::endl;
  std::cout << typeid(sum_5).name() << std::endl;

  std::cout << (*sum_3)(1, 2.7) << std::endl;
}