#include <iostream>
#include <fstream>
#include <string>

#include <creek/BytecodeInterpreter.hpp>
#include <creek/CFunction.hpp>
#include <creek/Expression.hpp>
#include <creek/Expression_ControlFlow.hpp>
#include <creek/Expression_DataTypes.hpp>
#include <creek/Interpreter.hpp>
#include <creek/Scope.hpp>
#include <creek/StandardLibrary.hpp>
#include <creek/VarName.hpp>
#include <creek/Version.hpp>
using namespace creek;


bool quit = false;

void func_quit()
{
    quit = true;
}


// show help
void show_usage(char* path);

// show version
void show_version(char* path);

// interpret source file
Expression* load_source_file(const std::string& path);

// interpret bytecode file
Expression* load_bytecode_file(const std::string& path);

// compile to bytecode file
void save_bytecode_file(const std::string& path, const Expression* program);

// execute interpreted program
void exec_program(Expression* program, Scope& scope);

// execute interactive
void exec_interactive(bool const_optimize, Scope& scope);


// main function
int main(int argc, char** argv)
{
    const char* output_path = nullptr;
    std::vector<const char*> input_paths;
    bool const_optimize = false;
    bool interactive = false;


    // parse command
    for (int i = 1; i < argc; i += 1)
    {
        // help
        if (strcmp(argv[i], "-h") == 0)
        {
            show_usage(argv[i]);
            return 0;
        }
        // version
        else if (strcmp(argv[i], "-v") == 0)
        {
            show_version(argv[i]);
            return 0;
        }
        // const optimize
        else if (strcmp(argv[i], "-c") == 0)
        {
            const_optimize = true;
        }
        // set output file
        else if (strcmp(argv[i], "-o") == 0)
        {
            i += 1;
            if (i >= argc)
            {
                show_usage(argv[0]);
                return -1;
            }
            if (output_path)
            {
                show_usage(argv[0]);
                return -1;
            }
            output_path = argv[i];
        }
        // interactive mode
        else if (strcmp(argv[i], "-i") == 0)
        {
            interactive = true;
        }
        // add input file
        else
        {
            input_paths.push_back(argv[i]);
        }
    }


    // decide what to do
    interactive = interactive || input_paths.size() == 0;

    Scope scope;
    if (!output_path || interactive)
    {
        load_standard_library(scope);
    }

    // input
    std::vector<Expression*> input_programs;
    for (auto& input_path : input_paths)
    {
        std::ifstream file(input_path, std::ios_base::binary);
        if (file.fail())
        {
            std::cerr << "Can't open input file " << input_path << ".\n";
            return -1;
        }

        // check magic number
        char magic[256];
        file.read(magic, BytecodeInterpreter::magic_number.size());
        if (strncmp(magic, BytecodeInterpreter::magic_number.c_str(), BytecodeInterpreter::magic_number.size()) == 0)
        {
            input_programs.emplace_back(load_bytecode_file(input_path));
        }
        else
        {
            input_programs.emplace_back(load_source_file(input_path));
        }
    }

    // program
    if (input_programs.size() > 0)
    {
        // input
        std::unique_ptr<Expression> program;
        if (input_programs.size() > 1)
        {
            std::vector<Expression*> do_exprs;
            for (auto& ip : input_programs)
            {
                do_exprs.push_back(new ExprDo(ip));
            }
            program.reset(new ExprBasicBlock(do_exprs));
        }
        else if (input_programs.size() == 1)
        {
            program.reset(input_programs.front());
        }
        else
        {
            program.reset(new ExprVoid());
        }

        // const_optimize
        if (const_optimize)
        {
            program.reset(program->const_optimize());
        }

        // output
        if (output_path)
        {
            save_bytecode_file(output_path, program.get());
        }
        else
        {
            exec_program(program.get(), scope);
        }
    }

    // interactive
    if (interactive)
    {
        exec_interactive(const_optimize, scope);
    }

    return 0;
}


// show help
void show_usage(char* path)
{
    std::cout << "usage: " << path << "  [options] [input files]\n";
    std::cout << "Available options:\n"
                 "    -h              Display usage.\n"
                 "    -v              Display version.\n"
                 "    -c              Optimize compile-time constants.\n"
                 "    -o <path>       Set output file.\n"
                 "    -i              Enter interactive mode after executing\n"
                 "                    input files.\n"
                 "If no input files where given, enter interactive mode.\n"
                 "If no output file is give, execute input.\n";
}

// show version
void show_version(char* path)
{
    std::cout << "Creek script interpreter linked v" << Version::linked().str() << ", loaded v" << Version::loaded().str() << "\n";
}


