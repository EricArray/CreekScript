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
        Object(std::make_shared<Definition>(Definition(class_obj, attrs)))
    {

    }

    // @brief  Make a new `Object`.
    // @param  class_obj   Class object.
    // @param  attrs       Object attributes by name.
    Object* Object::make(Data* class_obj, const std::map<VarName, Variable>& attrs)
    {
        Value new_value = std::make_shared<Definition>(Definition(class_obj, {}));
        for (auto& attr : attrs)
        {
            new_value->attrs.emplace_back(
                std::make_tuple<Variable, Variable>(new Identifier(attr.first), attr.second->copy()));
        }
        return new Object(new_value);
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


    // @name   Value access
    // @{
    // Get the bool value of this data.
    bool Object::bool_value() const
    {
        Variable class_obj = m_value->class_obj;
        Variable method = class_obj.index(new Identifier("to_boolean"));
        std::vector< std::unique_ptr<Data> > args;
        args.emplace_back(this->copy());
        Variable value = method->call(args);
        return value->bool_value();
    }

    // Get the char value of this data.
    char Object::char_value() const
    {
        Variable class_obj = m_value->class_obj;
        Variable method = class_obj.index(new Identifier("to_string"));
        std::vector< std::unique_ptr<Data> > args;
        args.emplace_back(this->copy());
        Variable value = method->call(args);
        return value->char_value();
    }

    // Get the int value of this data.
    int Object::int_value() const
    {
        Variable class_obj = m_value->class_obj;
        Variable method = class_obj.index(new Identifier("to_number"));
        std::vector< std::unique_ptr<Data> > args;
        args.emplace_back(this->copy());
        Variable value = method->call(args);
        return value->int_value();
    }

    // Get the float value of this data.
    float Object::float_value() const
    {
        Variable class_obj = m_value->class_obj;
        Variable method = class_obj.index(new Identifier("to_number"));
        std::vector< std::unique_ptr<Data> > args;
        args.emplace_back(this->copy());
        Variable value = method->call(args);
        return value->float_value();
    }

    // Get the string value of this data.
    std::string Object::string_value() const
    {
        Variable class_obj = m_value->class_obj;
        Variable method = class_obj.index(new Identifier("to_string"));
        std::vector< std::unique_ptr<Data> > args;
        args.emplace_back(this->copy());
        Variable value = method->call(args);
        return value->string_value();
    }

    // Get the vector value of this data.
    const std::vector<Variable>& Object::vector_value() const
    {
        return Data::vector_value();
    }
    // @}


    // @name   Container index
    // @{
    // Get the data at index.
    Data* Object::index(Data* key)
    {
        // TODO: rework
        for (auto& attr : m_value->attrs)
        {
            if (key->cmp(*std::get<0>(attr)) == 0)
            {
                return std::get<1>(attr)->copy();
            }
        }
        throw Exception(std::string("Index not found: ") + key->debug_text());
    }

    // Set the data at index.
    Data* Object::index(Data* key, Data* new_data)
    {
        // TODO: rework
        for (auto& attr : m_value->attrs)
        {
            if (key->cmp(*std::get<0>(attr)) == 0)
            {
                auto& v = std::get<1>(attr);
                v.data(new_data);
                return new_data->copy();
            }
        }
        m_value->attrs.push_back(std::make_tuple(Variable(key->copy()), Variable(new_data)));
        return new_data->copy();
    }
    // @}


    // @name   Arithmetic operations
    // @{
    // Addition.
    Data* Object::add(Data* other)
    {
        return call_method("add", {this->copy(), other->copy()});
    }

    // Subtraction.
    Data* Object::sub(Data* other)
    {
        return call_method("sub", {this->copy(), other->copy()});
    }

    // Multiplication.
    Data* Object::mul(Data* other)
    {
        return call_method("mul", {this->copy(), other->copy()});
    }

    // Divison.
    Data* Object::div(Data* other)
    {
        return call_method("div", {this->copy(), other->copy()});
    }

    // Modulo.
    Data* Object::mod(Data* other)
    {
        return call_method("mod", {this->copy(), other->copy()});
    }

    // Exponentiation.
    Data* Object::exp(Data* other)
    {
        return call_method("exp", {this->copy(), other->copy()});
    }

    // Unary minus.
    Data* Object::unm()
    {
        return call_method("unm", {this->copy()});
    }
    // @}


    // @name   Bitwise operations
    // @{
    // Bitwise AND.
    Data* Object::bit_and(Data* other)
    {
        return call_method("bit_and", {this->copy(), other->copy()});
    }

    // Bitwise OR.
    Data* Object::bit_or(Data* other)
    {
        return call_method("bit_or", {this->copy(), other->copy()});
    }

    // Bitwise XOR.
    Data* Object::bit_xor(Data* other)
    {
        return call_method("bit_xor", {this->copy(), other->copy()});
    }

    // Bitwise NOT.
    Data* Object::bit_not()
    {
        return call_method("bit_not", {this->copy()});
    }

    // Bitwise left shift.
    Data* Object::bit_left_shift(Data* other)
    {
        return call_method("bit_left_shift", {this->copy(), other->copy()});
    }

    // Bitwise right shift.
    Data* Object::bit_right_shift(Data* other)
    {
        return call_method("bit_right_shift", {this->copy(), other->copy()});
    }
    // @}


    // @name   Relational operations
    // Only one operation is defined.
    // @{
    // Compare less-than/equal/greater-than.
    // This special operation must return an integer.
    // @return -1 if less-than, 0 if equal, +1 if greater-than.
    int Object::cmp(Data* other)
    {
        Variable v(call_method("cmp", {this->copy(), other->copy()}));
        return v->int_value();
    }
    // @}


    // @name   Functional
    // @{
    // Call this object as a function.
    // @param  args    Arguments.
    // @return         Value returned from this function.
    Data* Object::call(std::vector< std::unique_ptr<Data> >& args)
    {
        std::vector< std::unique_ptr<Data> > new_args;
        new_args.emplace_back(this->copy());
        for (auto& arg : args)
        {
            new_args.emplace_back(arg.release());
        }
        return call_method("call", new_args);
    }
    // @}


    // @name   OOP
    // @{
    // @brief  Get the class of this object.
    Data* Object::get_class()
    {
        return m_value->class_obj->copy();
    }

    // @brief  Set the class of this object.
    void Object::set_class(Data* new_class)
    {
        m_value->class_obj.data(new_class);
    }
    // @}


    // @brief  Call a method of this object's class.
    // @param  method_name Name of the method to call.
    // @param  args        Arguments.
    // Self needs to be first argument.
    Data* Object::call_method(const std::string& method_name,
                              const std::vector<Data*>& args)
    {
        std::vector< std::unique_ptr<Data> > up_args;
        for (auto& arg : args)
        {
            up_args.emplace_back(arg);
        }
        return call_method(method_name, up_args);
    }


    // @brief  Call a method of this object's class.
    // @param  method_name Name of the method to call.
    // @param  args        Arguments.
    // Self needs to be first argument.
    Data* Object::call_method(const std::string& method_name,
                              std::vector< std::unique_ptr<Data> >& args)
    {
        Variable key = new Identifier(VarName::from_name(method_name));
        Variable class_obj = m_value->class_obj;
        if (!class_obj)
        {
            throw Exception("Object has no class");
        }
        Variable method = class_obj->index(*key);
        return method->call(args);
    }
}
