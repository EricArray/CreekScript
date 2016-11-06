#include <creek/Identifier.hpp>

#include <creek/Expression_DataTypes.hpp>
#include <creek/GlobalScope.hpp>

namespace creek
{
    // `Identifier` constructor.
    // @param  value        Identifier value.
    Identifier::Identifier(Value value) : m_value(value)
    {

    }

    // Create a copy from this data.
    Data* Identifier::copy() const
    {
        return new Identifier(m_value);
    }

    // Get data class name.
    std::string Identifier::class_name() const
    {
        return "Identifier";
    }

    // Get debug text.
    std::string Identifier::debug_text() const
    {
        return std::string("@") + this->string_value();
    }

    Expression* Identifier::to_expression() const
    {
        return new ExprIdentifier(m_value);
    }


    // @name   Value access.
    // @{
    // Get the bool value of this data.
    bool Identifier::bool_value() const
    {
        return true;
    }

    // // Set the bool value of this data.
    // void bool_value(bool new_value);

    // Get the int value of this data.
    int Identifier::int_value() const
    {
        return m_value.id();
    }

    // // Set the int value of this data.
    // void Identifier::int_value(int new_value);

    // Get the float value of this data.
    float Identifier::float_value() const
    {
        return m_value.id();
    }

    // // Set the float value of this data.
    // void Identifier::float_value(float new_value);

    // Get the string value of this data.
    std::string Identifier::string_value() const
    {
        return m_value.name();
    }

    // // Set the string value of this data.
    // void Identifier::string_value(const std::string& new_value);
    // @}


    // @name   Relational operations
    // Only one operation is defined.
    // @{
    // Compare less-than/equal/greater-than.
    // This special operation must return an integer.
    // @return -1 if less-than, 0 if equal, +1 if greater-than.
    int Identifier::cmp(Data* other)
    {
        int this_int = this->int_value();
        int other_int = other->int_value();

        if (this_int < other_int)
        {
            return -1;
        }
        else if (this_int > other_int)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    // @}

    Data* Identifier::get_class()
    {
        return GlobalScope::class_Identifier->copy();
    }
}
