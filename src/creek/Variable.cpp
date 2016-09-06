#include <creek/Variable.hpp>

#include <creek/Data.hpp>


namespace creek
{
    // `Variable` constructor.
    Variable::Variable()
    {

    }

    // `Variable` constructor.
    // @param  data        Initial data.
    Variable::Variable(Data* data) : m_data(data)
    {

    }

    // `Variable` copy constructor.
    Variable::Variable(const Variable& other) : m_data(other->copy())
    {

    }

    // `Variable` move constructor.
    Variable::Variable(Variable&& other) : m_data(other.release())
    {

    }

    // `Variable` copy operator.
    Variable& Variable::operator = (const Variable& other)
    {
        data(other->copy());
        return *this;
    }

    // `Variable` move operator.
    Variable& Variable::operator = (Variable&& other)
    {
        data(other.release());
        return *this;
    }

    // Get the stored data. (const)
    const Data* Variable::data() const
    {
        return m_data.get();
    }

    // Get the stored data.
    Data* Variable::data()
    {
        return m_data.get();
    }

    // Set the stored data.
    void Variable::data(Data* new_data)
    {
        m_data.reset(new_data);
    }

    // Get the stored data and release ownership.
    Data* Variable::release()
    {
        return m_data.release();
    }

    // Swap data with other variable.
    void Variable::swap(Variable& other)
    {
        m_data.swap(other.m_data);
    }

    // Get the soterd data (const).
    // Same as `data()`.
    const Data* Variable::operator * () const
    {
        return data();
    }

    // Get the soterd data.
    // Same as `data()`.
    Data* Variable::operator * ()
    {
        return data();
    }

    // Access stored data (const).
    const Data* Variable::operator -> () const
    {
        return data();
    }

    // Access stored data.
    Data* Variable::operator -> ()
    {
        return data();
    }


    // Binary operation: addition.
    Variable Variable::add(Variable& other)
    {
        return Variable(data()->add(other.data()));
    }

    // Binary operation: subtraction.
    Variable Variable::sub(Variable& other)
    {
        return Variable(data()->sub(other.data()));
    }

    // Binary operation: multiplication.
    Variable Variable::mul(Variable& other)
    {
        return Variable(data()->mul(other.data()));
    }

    // Binary operation: divison.
    Variable Variable::div(Variable& other)
    {
        return Variable(data()->div(other.data()));
    }

    // Binary operation: modulo.
    Variable Variable::mod(Variable& other)
    {
        return Variable(data()->mod(other.data()));
    }

    // Binary operation: exponentiation.
    Variable Variable::exp(Variable& other)
    {
        return Variable(data()->exp(other.data()));
    }

    Variable Variable::operator + (Variable& other) { return add(other); }
    Variable Variable::operator - (Variable& other) { return sub(other); }
    Variable Variable::operator * (Variable& other) { return mul(other); }
    Variable Variable::operator / (Variable& other) { return div(other); }
    Variable Variable::operator % (Variable& other) { return mod(other); }
    // Variable Variable::operator ** (Variable& other) { return exp(other); }
}
