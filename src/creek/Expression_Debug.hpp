#pragma once

#include <creek/Expression.hpp>

#include <memory>

#include <creek/api_mode.hpp>


namespace creek
{
    /// @defgroup   expression_debug    Debug expressions.
    /// To be used only in debugging only.
    /// @{

    /// @brief  Expression: Print a value to console.
    /// For debugging only.
    /// Returns evaluated expression.
    class CREEK_API ExprPrint : public Expression
    {
    public:
        /// @brief  `ExprPrint` constructor..
        /// @param  expression  Expression to get value.
        ExprPrint(Expression* expression);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;
        
        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_expression;
    };

    /// @}
}
