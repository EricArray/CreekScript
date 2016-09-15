#include <creek/Vector.hpp>

#include <sstream>


namespace creek
{
    // `Vector` constructor.
    // @param  value   Vector value.
    Vector::Vector(const Value& value) : m_value(value)
    {

    }


    Data* Vector::copy() const
    {
        return new Vector(m_value);
    }

    std::string Vector::class_name() const
    {
        return "Vector";
    }

    std::string Vector::debug_text() const
    {
        // return "[" + each item debug text + "]"
        std::stringstream stream;
        stream << "[";
        bool i = 0;
        for (auto& var : vector_value())
        {
            if (i > 0)
            {
                stream << ", ";
            }
            stream << var->debug_text();
            i += 1;
        }
        stream << "]";
        return stream.str();
    }


    bool Vector::bool_value() const
    {
        return true;
    }

    // void Vector::bool_value(bool new_value)
    // {
    //     m_value = new_value;
    // }

    // int Vector::int_value() const
    // {
    //     return m_value;
    // }

    // void Vector::int_value(int new_value)
    // {
    //     m_value = new_value;
    // }

    // float Vector::float_value() const
    // {
    //     return m_value;
    // }

    // void Vector::float_value(float new_value)
    // {
    //     m_value = new_value;
    // }

    // std::string Vector::string_value() const
    // {
    //     return m_value;
    // }

    // void Vector::string_value(const std::string& new_value)
    // {
    //     m_value = new_value;
    // }

    // Get the vector value of this data.
    std::vector<Variable>& Vector::vector_value() const
    {
        return *m_value;
    }



    Data* Vector::index(Data* key)
    {
        int pos = key->int_value();
        if (pos < 0) pos = vector_value().size() + pos;
        return vector_value()[pos]->copy();
    }

    Data* Vector::index(Data* key, Data* new_value)
    {
        int pos = key->int_value();
        if (pos < 0) pos = vector_value().size() + pos;
        vector_value()[pos].data(new_value->copy());
        return new_value;
    }


    // Data* Vector::add(Data* other)
    // {

    // }

    // Data* Vector::sub(Data* other)
    // {

    // }

    // Data* Vector::mul(Data* other)
    // {

    // }

    // Data* Vector::div(Data* other)
    // {

    // }

    // Data* Vector::mod(Data* other)
    // {

    // }

    // Data* Vector::exp(Data* other)
    // {

    // }

    // Data* Vector::min()
    // {

    // }

    // Data* Vector::bit_and(Data* other)
    // {

    // }

    // Data* Vector::bit_or(Data* other)
    // {

    // }

    // Data* Vector::bit_xor(Data* other)
    // {

    // }

    // Data* Vector::bit_not()
    // {

    // }


    int Vector::cmp(Data* other)
    {
        if (Vector* other_as_vector = dynamic_cast<Vector*>(other))
        {
            auto& this_vector = this->vector_value();
            auto& other_vector = other_as_vector->vector_value();

            size_t i = 0;
            while (true)
            {
                bool this_end = this_vector.size() <= i;
                bool other_end = other_vector.size() <= i;
                if (this_end || other_end)
                {
                    // -1 if this end, 1 if other end, 0 if both
                    return (this_end ? -1 : 0) + (other_end ? 1 : 0);
                }
                else
                {
                    // compare items
                    int item_cmp = this_vector[i].cmp(other_vector[i]);
                    if (item_cmp != 0)
                    {
                        return item_cmp;
                    }
                }

                i += 1;
            }
        }
        else
        {
            return Data::cmp(other);
        }
    }
}
