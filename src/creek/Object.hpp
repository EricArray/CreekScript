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
            /// Type alias: attribute list.
            using AttrList = std::vector< std::tuple<Variable, Variable> >;

            Definition(Data* class_obj, const AttrList& attrs) :
                class_obj(class_obj),
                attrs(attrs)
            {

            }

            Variable class_obj; ///< Class object.
            AttrList attrs; ///< Object attributes.
        };

        /// Stored value type.
        using Value = std::shared_ptr<Definition>;


        /// `Object` constructor.
        /// @param  value   Object value.
        Object(const Value& value);

        /// `Object` constructor.
        /// @param  class_obj   Class object.
        /// @param  attrs       Object attributes.
        Object(Data* class_obj, const Definition::AttrList& attrs);

        /// @brief  Make a new `Object`.
        /// @param  class_obj   Class object.
        /// @param  attrs       Object attributes by name.
        static Object* make(Data* class_obj, const std::map<VarName, Variable>& attrs);


        /// @brief  Get shared value.
        Value& value();


        /// Get a reference to the same object.
        Data* copy() const override;

        /// Get a reference to a shallow copy of this object.
        Data* clone() const override;

        /// Get data class name.
        std::string class_name() const override;

        /// Get debug text.
        std::string debug_text() const override;


        /// @name   Value access
        /// @{
        /// Get the bool value of this data.
        bool bool_value() const override;

        /// Get the char value of this data.
        char char_value() const override;

        /// Get the int value of this data.
        int int_value() const override;

        /// Get the float value of this data.
        float float_value() const override;

        /// Get the string value of this data.
        std::string string_value() const override;

        // Get the vector value of this data.
        const std::vector<Variable>& vector_value() const override;
        /// @}


        /// @name   Container index
        /// @{
        /// Get the data at index.
        Data* index(Data* key) override;

        /// Set the data at index.
        Data* index(Data* key, Data* new_data) override;
        /// @}


        /// @name   Arithmetic operations
        /// @{
        /// Addition.
        Data* add(Data* other) override;

        /// Subtraction.
        Data* sub(Data* other) override;

        /// Multiplication.
        Data* mul(Data* other) override;

        /// Divison.
        Data* div(Data* other) override;

        /// Modulo.
        Data* mod(Data* other) override;

        /// Exponentiation.
        Data* exp(Data* other) override;

        /// Unary minus.
        Data* unm() override;
        /// @}


        /// @name   Bitwise operations
        /// @{
        /// Bitwise AND.
        Data* bit_and(Data* other) override;

        /// Bitwise OR.
        Data* bit_or(Data* other) override;

        /// Bitwise XOR.
        Data* bit_xor(Data* other) override;

        /// Bitwise NOT.
        Data* bit_not() override;

        /// Bitwise left shift.
        Data* bit_left_shift(Data* other) override;

        /// Bitwise right shift.
        Data* bit_right_shift(Data* other) override;
        /// @}


        /// @name   Relational operations
        /// Only one operation is defined.
        /// @{
        /// Compare less-than/equal/greater-than.
        /// This special operation must return an integer.
        /// @return -1 if less-than, 0 if equal, +1 if greater-than.
        int cmp(Data* other) override;
        /// @}


        /// @name   Functional
        /// @{
        /// Call this object as a function.
        /// @param  args    Arguments.
        /// @return         Value returned from this function.
        Data* call(std::vector< std::unique_ptr<Data> >& args) override;
        /// @}


        /// @name   OOP
        /// @{
        /// @brief  Get the class of this object.
        Data* get_class() override;

        /// @brief  Set the class of this object.
        void set_class(Data* new_class);
        /// @}


        /// @brief  Call a method of this object's class.
        /// @param  method_name Name of the method to call.
        /// @param  args        Arguments.
        /// Self needs to be first argument.
        Data* call_method(const std::string& method_name,
                          const std::vector<Data*>& args);

        /// @brief  Call a method of this object's class.
        /// @param  method_name Name of the method to call.
        /// @param  args        Arguments.
        /// Self needs to be first argument.
        Data* call_method(const std::string& method_name,
                          std::vector< std::unique_ptr<Data> >& args);


    private:
        Value m_value;
    };
}
