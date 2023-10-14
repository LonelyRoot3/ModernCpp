#include <future>
#include <iostream>
#include <string>
int g_x = 10;

// 定义在全局作用域的lambda表达式，其捕获列表必定为空
auto g_foo = [] { return 100 * g_x; };
class Work {
 private:
  int value;

 public:
  Work() : value(42) {}
  std::future<int> spawn() {
    return std::async([*this]() -> int { return value; });
  }
};

int main() {
  static int s_y = 7;
  int x = 5;
  auto foo = [x](int y) -> int { return x * y; };
  std::cout << foo(8) << std::endl;

  // 7.2.1
  // 全局变量和静态局部变量都不能被捕获，但可以直接使用
  // capture of variable ‘g_x’ with non-automatic storage duration
  // capture of variable ‘s_y’ with non-automatic storage duration
  // auto foo_2 = [g_x, s_y, x] { return g_x + s_y + x; };
  auto foo_3 = [x] { return g_x + s_y + x; };
  std::cout << foo_3() << std::endl;

  // 7.2.2 捕获值与捕获引用
  // 结论：捕获值的时候，由于是值传递，所以程序会自动为捕获值的变脸开辟内存空间。
  // 但是空间的开辟和赋初始值都是在捕获的时候(也就是lambda定义的时候)发生，而不是调用的时候。
  // 不管lambda表达式调用多少次，捕获值的变量在lambda里的内存地址都不会变。
  // 所以如果第一次调用lambda时修改了它的值，那么第二次调用lambda的时候这个被修改的值能被看到（因为地址没变）。
  // 所以能获得一种近似静态局部变量的效果。当然，lambda中默认是不能修改捕获值的，所以要加mutable.
  int y = 8;
  // (1) lambda是个常量函数，即不能修改捕获的值
  // auto foo_4 = [x, y] {
  //   x++;  // error: increment of read-only variable ‘x’
  //   y++;  // error: increment of read-only variable ‘y’
  //   return x * y;
  // };
  // std::cout << foo_4() << std::endl;

  // (2)
  // 使用mutable描述符可以让我们在lambda函数体内修改捕获的值，但是在函数体外这个值依然不变
  // lambda执行前: x = 5, y = 8
  // lambda函数中: x = 6, y = 9
  // lambda执行后: x = 5, y = 8
  // lambda函数中: x = 7, y = 10
  // lambda第二次执行后: x = 5, y = 8
  std::cout << "main函数中 地址: &x = " << &x << ", &y = " << &y << std::endl;
  auto foo_5 = [x, y]() mutable {
    x++;
    y++;
    // lambda函数体内，值持续增加就像是一个静态局部变量
    std::cout << "lambda函数中: x = " << x << ", y = " << y << std::endl;
    std::cout << "lambda函数中 地址: &x = " << &x << ", &y = " << &y
              << std::endl;
    return x * y;
  };
  std::cout << "lambda执行前: x = " << x << ", y = " << y << std::endl;
  foo_5();
  // std::cout << "lambda返回值: " << foo_5() << std::endl;
  std::cout << "lambda执行后: x = " << x << ", y = " << y << std::endl;

  // 再次执行
  foo_5();
  std::cout << "lambda第二次执行后: x = " << x << ", y = " << y << std::endl;

  // 在main函数中修改 x，y
  x = 99;
  y = 99;
  std::cout << "lambda第三次执行前, main中: x = " << x << ", y = " << y
            << std::endl;
  // 第三次次执行
  foo_5();
  std::cout << "lambda第三次执行后: x = " << x << ", y = " << y << std::endl;

  // (3) 捕获引用，随便修改
  // y是捕获引用，所以地址与main中的y一致
  // x是捕获值，所以地址不一致
  auto foo_6 = [x, &y]() mutable {
    x++;
    y++;
    std::cout << "foo_6 lambda函数中: x = " << x << ", y = " << y << std::endl;
    std::cout << "foo_6 lambda函数中 地址: &x = " << &x << ", &y = " << &y
              << std::endl;
    return x * y;
  };
  foo_6();
  std::cout << "foo_6执行后: x = " << x << ", y = " << y << std::endl;

  y = 108;
  foo_6();
  std::cout << "foo_6第二次执行后: x = " << x << ", y = " << y << std::endl;

  // 7.7 泛型lambda表达式，用auto实现
  auto foo_7 = [](auto a1, auto a2) { return a1 + a2; };
  std::cout << "foo_7: " << foo_7(5, 3.2) << std::endl;

  // 7.8 this

  return 0;
}