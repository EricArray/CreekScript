#pragma once

#include <map>
#include <regex>
#include <set>
#include <string>

#include <creek/api_mode.hpp>
#include <creek/Bytecode.hpp>
#include <creek/VarNameMap.hpp>


namespace creek
{
    class Expression;


    /// Bytecode interpreter.
    class CREEK_API BytecodeInterpreter
    {
    public:
        /// @brief  Bytecode header.
        static const std::string magic_number;


        /// @brief  `Interpreter` constructor.
        BytecodeInterpreter();


        /// @brief  Compile to bytecode file.
        /// @param  path        Path to the bytecode file.
        /// @param  program     Expression to save.
        void save_file(const std::string& path, const Expression* program);

        /// @brief  Interpret a bytecode file.
        /// @param  path        Path to the bytecode file.
        Expression* load_file(const std::string& path);

        /// @brief  Interpret a bytecode.
        /// @param  bytecode    Bytecode.
        Expression* load_bytecode(Bytecode& bytecode);


    private:
        Bytecode load(const std::string& path);
        Expression* parse(Bytecode& bytecode);
        Expression* parse_expression(Bytecode& bytecode, const VarNameMap& var_name_map);
        VarName parse_var_name(Bytecode& bytecode, const VarNameMap& var_name_map);
    };


    class InvalidBytecode : Exception
    {
    public:
        InvalidBytecode();
    };
}
