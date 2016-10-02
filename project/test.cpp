#include <iostream>

#include <creek/creek.hpp>
using namespace creek;


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

    // create global scope
    Scope global;

    // try to execute the program
    try
    {
        std::cout << "Loading standard library...\n";
        load_standard_library(global);

        std::cout << "Running program:\n\n";
        Variable result = program->eval(global);

        std::cout << "\nProgram returned " << result->debug_text() << ".\n";
    }
    catch(const Exception& e)
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
