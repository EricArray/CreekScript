#include <creek/Expression_BasicDataTypes.hpp>

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
}
