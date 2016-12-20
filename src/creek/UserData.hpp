#pragma once

#include <creek/Data.hpp>

#include <creek/utility.hpp>
#include <creek/Variable.hpp>


namespace creek
{
    class DynFuncDef;
    class DynClassDef;


    /// @brief  Data type: Base for UserData<T> and UserData<T*>.
    /// @see    UserData
    template<class T> class CREEK_API UserData_base : public Data
    {
    public:
        /// @brief  Type alias: UserData_base.
        using base = UserData_base<T>;

        /// @brief  Class for this data type.
        /// This needs to be defined in a dynamic library.
        /// @see CREEK_CLASS_IMPL
        static Variable class_obj;

        /// @brief  Class definition.
        /// This needs to be defined in a dynamic library.
        /// @see CREEK_CLASS_IMPL
        static const DynClassDef* class_def;


        virtual T& reference() const = 0;
        virtual T* pointer() const = 0;


        /// @brief  Get data class name.
        std::string class_name() const override;

        /// @brief  Get debug text.
        std::string debug_text() const override;


        /// @name   OOP
        /// @{
        /// @brief  Get the class of this object.
        /// @return A new reference.
        Data* get_class(const SharedPointer<Scope>& scope) const override;
        /// @}

        /// @name   Object attribute
        /// @{
        /// @brief  Get the attribute.
        /// @brief  key         Attribute key.
        Data* attr(const SharedPointer<Scope>& scope, VarName key) override;

        /// @brief  Set the attribute.
        /// @brief  key         Attribute key.
        /// @brief  new_data    New data to save in attribute.
        Data* attr(const SharedPointer<Scope>& scope, VarName key, Data* new_data) override;
        /// @}
    };


    /// @brief  User data template.
    template<class T> class CREEK_API UserData : public UserData_base<T>
    {
    public:
        /// @brief  Stored value type.
        using Value = std::shared_ptr<T>;


        /// @brief  UserData constructor.
        /// @param  t       New value.
        /// Create a new value.
        UserData(typename Value::element_type* t);

        /// @brief  UserData constructor.
        /// @param  value   Shared value.
        /// Copy the value reference.
        UserData(const Value& value);

        const Value& value() const;

        typename std::remove_cv<T>::type& reference() const override;
        typename std::remove_cv<T>::type* pointer() const override;


        /// @brief  Create a copy of this data.
        /// Gets a new pointer to the same object.
        Data* copy() const override;

//        /// @brief  Create a shallow copy of this data.
//        /// Gets a new poitner to a new object.
//        Data* clone() const override;


        // /// @name   Value access
        // /// @{
        // /// @brief  Get the bool value of this data.
        // bool bool_value(const SharedPointer<Scope>& scope) const override;

        // /// @brief  Get the char value of this data.
        // char char_value(const SharedPointer<Scope>& scope) const override;

        // /// @brief  Get the int value of this data.
        // int int_value(const SharedPointer<Scope>& scope) const override;

        // /// @brief  Get the float value of this data.
        // double double_value(const SharedPointer<Scope>& scope) const override;

        // /// @brief  Get the string value of this data.
        // std::string string_value(const SharedPointer<Scope>& scope) const override;

        // /// @brief  Get the identifier value of this data.
        // VarName identifier_value(const SharedPointer<Scope>& scope) const override;

        // // @brief   Get the vector value of this data.
        // const std::vector<Variable>& vector_value(const SharedPointer<Scope>& scope) const override;
        // /// @}


        // /// @name   Container index
        // /// @{
        // /// @brief  Get the data at index.
        // /// @param  key         Index key.
        // Data* index(const SharedPointer<Scope>& scope, Data* key) override;

        // /// @brief  Set the data at index.
        // /// @param  key         Index key.
        // /// @param  new_data    New data to save in index.
        // Data* index(Data* key, Data* new_data) override;
        // /// @}


        // /// @name   Object attribute
        // /// @{
        // /// @brief  Get the attribute.
        // /// @brief  key         Attribute key.
        // Data* attr(const SharedPointer<Scope>& scope, VarName key) override;

        // /// @brief  Set the attribute.
        // /// @brief  key         Attribute key.
        // /// @brief  new_data    New data to save in attribute.
        // Data* attr(const SharedPointer<Scope>& scope, VarName key, Data* new_data) override;
        // /// @}


        // /// @name   Arithmetic operations
        // /// @{
        // /// @brief  Addition.
        // Data* add(const SharedPointer<Scope>& scope, Data* other) override;

        // /// @brief  Subtraction.
        // Data* sub(const SharedPointer<Scope>& scope, Data* other) override;

        // /// @brief  Multiplication.
        // Data* mul(const SharedPointer<Scope>& scope, Data* other) override;

        // /// @brief  Divison.
        // Data* div(const SharedPointer<Scope>& scope, Data* other) override;

        // /// @brief  Modulo.
        // Data* mod(const SharedPointer<Scope>& scope, Data* other) override;

        // /// @brief  Exponentiation.
        // Data* exp(const SharedPointer<Scope>& scope, Data* other) override;

        // /// @brief  Unary minus.
        // Data* unm(const SharedPointer<Scope>& scope) override;
        // /// @}


        // /// @name   Bitwise operations
        // /// @{
        // /// @brief  Bitwise AND.
        // Data* bit_and(const SharedPointer<Scope>& scope, Data* other) override;

        // /// @brief  Bitwise OR.
        // Data* bit_or(const SharedPointer<Scope>& scope, Data* other) override;

        // /// @brief  Bitwise XOR.
        // Data* bit_xor(const SharedPointer<Scope>& scope, Data* other) override;

        // /// @brief  Bitwise NOT.
        // Data* bit_not(const SharedPointer<Scope>& scope) override;

        // /// @brief  Bitwise left shift.
        // Data* bit_left_shift(const SharedPointer<Scope>& scope, Data* other) override;

        // /// @brief  Bitwise right shift.
        // Data* bit_right_shift(const SharedPointer<Scope>& scope, Data* other) override;
        // /// @}


        // /// @name   Relational operations
        // /// Only one operation is defined.
        // /// @{
        // /// Compare less-than/equal/greater-than.
        // /// This special operation must return an integer.
        // /// @return -1 if less-than, 0 if equal, +1 if greater-than.
        // int cmp(const SharedPointer<Scope>& scope, Data* other) override;
        // /// @}


        // /// @name   Functional
        // /// @{
        // /// Call this object as a function.
        // /// @param  args    Arguments.
        // /// @return         Value returned from this function.
        // Data* call(std::vector< std::unique_ptr<Data> >& args) override;
        // /// @}


    private:
        Value m_value;
    };


