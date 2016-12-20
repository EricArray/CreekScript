#pragma once

#include <creek/Data.hpp>

#include <vector>
#include <memory>

#include <creek/api_mode.hpp>
#include <creek/Exception.hpp>
#include <creek/Scope.hpp>
#include <creek/VarName.hpp>


namespace creek
{
    class Expression;


    /// Data type: function.
    class CREEK_API Function : public Data
    {
    public:
        /// Shared function definition.
        struct Definition
        {
            Definition(const SharedPointer<Scope>& parent, const std::vector<VarName>& arg_names,
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

            SharedPointer<Scope> parent; ///< Scope where the function was declared.
            std::vector<VarName> arg_names; ///< Arguments name.
            bool is_variadic; ///< Is variadic function.
            std::shared_ptr<Expression> body; ///< Function body block.
        };

        /// Stored value type.
        using Value = std::shared_ptr<Definition>;


        /// @brief  `Function` constructor..
        /// @param  value   Function value.
        Function(const Value& value);


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

        // Data* index(const SharedPointer<Scope>& scope, Data* key) override;
        // Data* index(const SharedPointer<Scope>& scope, Data* key, Data* new_value) override;

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

        Data* call(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args) override;


    private:
        Value m_value;
    };
}
