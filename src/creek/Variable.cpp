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

//    // Get the stored data. (const)
//    const Data* Variable::data() const
//    {
//        return m_data.get();
//    }

    // Get the stored data.
    Data* Variable::data() const
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
    Data* Variable::operator * () const
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
    Data* Variable::operator -> () const
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
        return data();// && data()->bool_value(scope);
    }


    // @name   Container index
    // @{
    // Get the data at index.
    Variable Variable::index(const SharedPointer<Scope>& scope, Variable key)
    {
        assert(data());
        assert(key.data());
        return Variable(data()->index(scope, key.data()));
    }

    // Set the data at index.
    Variable Variable::index(const SharedPointer<Scope>& scope, Variable key, Variable new_data)
    {
        assert(data());
        assert(key.data());
        assert(new_data.data());
        return Variable(data()->index(scope, key.data(), new_data.release()));
    }
    // @}


    /// @name   Object attribute
    /// @{
    /// @brief  Get the attribute.
    /// @brief  key         Attribute key.
    Variable Variable::attr(const SharedPointer<Scope>& scope, VarName key)
    {
        assert(data());
        return Variable(data()->attr(scope, key));
    }

    /// @brief  Set the attribute.
    /// @brief  key         Attribute key.
    /// @brief  new_data    New data to save in attribute.
    Variable Variable::attr(const SharedPointer<Scope>& scope, VarName key, Variable new_data)
    {
        assert(data());
        assert(new_data.data());
        return Variable(data()->attr(scope, key, new_data.release()));
    }
    /// @}


    // @name   Arithmetic operations
    // @{
    // Addition.
    Variable Variable::add(const SharedPointer<Scope>& scope, Variable& other)
    {
        assert(data());
        assert(other.data());
        return Variable(data()->add(scope, other.data()));
    }

    // Subtraction.
    Variable Variable::sub(const SharedPointer<Scope>& scope, Variable& other)
    {
        assert(data());
        assert(other.data());
        return Variable(data()->sub(scope, other.data()));
    }

    // Multiplication.
    Variable Variable::mul(const SharedPointer<Scope>& scope, Variable& other)
    {
        assert(data());
        assert(other.data());
        return Variable(data()->mul(scope, other.data()));
    }

    // Divison.
    Variable Variable::div(const SharedPointer<Scope>& scope, Variable& other)
    {
        assert(data());
        assert(other.data());
        return Variable(data()->div(scope, other.data()));
    }

    // Modulo.
    Variable Variable::mod(const SharedPointer<Scope>& scope, Variable& other)
    {
        assert(data());
        assert(other.data());
        return Variable(data()->mod(scope, other.data()));
    }

    // Exponentiation.
    Variable Variable::exp(const SharedPointer<Scope>& scope, Variable& other)
    {
        assert(data());
        assert(other.data());
        return Variable(data()->exp(scope, other.data()));
    }

    // Unary minus.
    Variable Variable::unm(const SharedPointer<Scope>& scope)
    {
        assert(data());
        return Variable(data()->unm(scope));
    }
    // @}


    // @name   Bitwise operations
    // @{
    // Bitwise and.
    Variable Variable::bit_and(const SharedPointer<Scope>& scope, Variable& other)
    {
        assert(data());
        assert(other.data());
        return Variable(data()->bit_and(scope, other.data()));
    }

    // Bitwise or.
    Variable Variable::bit_or(const SharedPointer<Scope>& scope, Variable& other)
    {
        assert(data());
        assert(other.data());
        return Variable(data()->bit_or(scope, other.data()));
    }

    // Bitwise xor.
    Variable Variable::bit_xor(const SharedPointer<Scope>& scope, Variable& other)
    {
        assert(data());
        assert(other.data());
        return Variable(data()->bit_xor(scope, other.data()));
    }

    // Bitwise not.
    Variable Variable::bit_not(const SharedPointer<Scope>& scope)
    {
        assert(data());
        return Variable(data()->bit_not(scope));
    }

    // Bitwise left shift.
    Variable Variable::bit_left_shift(const SharedPointer<Scope>& scope, Variable& other)
    {
        assert(data());
        assert(other.data());
        return Variable(data()->bit_left_shift(scope, other.data()));
    }

    // Bitwise right shift.
    Variable Variable::bit_right_shift(const SharedPointer<Scope>& scope, Variable& other)
    {
        assert(data());
        assert(other.data());
        return Variable(data()->bit_right_shift(scope, other.data()));
    }
    // @}


    // @name   Relational operations
    // Only one operation is defined.
    // @{
    // Compare less-than/equal/greater-than.
    // This special operation must return an integer.
    // @return -1 if less-than, 0 if equal, +1 if greater-than.
    int Variable::cmp(const SharedPointer<Scope>& scope, const Variable& other) const
    {
        assert(data());
        assert(other.data());
        return data()->cmp(scope, other.data());
    }
    // @}


    // // @name   Operators
    // // @{
    // // // Call equivalent data operation.
    // // VariableProxy Variable::operator [] (Variable& index)
    // // {

    // // }

    // Variable Variable::operator + (Variable& other) { return add(other); }
    // Variable Variable::operator - (Variable& other) { return sub(other); }
    // Variable Variable::operator * (Variable& other) { return mul(other); }
    // Variable Variable::operator / (Variable& other) { return div(other); }
    // Variable Variable::operator % (Variable& other) { return mod(other); }
    // // Variable Variable::operator ** (Variable& other) { return exp(other); }
    // Variable Variable::operator - ()                { return unm(); }

    // Variable Variable::operator & (Variable& other) { return bit_and(other); }
    // Variable Variable::operator | (Variable& other) { return bit_or(other); }
    // Variable Variable::operator ^ (Variable& other) { return bit_xor(other); }
    // Variable Variable::operator ~ ()                { return bit_not(); }
    // // @}
}
