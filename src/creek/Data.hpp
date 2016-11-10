#pragma once

#include <memory>
#include <string>
#include <vector>

#include <creek/api_mode.hpp>
#include <creek/Exception.hpp>
#include <creek/VarName.hpp>


namespace creek
{
    class Expression;
    class Variable;


    /// @brief  Abstract class for variable's data.
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
        /// @brief  Get the bool value of this data.
        virtual bool bool_value() const;

        /// @brief  Get the char value of this data.
        virtual char char_value() const;

        /// @brief  Get the int value of this data.
        virtual int int_value() const;

        /// @brief  Get the float value of this data.
        virtual float float_value() const;

        /// @brief  Get the string value of this data.
        virtual std::string string_value() const;

        /// @brief  Get the identifier value of this data.
        virtual VarName identifier_value() const;

        // @brief   Get the vector value of this data.
        virtual const std::vector<Variable>& vector_value() const;
        /// @}


        /// @name   Container index
        /// @{
        /// @brief  Get the data at index.
        /// @param  key         Index key.
        virtual Data* index(Data* key);

        /// @brief  Set the data at index.
        /// @param  key         Index key.
        /// @param  new_data    New data to save in index.
        virtual Data* index(Data* key, Data* new_data);
        /// @}


        /// @name   Object attribute
        /// @{
        /// @brief  Get the attribute.
        /// @brief  key         Attribute key.
        virtual Data* attr(VarName key);

        /// @brief  Set the attribute.
        /// @brief  key         Attribute key.
        /// @brief  new_data    New data to save in attribute.
        virtual Data* attr(VarName key, Data* new_data);
        /// @}


        /// @name   Arithmetic operations
        /// @{
        /// @brief  Addition.
        virtual Data* add(Data* other);

        /// @brief  Subtraction.
        virtual Data* sub(Data* other);

        /// @brief  Multiplication.
        virtual Data* mul(Data* other);

        /// @brief  Divison.
        virtual Data* div(Data* other);

        /// @brief  Modulo.
        virtual Data* mod(Data* other);

        /// @brief  Exponentiation.
        virtual Data* exp(Data* other);

        /// @brief  Unary minus.
        virtual Data* unm();
        /// @}


        /// @name   Bitwise operations
        /// @{
        /// @brief  Bitwise AND.
        virtual Data* bit_and(Data* other);

        /// @brief  Bitwise OR.
        virtual Data* bit_or(Data* other);

        /// @brief  Bitwise XOR.
        virtual Data* bit_xor(Data* other);

        /// @brief  Bitwise NOT.
        virtual Data* bit_not();

        /// @brief  Bitwise left shift.
        virtual Data* bit_left_shift(Data* other);

        /// @brief  Bitwise right shift.
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
        virtual Data* get_class() const;
        /// @}


        /// @brief  Call a method of this object's class.
        /// @param  method_name Name of the method to call.
        /// @param  args        Arguments.
        /// Self will be added as first argument.
        Data* call_method(
            VarName method_name,
            const std::vector<Data*>& args
        ) const;
    };


    /// Wrong number of arguments in function call.
    class CREEK_API WrongArgNumber : public Exception
    {
    public:
        /// @brief  `WrongArgNumber` constructor..
        /// @param  expected    Number of expected arguments.
        /// @param  passed      Number of passed arguments.
        WrongArgNumber(int expected, int passed);
    private:
        int m_expected;
        int m_passed;
    };
}
