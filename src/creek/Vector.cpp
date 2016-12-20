#include <creek/Vector.hpp>

#include <sstream>

#include <creek/Expression_DataTypes.hpp>
#include <creek/GlobalScope.hpp>


namespace creek
{
    // `Vector` constructor.
    // @param  value   Vector value.
    Vector::Vector(const Value& value) : m_value(value)
    {

    }

    /// @brief  Get shared value.
    const Vector::Value& Vector::value() const
    {
        return m_value;
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
        for (auto& var : *m_value)
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

    Expression* Vector::to_expression() const
    {
        std::vector<Expression*> new_values;
        for (auto& v : *m_value)
        {
            new_values.push_back(v->to_expression());
        }
        return new ExprVector(new_values);
    }


    bool Vector::bool_value(const SharedPointer<Scope>& scope) const
    {
        return true;
    }

    // Get the vector value of this data.
    std::vector<Variable>& Vector::vector_value(const SharedPointer<Scope>& scope) const
    {
        return *m_value;
    }



    Data* Vector::index(const SharedPointer<Scope>& scope, Data* key)
    {
        int pos = key->int_value(scope);
        if (pos < 0) pos = (*m_value).size() + pos;
        return (*m_value)[pos]->copy();
    }

    Data* Vector::index(const SharedPointer<Scope>& scope, Data* key, Data* new_value)
    {
        int pos = key->int_value(scope);
        if (pos < 0) pos = (*m_value).size() + pos;
        (*m_value)[pos].data(new_value->copy());
        return new_value;
    }


    int Vector::cmp(const SharedPointer<Scope>& scope, Data* other)
    {
        if (Vector* other_as_vector = dynamic_cast<Vector*>(other))
        {
            auto& this_vector = this->vector_value(scope);
            auto& other_vector = other_as_vector->vector_value(scope);

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
                    int item_cmp = this_vector[i].cmp(scope, other_vector[i]);
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
            return Data::cmp(scope, other);
        }
    }

    Data* Vector::get_class(const SharedPointer<Scope>& scope) const
    {
        return scope->global()->class_Vector->copy();
    }
}
