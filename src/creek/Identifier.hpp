#pragma once

#include <creek/Data.hpp>

#include <creek/api_mode.hpp>
#include <creek/VarName.hpp>


namespace creek
{
    /// Data type: variable names.
    class CREEK_API Identifier : public Data
    {
    public:
        /// Stored value type.
        using Value = VarName;


        /// @brief  `Identifier` constructor..
        /// @param  var_name    Variable name.
        Identifier(Value value);

        /// Create a copy from this data.
        Data* copy() const override;

        /// Get data class name.
        std::string class_name() const override;

        /// Get debug text.
        std::string debug_text() const override;

        Expression* to_expression() const override;


        /// @name   Value access.
        /// @{
        /// Get the bool value of this data.
        bool bool_value(const SharedPointer<Scope>& scope) const override;

        // /// Set the bool value of this data.
        // void bool_value(bool new_value) override;

        /// Get the int value of this data.
        int int_value(const SharedPointer<Scope>& scope) const override;

        // /// Set the int value of this data.
        // void int_value(int new_value) override;

        /// Get the float value of this data.
        double double_value(const SharedPointer<Scope>& scope) const override;

        // /// Set the float value of this data.
        // void float_value(float new_value) override;

        /// Get the string value of this data.
        const std::string& string_value(const SharedPointer<Scope>& scope) const override;

        // /// Set the string value of this data.
        // void string_value(const std::string& new_value) override;

        /// Get the identifier value of this data.
        VarName identifier_value(const SharedPointer<Scope>& scope) const override;
        /// @}


        // /// @name   Container index
        // /// @{
        // /// Get the data at index.
        // Data* index(const SharedPointer<Scope>& scope, Data* key) override;

        // /// Set the data at index.
        // Data* index(Data* key, Data* new_data) override;
        // /// @}


        // /// @name   Arithmetic operations
        // /// @{
        // /// Addition.
        // Data* add(const SharedPointer<Scope>& scope, Data* other) override;

        // /// Subtraction.
        // Data* sub(const SharedPointer<Scope>& scope, Data* other) override;

        // /// Multiplication.
        // Data* mul(const SharedPointer<Scope>& scope, Data* other) override;

        // /// Divison.
        // Data* div(const SharedPointer<Scope>& scope, Data* other) override;

        // /// Modulo.
        // Data* mod(const SharedPointer<Scope>& scope, Data* other) override;

        // /// Exponentiation.
        // Data* exp(const SharedPointer<Scope>& scope, Data* other) override;

        // /// Unary minus.
        // Data* unm(const SharedPointer<Scope>& scope) override;
        // /// @}


        // /// @name   Bitwise operations
        // /// @{
        // /// Bitwise and.
        // Data* bit_and(const SharedPointer<Scope>& scope, Data* other) override;

        // /// Bitwise or.
        // Data* bit_or(const SharedPointer<Scope>& scope, Data* other) override;

        // /// Bitwise xor.
        // Data* bit_xor(const SharedPointer<Scope>& scope, Data* other) override;

        // /// Bitwise not.
        // Data* bit_not(const SharedPointer<Scope>& scope) override;
        // /// @}


        /// @name   Relational operations
        /// Only one operation is defined.
        /// @{
        /// Compare less-than/equal/greater-than.
        /// This special operation must return an integer.
        /// @return -1 if less-than, 0 if equal, +1 if greater-than.
        int cmp(const SharedPointer<Scope>& scope, Data* other) override;
        /// @}

        Data* get_class(const SharedPointer<Scope>& scope) const override;

    private:
        Value m_value;
    };
}
