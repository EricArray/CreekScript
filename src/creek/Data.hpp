#pragma once

#include <memory>
#include <string>
#include <vector>

#include <creek/api_mode.hpp>
#include <creek/Exception.hpp>


namespace creek
{
    class Expression;
    class Variable;


    /// Abstract class for variables' data.
    class CREEK_API Data
    {
    public:
        virtual ~Data() = default;

        /// @brief  Create a copy of this data.
        virtual Data* copy() const;

        /// @brief  Create a shallow copy of this data.
        /// By default, calls `copy`.
        virtual Data* clone() const;

        /// @brief  Get data class name.
        virtual std::string class_name() const;

        /// @brief  Get debug text.
        /// Should be same as or more specific than `string_value`.
        virtual std::string debug_text() const;

        /// @brief  Get an expression to duplicate this data.
        /// By default throws an exception saying this data is not const.
        virtual Expression* to_expression() const;


        /// @name   Value access
        /// @{
        /// Get the bool value of this data.
        virtual bool bool_value() const;

        /// Get the char value of this data.
        virtual char char_value() const;

        /// Get the int value of this data.
        virtual int int_value() const;

        /// Get the float value of this data.
        virtual float float_value() const;

        /// Get the string value of this data.
        virtual std::string string_value() const;

        // Get the vector value of this data.
        virtual const std::vector<Variable>& vector_value() const;
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
        virtual Data* call(std::vector< std::unique_ptr<Data> >& args);
        /// @}


        /// @name   OOP
        /// @{
        /// @brief  Get the class of this object.
        /// @return A new reference.
        virtual Data* get_class();
        /// @}
    };


    /// Wrong number of arguments in function call.
    class CREEK_API WrongArgNumber : public Exception
    {
    public:
        /// `WrongArgNumber` constructor.
        /// @param  expected    Number of expected arguments.
        /// @param  passed      Number of passed arguments.
        WrongArgNumber(int expected, int passed);
    private:
        int m_expected;
        int m_passed;
    };
}
