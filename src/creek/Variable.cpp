#include <creek/Variable.hpp>

#include <creek/Data.hpp>
#include <creek/utility.hpp>


namespace creek
{
    // `Variable` constructor.
    Variable::Variable() : m_data(nullptr)
    {

    }

    // `Variable` destructor.
    Variable::~Variable()
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

    // Set the stored data.
    void Variable::reset(Data* new_data)
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
        assert(data());
        return data();
    }

    // Access stored data.
    Data* Variable::operator -> ()
    {
        assert(data());
        return data();
    }

    Variable::operator bool () const
    {
        return data() && data()->bool_value();
    }


    // @name   Container index
    // @{
    // Get the data at index.
    Variable Variable::index(Variable key)
    {
        assert(data());
        assert(key.data());
        return Variable(data()->index(key.data()));
    }

    // Set the data at index.
    Variable Variable::index(Variable key, Variable new_data)
    {
        assert(data());
        assert(key.data());
        assert(new_data.data());
        return Variable(data()->index(key.data(), new_data.release()));
    }
    // @}


    /// @name   Object attribute
    /// @{
    /// @brief  Get the attribute.
    /// @brief  key         Attribute key.
    Variable Variable::attr(VarName key)
    {
        assert(data());
        return Variable(data()->attr(key));
    }

    /// @brief  Set the attribute.
    /// @brief  key         Attribute key.
    /// @brief  new_data    New data to save in attribute.
    Variable Variable::attr(VarName key, Variable new_data)
    {
        assert(data());
        assert(new_data.data());
        return Variable(data()->attr(key, new_data.release()));
    }
    /// @}


    // @name   Arithmetic operations
    // @{
    // Addition.
    Variable Variable::add(Variable& other)
    {
        assert(data());
        assert(other.data());
        return Variable(data()->add(other.data()));
    }

    // Subtraction.
    Variable Variable::sub(Variable& other)
    {
        assert(data());
        assert(other.data());
        return Variable(data()->sub(other.data()));
    }

    // Multiplication.
    Variable Variable::mul(Variable& other)
    {
        assert(data());
        assert(other.data());
        return Variable(data()->mul(other.data()));
    }

    // Divison.
    Variable Variable::div(Variable& other)
    {
        assert(data());
        assert(other.data());
        return Variable(data()->div(other.data()));
    }

    // Modulo.
    Variable Variable::mod(Variable& other)
    {
        assert(data());
        assert(other.data());
        return Variable(data()->mod(other.data()));
    }

    // Exponentiation.
    Variable Variable::exp(Variable& other)
    {
        assert(data());
        assert(other.data());
        return Variable(data()->exp(other.data()));
    }

    // Unary minus.
    Variable Variable::unm()
    {
        assert(data());
        return Variable(data()->unm());
    }
    // @}


    // @name   Bitwise operations
    // @{
    // Bitwise and.
    Variable Variable::bit_and(Variable& other)
    {
        assert(data());
        assert(other.data());
        return Variable(data()->bit_and(other.data()));
    }

    // Bitwise or.
    Variable Variable::bit_or(Variable& other)
    {
        assert(data());
        assert(other.data());
        return Variable(data()->bit_or(other.data()));
    }

    // Bitwise xor.
    Variable Variable::bit_xor(Variable& other)
    {
        assert(data());
        assert(other.data());
        return Variable(data()->bit_xor(other.data()));
    }

    // Bitwise not.
    Variable Variable::bit_not()
    {
        assert(data());
        return Variable(data()->bit_not());
    }

    // Bitwise left shift.
    Variable Variable::bit_left_shift(Variable& other)
    {
        assert(data());
        assert(other.data());
        return Variable(data()->bit_left_shift(other.data()));
    }

    // Bitwise right shift.
    Variable Variable::bit_right_shift(Variable& other)
    {
        assert(data());
        assert(other.data());
        return Variable(data()->bit_right_shift(other.data()));
    }
    // @}


    // @name   Relational operations
    // Only one operation is defined.
    // @{
    // Compare less-than/equal/greater-than.
    // This special operation must return an integer.
    // @return -1 if less-than, 0 if equal, +1 if greater-than.
    int Variable::cmp(Variable& other)
    {
        assert(data());
        assert(other.data());
        return data()->cmp(other.data());
    }
    // @}


    // @name   Operators
    // @{
    // // Call equivalent data operation.
    // VariableProxy Variable::operator [] (Variable& index)
    // {

    // }

    Variable Variable::operator + (Variable& other) { return add(other); }
    Variable Variable::operator - (Variable& other) { return sub(other); }
    Variable Variable::operator * (Variable& other) { return mul(other); }
    Variable Variable::operator / (Variable& other) { return div(other); }
    Variable Variable::operator % (Variable& other) { return mod(other); }
    // Variable Variable::operator ** (Variable& other) { return exp(other); }
    Variable Variable::operator - ()                { return unm(); }

    Variable Variable::operator & (Variable& other) { return bit_and(other); }
    Variable Variable::operator | (Variable& other) { return bit_or(other); }
    Variable Variable::operator ^ (Variable& other) { return bit_xor(other); }
    Variable Variable::operator ~ ()                { return bit_not(); }
    // @}
}
