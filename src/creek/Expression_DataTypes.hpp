#pragma once

#include <creek/Expression.hpp>

#include <creek/api_mode.hpp>
#include <creek/Boolean.hpp>
#include <creek/CFunction.hpp>
#include <creek/Function.hpp>
#include <creek/Identifier.hpp>
#include <creek/Null.hpp>
#include <creek/Number.hpp>
#include <creek/String.hpp>
#include <creek/VarName.hpp>
#include <creek/Vector.hpp>
#include <creek/Void.hpp>


namespace creek
{
    /// @defgroup   expression_data Basic data type expressions
    /// @{

    /// @brief  Expression: Create a void data.
    /// Returns a new `Void`.
    class CREEK_API ExprVoid : public Expression
    {
    public:
        /// `ExprVoid` constructor.
        ExprVoid();

        Variable eval(Scope& scope) override;
    };


    /// @brief  Expression: Create a null data.
    /// Returns a new `Null`.
    class CREEK_API ExprNull : public Expression
    {
    public:
        /// `ExprNull` constructor.
        ExprNull();

        Variable eval(Scope& scope) override;
    };


    /// @brief  Expression: Create a boolean data.
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


    /// @brief  Expression: Create a number data.
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


    /// @brief  Expression: Create a string data.
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


    /// @brief  Expression: Create a identifier data.
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


    /// @brief  Expression: Create a vector data.
    /// Returns a new, empty `Vector`.
    class CREEK_API ExprVector : public Expression
    {
    public:
        /// @brief  `ExprVector` constructor.
        /// @param  values  List of initial values.
        ExprVector(std::vector<Expression*> values);

        Variable eval(Scope& scope) override;

    private:
        std::vector< std::unique_ptr<Expression> > m_values;
    };


    /// @brief  Expression: Create a function data.
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
        std::shared_ptr<Expression> m_body;
    };


    /// @brief  Expression: Create a C function interface data.
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


    /// @brief  Expression: Create a class data.
    /// Returns a new `Object`.
    class CREEK_API ExprClass : public Expression
    {
    public:
        /// @brief  Class method definition.
        struct MethodDef
        {
            MethodDef(VarName id, const std::vector<VarName>& arg_names,
                      bool is_variadic, Expression* body) :
                id(id),
                arg_names(arg_names),
                is_variadic(is_variadic),
                body(body)
            {

            }

            VarName id; ///< Method name.
            std::vector<VarName> arg_names; ///< Argument names.
            bool is_variadic; ///< Is this method variadic?
            std::shared_ptr<Expression> body; ///< Expression evaluated when called.
        };

        /// @brief  `ExprClass` constructor.
        /// @param  id          Class name.
        /// @param  super_class Expression for the super class.
        /// @param  method_defs List of method definitions.
        ExprClass(VarName id, Expression* super_class, std::vector<MethodDef>& method_defs);

        Variable eval(Scope& scope) override;

    private:
        VarName m_id;
        std::unique_ptr<Expression> m_super_class;
        std::vector<MethodDef> m_method_defs;
    };

    /// @}
}
