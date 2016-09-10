#include <creek/Boolean.hpp>


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
        return string_value();
    }


    bool Boolean::bool_value() const
    {
        return m_value;
    }

//    void Boolean::bool_value(bool new_value)
//    {
//        m_value = new_value;
//    }

    int Boolean::int_value() const
    {
        return m_value;
    }

//    void Boolean::int_value(int new_value)
//    {
//        m_value = new_value;
//    }

    float Boolean::float_value() const
    {
        return m_value;
    }

//    void Boolean::float_value(float new_value)
//    {
//        m_value = new_value > 0;
//    }

    std::string Boolean::string_value() const
    {
        return m_value ? "true" : "false";
    }

//    void Boolean::string_value(const std::string& new_value)
//    {
//        m_value = new_value == "true" ? true : false;
//    }


    // Data* Boolean::index(Data* key)
    // {

    // }

    // Data* Boolean::index(Data* key, Data* new_value)
    // {

    // }


    // Data* Boolean::add(Data* other)
    // {

    // }

    // Data* Boolean::sub(Data* other)
    // {

    // }

    // Data* Boolean::mul(Data* other)
    // {

    // }

    // Data* Boolean::div(Data* other)
    // {

    // }

    // Data* Boolean::mod(Data* other)
    // {

    // }

    // Data* Boolean::exp(Data* other)
    // {

    // }

    // Data* Boolean::min()
    // {

    // }

    // Data* Boolean::bit_and(Data* other)
    // {

    // }

    // Data* Boolean::bit_or(Data* other)
    // {

    // }

    // Data* Boolean::bit_xor(Data* other)
    // {

    // }

    // Data* Boolean::bit_not()
    // {

    // }


    int Boolean::cmp(Data* other)
    {
        bool this_value = this->bool_value();
        bool other_value = other->bool_value();
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
}
