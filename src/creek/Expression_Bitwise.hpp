#pragma once

#include <creek/Expression.hpp>

#include <memory>


namespace creek
{
    /// @defgroup   expression_bitwise  Bitwise operations
    /// @{
        
    /// Expression: Bitwise AND two values.
    /// Returns L & R.
    class ExprBitAnd : public Expression
    {
    public:
        /// `ExprBitAnd` constructor.
        /// @param  lexpr       Expression for left parameter.
        /// @param  rexpr       Expression for right parameter.
        ExprBitAnd(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };
        

    /// Expression: Bitwise OR two values.
    /// Returns L | R.
    class ExprBitOr : public Expression
    {
    public:
        /// `ExprBitOr` constructor.
        /// @param  lexpr       Expression for left parameter.
        /// @param  rexpr       Expression for right parameter.
        ExprBitOr(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };
        

    /// Expression: Bitwise XOR two values.
    /// Returns L ^ R.
    class ExprBitXor : public Expression
    {
    public:
        /// `ExprBitXor` constructor.
        /// @param  lexpr       Expression for left parameter.
        /// @param  rexpr       Expression for right parameter.
        ExprBitXor(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };
        

    /// Expression: Bitwise NOT one value.
    /// Returns ~L.
    class ExprBitNot : public Expression
    {
    public:
        /// `ExprBitNot` constructor.
        /// @param  expr        Expression to bitwise negate.
        ExprBitNot(Expression* expr);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_expr;
    };
        

    /// Expression: Bitwise left shift two values.
    /// Returns L << R.
    class ExprBitLeftShift : public Expression
    {
    public:
        /// `ExprBitLeftShift` constructor.
        /// @param  lexpr       Expression for left parameter.
        /// @param  rexpr       Expression for right parameter.
        ExprBitLeftShift(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };
        

    /// Expression: Bitwise right shift two values.
    /// Returns L >> R.
    class ExprBitRightShift : public Expression
    {
    public:
        /// `ExprBitRightShift` constructor.
        /// @param  lexpr       Expression for left parameter.
        /// @param  rexpr       Expression for right parameter.
        ExprBitRightShift(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };

    /// @}
}