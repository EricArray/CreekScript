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
        /// @brief  `Variable` constructor..
        Variable();

        /// @brief  `Variable` constructor..
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
//        /// Get the stored data (const).
//        const Data* data() const;

        /// Set the stored data.
        /// The older data is deleted.
        void data(Data* new_data);

        /// Set the stored data.
        /// The older data is deleted.
        void reset(Data* new_data);

        /// Get the stored data and release ownership.
        Data* release();

        /// Swap data with other variable.
        void swap(Variable& other);

        /// Get the soterd data (const).
        /// Same as `data()`.
        Data* operator * () const;

        /// Get the soterd data.
        /// Same as `data()`.
        Data* operator * ();

        /// Access stored data (const).
        Data* operator -> () const;

        /// Access stored data.
        Data* operator -> ();

        /// Check if not null.
        operator bool () const;
        /// @}


        /// @name   Container index
        /// @{
        /// Get the data at index.
        Variable index(const SharedPointer<Scope>& scope, Variable key);

        /// Set the data at index.
        Variable index(const SharedPointer<Scope>& scope, Variable key, Variable new_data);
        /// @}


        /// @name   Object attribute
        /// @{
        /// @brief  Get the attribute.
        /// @brief  key         Attribute key.
        Variable attr(const SharedPointer<Scope>& scope, VarName key);

        /// @brief  Set the attribute.
        /// @brief  key         Attribute key.
        /// @brief  new_data    New data to save in attribute.
        Variable attr(const SharedPointer<Scope>& scope, VarName key, Variable new_data);
        /// @}


        /// @name   Arithmetic operations
        /// @{
        /// Addition.
        Variable add(const SharedPointer<Scope>& scope, Variable& other);

        /// Subtraction.
        Variable sub(const SharedPointer<Scope>& scope, Variable& other);

        /// Multiplication.
        Variable mul(const SharedPointer<Scope>& scope, Variable& other);

        /// Divison.
        Variable div(const SharedPointer<Scope>& scope, Variable& other);

        /// Modulo.
        Variable mod(const SharedPointer<Scope>& scope, Variable& other);

        /// Exponentiation.
        Variable exp(const SharedPointer<Scope>& scope, Variable& other);

        /// Unary minus.
        Variable unm(const SharedPointer<Scope>& scope);
        /// @}


        /// @name   Bitwise operations
        /// @{
        /// Bitwise and.
        Variable bit_and(const SharedPointer<Scope>& scope, Variable& other);

        /// Bitwise or.
        Variable bit_or(const SharedPointer<Scope>& scope, Variable& other);

        /// Bitwise xor.
        Variable bit_xor(const SharedPointer<Scope>& scope, Variable& other);

        /// Bitwise not.
        Variable bit_not(const SharedPointer<Scope>& scope);

        /// Bitwise left shift.
        Variable bit_left_shift(const SharedPointer<Scope>& scope, Variable& other);

        /// Bitwise right shift.
        Variable bit_right_shift(const SharedPointer<Scope>& scope, Variable& other);
        /// @}


        /// @name   Relational operations
        /// Only one operation is defined.
        /// @{
        /// Compare less-than/equal/greater-than.
        /// This special operation must return an integer.
        /// @return -1 if less-than, 0 if equal, +1 if greater-than.
        int cmp(const SharedPointer<Scope>& scope, const Variable& other) const;
        /// @}


        // /// @name   Operators
        // /// @{
        // /// Call equivalent data operation.
        // // ProxyVariable operator [] (Variable& index);

        // Variable operator + (Variable& other);
        // Variable operator - (Variable& other);
        // Variable operator * (Variable& other);
        // Variable operator / (Variable& other);
        // Variable operator % (Variable& other);
        // // Variable operator ** (Variable& other); // not free operator with same precedence as pow.
        // Variable operator - ();

        // Variable operator & (Variable& other);
        // Variable operator | (Variable& other);
        // Variable operator ^ (Variable& other);
        // Variable operator ~ ();
        // /// @}

    private:
        /// Get the stored data.
        Data* data() const;

        std::unique_ptr<Data> m_data = nullptr;
    };
}
