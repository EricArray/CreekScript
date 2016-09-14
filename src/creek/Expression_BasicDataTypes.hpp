#pragma once

#include <creek/Expression.hpp>

#include <creek/Boolean.hpp>
#include <creek/Function.hpp>
#include <creek/Identifier.hpp>
#include <creek/Number.hpp>
#include <creek/String.hpp>
#include <creek/VarName.hpp>
#include <creek/Vector.hpp>
#include <creek/Void.hpp>


namespace creek
{
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


    /// Expression: Create a boolean data.
    /// Returns a new `Boolean`.
    class ExprBoolean : public Expression
    {
    public:
        /// `ExprBoolean` constructor.
        /// @param  value       Boolean value.
        ExprBoolean(Boolean::Value value);

        Variable eval(Scope& scope) override;

    private:
        Boolean::Value m_value;
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


    /// Expression: Create a identifier data.
    /// Returns a new `Identifier`.
    class ExprIdentifier : public Expression
    {
    public:
        /// `ExprIdentifier` constructor.
        /// @param  value       Identifier value.
        ExprIdentifier(Identifier::Value value);

        Variable eval(Scope& scope) override;

    private:
        Identifier::Value m_value;
    };


    /// Expression: Create a vector data.
    /// Returns a new, empty `Vector`.
    class ExprVector : public Expression
    {
    public:
        /// `ExprVector` constructor.
        ExprVector();

        Variable eval(Scope& scope) override;
    };


    /// Expression: Create a function data.
    /// Returns a new `Function`.
    class ExprFunction : public Expression
    {
    public:
        /// `ExprFunction` constructor.
        /// @param  arg_names   Names of arguments.
        /// @param  body        Function body block.
        ExprFunction(const std::vector<VarName>& arg_names, Expression* body);

        Variable eval(Scope& scope) override;

    private:
        std::vector<VarName> m_arg_names;
        std::unique_ptr<Expression> m_body;
    };

    /// @}
}
