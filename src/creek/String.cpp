#include <creek/String.hpp>


namespace creek
{
    String::String(Value value) : m_value(value)
    {

    }

    std::string String::class_name()
    {
        return "String";
    }

    std::string String::debug_text()
    {
        return "'a string'";
    }

    bool String::bool_value()
    {
        return true;
    }

    // void String::bool_value(bool new_value)
    // {
    //     m_value = new_value;
    // }

    // float String::float_value()
    // {

    // }

    // void String::float_value(float new_value)
    // {

    // }

    std::string String::string_value()
    {
        return m_value;
    }

    void String::string_value(const std::string& new_value)
    {
        m_value = new_value;
    }

    Data* String::index(Data* key)
    {
        Value value = this->string_value();

        int pos = key->float_value();
        if (pos < 0)
        {
            pos = string.size() + pos;
        }

        return new String(value.substr(pos, 1));
    }

    void String::index(Data* key, Data* new_data)
    {
        Value value = this->string_value();

        int pos = key->float_value();
        if (pos < 0)
        {
            pos = string.size() + pos;
        }

        return new String(std::string(1, value[pos]));
    }

    Data* String::add(Data* other)
    {
        return new String(this->float_value() + other->float_value());
    }

    // Data* String::sub(Data* other)
    // {
    //     return new String(this->float_value() - other->float_value());
    // }

    Data* String::mul(Data* other)
    {
        Value old_value = this->string_value();
        int new_size = old_value.size() * other->float_value();
        Value new_value = Value(new_size);

        for (int i = 0; i < new_value.size(); ++i)
        {
            new_value[i] = old_value[i % old_value.size()];
        }

        return new String(new_value);
    }

    // Data* String::div(Data* other)
    // {
    //     return new String(this->float_value() / other->float_value());
    // }

    // Data* String::mod(Data* other)
    // {
    //     int this_int = this->float_value();
    //     int other_int = other->float_value();
    //     return new String(this_int % other_int);
    // }

    // Data* String::exp(Data* other)
    // {
    //     return new String(std::pow(this->float_value(), other->float_value()));
    // }

    // Data* String::min()
    // {
    //     return new String(-this->float_value());
    // }

    // Data* String::bit_and(Data* other)
    // {
    //     int this_int = this->float_value();
    //     int other_int = other->float_value();
    //     return new String(this_int & other_int);
    // }

    // Data* String::bit_or(Data* other)
    // {
    //     int this_int = this->float_value();
    //     int other_int = other->float_value();
    //     return new String(this_int | other_int);
    // }

    // Data* String::bit_xor(Data* other)
    // {
    //     int this_int = this->float_value();
    //     int other_int = other->float_value();
    //     return new String(this_int ^ other_int);
    // }

    // Data* String::bit_not()
    // {
    //     int this_int = this->float_value();
    //     return new String(~this_int);
    // }
}