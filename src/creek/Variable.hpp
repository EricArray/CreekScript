#pragma once

#include <memory>

#include <creek/api_mode.hpp>
#include <creek/Data.hpp>


namespace creek
{
    /// Stores a data of any type.
    /// Has shortcuts to operate with stored data.
    /// Overloads operator for operations.
    class CREEK_API Variable
    {
    public:
        /// `Variable` constructor.
        Variable();

        /// `Variable` constructor.
        /// @param  data        Initial data.
        Variable(Data* data);

        /// `Variable` copy constructor.
        Variable(const Variable& other);

        /// `Variable` move constructor.
        Variable(Variable&& other);

        /// `Variable` copy operator.
        Variable& operator = (const Variable& other);

        /// `Variable` move operator.
        Variable& operator = (Variable&& other);

        /// `Variable` destructor.
        ~Variable();


        /// @name   Data access
        /// @{
        /// Get the stored data (const).
        const Data* data() const;

        /// Set the stored data.
        void data(Data* new_data);

        /// Get the stored data and release ownership.
        Data* release();

        /// Swap data with other variable.
        void swap(Variable& other);

        /// Get the soterd data (const).
        /// Same as `data()`.
        const Data* operator * () const;

        /// Get the soterd data.
        /// Same as `data()`.
        Data* operator * ();

        /// Access stored data (const).
        const Data* operator -> () const;

        /// Access stored data.
        Data* operator -> ();

        /// Check if not null.
        operator bool () const;
        /// @}


        /// @name   Container index
        /// @{
        /// Get the data at index.
        Variable index(Variable key);

        /// Set the data at index.
        Variable index(Variable key, Variable new_data);
        /// @}


        /// @name   Arithmetic operations
        /// @{
        /// Addition.
        Variable add(Variable& other);

        /// Subtraction.
        Variable sub(Variable& other);

        /// Multiplication.
        Variable mul(Variable& other);

        /// Divison.
        Variable div(Variable& other);

        /// Modulo.
        Variable mod(Variable& other);

        /// Exponentiation.
        Variable exp(Variable& other);

        /// Unary minus.
        Variable unm();
        /// @}


        /// @name   Bitwise operations
        /// @{
        /// Bitwise and.
        Variable bit_and(Variable& other);

        /// Bitwise or.
        Variable bit_or(Variable& other);

        /// Bitwise xor.
        Variable bit_xor(Variable& other);

        /// Bitwise not.
        Variable bit_not();

        /// Bitwise left shift.
        Variable bit_left_shift(Variable& other);

        /// Bitwise right shift.
        Variable bit_right_shift(Variable& other);
        /// @}


        /// @name   Relational operations
        /// Only one operation is defined.
        /// @{
        /// Compare less-than/equal/greater-than.
        /// This special operation must return an integer.
        /// @return -1 if less-than, 0 if equal, +1 if greater-than.
        int cmp(Variable& other);
        /// @}


        /// @name   Operators
        /// @{
        /// Call equivalent data operation.
        // ProxyVariable operator [] (Variable& index);

        Variable operator + (Variable& other);
        Variable operator - (Variable& other);
        Variable operator * (Variable& other);
        Variable operator / (Variable& other);
        Variable operator % (Variable& other);
        // Variable operator ** (Variable& other); // not free operator with same precedence as pow.
        Variable operator - ();

        Variable operator & (Variable& other);
        Variable operator | (Variable& other);
        Variable operator ^ (Variable& other);
        Variable operator ~ ();
        /// @}

    private:
        /// Get the stored data.
        Data* data();

        std::unique_ptr<Data> m_data = nullptr;
    };
}
