#include <iostream>
#include <fstream>

#include <creek/creek.hpp>
#include <creek/VarNameMap.hpp>
#include <creek/BytecodeInterpreter.hpp>
using namespace creek;


int main(int argc, char** argv)
{
    // interpreter
    Interpreter interpreter;

    // create program
    std::unique_ptr<Expression> program;
    try
    {
        program.reset(interpreter.load_file("test.creek"));

        {
            std::cout << "saving program\n";

            VarNameMap var_name_map;
            auto bytecode = program->bytecode(var_name_map);
            auto bytes = bytecode.bytes();

            std::ofstream file("test.creekb", std::ios_base::binary|std::ios_base::trunc);
            file.write(bytes.c_str(), bytes.size());
        }
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

    BytecodeInterpreter bi;
    bi.save_file("test.creek.b", program.get());

    program.reset(bi.load_file("test.creek.b"));

    // create base scope
    Scope base;

    // try to execute the program
    try
    {
        std::cout << "Loading standard library...\n";
        load_standard_library(base);

        std::cout << "Running program:\n";
        Variable result = program->eval(base);

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
