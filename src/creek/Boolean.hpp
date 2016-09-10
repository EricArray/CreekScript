#pragma once

#include <creek/Data.hpp>


namespace creek
{
    /// Data type: boolean.
    class Boolean : public Data
    {
    public:
        /// Stored value type.
        using Value = bool;


        /// Constructor.
        /// @param  value   String value.
        Boolean(Value value);


        Data* copy() const override;
        std::string class_name() const override;
        std::string debug_text() const override;

        bool bool_value() const override;
//        void bool_value(bool new_value) override;
        int int_value() const override;
//        void int_value(int new_value) override;
        float float_value() const override;
//        void float_value(float new_value) override;
        std::string string_value() const override;
//        void string_value(const std::string& new_value) override;

        // Data* index(Data* key) override;
        // Data* index(Data* key, Data* new_value) override;

        // Data* add(Data* other) override;
        // Data* sub(Data* other) override;
        // Data* mul(Data* other) override;
        // Data* div(Data* other) override;
        // Data* mod(Data* other) override;
        // Data* exp(Data* other) override;
        // Data* min() override;
        // Data* bit_and(Data* other) override;
        // Data* bit_or(Data* other) override;
        // Data* bit_xor(Data* other) override;
        // Data* bit_not() override;
        int cmp(Data* other) override;


    private:
        Value m_value;
    };
}
