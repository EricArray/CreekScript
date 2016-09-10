#include <creek/Number.hpp>

#include <cmath>


namespace creek
{
    Number::Number(Value value) : m_value(value)
    {

    }

    Data* Number::copy() const
    {
        return new Number(m_value);
    }

    std::string Number::class_name() const
    {
        return "Number";
    }

    std::string Number::debug_text() const
    {
        return std::to_string(m_value);
    }

    bool Number::bool_value() const
    {
        return m_value >= Value(0);
    }

//    void Number::bool_value(bool new_value)
//    {
//        m_value = new_value;
//    }

    int Number::int_value() const
    {
        return m_value;
    }

//    void Number::int_value(int new_value)
//    {
//        m_value = new_value;
//    }

    float Number::float_value() const
    {
        return m_value;
    }

//    void Number::float_value(float new_value)
//    {
//        m_value = new_value;
//    }

    // std::string Number::string_value()
    // {

    // }

    // void Number::string_value(const std::string& new_value)
    // {

    // }

    // Data* Number::index(Data* key)
    // {

    // }

    // void Number::index(Data* key, Data* new_value)
    // {

    // }

    Data* Number::add(Data* other)
    {
        return new Number(this->float_value() + other->float_value());
    }

    Data* Number::sub(Data* other)
    {
        return new Number(this->float_value() - other->float_value());
    }

    Data* Number::mul(Data* other)
    {
        return new Number(this->float_value() * other->float_value());
    }

    Data* Number::div(Data* other)
    {
        return new Number(this->float_value() / other->float_value());
    }

    Data* Number::mod(Data* other)
    {
        return new Number(this->int_value() % other->int_value());
    }

    Data* Number::exp(Data* other)
    {
        return new Number(std::pow(this->float_value(), other->float_value()));
    }

    Data* Number::unm()
    {
        return new Number(-this->float_value());
    }

    Data* Number::bit_and(Data* other)
    {
        return new Number(this->int_value() & other->int_value());
    }

    Data* Number::bit_or(Data* other)
    {
        return new Number(this->int_value() | other->int_value());
    }

    Data* Number::bit_xor(Data* other)
    {
        return new Number(this->int_value() ^ other->int_value());
    }

    Data* Number::bit_not()
    {
        return new Number(~this->int_value());
    }

    Data* Number::bit_left_shift(Data* other)
    {
        return new Number(this->int_value() << other->int_value());
    }

    Data* Number::bit_right_shift(Data* other)
    {
        return new Number(this->int_value() >> other->int_value());
    }

    int Number::cmp(Data* other)
    {
        float this_float = this->float_value();
        float other_float = other->float_value();

        if (this_float < other_float)
        {
            return -1;
        }
        else if (this_float > other_float)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}
