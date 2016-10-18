#include <iostream>
#include <string>

#include <creek/CFunction.hpp>
#include <creek/Expression.hpp>
#include <creek/Interpreter.hpp>
#include <creek/Scope.hpp>
#include <creek/StandardLibrary.hpp>
#include <creek/VarName.hpp>


bool quit = false;

void func_quit()
{
    quit = true;
}


int main(int argc, char** argv)
{
    creek::Scope scope;

    creek::load_standard_library(scope);

    scope.create_local_var(creek::VarName("quit"), new creek::CFunction(scope, &func_quit));


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

            std::unique_ptr<creek::Expression> program;
            while (!program.get())
            {
                try
                {
                    creek::Interpreter inter;
                    program.reset(inter.load_code(input));
                }
                catch (const creek::SyntaxError& e)
                {
                    if (e.token().type() == creek::TokenType::eof)
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

            creek::Variable result = program->eval(scope);
            std::cout << " -> " << result->debug_text() << "\n";
        }
        catch (const creek::LexicError& e)
        {
            std::cerr << "    " << std::string(e.column() - 1, ' ') << "^\n";
            std::cerr << "\t" << e.line() << ":" << e.column() << "\n";
            std::cerr << "\t" << e.message() << "\n";
        }
        catch (const creek::SyntaxError& e)
        {
            std::cerr << "    " << std::string(e.token().column() - 1, ' ') << std::string(e.token().text().size(), '^') << "\n";
            std::cerr << "\t" << e.token().line() << ":" << e.token().column() << "\t `" << e.token().text() << "` (" << creek::Token::type_names.at(e.token().type()) << ")\n";
            std::cerr << "\t" << e.message() << "\n";
        }
        catch (const creek::Exception& e)
        {
            std::cout << "Uncaught exception: " << e.message() << "\n";
        }
    }

    return 0;
}
