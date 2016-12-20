#include <creek/Number.hpp>

#include <cmath>

#include <creek/Expression_DataTypes.hpp>
#include <creek/GlobalScope.hpp>
#include <creek/utility.hpp>


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

    Expression* Number::to_expression() const
    {
        return new ExprNumber(m_value);
    }


    bool Number::bool_value(const SharedPointer<Scope>& scope) const
    {
        return m_value > Value(0);
    }

    // void Number::bool_value(bool new_value)
    // {
        // m_value = new_value;
    // }

    int Number::int_value(const SharedPointer<Scope>& scope) const
    {
        return m_value;
    }

    // void Number::int_value(int new_value)
    // {
        // m_value = new_value;
    // }

    double Number::double_value(const SharedPointer<Scope>& scope) const
    {
        return m_value;
    }

    // void Number::float_value(float new_value)
    // {
        // m_value = new_value;
    // }

    // const std::string& Number::string_value(const SharedPointer<Scope>& scope) const
    // {
    //     return float_to_string(m_value, 10);
    // }

    // void Number::string_value(const std::string& new_value)
    // {

    // }

    // Data* Number::index(const SharedPointer<Scope>& scope, Data* key)
    // {

    // }

    // void Number::index(const SharedPointer<Scope>& scope, Data* key, Data* new_value)
    // {

    // }

    Data* Number::add(const SharedPointer<Scope>& scope, Data* other)
    {
        return new Number(this->double_value(scope) + other->double_value(scope));
    }

    Data* Number::sub(const SharedPointer<Scope>& scope, Data* other)
    {
        return new Number(this->double_value(scope) - other->double_value(scope));
    }

    Data* Number::mul(const SharedPointer<Scope>& scope, Data* other)
    {
        return new Number(this->double_value(scope) * other->double_value(scope));
    }

    Data* Number::div(const SharedPointer<Scope>& scope, Data* other)
    {
        return new Number(this->double_value(scope) / other->double_value(scope));
    }

    Data* Number::mod(const SharedPointer<Scope>& scope, Data* other)
    {
        return new Number(this->int_value(scope) % other->int_value(scope));
    }

    Data* Number::exp(const SharedPointer<Scope>& scope, Data* other)
    {
        return new Number(std::pow(this->double_value(scope), other->double_value(scope)));
    }

    Data* Number::unm(const SharedPointer<Scope>& scope)
    {
        return new Number(-this->double_value(scope));
    }

    Data* Number::bit_and(const SharedPointer<Scope>& scope, Data* other)
    {
        return new Number(this->int_value(scope) & other->int_value(scope));
    }

    Data* Number::bit_or(const SharedPointer<Scope>& scope, Data* other)
    {
        return new Number(this->int_value(scope) | other->int_value(scope));
    }

    Data* Number::bit_xor(const SharedPointer<Scope>& scope, Data* other)
    {
        return new Number(this->int_value(scope) ^ other->int_value(scope));
    }

    Data* Number::bit_not(const SharedPointer<Scope>& scope)
    {
        return new Number(~this->int_value(scope));
    }

    Data* Number::bit_left_shift(const SharedPointer<Scope>& scope, Data* other)
    {
        return new Number(this->int_value(scope) << other->int_value(scope));
    }

    Data* Number::bit_right_shift(const SharedPointer<Scope>& scope, Data* other)
    {
        return new Number(this->int_value(scope) >> other->int_value(scope));
    }

    int Number::cmp(const SharedPointer<Scope>& scope, Data* other)
    {
        float this_float = this->double_value(scope);
        float other_float = other->double_value(scope);

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

    Data* Number::get_class(const SharedPointer<Scope>& scope) const
    {
        return scope->global()->class_Number->copy();
    }
}