    /// @brief  UserData specialization for pointers.
    template<class T> class CREEK_API UserData<T*> : public UserData_base<T>
    {
    public:
        // TODO: UserData<pointer to pointer>
        static_assert(std::is_pointer<T>::value == false, "Pointer to pointer is not supported");

        using Value = std::shared_ptr<T*>;

        UserData(typename Value::element_type* t);
        UserData(const Value& value);

        const Value& value() const;

        T& reference() const override;
        T* pointer() const override;

        Data* copy() const override;

    private:
        Value m_value;
    };


    /// @brief  UserData specialization for const.
    template<class T> class CREEK_API UserData<const T> : public UserData<T>
    {

    };


    /// @brief  UserData specialization for const pointer.
    template<class T> class CREEK_API UserData<const T*> : public UserData<T>
    {

    };


//    template<class T> class UserData<T*> : public UserData<T>
//    {
//        Data* get_class(const SharedPointer<Scope>& scope) const override;
//    };
}


// template implementation
namespace creek
{
    // base
    template<class T> std::string UserData_base<T>::class_name() const
    {
        return "UserData";
    }

    template<class T> std::string UserData_base<T>::debug_text() const
    {
        return std::string("UserData(") + int_to_string(uintptr_t(this), 16) + std::string(")");
    }

    template<class T> Data* UserData_base<T>::get_class(const SharedPointer<Scope>& scope) const
    {
        if (!class_obj)
        {
            throw Exception("Dynamic class not yet loaded");
        }
        return class_obj->copy();
    }

    // normal
    template<class T> UserData<T>::UserData(typename Value::element_type* t) : UserData(Value(t))
    {

    }

    template<class T> UserData<T>::UserData(const Value& value) : m_value(value)
    {

    }

    template<class T> const std::shared_ptr<T>& UserData<T>::value() const
    {
        return m_value;
    }

    template<class T> typename std::remove_cv<T>::type& UserData<T>::reference() const
    {
        assert(m_value.get());
        return *m_value.get();
    }

    template<class T> typename std::remove_cv<T>::type* UserData<T>::pointer() const
    {
        assert(m_value.get());
        return m_value.get();
    }

    template<class T> Data* UserData<T>::copy() const
    {
        return new UserData<T>(m_value);
    }


    // pointer
    template<class T> UserData<T*>::UserData(typename Value::element_type* t) : UserData(Value(t))
    {

    }

    template<class T> UserData<T*>::UserData(const Value& value) : m_value(value)
    {

    }

    template<class T> auto UserData<T*>::value() const -> const Value&
    {
        return m_value;
    }

    template<class T> T& UserData<T*>::reference() const
    {
        assert(m_value.get());
        return **m_value.get();
    }

    template<class T> T* UserData<T*>::pointer() const
    {
        assert(m_value.get());
        return *m_value.get();
    }

    template<class T> Data* UserData<T*>::copy() const
    {
        return new UserData<T*>(m_value);
    }
}
