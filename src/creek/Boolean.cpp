#include <creek/Boolean.hpp>

#include <creek/Expression_DataTypes.hpp>
#include <creek/GlobalScope.hpp>


namespace creek
{
    // `Boolean` constructor.
    // @param  value   Boolean value.
    Boolean::Boolean(Value value) : m_value(value)
    {

    }


    Data* Boolean::copy() const
    {
        return new Boolean(m_value);
    }

    std::string Boolean::class_name() const
    {
        return "Boolean";
    }

    std::string Boolean::debug_text() const
    {
        static const std::string true_str = "true";
        static const std::string false_str = "false";
        return m_value ? true_str : false_str;
    }

    Expression* Boolean::to_expression() const
    {
        return new ExprBoolean(m_value);
    }


    bool Boolean::bool_value(const SharedPointer<Scope>& scope) const
    {
        return m_value;
    }

    // void Boolean::bool_value(bool new_value)
    // {
        // m_value = new_value;
    // }

    int Boolean::int_value(const SharedPointer<Scope>& scope) const
    {
        return m_value;
    }

    // void Boolean::int_value(int new_value)
    // {
        // m_value = new_value;
    // }

    double Boolean::double_value(const SharedPointer<Scope>& scope) const
    {
        return m_value;
    }

    // void Boolean::float_value(float new_value)
    // {
        // m_value = new_value > 0;
    // }

    const std::string& Boolean::string_value(const SharedPointer<Scope>& scope) const
    {
        static const std::string true_str = "true";
        static const std::string false_str = "false";
        return m_value ? true_str : false_str;
    }

    // void Boolean::string_value(const std::string& new_value)
    // {
        // m_value = new_value == "true" ? true : false;
    // }


    // Data* Boolean::index(const SharedPointer<Scope>& scope, Data* key)
    // {

    // }

    // Data* Boolean::index(const SharedPointer<Scope>& scope, Data* key, Data* new_value)
    // {

    // }


    // Data* Boolean::add(const SharedPointer<Scope>& scope, Data* other)
    // {

    // }

    // Data* Boolean::sub(const SharedPointer<Scope>& scope, Data* other)
    // {

    // }

    // Data* Boolean::mul(const SharedPointer<Scope>& scope, Data* other)
    // {

    // }

    // Data* Boolean::div(const SharedPointer<Scope>& scope, Data* other)
    // {

    // }

    // Data* Boolean::mod(const SharedPointer<Scope>& scope, Data* other)
    // {

    // }

    // Data* Boolean::exp(const SharedPointer<Scope>& scope, Data* other)
    // {

    // }

    // Data* Boolean::min()
    // {

    // }

    // Data* Boolean::bit_and(const SharedPointer<Scope>& scope, Data* other)
    // {

    // }

    // Data* Boolean::bit_or(const SharedPointer<Scope>& scope, Data* other)
    // {

    // }

    // Data* Boolean::bit_xor(const SharedPointer<Scope>& scope, Data* other)
    // {

    // }

    // Data* Boolean::bit_not(const SharedPointer<Scope>& scope)
    // {

    // }


    int Boolean::cmp(const SharedPointer<Scope>& scope, Data* other)
    {
        bool this_value = this->bool_value(scope);
        bool other_value = other->bool_value(scope);
        if (this_value < other_value)
        {
            return -1;
        }
        else if (this_value > other_value)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    Data* Boolean::get_class(const SharedPointer<Scope>& scope) const
    {
        return scope->global()->class_Boolean->copy();
    }
}
