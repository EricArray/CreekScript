#pragma once

#include <creek/Data.hpp>

#include <creek/api_mode.hpp>


namespace creek
{
    /// @brief  Data type: Null pointer.
    class CREEK_API Null : public Data
    {
    public:
        /// @brief  `Null` Constructor.
        Null();


        Data* copy() const override;
        std::string class_name() const override;
        std::string debug_text() const override;

        bool bool_value() const override;
        int int_value() const override;
        float float_value() const override;
        std::string string_value() const override;

        int cmp(Data* other) override;
        
        Data* get_class() override;
    };
}