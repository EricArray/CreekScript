#pragma once

#include <creek/Data.hpp>

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <creek/api_mode.hpp>
#include <creek/Exception.hpp>
#include <creek/Variable.hpp>
#include <creek/VarName.hpp>


namespace creek
{
    /// Data type: dynamic object (reference).
    class CREEK_API Object : public Data
    {
    public:
        /// @brief  Shared object definition.
        struct Definition
        {
            /// @brief  Type alias: attribute list.
            // using AttrList = std::vector< std::tuple<Variable, Variable> >;
            using AttrList = std::map<VarName, Variable>;

            Definition(Data* class_obj, const AttrList& attrs) :
                class_obj(class_obj)
//                attrs(attrs)
            {
                for (auto& attr : attrs)
                {
                    this->attrs[attr.first] = attr.second->copy();
                }
            }

            Variable class_obj; ///< Class object.
            AttrList attrs; ///< Object attributes.
        };

        /// @brief  Stored value type.
        using Value = std::shared_ptr<Definition>;


        /// @brief  `Object` constructor..
        /// @param  value   Object value.
        Object(const Value& value);

        /// @brief  `Object` constructor..
        /// @param  class_obj   Class object.
        /// @param  attrs       Object attributes.
        Object(Data* class_obj, const Definition::AttrList& attrs);

        /// @brief  Make a new `Object`.
        /// @param  class_obj   Class object.
        /// @param  attrs       Object attributes by name.
        static Object* make(Data* class_obj, const std::map<VarName, Variable>& attrs);


        /// @brief  Get shared value.
        Value& value();


        /// @brief  Get a reference to the same object.
        Data* copy() const override;

        /// @brief  Get a reference to a shallow copy of this object.
        Data* clone() const override;

        /// @brief  Get data class name.
        std::string class_name() const override;

        /// @brief  Get debug text.
        std::string debug_text() const override;


        /// @name   Value access
        /// @{
        /// @brief  Get the bool value of this data.
        bool bool_value() const override;

        /// @brief  Get the char value of this data.
        char char_value() const override;

        /// @brief  Get the int value of this data.
        int int_value() const override;

        /// @brief  Get the float value of this data.
        float float_value() const override;

        /// @brief  Get the string value of this data.
        std::string string_value() const override;

        /// @brief  Get the vector value of this data.
        const std::vector<Variable>& vector_value() const override;
        /// @}


        /// @name   Container index
        /// @{
        /// @brief  Get the data at index.
        Data* index(Data* key) override;

        /// @brief  Set the data at index.
        Data* index(Data* key, Data* new_data) override;
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
        Data* add(Data* other) override;

        /// @brief  Subtraction.
        Data* sub(Data* other) override;

        /// @brief  Multiplication.
        Data* mul(Data* other) override;

        /// @brief  Divison.
        Data* div(Data* other) override;

        /// @brief  Modulo.
        Data* mod(Data* other) override;

        /// @brief  Exponentiation.
        Data* exp(Data* other) override;

        /// @brief  Unary minus.
        Data* unm() override;
        /// @}


        /// @name   Bitwise operations
        /// @{
        /// @brief  Bitwise AND.
        Data* bit_and(Data* other) override;

        /// @brief  Bitwise OR.
        Data* bit_or(Data* other) override;

        /// @brief  Bitwise XOR.
        Data* bit_xor(Data* other) override;

        /// @brief  Bitwise NOT.
        Data* bit_not() override;

        /// @brief  Bitwise left shift.
        Data* bit_left_shift(Data* other) override;

        /// @brief  Bitwise right shift.
        Data* bit_right_shift(Data* other) override;
        /// @}


        /// @name   Relational operations
        /// Only one operation is defined.
        /// @{
        /// @brief  Compare less-than/equal/greater-than.
        /// This special operation must return an integer.
        /// @return -1 if less-than, 0 if equal, +1 if greater-than.
        int cmp(Data* other) override;
        /// @}


        /// @name   Functional
        /// @{
        /// @brief  Call this object as a function.
        /// @param  args    Arguments.
        /// @return         Value returned from this function.
        Data* call(std::vector< std::unique_ptr<Data> >& args) override;
        /// @}


        /// @name   OOP
        /// @{
        /// @brief  Get the class of this object.
        Data* get_class() const override;

        /// @brief  Set the class of this object.
        void set_class(Data* new_class);
        /// @}


    private:
        Value m_value;
    };
}
