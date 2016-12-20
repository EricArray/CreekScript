#include <creek/Object.hpp>

#include <tuple>

#include <creek/Identifier.hpp>


namespace creek
{
    // `Object` constructor.
    // @param  value   Object value.
    Object::Object(const Value& value) : m_value(value)
    {

    }

    // `Object` constructor.
    // @param  class_obj   Class object.
    // @param  attrs       Object attributes.
    Object::Object(Data* class_obj, const Definition::AttrList& attrs) :
        Object(Value::make(class_obj, attrs))
    {

    }

    // @brief  Make a new `Object`.
    // @param  class_obj   Class object.
    // @param  attrs       Object attributes by name.
    Object* Object::make(Data* class_obj, const std::map<VarName, Variable>& attrs)
    {
//        Value new_value = std::make_shared<Definition>(Definition(class_obj, {}));
//        for (auto& attr : attrs)
//        {
////            new_value->attrs.emplace_back(
////                std::make_tuple<Variable, Variable>(new Identifier(attr.first), attr.second->copy()));
//            new_value->attrs[attr.first] = attr.second->copy();
//        }
        return new Object(class_obj, attrs);
    }


    // @brief  Get shared value.
    Object::Value& Object::value()
    {
        return m_value;
    }


    // Get a reference to the same object.
    Data* Object::copy() const
    {
        return new Object(m_value);
    }

    // Get a reference to a shallow copy of this object.
    Data* Object::clone() const
    {
        return new Object(m_value->class_obj->copy(), m_value->attrs);
    }

    // Get data class name.
    std::string Object::class_name() const
    {
        return "Object";
    }

    // Get debug text.
    std::string Object::debug_text() const
    {
        std::stringstream stream;
        stream << "Object(" << this << ")";
        return stream.str();
    }

    /// @brief  Used for garbage collection.
    void Object::garbage_trace()
    {
        if (m_value)
        {
            m_value->garbage_trace();
        }
    }


    // @name   Value access
    // @{
    // Get the bool value of this data.
    bool Object::bool_value(const SharedPointer<Scope>& scope) const
    {
        Variable v = call_method(scope, "to_boolean", {});
        return v->bool_value(scope);
        // Variable class_obj = m_value->class_obj;
        // Variable method = class_obj.index(new Identifier("to_boolean"));
        // std::vector< std::unique_ptr<Data> > args;
        // args.emplace_back(this->copy());
        // Variable value = method->call(args);
        // return value->bool_value(scope);
    }

    // Get the char value of this data.
    char Object::char_value(const SharedPointer<Scope>& scope) const
    {
        Variable v = call_method(scope, "to_string", {});
        return v->char_value(scope);
        // Variable class_obj = m_value->class_obj;
        // Variable method = class_obj.index(new Identifier("to_string"));
        // std::vector< std::unique_ptr<Data> > args;
        // args.emplace_back(this->copy());
        // Variable value = method->call(args);
        // return value->char_value(scope);
    }

    // Get the int value of this data.
    int Object::int_value(const SharedPointer<Scope>& scope) const
    {
        Variable v = call_method(scope, "to_number", {});
        return v->int_value(scope);
        // Variable class_obj = m_value->class_obj;
        // Variable method = class_obj.index(new Identifier("to_number"));
        // std::vector< std::unique_ptr<Data> > args;
        // args.emplace_back(this->copy());
        // Variable value = method->call(args);
        // return value->int_value(scope);
    }

    // Get the float value of this data.
    double Object::double_value(const SharedPointer<Scope>& scope) const
    {
        Variable v = call_method(scope, "to_number", {});
        return v->double_value(scope);
        // Variable class_obj = m_value->class_obj;
        // Variable method = class_obj.index(new Identifier("to_number"));
        // std::vector< std::unique_ptr<Data> > args;
        // args.emplace_back(this->copy());
        // Variable value = method->call(args);
        // return value->double_value(scope);
    }

    // // Get the string value of this data.
    // std::string Object::string_value(const SharedPointer<Scope>& scope) const
    // {
    //     Variable v = call_method(scope, "to_string", {});
    //     return v->string_value(scope);
    //     // Variable class_obj = m_value->class_obj;
    //     // Variable method = class_obj.index(new Identifier("to_string"));
    //     // std::vector< std::unique_ptr<Data> > args;
    //     // args.emplace_back(this->copy());
    //     // Variable value = method->call(args);
    //     // return value->string_value(scope);
    // }

    // Get the vector value of this data.
    const std::vector<Variable>& Object::vector_value(const SharedPointer<Scope>& scope) const
    {
        return Data::vector_value(scope);
    }
    // @}


    // @name   Container index
    // @{
    // Get the data at index.
    Data* Object::index(const SharedPointer<Scope>& scope, Data* key)
    {
        // // TODO: rework
        // for (auto& attr : m_value->attrs)
        // {
        //     if (key->cmp(scope, *std::get<0>(attr)) == 0)
        //     {
        //         return std::get<1>(attr)->copy();
        //     }
        // }
        // throw Exception(std::string("Index not found: ") + key->debug_text());

        // return attr(key->identifier_value(scope));
        return call_method(scope, "index_get", {key->copy()});
    }

