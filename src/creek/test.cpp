#include <iostream>

#include <creek/Exception.hpp>
#include <creek/Expression.hpp>
#include <creek/Scope.hpp>


int main(int argc, char** argv)
{
    using namespace creek;


    // create program
    std::unique_ptr<Expression> program(new ExprBlock({
        new ExprPrint(new ExprString("Test program")),
        new ExprBlock({
            new ExprLocalVar(VarName::from_name("x"), new ExprNumber(5)),
            new ExprLocalVar(VarName::from_name("y"), new ExprNumber(10)),
            new ExprPrint(new ExprAdd(new ExprLoadVar(VarName::from_name("x")), new ExprLoadVar(VarName::from_name("y")))),
        }),
    }));


    // create global scope
    Scope scope;


    // try to execute the program
    try
    {
        Variable result;

        for (int i = 0; i < 100; ++i) result = (program->eval(scope));

        // print returned value
        std::cout << "Program returned " << result->debug_text() << ".\n";
    }
    catch(Exception& e)
    {
        std::cerr << "Creek exception: " << e.message() << ".\n";
    }
    catch(...)
    {
        std::cerr << "Unknown excpetion.\n";
    }


    return 0;
}
