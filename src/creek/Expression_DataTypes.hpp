#pragma once

#include <creek/Expression.hpp>

#include <creek/api_mode.hpp>
#include <creek/Boolean.hpp>
#include <creek/CFunction.hpp>
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
    class CREEK_API ExprVoid : public Expression
    {
    public:
        /// `ExprVoid` constructor.
        ExprVoid();

        Variable eval(Scope& scope) override;
    };


    /// Expression: Create a boolean data.
    /// Returns a new `Boolean`.
    class CREEK_API ExprBoolean : public Expression
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
    class CREEK_API ExprNumber : public Expression
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
    class CREEK_API ExprString : public Expression
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
    class CREEK_API ExprIdentifier : public Expression
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
    class CREEK_API ExprVector : public Expression
    {
    public:
        /// `ExprVector` constructor.
        ExprVector();

        Variable eval(Scope& scope) override;
    };


    /// Expression: Create a function data.
    /// Returns a new `Function`.
    class CREEK_API ExprFunction : public Expression
    {
    public:
        /// `ExprFunction` constructor.
        /// @param  arg_names   Names of arguments.
        /// @param  variadic    Create a variadic function.
        /// @param  body        Function body block.
        ExprFunction(const std::vector<VarName>& arg_names, bool variadic, Expression* body);

        Variable eval(Scope& scope) override;

    private:
        std::vector<VarName> m_arg_names;
        bool m_variadic;
        std::unique_ptr<Expression> m_body;
    };


    /// Expression: Create a C function interface data.
    /// Returns a new `CFunction`.
    class CREEK_API ExprCFunction : public Expression
    {
    public:
        /// `ExprCFunction` constructor.
        /// @param  argn        Number of arguments.
        /// @param  variadic    Create a variadic function.
        /// @param  listener    Listener function to call.
        ExprCFunction(unsigned argn, bool variadic, CFunction::Listener listener);

        Variable eval(Scope& scope) override;

    private:
        unsigned m_argn;
        bool m_variadic;
        CFunction::Listener m_listener;
    };

    /// @}
}
