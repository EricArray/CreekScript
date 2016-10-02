#include <creek/Expression_DataTypes.hpp>

#include <creek/Scope.hpp>
#include <creek/Variable.hpp>


namespace creek
{
    // `ExprVoid` constructor.
    ExprVoid::ExprVoid()
    {

    }

    Variable ExprVoid::eval(Scope& scope)
    {
        return Variable(new Void());
    }


    // `ExprBoolean` constructor.
    // @param  value       Boolean value.
    ExprBoolean::ExprBoolean(Boolean::Value value) : m_value(value)
    {

    }

    Variable ExprBoolean::eval(Scope& scope)
    {
        return Variable(new Boolean(m_value));
    }


    // `ExprNumber` constructor.
    // @param  value       Number value.
    ExprNumber::ExprNumber(Number::Value value) : m_value(value)
    {

    }

    Variable ExprNumber::eval(Scope& scope)
    {
        return Variable(new Number(m_value));
    }


    // `ExprString` constructor.
    // @param  value       String value.
    ExprString::ExprString(String::Value value) : m_value(value)
    {

    }

    Variable ExprString::eval(Scope& scope)
    {
        return Variable(new String(m_value));
    }


    // `ExprIdentifier` constructor.
    // @param  value       Identifier value.
    ExprIdentifier::ExprIdentifier(Identifier::Value value) : m_value(value)
    {

    }

    Variable ExprIdentifier::eval(Scope& scope)
    {
        return Variable(new Identifier(m_value));
    }


    // `ExprVector` constructor.
    ExprVector::ExprVector()
    {

    }

    Variable ExprVector::eval(Scope& scope)
    {
        Vector::Value new_value = std::make_shared< std::vector<Variable> >();
        return Variable(new Vector(new_value));
    }


    // `ExprFunction` constructor.
    // @param  arg_names   Names of arguments.
    // @param  variadic    Create a variadic function.
    // @param  body        Function body block.
    ExprFunction::ExprFunction(const std::vector<VarName>& arg_names, bool variadic, Expression* body) :
        m_arg_names(arg_names),
        m_variadic(variadic),
        m_body(body)
    {

    }

    Variable ExprFunction::eval(Scope& scope)
    {
        Function::Definition* def = new Function::Definition(scope, m_arg_names, m_variadic, m_body.release());
        Function::Value new_value(def);
        return Variable(new Function(new_value));
    }


    // `ExprCFunction` constructor.
    // @param  argn        Number of arguments.
    // @param  variadic    Create a variadic function.
    // @param  listener    Listener function to call.
    ExprCFunction::ExprCFunction(unsigned argn, bool variadic, CFunction::Listener listener) :
        m_argn(argn),
        m_variadic(variadic),
        m_listener(listener)
    {

    }

    Variable ExprCFunction::eval(Scope& scope)
    {
        CFunction::Definition* def = new CFunction::Definition(scope, m_argn, m_variadic, m_listener);
        CFunction::Value new_value(def);
        return Variable(new CFunction(new_value));
    }
}
