#include <creek/Data.hpp>

#include <creek/Exception.hpp>
#include <creek/Variable.hpp>


namespace creek
{
    Data* Data::copy() const
    {
        throw Undefined(class_name() + "::copy");
    }

    Data* Data::clone() const
    {
        return copy();
    }

    std::string Data::class_name() const
    {
        return "Data";
    }

    std::string Data::debug_text() const
    {
        throw Undefined(class_name() + "::debug_text");
    }

    /// @brief  Get an expression to duplicate this data.
    /// By default throws an exception saying this data is not const.
    Expression* Data::to_expression() const
    {
        throw Exception("Can't get expression from non-const data");
    }


    bool Data::bool_value() const
    {
        throw Undefined(class_name() + "::bool_value");
    }

    // void Data::bool_value(bool new_value)
    // {
    //     throw Undefined(class_name() + "::bool_value");
    // }

    char Data::char_value() const
    {
        throw Undefined(class_name() + "::char_value");
    }

    int Data::int_value() const
    {
        throw Undefined(class_name() + "::int_value");
    }

    // void Data::int_value(int new_value)
    // {
    //     throw Undefined(class_name() + "::int_value");
    // }

    float Data::float_value() const
    {
        throw Undefined(class_name() + "::float_value");
    }

    // void Data::float_value(float new_value)
    // {
    //     throw Undefined(class_name() + "::float_value");
    // }

    std::string Data::string_value() const
    {
        throw Undefined(class_name() + "::string_value");
    }

    // void Data::string_value(const std::string& new_value)
    // {
    //     throw Undefined(class_name() + "::string_value");
    // }

    VarName Data::identifier_value() const
    {
        throw Undefined(class_name() + "::identifier_value");
    }

    const std::vector<Variable>& Data::vector_value() const
    {
        throw Undefined(class_name() + "::vector_value");
    }

    Data* Data::index(Data* key)
    {
        throw Undefined(class_name() + "::index get");
    }

    Data* Data::index(Data* key, Data* new_data)
    {
        throw Undefined(class_name() + "::index set");
    }
    

    /// @name   Object attribute
    /// @{
    /// @brief  Get the attribute.
    Data* Data::attr(VarName key)
    {
        throw Undefined(class_name() + "::attr get");
    }

    /// @brief  Set the attribute.
    Data* Data::attr(VarName key, Data* new_data)
    {
        throw Undefined(class_name() + "::attr set");
    }
    /// @}


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

    Data* Data::unm()
    {
        throw Undefined(class_name() + "::unm");
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

    Data* Data::bit_left_shift(Data* other)
    {
        throw Undefined(class_name() + "::bit_left_shift");
    }

    Data* Data::bit_right_shift(Data* other)
    {
        throw Undefined(class_name() + "::bit_right_shift");
    }

    int Data::cmp(Data* other)
    {
        throw Undefined(class_name() + "::cmp");
    }

    Data* Data::call(std::vector< std::unique_ptr<Data> >& args)
    {
        throw Undefined(class_name() + "::call");
    }

    Data* Data::get_class()
    {
        throw Undefined(class_name() + "::get_class");
    }


    // `WrongArgNumber` constructor.
    // @param  expected    Number of expected arguments.
    // @param  passed      Number of passed arguments.
    WrongArgNumber::WrongArgNumber(int expected, int passed) :
        m_expected(expected),
        m_passed(passed)
    {
        stream() << "Wrong number of arguments: expected " << expected << ", passed " << passed;
    }
}
