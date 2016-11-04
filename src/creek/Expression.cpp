#include <creek/Expression.hpp>


namespace creek
{
    /// @brief  Get an equivalent constant expression from this.
    /// @return If can convert to const at compile time, return a new
    ///         expression pointer, else, return `nullptr`. Can return
    ///         `this`, so check before deleting.
    /// By default, returns `nullptr`.
    virtual Expression* Expression::to_const() const
    {
        return nullptr;
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
