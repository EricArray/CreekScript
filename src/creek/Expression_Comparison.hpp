#pragma once

#include <creek/Expression.hpp>

#include <memory>


namespace creek
{
    /// @defgroup   expression_comparison   Comparison opereations
    /// @{

    /// Expression: Compare two values.
    /// Returns -1 if less-than, 0 if equal and 1 if greater-than.
    /// Returns L <=> R.
    class ExprCmp : public Expression
    {
    public:
        /// `ExprCmp` constructor.
        /// @param  lexpr   Expression for left parameter.
        /// @param  rexpr   Expression for right parameter.
        ExprCmp(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };


    /// Expression: Equal to.
    /// Returns L == R.
    class ExprEQ : public Expression
    {
    public:
        /// `ExprEQ` constructor.
        /// @param  lexpr   Expression for left parameter.
        /// @param  rexpr   Expression for right parameter.
        ExprEQ(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };


    /// Expression: Not equal to.
    /// Returns L != R.
    class ExprNE : public Expression
    {
    public:
        /// `ExprNE` constructor.
        /// @param  lexpr   Expression for left parameter.
        /// @param  rexpr   Expression for right parameter.
        ExprNE(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };


    /// Expression: Less than.
    /// Returns L < R.
    class ExprLT : public Expression
    {
    public:
        /// `ExprLT` constructor.
        /// @param  lexpr   Expression for left parameter.
        /// @param  rexpr   Expression for right parameter.
        ExprLT(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };


    /// Expression: Less than or equal to.
    /// Returns L <= R.
    class ExprLE : public Expression
    {
    public:
        /// `ExprLE` constructor.
        /// @param  lexpr   Expression for left parameter.
        /// @param  rexpr   Expression for right parameter.
        ExprLE(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };


    /// Expression: Greater than.
    /// Returns L > R.
    class ExprGT : public Expression
    {
    public:
        /// `ExprGT` constructor.
        /// @param  lexpr   Expression for left parameter.
        /// @param  rexpr   Expression for right parameter.
        ExprGT(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };


    /// Expression: Greater than or equal to.
    /// Returns L >= R.
    class ExprGE : public Expression
    {
    public:
        /// `ExprGE` constructor.
        /// @param  lexpr   Expression for left parameter.
        /// @param  rexpr   Expression for right parameter.
        ExprGE(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };

    /// @}
}