// interpret source file
Expression* load_source_file(const std::string& path)
{
    // interpreter
    Interpreter interpreter;

    // create program
    Expression* program = nullptr;
    try
    {
        program = interpreter.load_file(path);
    }
    catch (const LexicError& e)
    {
        std::cerr << "Exception thrown while scanning:\n";
        std::cerr << "\t" << e.line() << ":" << e.column() << "\n";
        std::cerr << "\t" << e.message() << "\n";
        return nullptr;
    }
    catch (const SyntaxError& e)
    {
        std::cerr << "Exception thrown while parsing:\n";
        std::cerr << "\t" << e.token().line() << ":" << e.token().column() << "\t `" << e.token().text() << "` (" << Token::type_names.at(e.token().type()) << ")\n";
        std::cerr << "\t" << e.message() << "\n";
        return nullptr;
    }
    catch (const Exception& e)
    {
        std::cerr << "Exception thrown while loading:\n";
        std::cerr << "\t" << e.message() << "\n";
        return nullptr;
    }
    catch (const std::exception& e)
    {
        std::cerr << "C++ exception thrown while loading:\n";
        std::cerr << "\t" << e.what() << "\n";
        return nullptr;
    }
    catch (...)
    {
        std::cerr << "Unknown exception thrown while loading.\n";
        return nullptr;
    }

    return program;
}


// interpret bytecode file
Expression* load_bytecode_file(const std::string& path)
{
    // interpreter
    BytecodeInterpreter bi;

    // create program
    Expression* program = nullptr;
    try
    {
        program = bi.load_file(path);
    }
    catch (const Exception& e)
    {
        std::cerr << "Exception thrown while loading:\n";
        std::cerr << "\t" << e.message() << "\n";
        return nullptr;
    }
    catch (const std::exception& e)
    {
        std::cerr << "C++ exception thrown while loading:\n";
        std::cerr << "\t" << e.what() << "\n";
        return nullptr;
    }
    catch (...)
    {
        std::cerr << "Unknown exception thrown while loading.\n";
        return nullptr;
    }

    return program;
}


// compile to bytecode file
void save_bytecode_file(const std::string& path, const Expression* program)
{
    BytecodeInterpreter bi;
    bi.save_file(path, program);
}


// execute interpreted program
void exec_program(Expression* program, Scope& scope)
{
    // try to execute the program
    try
    {
        // std::cout << "Running program:\n";
        Variable result = program->eval(scope);

        std::cout << "Program returned " << result->debug_text() << ".\n";
    }
    catch(const Exception& e)
    {
        std::cerr << "Uncaught exception: " << e.message() << ".\n";
    }
    catch(const std::exception& e)
    {
        std::cerr << "Uncaught C++ exception: " << e.what() << ".\n";
    }
    catch(...)
    {
        std::cerr << "Unknown exception.\n";
    }
}


// execute interactive
void exec_interactive(bool const_optimize, Scope& scope)
{
    scope.create_local_var(VarName("quit"), new CFunction(scope, &func_quit));

    while (!quit)
    {
        try
        {
            std::cout << ">>> ";

            std::string input;
            std::getline(std::cin, input);

            if (input.size() == 0)
            {
                continue;
            }

            std::unique_ptr<Expression> program;
            while (!program.get())
            {
                try
                {
                    Interpreter interpreter;
                    program.reset(interpreter.load_code(input));

                    if (const_optimize)
                    {
                        program.reset(program->const_optimize());
                    }
                }
                catch (const SyntaxError& e)
                {
                    if (e.token().type() == TokenType::eof)
                    {
                        std::cout << "... ";

                        std::string append;
                        std::getline(std::cin, append);

                        input += "\n";
                        input += append;
                    }
                    else
                    {
                        throw e;
                    }
                }
            }

            Variable result = program->eval(scope);
            std::cout << " -> " << result->debug_text() << "\n";
        }
        catch (const LexicError& e)
        {
            std::cerr << "    " << std::string(e.column() - 1, ' ') << "^\n";
            std::cerr << "\t" << e.line() << ":" << e.column() << "\n";
            std::cerr << "\t" << e.message() << "\n";
        }
        catch (const SyntaxError& e)
        {
            std::cerr << "    " << std::string(e.token().column() - 1, ' ') << std::string(e.token().text().size(), '^') << "\n";
            std::cerr << "\t" << e.token().line() << ":" << e.token().column() << "\t `" << e.token().text() << "` (" << Token::type_names.at(e.token().type()) << ")\n";
            std::cerr << "\t" << e.message() << "\n";
        }
        catch (const Exception& e)
        {
            std::cout << "Uncaught exception: " << e.message() << "\n";
        }
        catch (const std::exception& e)
        {
            std::cout << "Uncaught C++ exception: " << e.what() << "\n";
        }
    }
}
