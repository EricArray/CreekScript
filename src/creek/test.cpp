#include <iostream>

#include <creek/Exception.hpp>
#include <creek/Expression.hpp>
#include <creek/Expression_Arithmetic.hpp>
#include <creek/Expression_BasicDataTypes.hpp>
#include <creek/Expression_Bitwise.hpp>
#include <creek/Expression_Boolean.hpp>
#include <creek/Expression_ControlFlow.hpp>
#include <creek/Expression_Debug.hpp>
#include <creek/Expression_Variable.hpp>
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
        new ExprPrint(new ExprIdentifier(VarName::from_name("x"))),
        new ExprPrint(new ExprVector()),
        
        new ExprPrint(new ExprString("Test bitwise")),
        new ExprPrint(new ExprNumber(0xFF00)),
        new ExprPrint(new ExprBitAnd(new ExprNumber(0xFF00), new ExprNumber(0x0FF0))),
        new ExprPrint(new ExprBitOr(new ExprBitAnd(new ExprNumber(0xFF00), new ExprNumber(0x0FF0)), new ExprNumber(0x000F))),

        new ExprPrint(new ExprString("Test boolean")),
        new ExprPrint(new ExprBoolAnd(new ExprBoolean(true), new ExprBoolean(false))),
        new ExprPrint(new ExprBoolAnd(new ExprNumber(12), new ExprNumber(-12))),
        new ExprPrint(new ExprBoolAnd(new ExprNumber(-12), new ExprNumber(12))),
        new ExprPrint(new ExprBoolOr(new ExprNumber(34), new ExprBoolean(false))),
    }));


    // create global scope
    Scope scope;


    // try to execute the program
    try
    {
        std::cout << "Running program:\n\n";

        Variable result;

        result = (program->eval(scope));

        // print returned value
        std::cout << "\nProgram returned " << result->debug_text() << ".\n";
    }
    catch(Exception& e)
    {
        std::cerr << "Creek exception: " << e.message() << ".\n";
    }
    catch(...)
    {
        std::cerr << "Unknown exception.\n";
    }


    return 0;
}
