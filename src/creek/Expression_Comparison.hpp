#pragma once

#include <creek/Expression.hpp>

#include <memory>

#include <creek/api_mode.hpp>


namespace creek
{
    /// @defgroup   expression_comparison   Comparison opereations
    /// @{

    /// @brief  Expression: Compare two values.
    /// Returns -1 if less-than, 0 if equal and 1 if greater-than.
    /// Returns L <=> R.
    class CREEK_API ExprCmp : public Expression
    {
    public:
        /// @brief  `ExprCmp` constructor..
        /// @param  lexpr   Expression for left parameter.
        /// @param  rexpr   Expression for right parameter.
        ExprCmp(Expression* lexpr, Expression* rexpr);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;
        
        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };



    /// @brief  Expression: Equal to.
    /// Returns L == R.
    class CREEK_API ExprEQ : public Expression
    {
    public:
        /// @brief  `ExprEQ` constructor..
        /// @param  lexpr   Expression for left parameter.
        /// @param  rexpr   Expression for right parameter.
        ExprEQ(Expression* lexpr, Expression* rexpr);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };


    /// @brief  Expression: Not equal to.
    /// Returns L != R.
    class CREEK_API ExprNE : public Expression
    {
    public:
        /// @brief  `ExprNE` constructor..
        /// @param  lexpr   Expression for left parameter.
        /// @param  rexpr   Expression for right parameter.
        ExprNE(Expression* lexpr, Expression* rexpr);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };


    /// @brief  Expression: Less than.
    /// Returns L < R.
    class CREEK_API ExprLT : public Expression
    {
    public:
        /// @brief  `ExprLT` constructor..
        /// @param  lexpr   Expression for left parameter.
        /// @param  rexpr   Expression for right parameter.
        ExprLT(Expression* lexpr, Expression* rexpr);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };


    /// @brief  Expression: Less than or equal to.
    /// Returns L <= R.
    class CREEK_API ExprLE : public Expression
    {
    public:
        /// @brief  `ExprLE` constructor..
        /// @param  lexpr   Expression for left parameter.
        /// @param  rexpr   Expression for right parameter.
        ExprLE(Expression* lexpr, Expression* rexpr);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };


    /// @brief  Expression: Greater than.
    /// Returns L > R.
    class CREEK_API ExprGT : public Expression
    {
    public:
        /// @brief  `ExprGT` constructor..
        /// @param  lexpr   Expression for left parameter.
        /// @param  rexpr   Expression for right parameter.
        ExprGT(Expression* lexpr, Expression* rexpr);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };


    /// @brief  Expression: Greater than or equal to.
    /// Returns L >= R.
    class CREEK_API ExprGE : public Expression
    {
    public:
        /// @brief  `ExprGE` constructor..
        /// @param  lexpr   Expression for left parameter.
        /// @param  rexpr   Expression for right parameter.
        ExprGE(Expression* lexpr, Expression* rexpr);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };

    /// @}
}
