#pragma once

#include <creek/api_mode.hpp>
#include <creek/Bytecode.hpp>
#include <creek/Exception.hpp>
#include <creek/OpCode.hpp>
#include <creek/Shared.hpp>
#include <creek/VarNameMap.hpp>


namespace creek
{
    class Scope;
    class Variable;


    /// Expression statement in a program.
    class CREEK_API Expression
    {
    public:
        virtual ~Expression() = default;


        /// @brief  Get a copy of this expression.
        virtual Expression* clone() const = 0;

        /// @brief  Can be evaluated at compile time?
        /// By default returns false.
        virtual bool is_const() const;

        /// @brief  Get an equivalent, optimized expression from this.
        /// By default returns a copy of this.
        virtual Expression* const_optimize() const;


        /// @brief  Evaluate this expression.
        /// @return Result of the expression; may be `nullptr`.
        virtual Variable eval(const SharedPointer<Scope>& scope) = 0;

        /// @brief  Get the bytecode of this expression.
        virtual Bytecode bytecode(VarNameMap& var_name_map) const = 0;
    };


    /// Exception raised during runtime.
    class CREEK_API RuntimeError : public Exception
    {
    public:
        /// @brief  `RuntimeError` constructor..
        /// @param  expr    Expression associated with the error.
        RuntimeError(const Expression* expr);

        /// Get the expression.
        const Expression* expr() const;

    private:
        const Expression* m_expr;
    };


    /// Bad argument in a function call.
    class CREEK_API BadArgument : public RuntimeError
    {
    public:
        /// @brief  `BadArgument` constructor..
        /// @param  expr        Expression associated with the error.
        /// @param  arg_name    Name of the argument.
        BadArgument(const Expression* expr, const std::string& arg_name);

        /// Get argument name.
        const std::string& arg_name() const;

    private:
        std::string m_arg_name;
    };
}
