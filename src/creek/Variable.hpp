#pragma once

#include <memory>

#include <creek/Data.hpp>


namespace creek
{
    /// Stores a data of any type.
    /// Has shortcuts to operate with stored data.
    /// Overloads operator for operations.
    class Variable
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


        /// @name   Data access
        /// @{
        /// Get the stored data (const).
        const Data* data() const;

        /// Get the stored data.
        Data* data();

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
        /// @}


        /// @name   Data operations
        /// @{
        /// Binary operation: addition.
        Variable add(Variable& other);

        /// Binary operation: subtraction.
        Variable sub(Variable& other);

        /// Binary operation: multiplication.
        Variable mul(Variable& other);

        /// Binary operation: divison.
        Variable div(Variable& other);

        /// Binary operation: modulo.
        Variable mod(Variable& other);

        /// Binary operation: exponentiation.
        Variable exp(Variable& other);
        /// @}


        /// @name   Operators
        /// @{
        /// Call equivalent data operation.
        Variable operator + (Variable& other);
        Variable operator - (Variable& other);
        Variable operator * (Variable& other);
        Variable operator / (Variable& other);
        Variable operator % (Variable& other);
        // Variable operator ** (Variable& other); // not free operator with same precedence as pow.
        /// @}

    private:
        std::unique_ptr<Data> m_data = nullptr;
    };
}
