#include <creek/StandardLibrary.hpp>

#include <iostream>
#include <fstream>

#include <creek/CFunction.hpp>
#include <creek/Expression.hpp>
#include <creek/Identifier.hpp>
#include <creek/Interpreter.hpp>
#include <creek/Number.hpp>
#include <creek/Object.hpp>
#include <creek/Scope.hpp>
#include <creek/Void.hpp>


namespace creek
{
    Data* func_print(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto& strings = args[0];
        for (auto& string : strings->vector_value())
        {
            std::cout << string->string_value();
        }
        return new Void();
    }


    Data* func_scan(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        delete func_print(scope, args);

        std::string input;
        std::getline(std::cin, input);
        return new String(input);
    }


    Data* func_debug(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto& values = args[0];
        for (auto& value : values->vector_value())
        {
            std::cout << "\t" << value->debug_text() << "\n";
        }
        return new Void();
    }


    Data* func_require(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        static const std::vector<std::string> path_templates
        {
            "./?.txt",
        };

        auto module_name = args[0]->string_value();


        // check path
        std::string path;
        bool found = false;
        for (auto& path_template : path_templates)
        {
            // resolve path template
            path = path_template;
            size_t pos = 0;
            while (true)
            {
                pos = path.find_first_of('?', pos);
                if (pos == std::string::npos)
                    break;
                path.replace(pos, 1, module_name);
            }

            // test file existence
            std::ifstream test_file(path);
            if (!test_file.fail())
            {
                found = true;
            }
        }

        if (!found)
        {
            throw Exception(std::string("Can't find module file ") + module_name);
        }


        // interpreter
        Interpreter interpreter;

        // create program
        std::unique_ptr<Expression> program;
        program.reset(interpreter.load_file(path));

        // run program
        Variable result = program->eval(scope);
        return result.release();
    }


    // Load standard library.
    // @param  scope   Scope where standard variables are created.
    void load_standard_library(Scope& scope)
    {
        // global functions
        scope.create_local_var(VarName::from_name("print"),     new CFunction(scope, 1, true, &func_print));
        scope.create_local_var(VarName::from_name("scan"),      new CFunction(scope, 1, true, &func_scan));
        scope.create_local_var(VarName::from_name("debug"),     new CFunction(scope, 1, true, &func_debug));
        scope.create_local_var(VarName::from_name("exit"),      new CFunction(scope, &exit));
        scope.create_local_var(VarName::from_name("require"),   new CFunction(scope, 1, false, &func_require));
    }
}
