#pragma once

#include <creek/Data.hpp>

#include <memory>
#include <vector>

#include <creek/api_mode.hpp>
#include <creek/Variable.hpp>


namespace creek
{
    /// Data type: dynamic array.
    class CREEK_API Vector : public Data
    {
    public:
        /// Stored value type.
        using Value = std::shared_ptr< std::vector<Variable> >;


        /// @brief  `Vector` constructor..
        /// @param  value   Vector value.
        Vector(const Value& value);


        /// @brief  Get shared value.
        const Value& value() const;


        /// Get a new reference to the same vector.
        Data* copy() const override;
        std::string class_name() const override;
        std::string debug_text() const override;
        Expression* to_expression() const override;

        bool bool_value(const SharedPointer<Scope>& scope) const override;
        // void bool_value(bool new_value) override;
        // int int_value(const SharedPointer<Scope>& scope) const override;
        // void int_value(int new_value) override;
        // double double_value(const SharedPointer<Scope>& scope) const override;
        // void float_value(float new_value) override;
        // std::string string_value(const SharedPointer<Scope>& scope) const override;
        // void string_value(const std::string& new_value) override;
        std::vector<Variable>& vector_value(const SharedPointer<Scope>& scope) const override;

        Data* index(const SharedPointer<Scope>& scope, Data* key) override;
        Data* index(const SharedPointer<Scope>& scope, Data* key, Data* new_value) override;

        // Data* add(const SharedPointer<Scope>& scope, Data* other) override;
        // Data* sub(const SharedPointer<Scope>& scope, Data* other) override;
        // Data* mul(const SharedPointer<Scope>& scope, Data* other) override;
        // Data* div(const SharedPointer<Scope>& scope, Data* other) override;
        // Data* mod(const SharedPointer<Scope>& scope, Data* other) override;
        // Data* exp(const SharedPointer<Scope>& scope, Data* other) override;
        // Data* min() override;
        // Data* bit_and(const SharedPointer<Scope>& scope, Data* other) override;
        // Data* bit_or(const SharedPointer<Scope>& scope, Data* other) override;
        // Data* bit_xor(const SharedPointer<Scope>& scope, Data* other) override;
        // Data* bit_not(const SharedPointer<Scope>& scope) override;

        int cmp(const SharedPointer<Scope>& scope, Data* other) override;

        Data* get_class(const SharedPointer<Scope>& scope) const override;

    private:
        Value m_value;
    };
}
