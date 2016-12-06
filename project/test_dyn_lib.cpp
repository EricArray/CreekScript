#include <creek/DynLibrary.hpp>

#include <iostream>

//// Dynamic class.
//class MyClass
//{
//public:
//    MyClass(int x) : x(x) { std::cout << "MyClass constructor: x = " << x << "\n"; }
//    MyClass(const MyClass& other) : x(other.x) { std::cout << "MyClass copy constructor: x = " << x << "\n"; }
//    MyClass(MyClass&& other) : x(other.x) { other.x = -1; std::cout << "MyClass move constructor: x = " << x << "\n"; }
//    ~MyClass() { std::cout << "MyClass destructor: x = " << x << "\n"; }
//    static MyClass create(int x);
//    void info();
//    void reset(const MyClass& other);
//
//private:
//    int x = 0;
//};
//
//MyClass MyClass::create(int x)  {
//    return MyClass(x);
//}
//
//void MyClass::info() {
//    std::cout << "INFO: this = " << this << "; x = " << x << ";\n";
//}
//
//void MyClass::reset(const MyClass& other) {
//    std::cout << "RESET: this = " << this << "; x = " << x << "; other = " << &other << "; x = " << other.x << "\n";
//    x = other.x;
//}
//
//CREEK_CLASS(MyClass, MyClass)
//(
//    CREEK_CLASS_METHOD(new,             &MyClass::create),
//    CREEK_CLASS_METHOD(info,            &MyClass::info),
//    CREEK_CLASS_METHOD(reset,           &MyClass::reset)
//);
//

void test(const char* text) {
    std::cout << text << "\n";
}

CREEK_FUNC(test, &test);
