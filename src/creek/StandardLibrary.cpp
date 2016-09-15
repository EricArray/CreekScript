#include <creek/StandardLibrary.hpp>

#include <iostream>

#include <creek/CFunction.hpp>
#include <creek/Scope.hpp>
#include <creek/Void.hpp>


namespace creek
{
    Data* func_print(std::vector< std::unique_ptr<Data> >& args)
    {
        for (auto& arg : args[0]->vector_value())
        {
            std::cout << arg->string_value();
        }

        return new Void();
    }


    Data* func_debug(std::vector< std::unique_ptr<Data> >& args)
    {
        for (auto& arg : args[0]->vector_value())
        {
            std::cout << arg->debug_text();
        }

        return new Void();
    }


    // Load standard library.
    // @param  scope   Scope where standard variables are created.
    void load_standard_library(Scope& scope)
    {
        scope.create_local_var(VarName::from_name("print"), new CFunction(1, true, &func_print));
        scope.create_local_var(VarName::from_name("debug"), new CFunction(1, true, &func_debug));
        scope.create_local_var(VarName::from_name("exit"), new CFunction(&exit));
    }
}
