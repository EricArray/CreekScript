#pragma once

#include <creek/Expression.hpp>

#include <memory>

#include <creek/api_mode.hpp>


namespace creek
{
    /// @defgroup   expression_debug    Debug expressions.
    /// To be used only in debugging only.
    /// @{

    /// Expression: Print a value to console.
    /// For debugging only.
    /// Returns evaluated expression.
    class CREEK_API ExprPrint : public Expression
    {
    public:
        /// `ExprPrint` constructor.
        /// @param  expression  Expression to get value.
        ExprPrint(Expression* expression);

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_expression;
    };

    /// @}
}
