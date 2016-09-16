#pragma once

#include <creek/Expression.hpp>

#include <memory>

#include <creek/api_mode.hpp>


namespace creek
{
    /// @defgroup   expression_boolean  Boolean operations
    /// @{

    /// Expression: Short circuit boolean AND.
    /// If L is false, returns L, else, returns R.
    class CREEK_API ExprBoolAnd : public Expression
    {
    public:
        /// `ExprBoolAnd` constructor.
        /// @param  lexpr       Expression for left parameter.
        /// @param  rexpr       Expression for right parameter.
        ExprBoolAnd(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };


    /// Expression: Short circuit boolean OR.
    /// If L is true, returns L, else, returns R.
    class CREEK_API ExprBoolOr : public Expression
    {
    public:
        /// `ExprBoolOr` constructor.
        /// @param  lexpr       Expression for left parameter.
        /// @param  rexpr       Expression for right parameter.
        ExprBoolOr(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };


    /// Expression: Boolean XOR.
    /// Creates a new Boolean data.
    /// Returns L XOR R.
    class CREEK_API ExprBoolXor : public Expression
    {
    public:
        /// `ExprBoolXor` constructor.
        /// @param  lexpr       Expression for left parameter.
        /// @param  rexpr       Expression for right parameter.
        ExprBoolXor(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };


    /// Expression: Boolean NOT.
    /// Returns NOT L.
    class CREEK_API ExprBoolNot : public Expression
    {
    public:
        /// `ExprBoolNot` constructor.
        /// @param  expr        Expression to negate.
        ExprBoolNot(Expression* expr);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_expr;
    };

    /// @}
}
