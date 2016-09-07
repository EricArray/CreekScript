// replace DataTypeName
// uncomment and implement requiered methods
// reimplement debug_text and value accessors as needed

#include <creek/DataTypeName.hpp>


namespace creek
{
    // `DataTypeName` constructor.
    // @param  value   DataTypeName value.
    DataTypeName::DataTypeName(Value value) : m_value(value)
    {

    }


    Data* DataTypeName::copy() const
    {
        return new DataTypeName(m_value);
    }

    std::string DataTypeName::class_name() const
    {
        return "DataTypeName";
    }

    std::string DataTypeName::debug_text() const
    {
        return std::string("DataTypeName(") + m_value + std::string(")");
    }


    // bool DataTypeName::bool_value() const
    // {
    //     return m_value;
    // }

    // void DataTypeName::bool_value(bool new_value)
    // {
    //     m_value = new_value;
    // }

    // int DataTypeName::int_value() const
    // {
    //     return m_value;
    // }

    // void DataTypeName::int_value(int new_value)
    // {
    //     m_value = new_value;
    // }

    // float DataTypeName::float_value() const
    // {
    //     return m_value;
    // }

    // void DataTypeName::float_value(float new_value)
    // {
    //     m_value = new_value;
    // }

    // std::string DataTypeName::string_value() const
    // {
    //     return m_value;
    // }

    // void DataTypeName::string_value(const std::string& new_value)
    // {
    //     m_value = new_value;
    // }


    // Data* DataTypeName::index(Data* key)
    // {

    // }

    // Data* DataTypeName::index(Data* key, Data* new_value)
    // {

    // }


    // Data* DataTypeName::add(Data* other)
    // {

    // }

    // Data* DataTypeName::sub(Data* other)
    // {

    // }

    // Data* DataTypeName::mul(Data* other)
    // {

    // }

    // Data* DataTypeName::div(Data* other)
    // {

    // }

    // Data* DataTypeName::mod(Data* other)
    // {

    // }

    // Data* DataTypeName::exp(Data* other)
    // {

    // }

    // Data* DataTypeName::min()
    // {

    // }

    // Data* DataTypeName::bit_and(Data* other)
    // {

    // }

    // Data* DataTypeName::bit_or(Data* other)
    // {

    // }

    // Data* DataTypeName::bit_xor(Data* other)
    // {

    // }

    // Data* DataTypeName::bit_not()
    // {

    // }

    // Data* DataTypeName::bit_left_shift(Data* other)
    // {

    // }

    // Data* DataTypeName::bit_right_shift(Data* other)
    // {

    // }


    // int DataTypeName::cmp(Data* other)
    // {
    //     auto this_value = this->used_value();
    //     auto other_value = other->used_value();
    //     if (this_value < other_value)
    //     {
    //         return -1;
    //     }
    //     else if (this_value > other_value)
    //     {
    //         return 1;
    //     }
    //     else 
    //     {
    //         return 0;
    //     }
    // }
}
