#pragma once

#include <creek/Exception.hpp>


namespace creek
{
    class Scope;
    class Variable;


    /// Expression statement in a program.
    class Expression
    {
    public:
        virtual ~Expression() = default;

        /// Evaluate this expression.
        /// @return Result of the expression; may be `nullptr`.
        virtual Variable eval(Scope& scope) = 0;
    };


    /// Exception raised during runtime.
    class RuntimeError : public Exception
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
    class BadArgument : public RuntimeError
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
