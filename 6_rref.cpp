#include <cstring>
#include <iostream>
#include <string>

class BigMemoryPool {
 public:
  static const int PoolSize = 4096;
  BigMemoryPool() : pool_(new char[PoolSize]) {
    std::cout << "默认构造函数" << std::endl;
  }

  ~BigMemoryPool() {
    // std::cout << "析构函数" << std::endl;
    if (nullptr != pool_) {
      delete[] pool_;
    }
  }

  BigMemoryPool(const BigMemoryPool& other) : pool_(new char[PoolSize]) {
    std::cout << "复制构造函数" << std::endl;
    if (nullptr != other.pool_) {
      memcpy(pool_, other.pool_, PoolSize);
    }
  }

  BigMemoryPool(BigMemoryPool&& other) {
    std::cout << "移动构造函数" << std::endl;
    pool_ = other.pool_;
    other.pool_ = nullptr;
  }

  BigMemoryPool& operator=(const BigMemoryPool& other) {
    std::cout << "赋值运算符" << std::endl;
    if (nullptr != other.pool_) {
      memcpy(pool_, other.pool_, PoolSize);
    }
    return *this;
  }

  BigMemoryPool& operator=(BigMemoryPool&& other) {
    std::cout << "移动赋值运算符" << std::endl;
    if (nullptr != pool_) {
      delete[] pool_;
    }
    pool_ = other.pool_;
    other.pool_ = nullptr;
    return *this;
  }

 private:
  char* pool_;
};

BigMemoryPool get_pool(const BigMemoryPool& pool) {
  std::cout << "start get" << std::endl;
  // pool 不是右值，地址就是make_pool()里的局部变量的地址
  // 所以这里的return调用的是复制构造函数，而不是移动构造函数
  return pool;
}

BigMemoryPool make_pool() {
  std::cout << "start make" << std::endl;
  BigMemoryPool pool;
  // get_pool()返回的是个临时对象，所以是个右值
  // 此处的return调用的是移动构造函数
  return get_pool(pool);
}

void move_pool(BigMemoryPool&& pool) {
  std::cout << "move_pool: " << &pool << std::endl;
  // 形参永远为左值，所以这里调用的是复制构造函数
  // BigMemoryPool my_pool(pool);

  // 将左值转为右值，现在调用移动构造函数
  BigMemoryPool my_pool(std::move(pool));
}

void print_address(int&& a) {
  std::cout << "print_address: " << &a << std::endl;
}

void print_address_left(int& a) {
  std::cout << "print_address_left: " << &a << std::endl;
}

template <class T>
void show_type(T t) {
  std::cout << typeid(t).name() << std::endl;
}

template <class T>
void show_type_2(T&& t) {
  std::cout << typeid(t).name() << std::endl;
}

template <class T>
void perfect_forwarding(T&& t) {
  show_type(static_cast<T&&>(t));
  show_type(std::forward<T>(t));
  show_type_2(t);
  show_type(t);
  std::cout << std::endl;
}

std::string get_string() { return "Thanks for your fish!"; }

int main() {
  // 调用构造函数
  // BigMemoryPool my_pool = make_pool();

  // 先调用构造函数，再调用赋值操作符
  // BigMemoryPool my_pool;
  // my_pool = make_pool();

  // move_pool(make_pool());

  // 形参为右值引用，可取形参地址，所以它还是一个左值。
  // int a = 3;
  // int b = 3;

  // print_address(3);
  // print_address(4);
  // print_address(0);

  // std::cout << "address: " << &a << "," << &b << std::endl;
  // print_address_left(a);
  // print_address_left(b);
  // print_address(std::move(a));
  // print_address(std::move(b));
  // print_address(0);

  // 完美转发
  std::string s = "Thanks for your fish!";
  perfect_forwarding(s);
  perfect_forwarding(get_string());

  return 0;
}