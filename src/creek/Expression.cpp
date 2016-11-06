#include <creek/Expression.hpp>


namespace creek
{
    /// @brief  Is this expression constant?
    /// By default returns false.
    bool Expression::is_const() const
    {
        return false;
    }

    /// @brief  Get an equivalent, optimized expression from this.
    /// By default, returns a copy of this.
    Expression* Expression::const_optimize() const
    {
        return clone();
    }


    // `RuntimeError` constructor.
    // @param  expr    Expression associated with the error.
    RuntimeError::RuntimeError(const Expression* expr) : m_expr(expr)
    {
        stream() << "Runtime error: ";
    }

    // Get the expression.
    const Expression* RuntimeError::expr() const
    {
        return m_expr;
    }


    // `BadArgument` constructor.
    // @param  expr        Expression associated with the error.
    // @param  arg_name    Name of the argument.
    BadArgument::BadArgument(const Expression* expr, const std::string& arg_name) :
        RuntimeError(expr),
        m_arg_name(arg_name)
    {
        stream() << "Bad argument " << arg_name << " in function call";
    }

    // Get argument name.
    const std::string& BadArgument::arg_name() const
    {
        return m_arg_name;
    }
}
