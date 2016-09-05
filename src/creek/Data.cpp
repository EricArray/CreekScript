#include <creek/Data.hpp>

#include <creek/Variable.hpp>


namespace creek
{
    std::string Data::class_name()
    {
        return "Data";
    }

    std::string Data::debug_text()
    {
        throw Undefined(class_name() + "::debug_text");
    }

    bool Data::bool_value()
    {
        throw Undefined(class_name() + "::bool_value");
    }

    void Data::bool_value(bool new_value)
    {
        throw Undefined(class_name() + "::bool_value");
    }

    float Data::float_value()
    {
        throw Undefined(class_name() + "::float_value");
    }

    void Data::float_value(float new_value)
    {
        throw Undefined(class_name() + "::float_value");
    }

    std::string Data::string_value()
    {
        throw Undefined(class_name() + "::string_value");
    }

    void Data::string_value(const std::string& new_value)
    {
        throw Undefined(class_name() + "::string_value");
    }

    Data* Data::index(Data* key)
    {
        throw Undefined(class_name() + "::index");
    }

    void Data::index(Data* key, Data* new_data)
    {
        throw Undefined(class_name() + "::index");
    }

    Data* Data::add(Data* other)
    {
        throw Undefined(class_name() + "::add");
    }

    Data* Data::sub(Data* other)
    {
        throw Undefined(class_name() + "::sub");
    }

    Data* Data::mul(Data* other)
    {
        throw Undefined(class_name() + "::mul");
    }

    Data* Data::div(Data* other)
    {
        throw Undefined(class_name() + "::div");
    }

    Data* Data::mod(Data* other)
    {
        throw Undefined(class_name() + "::mod");
    }

    Data* Data::exp(Data* other)
    {
        throw Undefined(class_name() + "::exp");
    }

    Data* Data::min()
    {
        throw Undefined(class_name() + "::min");
    }

    Data* Data::bit_and(Data* other)
    {
        throw Undefined(class_name() + "::bit_and");
    }

    Data* Data::bit_or(Data* other)
    {
        throw Undefined(class_name() + "::bit_or");
    }

    Data* Data::bit_xor(Data* other)
    {
        throw Undefined(class_name() + "::bit_xor");
    }

    Data* Data::bit_not()
    {
        throw Undefined(class_name() + "::bit_not");
    }
}