#pragma once

#include <creek/Expression.hpp>

#include <memory>

#include <creek/VarName.hpp>


namespace creek
{
    /// @defgroup   expression_variable Variable manipulating expressions
    /// @{

    /// Expression: Declare a local variable.
    /// Returns a copy of the evaluated expression.
    class ExprLocalVar : public Expression
    {
    public:
        /// `ExprLocalVar` constructor.
        /// @param  var_name    Variable name.
        /// @param  expression  Expression to get value.
        ExprLocalVar(VarName var_name, Expression* expression);

        Variable eval(Scope& scope) override;

    private:
        VarName m_var_name;
        std::unique_ptr<Expression> m_expression;
    };


    /// Expression: Copy the value from a variable.
    /// Returns a copy of the value loaded from the variable.
    class ExprLoadVar : public Expression
    {
    public:
        /// `ExprLoadVar` constructor.
        /// @param  var_name    Variable name.
        ExprLoadVar(VarName var_name);

        Variable eval(Scope& scope) override;

    private:
        VarName m_var_name;
    };


    /// Expression: Set the value from a variable.
    /// Returns a copy of the value stored in the variable.
    class ExprStoreVar : public Expression
    {
    public:
        /// `ExprStoreVar` constructor.
        /// @param  var_name    Variable name.
        /// @param  expression  Expression to get value.
        ExprStoreVar(VarName var_name, Expression* expression);

        Variable eval(Scope& scope) override;

    private:
        VarName m_var_name;
        std::unique_ptr<Expression> m_expression;
    };

    /// @}
}
