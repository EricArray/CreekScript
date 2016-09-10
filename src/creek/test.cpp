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
#include <creek/Interpreter.hpp>
#include <creek/Scope.hpp>


int main(int argc, char** argv)
{
    using namespace creek;

    // interpreter
    Interpreter interpreter;

    // create program
    std::unique_ptr<Expression> program;
    try
    {
        program.reset(interpreter.load_file("test.txt"));
    }
    catch (const SyntaxError& e)
    {
        std::cerr << "Exception throw while loading:\n";
        std::cerr << "\t`" << e.token().text() << "` (" << InterpreterToken::type_names.at(e.token().type()) << ")\n";
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

    // create global scope
    Scope scope;

    // try to execute the program
    try
    {
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
