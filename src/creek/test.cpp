#include <iostream>

#include <creek/Exception.hpp>
#include <creek/Expression.hpp>
#include <creek/Expression_Arithmetic.hpp>
#include <creek/Expression_Bitwise.hpp>
#include <creek/Expression_Boolean.hpp>
#include <creek/Expression_ControlFlow.hpp>
#include <creek/Expression_DataTypes.hpp>
#include <creek/Expression_Debug.hpp>
#include <creek/Expression_Variable.hpp>
#include <creek/Interpreter.hpp>
#include <creek/Resolver.hpp>
#include <creek/Scope.hpp>
#include <creek/StandardLibrary.hpp>
using namespace creek;


template<class T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& vec)
{
    os << "{";
    int i = 0;
    for (auto& item : vec)
    {
        if (i > 0) os << ", ";
        os << item;
        i += 1;
    }
    os << "}";
    return os;
}

template<class T>
std::ostream& operator << (std::ostream& os, const std::function<T>& f)
{
    os << "?(*)(?)";
    return os;
}

#define test_v2d(T, V) \
{ \
    T v = (V); \
    std::unique_ptr<Data> d(Resolver::value_to_data<T>(v)); \
    std::cout << "value_to_data<" #T ">(" << v << ")\t=> " << d->debug_text() << "\n"; \
}

#define test_d2v(T, D) \
{ \
    Data* d = (D); \
    T v = Resolver::data_to_value<T>(d); \
    std::cout << "data_to_value<" #T ">(" << d->debug_text() << ")\t=> " << v << "\n"; \
}

void print(std::string str)
{
    std::cout << str;
}

std::string scan()
{
    std::string str;
    std::getline(std::cin, str);
    return str;
}

int main2()
{
    std::cout << std::boolalpha;

    test_v2d(bool, true);
    test_v2d(char, 'Z');
    test_v2d(int, 11);
    test_v2d(float, 3.1415f);
    test_v2d(std::string, "hola mundo");
    std::vector<int> vec = {0,1,2,3};
    test_v2d(std::vector<int>, vec);

    std::cout << std::endl;

    test_d2v(bool, new Boolean(true));
    test_d2v(char, new String("foo"));
    test_d2v(int, new Number(11));
    test_d2v(float, new Number(3.1415));
    test_d2v(std::string, new String("bar baz"));

    std::cout << std::endl;

    {
        std::cout << "running function" << std::endl;
//        Data* f = new CFunction(std::function<void(std::string)>(&print));
        Variable f = new CFunction(&print);
        std::vector<std::unique_ptr<Data>> args;
        args.emplace_back(new String("hola\n"));
        Variable r = f->call(args);
        std::cout << "returned " << r->debug_text() << "\n";
    }

    std::cout << std::endl;

    {
        std::cout << "running function" << std::endl;
        Variable f = new CFunction(&scan);
        std::vector<std::unique_ptr<Data>> args;
        Variable r = f->call(args);
        std::cout << "returned " << r->debug_text() << "\n";
    }

    return 0;
}


int main(int argc, char** argv)
{
    // interpreter
    Interpreter interpreter;

    // create program
    std::unique_ptr<Expression> program;
    try
    {
        program.reset(interpreter.load_file("test.txt"));
    }
    catch (const LexicError& e)
    {
        std::cerr << "Exception throw while scanning:\n";
        std::cerr << "\t" << e.line() << ":" << e.column() << "\n";
        std::cerr << "\t" << e.message() << "\n";
        return -1;
    }
    catch (const SyntaxError& e)
    {
        std::cerr << "Exception throw while parsing:\n";
        std::cerr << "\t" << e.token().line() << ":" << e.token().column() << "\t `" << e.token().text() << "` (" << Token::type_names.at(e.token().type()) << ")\n";
        std::cerr << "\t" << e.message() << "\n";
        return -1;
    }
    catch (const Exception& e)
    {
        std::cerr << "Exception throw while loading:\n";
        std::cerr << "\t" << e.message() << "\n";
        return -1;
    }
    catch (...)
    {
        std::cerr << "Unknown exception throw while loading\n";
        return -1;
    }
    std::cout << std::endl;

    // create global scope
    Scope scope;

    // try to execute the program
    try
    {
        std::cout << "Loading standard library...\n";
        load_standard_library(scope);

        std::cout << "Running program:\n\n";
        Variable result = program->eval(scope);

        std::cout << "\nProgram returned " << result->debug_text() << ".\n";
    }
    catch(Exception& e)
    {
        std::cerr << "Creek exception: " << e.message() << ".\n";
        return -1;
    }
    catch(...)
    {
        std::cerr << "Unknown exception.\n";
        return -1;
    }

    return 0;
}
