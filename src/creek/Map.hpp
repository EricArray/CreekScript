#pragma once

#include <creek/Data.hpp>

#include <memory>
#include <map>

#include <creek/api_mode.hpp>
#include <creek/Object.hpp>
#include <creek/Variable.hpp>


namespace creek
{
    /// Data type: Associative container.
    class CREEK_API Map : public Data
    {
    public:
        /// @brief  Map key.
        struct Key {
            Key(const SharedPointer<Scope>& scope, Data* key) : class_num(0), scope(scope), key(key) {
                if (key) {
                    Variable v = key->get_class(scope);
                    if (auto o = dynamic_cast<Object*>(*v))
                    {
                        class_num = reinterpret_cast<uintptr_t>(o->value().get());
                    }
                }
            }

            bool operator < (const Key& other) const {
                if (class_num == other.class_num) {
                    return key.cmp(scope, other.key) < 0;
                } else {
                    return class_num < other.class_num;
                }
            }

            Data* operator -> () const { return *key; }

            uintptr_t class_num; ///< Identifier for class of key.
            SharedPointer<Scope> scope; ///< Scope.
            Variable key; ///< Key.
        };

        /// @brief  Map shared definition.
        using Definition = std::map<Key, Variable>;

        /// @brief  Stored value type.
        using Value = std::shared_ptr<Definition>;


        /// @brief  `Map` constructor..
        /// @param  value   Map value.
        Map(const Value& value);


        /// @brief  Get shared value.
        const Value& value() const;


        /// @brief  Get a new reference to the same vector.
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
        // std::vector<Variable>& vector_value(const SharedPointer<Scope>& scope) const override;

        Data* index(const SharedPointer<Scope>& scope, Data* key) override;
        Data* index(const SharedPointer<Scope>& scope, Data* key, Data* new_value) override;

        Data* attr(const SharedPointer<Scope>& scope, VarName key) override;
        Data* attr(const SharedPointer<Scope>& scope, VarName key, Data* new_value) override;

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

        // int cmp(const SharedPointer<Scope>& scope, Data* other) override;

        Data* get_class(const SharedPointer<Scope>& scope) const override;

    private:
        Value m_value;
    };
}
