#pragma once

#include <creek/Data.hpp>

#include <vector>
#include <memory>

#include <creek/api_mode.hpp>
#include <creek/Exception.hpp>
#include <creek/VarName.hpp>


namespace creek
{
    class Scope;
    class Expression;


    /// Data type: function.
    class CREEK_API Function : public Data
    {
    public:
        /// Shared function definition.
        struct Definition
        {
            Definition(Scope& parent, const std::vector<VarName>& arg_names,
                       bool is_variadic, const std::shared_ptr<Expression>& body) :
                parent(parent),
                arg_names(arg_names),
                is_variadic(is_variadic),
                body(body)
            {
                if (is_variadic && arg_names.size() == 0)
                {
                    this->arg_names.push_back(VarName::from_name("_"));
                }
            }

            Scope& parent; ///< Scope where the function was declared.
            std::vector<VarName> arg_names; ///< Arguments name.
            bool is_variadic; ///< Is variadic function.
            std::shared_ptr<Expression> body; ///< Function body block.
        };

        /// Stored value type.
        using Value = std::shared_ptr<Definition>;


        /// `Function` constructor.
        /// @param  value   Function value.
        Function(const Value& value);


        Data* copy() const override;
        std::string class_name() const override;
        std::string debug_text() const override;
        Expression* to_expression() const override;

        bool bool_value() const override;
        // void bool_value(bool new_value) override;
        // int int_value() const override;
        // void int_value(int new_value) override;
        // float float_value() const override;
        // void float_value(float new_value) override;
        // std::string string_value() const override;
        // void string_value(const std::string& new_value) override;

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

        Data* call(std::vector< std::unique_ptr<Data> >& args) override;


    private:
        Value m_value;
    };
}
