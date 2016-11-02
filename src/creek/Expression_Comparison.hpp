#pragma once

#include <creek/Expression.hpp>

#include <memory>

#include <creek/api_mode.hpp>


namespace creek
{
    /// @defgroup   expression_comparison   Comparison opereations
    /// @{

    /// Expression: Compare two values.
    /// Returns -1 if less-than, 0 if equal and 1 if greater-than.
    /// Returns L <=> R.
    class CREEK_API ExprCmp : public Expression
    {
    public:
        /// `ExprCmp` constructor.
        /// @param  lexpr   Expression for left parameter.
        /// @param  rexpr   Expression for right parameter.
        ExprCmp(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };


    /// Expression: Equal to.
    /// Returns L == R.
    class CREEK_API ExprEQ : public Expression
    {
    public:
        /// `ExprEQ` constructor.
        /// @param  lexpr   Expression for left parameter.
        /// @param  rexpr   Expression for right parameter.
        ExprEQ(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };


    /// Expression: Not equal to.
    /// Returns L != R.
    class CREEK_API ExprNE : public Expression
    {
    public:
        /// `ExprNE` constructor.
        /// @param  lexpr   Expression for left parameter.
        /// @param  rexpr   Expression for right parameter.
        ExprNE(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };


    /// Expression: Less than.
    /// Returns L < R.
    class CREEK_API ExprLT : public Expression
    {
    public:
        /// `ExprLT` constructor.
        /// @param  lexpr   Expression for left parameter.
        /// @param  rexpr   Expression for right parameter.
        ExprLT(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };


    /// Expression: Less than or equal to.
    /// Returns L <= R.
    class CREEK_API ExprLE : public Expression
    {
    public:
        /// `ExprLE` constructor.
        /// @param  lexpr   Expression for left parameter.
        /// @param  rexpr   Expression for right parameter.
        ExprLE(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };


    /// Expression: Greater than.
    /// Returns L > R.
    class CREEK_API ExprGT : public Expression
    {
    public:
        /// `ExprGT` constructor.
        /// @param  lexpr   Expression for left parameter.
        /// @param  rexpr   Expression for right parameter.
        ExprGT(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };


    /// Expression: Greater than or equal to.
    /// Returns L >= R.
    class CREEK_API ExprGE : public Expression
    {
    public:
        /// `ExprGE` constructor.
        /// @param  lexpr   Expression for left parameter.
        /// @param  rexpr   Expression for right parameter.
        ExprGE(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };

    /// @}
}
