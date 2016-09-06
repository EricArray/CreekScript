#pragma once

#include <string>


namespace creek
{
    class Variable;


    /// Abstract class for variables' data.
    class Data
    {
    public:
        virtual ~Data() = default;

        /// Create a copy from this data.
        virtual Data* copy() const;

        /// Get data class name.
        virtual std::string class_name() const;

        /// Get debug text.
        virtual std::string debug_text() const;


        /// @name   Value access.
        /// @{
        /// Get the bool value of this data.
        virtual bool bool_value();

        /// Set the bool value of this data.
        virtual void bool_value(bool new_value);

        /// Get the float value of this data.
        virtual float float_value();

        /// Set the float value of this data.
        virtual void float_value(float new_value);

        /// Get the string value of this data.
        virtual std::string string_value();

        /// Set the string value of this data.
        virtual void string_value(const std::string& new_value);
        /// @}


        /// @name   Container index
        /// @{
        /// Get the data at index.
        virtual Data* index(Data* key);

        /// Set the data at index.
        virtual Data* index(Data* key, Data* new_data);
        /// @}


        /// @name   Arithmetic operations
        /// @{
        /// Addition.
        virtual Data* add(Data* other);

        /// Subtraction.
        virtual Data* sub(Data* other);

        /// Multiplication.
        virtual Data* mul(Data* other);

        /// Divison.
        virtual Data* div(Data* other);

        /// Modulo.
        virtual Data* mod(Data* other);

        /// Exponentiation.
        virtual Data* exp(Data* other);

        /// Unary minus.
        virtual Data* unm();
        /// @}


        /// @name   Bitwise operations
        /// @{
        /// Bitwise and.
        virtual Data* bit_and(Data* other);

        /// Bitwise or.
        virtual Data* bit_or(Data* other);

        /// Bitwise xor.
        virtual Data* bit_xor(Data* other);

        /// Bitwise not.
        virtual Data* bit_not();
        /// @}


        /// @name   Relational operations
        /// Only one operation is defined.
        /// @{
        /// Compare less-than/equal/greater-than.
        /// This special operation must return an integer.
        /// @return -1 if less-than, 0 if equal, +1 if greater-than.
        virtual int cmp(Data* other);
        /// @}
    };
}
