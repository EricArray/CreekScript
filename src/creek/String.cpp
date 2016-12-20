#include <creek/String.hpp>

#include <creek/Expression_DataTypes.hpp>
#include <creek/GlobalScope.hpp>
#include <creek/utility.hpp>


namespace creek
{
    String::String(Value value) : m_value(value)
    {

    }

    const String::Value& String::value() const
    {
        return m_value;
    }

    String::Value& String::value()
    {
        return m_value;
    }

    Data* String::copy() const
    {
        return new String(m_value);
    }

    std::string String::class_name() const
    {
        return "String";
    }

    std::string String::debug_text() const
    {
        return std::string("\"") + escape_string(m_value) + std::string("\"");
    }

    Expression* String::to_expression() const
    {
        return new ExprString(m_value);
    }


    bool String::bool_value(const SharedPointer<Scope>& scope) const
    {
        return true;
    }

    char String::char_value(const SharedPointer<Scope>& scope) const
    {
        return m_value.size() == 0 ? '\0' : m_value.front();
    }

    const std::string& String::string_value(const SharedPointer<Scope>& scope) const
    {
        return m_value;
    }

    // void String::string_value(const std::string& new_value)
    // {
        // m_value = new_value;
    // }

    Data* String::index(const SharedPointer<Scope>& scope, Data* key)
    {
        Value value = this->string_value(scope);

        int pos = key->int_value(scope);
        if (pos < 0)
        {
            pos = value.size() + pos;
        }

        return new String(value.substr(pos, 1));
    }

    Data* String::index(const SharedPointer<Scope>& scope, Data* key, Data* new_data)
    {
        int pos = key->int_value(scope);
        if (pos < 0)
        {
            pos = m_value.size() + pos;
        }
        m_value[pos] = new_data->int_value(scope);

        return new_data;
    }

    Data* String::add(const SharedPointer<Scope>& scope, Data* other)
    {
        return new String(this->string_value(scope) + other->string_value(scope));
    }

    // Data* String::sub(const SharedPointer<Scope>& scope, Data* other)
    // {
    //     return new String(this->double_value(scope) - other->double_value(scope));
    // }

    Data* String::mul(const SharedPointer<Scope>& scope, Data* other)
    {
        Value old_value = this->string_value(scope);
        size_t new_size = old_value.size() * other->double_value(scope);
        Value new_value(new_size, ' ');

        for (size_t i = 0; i < new_value.size(); ++i)
        {
            new_value[i] = old_value[i % old_value.size()];
        }

        return new String(new_value);
    }

    // Data* String::div(const SharedPointer<Scope>& scope, Data* other)
    // {
    //     return new String(this->double_value(scope) / other->double_value(scope));
    // }

    // Data* String::mod(const SharedPointer<Scope>& scope, Data* other)
    // {
    //     int this_int = this->double_value(scope);
    //     int other_int = other->double_value(scope);
    //     return new String(this_int % other_int);
    // }

    // Data* String::exp(const SharedPointer<Scope>& scope, Data* other)
    // {
    //     return new String(std::pow(this->double_value(scope), other->double_value(scope)));
    // }

    // Data* String::min()
    // {
    //     return new String(-this->double_value(scope));
    // }

    // Data* String::bit_and(const SharedPointer<Scope>& scope, Data* other)
    // {
    //     int this_int = this->double_value(scope);
    //     int other_int = other->double_value(scope);
    //     return new String(this_int & other_int);
    // }

    // Data* String::bit_or(const SharedPointer<Scope>& scope, Data* other)
    // {
    //     int this_int = this->double_value(scope);
    //     int other_int = other->double_value(scope);
    //     return new String(this_int | other_int);
    // }

    // Data* String::bit_xor(const SharedPointer<Scope>& scope, Data* other)
    // {
    //     int this_int = this->double_value(scope);
    //     int other_int = other->double_value(scope);
    //     return new String(this_int ^ other_int);
    // }

    // Data* String::bit_not(const SharedPointer<Scope>& scope)
    // {
    //     int this_int = this->double_value(scope);
    //     return new String(~this_int);
    // }

    int String::cmp(const SharedPointer<Scope>& scope, Data* other)
    {
        return this->string_value(scope).compare(other->string_value(scope));
    }

    Data* String::get_class(const SharedPointer<Scope>& scope) const
    {
        return scope->global()->class_String->copy();
    }
}
