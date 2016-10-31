#pragma once

#include <creek/Expression.hpp>

#include <memory>

#include <creek/api_mode.hpp>
#include <creek/VarName.hpp>


namespace creek
{
    /// @defgroup   expression_variable Variable manipulating expressions
    /// @{

    /// @brief  Expression: Create a new variable in current scope.
    /// Returns a copy of the evaluated expression.
    class CREEK_API ExprCreateLocal : public Expression
    {
    public:
        /// @brief  `ExprCreateLocal` constructor.
        /// @param  var_name    Variable name.
        /// @param  expression  Expression to get value.
        ExprCreateLocal(VarName var_name, Expression* expression);

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        VarName m_var_name;
        std::unique_ptr<Expression> m_expression;
    };


    /// @brief  Expression: Copy the value of a variable from current scope.
    /// Returns a copy of the value stored at the variable.
    class CREEK_API ExprLoadLocal : public Expression
    {
    public:
        /// @brief  `ExprLoadLocal` constructor.
        /// @param  var_name    Variable name.
        ExprLoadLocal(VarName var_name);

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        VarName m_var_name;
    };


    /// @brief  Expression: Set the value of a variable from current scope.
    /// Returns a copy of the value stored at the variable.
    class CREEK_API ExprStoreLocal : public Expression
    {
    public:
        /// @brief  `ExprStoreLocal` constructor.
        /// @param  var_name    Variable name.
        /// @param  expression  Expression to get value.
        ExprStoreLocal(VarName var_name, Expression* expression);

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        VarName m_var_name;
        std::unique_ptr<Expression> m_expression;
    };

    /// @brief  Expression: Create a new variable in global scope.
    /// Returns a copy of the evaluated expression.
    class CREEK_API ExprCreateGlobal : public Expression
    {
    public:
        /// @brief  `ExprCreateGlobal` constructor.
        /// @param  var_name    Variable name.
        /// @param  expression  Expression to get value.
        ExprCreateGlobal(VarName var_name, Expression* expression);

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        VarName m_var_name;
        std::unique_ptr<Expression> m_expression;
    };


    /// @brief  Expression: Copy the value of a variable from global scope.
    /// Returns a copy of the value stored at the variable.
    class CREEK_API ExprLoadGlobal : public Expression
    {
    public:
        /// @brief  `ExprLoadGlobal` constructor.
        /// @param  var_name    Variable name.
        ExprLoadGlobal(VarName var_name);

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        VarName m_var_name;
    };


    /// @brief  Expression: Set the value of a variable from global scope.
    /// Returns a copy of the value stored at the variable.
    class CREEK_API ExprStoreGlobal : public Expression
    {
    public:
        /// @brief  `ExprStoreGlobal` constructor.
        /// @param  var_name    Variable name.
        /// @param  expression  Expression to get value.
        ExprStoreGlobal(VarName var_name, Expression* expression);

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        VarName m_var_name;
        std::unique_ptr<Expression> m_expression;
    };

    /// @}
}
