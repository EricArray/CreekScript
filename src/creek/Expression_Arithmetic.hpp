#pragma once

#include <creek/Expression.hpp>

#include <memory>


namespace creek
{
    /// @defgroup   expression_arithmetic   Arithmetic operations
    /// @{
        
    /// Expression: Add two values.
    /// Returns L + R.
    class ExprAdd : public Expression
    {
    public:
        /// `ExprAdd` constructor.
        /// @param  lexpr       Expression for left parameter.
        /// @param  rexpr       Expression for right parameter.
        ExprAdd(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };
        

    /// Expression: Subtract two values.
    /// Returns L - R.
    class ExprSub : public Expression
    {
    public:
        /// `ExprSub` constructor.
        /// @param  lexpr       Expression for left parameter.
        /// @param  rexpr       Expression for right parameter.
        ExprSub(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };


    /// Expression: Multiply two values.
    /// Returns L * R.
    class ExprMul : public Expression
    {
    public:
        /// `ExprMul` constructor.
        /// @param  lexpr       Expression for left parameter.
        /// @param  rexpr       Expression for right parameter.
        ExprMul(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };

        
    /// Expression: Divide two values.
    /// Returns L / R.
    class ExprDiv : public Expression
    {
    public:
        /// `ExprDiv` constructor.
        /// @param  lexpr       Expression for left parameter.
        /// @param  rexpr       Expression for right parameter.
        ExprDiv(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };

        

    /// Expression: Modulo two values.
    /// Returns L % R.
    class ExprMod : public Expression
    {
    public:
        /// `ExprMod` constructor.
        /// @param  lexpr       Expression for left parameter.
        /// @param  rexpr       Expression for right parameter.
        ExprMod(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };

        
    /// Expression: Exponentiate two values.
    /// Returns L ** R.
    class ExprExp : public Expression
    {
    public:
        /// `ExprExp` constructor.
        /// @param  lexpr       Expression for left parameter.
        /// @param  rexpr       Expression for right parameter.
        ExprExp(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };


    /// Expression: Negate one values.
    /// Returns -L.
    class ExprUnm : public Expression
    {
    public:
        /// `ExprUnm` constructor.
        /// @param  expr        Expression to negate.
        ExprUnm(Expression* expr);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_expr;
    };

    /// @}
}