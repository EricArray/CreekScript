#include <creek/DynLibrary.hpp>

#include <iostream>



// Dynamic function.
void my_print(std::string output)
{
    std::cout << "CALLING my_print: " << output << "\n";
}

CREEK_FUNC(my_print, &my_print);



// Dynamic class.
class MyClass
{
public:
    MyClass(int x) : x(x) { std::cout << "MyClass constructor: x = " << x << "\n"; }
    MyClass(const MyClass& other) : x(other.x) { std::cout << "MyClass copy constructor: x = " << x << "\n"; }
    MyClass(MyClass&& other) : x(other.x) { other.x = -1; std::cout << "MyClass move constructor: x = " << x << "\n"; }
    ~MyClass() { std::cout << "MyClass destructor: x = " << x << "\n"; }
    static MyClass create(int x);
    void info();

private:
    int x = 0;
};

MyClass MyClass::create(int x)  {
    return MyClass(x);
}

void MyClass::info() {
    std::cout << "INFO: this = " << this << "; x = " << x << ";\n";
}

CREEK_CLASS(MyClass, MyClass)
{
    CREEK_CLASS_METHOD(new,             &MyClass::create),
    CREEK_CLASS_METHOD(info,            &MyClass::info),
};


creek::Data* inspect_ud(creek::Scope& scope, std::vector< std::unique_ptr<creek::Data> >& args) {
    auto ud = args[0]->assert_cast< creek::UserData<MyClass*> >();
    std::cout <<
        "Inspecting:\n" <<
        "\t" << ud << "\n" <<
        "\t" << ud->debug_text() << "\n" <<
        "\t" << &ud->reference() << "\n";
    return new creek::Void();
}

CREEK_FUNC_X(inspect_ud, 1, false, inspect_ud);