    // Set the data at index.
    Data* Object::index(const SharedPointer<Scope>& scope, Data* key, Data* new_data)
    {
        // // TODO: rework
        // for (auto& attr : m_value->attrs)
        // {
        //     if (key->cmp(scope, *std::get<0>(attr)) == 0)
        //     {
        //         auto& v = std::get<1>(attr);
        //         v.data(new_data);
        //         return new_data->copy();
        //     }
        // }
        // m_value->attrs.push_back(std::make_tuple(Variable(key->copy()), Variable(new_data)));
        // return new_data->copy();

        // return attr(key->identifier_value(scope), new_data);
        return call_method(scope, "index_set", {key->copy(), new_data->copy()});
    }
    // @}


    /// @name   Object attribute
    /// @{
    /// @brief  Get the attribute.
    /// @brief  key         Attribute key.
    Data* Object::attr(const SharedPointer<Scope>& scope, VarName key)
    {
        auto iter = m_value->attrs.find(key);
        if (iter == m_value->attrs.end())
        {
            throw Exception(std::string("Attribute not found: ") + key.name());
        }
        return iter->second->copy();
    }

    /// @brief  Set the attribute.
    /// @brief  key         Attribute key.
    /// @brief  new_data    New data to save in attribute.
    Data* Object::attr(const SharedPointer<Scope>& scope, VarName key, Data* new_data)
    {
        m_value->attrs[key].reset(new_data);
        return new_data->copy();
    }
    /// @}


    // @name   Arithmetic operations
    // @{
    // Addition.
    Data* Object::add(const SharedPointer<Scope>& scope, Data* other)
    {
        return call_method(scope, "add", {other->copy()});
    }

    // Subtraction.
    Data* Object::sub(const SharedPointer<Scope>& scope, Data* other)
    {
        return call_method(scope, "sub", {other->copy()});
    }

    // Multiplication.
    Data* Object::mul(const SharedPointer<Scope>& scope, Data* other)
    {
        return call_method(scope, "mul", {other->copy()});
    }

    // Divison.
    Data* Object::div(const SharedPointer<Scope>& scope, Data* other)
    {
        return call_method(scope, "div", {other->copy()});
    }

    // Modulo.
    Data* Object::mod(const SharedPointer<Scope>& scope, Data* other)
    {
        return call_method(scope, "mod", {other->copy()});
    }

    // Exponentiation.
    Data* Object::exp(const SharedPointer<Scope>& scope, Data* other)
    {
        return call_method(scope, "exp", {other->copy()});
    }

    // Unary minus.
    Data* Object::unm(const SharedPointer<Scope>& scope)
    {
        return call_method(scope, "unm", {});
    }
    // @}


    // @name   Bitwise operations
    // @{
    // Bitwise AND.
    Data* Object::bit_and(const SharedPointer<Scope>& scope, Data* other)
    {
        return call_method(scope, "bit_and", {other->copy()});
    }

    // Bitwise OR.
    Data* Object::bit_or(const SharedPointer<Scope>& scope, Data* other)
    {
        return call_method(scope, "bit_or", {other->copy()});
    }

    // Bitwise XOR.
    Data* Object::bit_xor(const SharedPointer<Scope>& scope, Data* other)
    {
        return call_method(scope, "bit_xor", {other->copy()});
    }

    // Bitwise NOT.
    Data* Object::bit_not(const SharedPointer<Scope>& scope)
    {
        return call_method(scope, "bit_not", {});
    }

    // Bitwise left shift.
    Data* Object::bit_left_shift(const SharedPointer<Scope>& scope, Data* other)
    {
        return call_method(scope, "bit_left_shift", {other->copy()});
    }

    // Bitwise right shift.
    Data* Object::bit_right_shift(const SharedPointer<Scope>& scope, Data* other)
    {
        return call_method(scope, "bit_right_shift", {other->copy()});
    }
    // @}


    // @name   Relational operations
    // Only one operation is defined.
    // @{
    // Compare less-than/equal/greater-than.
    // This special operation must return an integer.
    // @return -1 if less-than, 0 if equal, +1 if greater-than.
    int Object::cmp(const SharedPointer<Scope>& scope, Data* other)
    {
        Variable v(call_method(scope, "cmp", {other->copy()}));
        return v->int_value(scope);
    }
    // @}


    // @name   Functional
    // @{
    // Call this object as a function.
    // @param  args    Arguments.
    // @return         Value returned from this function.
    Data* Object::call(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        std::vector<Data*> new_args;
//        new_args.emplace_back(this->copy());
        for (auto& arg : args)
        {
            new_args.emplace_back(arg.release());
        }
        return call_method(scope, "call", new_args);
    }
    // @}


    // @name   OOP
    // @{
    // @brief  Get the class of this object.
    Data* Object::get_class(const SharedPointer<Scope>& scope) const
    {
        return m_value->class_obj->copy();
    }

    // @brief  Set the class of this object.
    void Object::set_class(Data* new_class)
    {
        m_value->class_obj.data(new_class);
    }
    // @}
}
