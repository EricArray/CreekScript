#pragma once

#include <creek/api_mode.hpp>
#include <creek/Bytecode.hpp>
#include <creek/Exception.hpp>
#include <creek/OpCode.hpp>
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

        /// @brief  Evaluate this expression.
        /// @return Result of the expression; may be `nullptr`.
        virtual Variable eval(Scope& scope) = 0;

        /// @brief  Get an equivalent constant expression from this.
        /// @return If can convert to const at compile time, return a new
        ///         expression pointer, else, return `nullptr`. Can return
        ///         `this`, so check before deleting.
        /// By default, returns `nullptr`.
        virtual Expression* to_const() const;

        /// @brief  Get the bytecode of this expression.
        virtual Bytecode bytecode(VarNameMap& var_name_map) const = 0;
    };


    /// Exception raised during runtime.
    class CREEK_API RuntimeError : public Exception
    {
    public:
        /// `RuntimeError` constructor.
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
        /// `BadArgument` constructor.
        /// @param  expr        Expression associated with the error.
        /// @param  arg_name    Name of the argument.
        BadArgument(const Expression* expr, const std::string& arg_name);

        /// Get argument name.
        const std::string& arg_name() const;

    private:
        std::string m_arg_name;
    };
}
