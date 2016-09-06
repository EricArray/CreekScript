#pragma once

#include <memory>
#include <vector>

#include <creek/Number.hpp>
#include <creek/String.hpp>
#include <creek/VarName.hpp>
#include <creek/Void.hpp>


namespace creek
{
    class Data;
    class Scope;


    /// Expression statement in a program.
    class Expression
    {
    public:
        virtual ~Expression() = default;

        /// Evaluate this expression.
        /// @return Result of the expression; may be `nullptr`.
        virtual Variable eval(Scope& scope) = 0;
    };



    /// @defgroup   expression_debug    Debug expressions.
    /// To be used only in debugging only.
    /// @{

    /// Expression: Print a value to console.
    /// For debugging only.
    /// Returns evaluated expression.
    class ExprPrint : public Expression
    {
    public:
        /// `ExprPrint` constructor.
        /// @param  expression  Expression to get value.
        ExprPrint(Expression* expression);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_expression;
    };

    /// @}



    /// @defgroup   expression_control_flow Control flow expressions
    /// @{

    /// Expression: Block of expressions.
    /// Begin a new scope and executes each expression.
    /// Returns result of last evaluated expression.
    class ExprBlock : public Expression
    {
    public:
        /// `ExprBlock` constructor.
        /// @param  expressions  List of expressions to evaluate.
        ExprBlock(std::vector<Expression*>&& expressions);

        Variable eval(Scope& scope) override;

    private:
        std::vector< std::unique_ptr<Expression> > m_expressions;
    };

    /// Expression: If-else block.
    /// Returns result of last evaluated branch, or void.
    class ExprIf : public Expression
    {
    public:
        /// `ExprIf` constructor.
        /// @param  condition       Contidion expression.
        /// @param  true_branch     Expression to evaluate when true.
        /// @param  false_branch    Expression to evaluate when false.
        ExprIf(Expression* condition, Expression* true_branch, Expression* false_branch);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_condition;
        std::unique_ptr<Expression> m_true_branch;
        std::unique_ptr<Expression> m_false_branch;
    };

    /// @}



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



    /// @defgroup   expression_data Basic data type expressions
    /// @{

    /// Expression: Create a void data.
    /// Returns a new `Void`.
    class ExprVoid : public Expression
    {
    public:
        /// `ExprVoid` constructor.
        ExprVoid();

        Variable eval(Scope& scope) override;
    };


    /// Expression: Create a number data.
    /// Returns a new `Number`.
    class ExprNumber : public Expression
    {
    public:
        /// `ExprNumber` constructor.
        /// @param  value       Number value.
        ExprNumber(Number::Value value);

        Variable eval(Scope& scope) override;

    private:
        Number::Value m_value;
    };


    /// Expression: Create a string data.
    /// Returns a new `String`.
    class ExprString : public Expression
    {
    public:
        /// `ExprString` constructor.
        /// @param  value       String value.
        ExprString(String::Value value);

        Variable eval(Scope& scope) override;

    private:
        String::Value m_value;
    };

    /// @}



    /// @defgroup   expression_arithmetic   Arithmetic operations
    /// @{

    /// Expression: Add two values.
    /// Returns R + L.
    class ExprAdd : public Expression
    {
    public:
        /// `ExprAdd` constructor.
        /// @param  lexpr       Expression for left parameter.
        /// @param  rexpr      Expression for right parameter.
        ExprAdd(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };

    /// @}
}
