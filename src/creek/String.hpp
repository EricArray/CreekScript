#pragma once

#include <creek/Data.hpp>

#include <string>


namespace creek
{
    /// Data type: character string.
    class String : public Data
    {
    public:
        /// Stored value type.
        using Value = std::string;


        /// Constructor.
        /// @param  value   String value.
        String(Value value);


        Data* copy() const override;
        std::string class_name() const override;
        std::string debug_text() const override;

        bool bool_value() override;
        // void bool_value(bool new_value) override;
        // float float_value() override;
        // void float_value(float new_value) override;
        std::string string_value() override;
        void string_value(const std::string& new_value) override;

        Data* index(Data* key) override;
        Data* index(Data* key, Data* new_value) override;

        Data* add(Data* other) override;
        // Data* sub(Data* other) override;
        Data* mul(Data* other) override;
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
