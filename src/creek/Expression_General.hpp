#pragma once

#include <creek/Expression.hpp>

#include <memory>
#include <vector>


namespace creek
{
    /// @defgroup   expression_general  General expressions.
    /// @{

    /// Expression: Call a function.
    /// Returns value returned by the function.
    class ExprCall : public Expression
    {
    public:
        /// `ExprCall` constructor.
        /// @param  function    Function expression.
        /// @param  args        Arguments to pass to the function.
        ExprCall(Expression* function, const std::vector<Expression*>& args);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_function;
        std::vector< std::unique_ptr<Expression> > m_args;
    };

    /// Expression: Get array subscript.
    /// Returns value of the array at the index.
    class ExprIndexGet : public Expression
    {
    public:
        /// `ExprIndexGet` constructor.
        /// @param  array   Expression for the array object.
        /// @param  index   Expression for the index.
        ExprIndexGet(Expression* array, Expression* index);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_array;
        std::unique_ptr<Expression> m_index;
    };

    /// Expression: Set array subscript.
    /// Returns new value of the array at the index.
    class ExprIndexSet : public Expression
    {
    public:
        /// `ExprIndexSet` constructor.
        /// @param  array       Expression for the array object.
        /// @param  index       Expression for the index.
        /// @param  value       Expression for the new value.
        ExprIndexSet(Expression* array, Expression* index, Expression* value);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_array;
        std::unique_ptr<Expression> m_index;
        std::unique_ptr<Expression> m_value;
    };

    /// @}
}
