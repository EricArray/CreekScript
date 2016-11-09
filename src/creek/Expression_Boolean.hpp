#pragma once

#include <creek/Expression.hpp>

#include <memory>

#include <creek/api_mode.hpp>


namespace creek
{
    /// @defgroup   expression_boolean  Boolean operations
    /// @{


    /// @brief  Expression: Short circuit boolean AND.
    /// If L is false, returns L, else, returns R.
    class CREEK_API ExprBoolAnd : public Expression
    {
    public:
        /// @brief  `ExprBoolAnd` constructor..
        /// @param  lexpr       Expression for left parameter.
        /// @param  rexpr       Expression for right parameter.
        ExprBoolAnd(Expression* lexpr, Expression* rexpr);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };


    /// @brief  Expression: Short circuit boolean OR.
    /// If L is true, returns L, else, returns R.
    class CREEK_API ExprBoolOr : public Expression
    {
    public:
        /// @brief  `ExprBoolOr` constructor..
        /// @param  lexpr       Expression for left parameter.
        /// @param  rexpr       Expression for right parameter.
        ExprBoolOr(Expression* lexpr, Expression* rexpr);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };


    /// @brief  Expression: Boolean XOR.
    /// Creates a new Boolean data.
    /// Returns L XOR R.
    class CREEK_API ExprBoolXor : public Expression
    {
    public:
        /// @brief  `ExprBoolXor` constructor..
        /// @param  lexpr       Expression for left parameter.
        /// @param  rexpr       Expression for right parameter.
        ExprBoolXor(Expression* lexpr, Expression* rexpr);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };


    /// @brief  Expression: Boolean NOT.
    /// Returns NOT L.
    class CREEK_API ExprBoolNot : public Expression
    {
    public:
        /// @brief  `ExprBoolNot` constructor..
        /// @param  expr        Expression to negate.
        ExprBoolNot(Expression* expr);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;
        
        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_expr;
    };

    /// @}
}
