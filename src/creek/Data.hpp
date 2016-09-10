#pragma once

#include <memory>
#include <string>
#include <vector>


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
        /// Should be same as or more specific than `string_value`.
        virtual std::string debug_text() const;


        /// @name   Value access
        /// @{
        /// Get the bool value of this data.
        virtual bool bool_value() const;

        // /// Set the bool value of this data.
        // virtual void bool_value(bool new_value);

        /// Get the int value of this data.
        virtual int int_value() const;

        // /// Set the int value of this data.
        // virtual void int_value(int new_value);

        /// Get the float value of this data.
        virtual float float_value() const;

        // /// Set the float value of this data.
        // virtual void float_value(float new_value);

        /// Get the string value of this data.
        virtual std::string string_value() const;

        // /// Set the string value of this data.
        // virtual void string_value(const std::string& new_value);
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
        /// Bitwise AND.
        virtual Data* bit_and(Data* other);

        /// Bitwise OR.
        virtual Data* bit_or(Data* other);

        /// Bitwise XOR.
        virtual Data* bit_xor(Data* other);

        /// Bitwise NOT.
        virtual Data* bit_not();

        /// Bitwise left shift.
        virtual Data* bit_left_shift(Data* other);

        /// Bitwise right shift.
        virtual Data* bit_right_shift(Data* other);
        /// @}


        /// @name   Relational operations
        /// Only one operation is defined.
        /// @{
        /// Compare less-than/equal/greater-than.
        /// This special operation must return an integer.
        /// @return -1 if less-than, 0 if equal, +1 if greater-than.
        virtual int cmp(Data* other);
        /// @}


        /// @name   Functional
        /// @{
        /// Call this object as a function.
        /// @param  args    Arguments.
        /// @return         Value returned from this function.
        virtual Data* call(const std::vector< std::unique_ptr<Data> >& args);
        /// @}
    };
}
