#include <creek/Expression_General.hpp>

#include <creek/Scope.hpp>
#include <creek/Variable.hpp>
#include <creek/Void.hpp>


namespace creek
{
    // @brief  `ExprConst` constructor.
    // @param  data    Constant data to be copied.
    ExprConst::ExprConst(Data* data) :
        m_data(data)
    {

    }

    Expression* ExprConst::clone() const
    {
        return new ExprConst(m_data->copy());
    }

    bool ExprConst::is_const() const
    {
        return true;
    }

    Variable ExprConst::eval(Scope& scope)
    {
        return m_data->copy();
    }

    Bytecode ExprConst::bytecode(VarNameMap& var_name_map) const
    {
        std::unique_ptr<Expression> e(m_data->to_expression());
        return e->bytecode(var_name_map);
    }


    // @brief  `ExprCall` constructor.
    // @param  function    Function expression.
    // @param  args        Arguments to pass to the function.
    ExprCall::ExprCall(Expression* function, const std::vector<Expression*>& args) :
        m_function(function)
    {
        for (auto& arg : args)
        {
            m_args.emplace_back(arg);
        }
    }

    Expression* ExprCall::clone() const
    {
        std::vector<Expression*> new_args;
        for (auto& a : m_args)
        {
            new_args.push_back(a->clone());
        }
        return new ExprCall(m_function->clone(), new_args);
    }

    bool ExprCall::is_const() const
    {
        return false;
    }

    Expression* ExprCall::const_optimize() const
    {
        std::vector<Expression*> new_args;
        for (auto& a : m_args)
        {
            new_args.push_back(a->const_optimize());
        }
        return new ExprCall(m_function->const_optimize(), new_args);
    }

    Variable ExprCall::eval(Scope& scope)
    {
        Variable function = m_function->eval(scope);

        std::vector< std::unique_ptr<Data> > args;
        for (auto& a : m_args)
        {
            args.emplace_back(a->eval(scope).release());
        }

        return function->call(args);
    }

    Bytecode ExprCall::bytecode(VarNameMap& var_name_map) const
    {
        Bytecode b;
        b << static_cast<uint8_t>(OpCode::call);
        b << m_function->bytecode(var_name_map);
        b << static_cast<uint32_t>(m_args.size());
        for (auto& arg : m_args)
        {
            b << arg->bytecode(var_name_map);
        }
        return b;
    }


    // @brief  `ExprVariadicCall` constructor.
    // @param  function    Function expression.
    // @param  args        Arguments to pass to the function.
    // @param  vararg      Argument to expand before calling.
    ExprVariadicCall::ExprVariadicCall(Expression* function, const std::vector<Expression*>& args, Expression* vararg) :
        m_function(function),
        m_vararg(vararg)
    {
        for (auto& arg : args)
        {
            m_args.emplace_back(arg);
        }
    }

    Expression* ExprVariadicCall::clone() const
    {
        std::vector<Expression*> new_args;
        for (auto& a : m_args)
        {
            new_args.push_back(a->clone());
        }
        return new ExprVariadicCall(m_function->clone(), new_args, m_vararg->clone());
    }

    bool ExprVariadicCall::is_const() const
    {
        return false;
    }

    Expression* ExprVariadicCall::const_optimize() const
    {
        std::vector<Expression*> new_args;
        for (auto& a : m_args)
        {
            new_args.push_back(a->const_optimize());
        }
        return new ExprVariadicCall(m_function->const_optimize(), new_args, m_vararg->const_optimize());
    }

    Variable ExprVariadicCall::eval(Scope& scope)
    {
        // normal arguments
        std::vector< std::unique_ptr<Data> > args;
        for (auto& a : m_args)
        {
            args.emplace_back(a->eval(scope).release());
        }

        // variadic argument
        Variable vararg = m_vararg->eval(scope);
        for (auto& a : vararg->vector_value())
        {
            args.emplace_back(a->copy());
        }

        // call function
        Variable function = m_function->eval(scope);
        return function->call(args);
    }

    Bytecode ExprVariadicCall::bytecode(VarNameMap& var_name_map) const
    {
        Bytecode b;
        b << static_cast<uint8_t>(OpCode::variadic_call);
        b << m_function->bytecode(var_name_map);
        b << static_cast<uint32_t>(m_args.size());
        for (auto& arg : m_args)
        {
            b << arg->bytecode(var_name_map);
        }
        b << m_vararg->bytecode(var_name_map);
        return b;
    }


    /// @brief  `ExprCallMethod` constructor.
    /// @param  object      Object expression.
    /// @param  method_name Method name.
    /// @param  args        Arguments to pass to the method.
    ExprCallMethod::ExprCallMethod(Expression* object, VarName method_name, const std::vector<Expression*>& args) :
        m_object(object),
        m_method_name(method_name)
    {
        for (auto& arg : args)
        {
            m_args.emplace_back(arg);
        }
    }

    Expression* ExprCallMethod::clone() const
    {
        std::vector<Expression*> new_args;
        for (auto& a : m_args)
        {
            new_args.push_back(a->clone());
        }
        return new ExprCallMethod(m_object->clone(), m_method_name, new_args);
    }

    bool ExprCallMethod::is_const() const
    {
        return false;
    }

    Expression* ExprCallMethod::const_optimize() const
    {
        std::vector<Expression*> new_args;
        for (auto& a : m_args)
        {
            new_args.push_back(a->const_optimize());
        }
        return new ExprCallMethod(m_object->const_optimize(), m_method_name, new_args);
    }

    Variable ExprCallMethod::eval(Scope& scope)
    {
        Variable object = m_object->eval(scope);
        Variable class_obj = object->get_class();
        Variable method = class_obj->attr(m_method_name);

        std::vector< std::unique_ptr<Data> > args;
        args.emplace_back(object->copy());
        for (auto& a : m_args)
        {
            args.emplace_back(a->eval(scope).release());
        }

        return method->call(args);
    }

    Bytecode ExprCallMethod::bytecode(VarNameMap& var_name_map) const
    {
        Bytecode b;
        b << static_cast<uint8_t>(OpCode::call_method);
        b << m_object->bytecode(var_name_map);
        b << var_name_map.id_from_name(m_method_name.name());
        b << static_cast<uint32_t>(m_args.size());
        for (auto& arg : m_args)
        {
            b << arg->bytecode(var_name_map);
        }
        return b;
    }


    // @brief  `ExprVariadicCallMethod` constructor.
    // @param  object      Object expression.
    /// @param  method_name Method name.
    // @param  args        Arguments to pass to the method.
    // @param  vararg      Argument to expand before calling.
    ExprVariadicCallMethod::ExprVariadicCallMethod(Expression* object, VarName method_name, const std::vector<Expression*>& args, Expression* vararg) :
        m_object(object),
        m_method_name(method_name),
        m_vararg(vararg)
    {
        for (auto& arg : args)
        {
            m_args.emplace_back(arg);
        }
    }

    Expression* ExprVariadicCallMethod::clone() const
    {
        std::vector<Expression*> new_args;
        for (auto& a : m_args)
        {
            new_args.push_back(a->clone());
        }
        return new ExprVariadicCallMethod(m_object->clone(), m_method_name, new_args, m_vararg->clone());
    }

    bool ExprVariadicCallMethod::is_const() const
    {
        return false;
    }

    Expression* ExprVariadicCallMethod::const_optimize() const
    {
        std::vector<Expression*> new_args;
        for (auto& a : m_args)
        {
            new_args.push_back(a->const_optimize());
        }
        return new ExprVariadicCallMethod(m_object->const_optimize(), m_method_name, new_args, m_vararg->const_optimize());
    }

    Variable ExprVariadicCallMethod::eval(Scope& scope)
    {
        // normal arguments
        std::vector< std::unique_ptr<Data> > args;
        for (auto& a : m_args)
        {
            args.emplace_back(a->eval(scope).release());
        }

        // variadic argument
        Variable vararg = m_vararg->eval(scope);
        for (auto& a : vararg->vector_value())
        {
            args.emplace_back(a->copy());
        }

        // call method
        Variable object = m_object->eval(scope);
        Variable class_obj = object->get_class();
        Variable method = class_obj->attr(m_method_name);
        return method->call(args);
    }

    Bytecode ExprVariadicCallMethod::bytecode(VarNameMap& var_name_map) const
    {
        Bytecode b;
        b << static_cast<uint8_t>(OpCode::variadic_call_method);
        b << m_object->bytecode(var_name_map);
        b << var_name_map.id_from_name(m_method_name.name());
        b << static_cast<uint32_t>(m_args.size());
        for (auto& arg : m_args)
        {
            b << arg->bytecode(var_name_map);
        }
        b << m_vararg->bytecode(var_name_map);
        return b;
    }


    // @brief  `ExprIndexGet` constructor.
    // @param  array   Expression for the array object.
    // @param  index   Expression for the index.
    ExprIndexGet::ExprIndexGet(Expression* array, Expression* index) :
        m_array(array),
        m_index(index)
    {

    }

    Expression* ExprIndexGet::clone() const
    {
        return new ExprIndexGet(m_array->clone(), m_index->clone());
    }

    bool ExprIndexGet::is_const() const
    {
        return false;
    }

    Expression* ExprIndexGet::const_optimize() const
    {
        return new ExprIndexGet(m_array->const_optimize(), m_index->const_optimize());
    }

    Variable ExprIndexGet::eval(Scope& scope)
    {
        Variable a = m_array->eval(scope);
        Variable i = m_index->eval(scope);
        return a.index(i);
    }

    Bytecode ExprIndexGet::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(OpCode::index_get) << m_array->bytecode(var_name_map) << m_index->bytecode(var_name_map);
    }


    // @brief  `ExprIndexSet` constructor.
    // @param  array       Expression for the array object.
    // @param  index       Expression for the index.
    // @param  value       Expression for the new value.
    ExprIndexSet::ExprIndexSet(Expression* array, Expression* index, Expression* value) :
        m_array(array),
        m_index(index),
        m_value(value)
    {

    }

    Expression* ExprIndexSet::clone() const
    {
        return new ExprIndexSet(m_array->clone(), m_index->clone(), m_value->clone());
    }

    bool ExprIndexSet::is_const() const
    {
        return false;
    }

    Expression* ExprIndexSet::const_optimize() const
    {
        return new ExprIndexSet(m_array->const_optimize(), m_index->const_optimize(), m_value->const_optimize());
    }

    Variable ExprIndexSet::eval(Scope& scope)
    {
        Variable a = m_array->eval(scope);
        Variable i = m_index->eval(scope);
        Variable v = m_value->eval(scope);
        return a.index(i, v);
    }

    Bytecode ExprIndexSet::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(OpCode::index_set) << m_array->bytecode(var_name_map) << m_index->bytecode(var_name_map) << m_value->bytecode(var_name_map);
    }


    /// @brief  `ExprAttrGet` constructor.
    /// @param  object  Expression for the object.
    /// @param  attr    Attribute name.
    ExprAttrGet::ExprAttrGet(Expression* object, VarName attr) :
        m_object(object),
        m_attr(attr)
    {

    }

    Expression* ExprAttrGet::clone() const
    {
        return new ExprAttrGet(m_object->clone(), m_attr);
    }

    bool ExprAttrGet::is_const() const
    {
        return m_object->is_const();
    }

    Expression* ExprAttrGet::const_optimize() const
    {
        if (is_const())
        {
            Scope scope;
            Variable object = m_object->eval(scope);
            return new ExprConst(object->attr(m_attr));
        }
        else
        {
            return new ExprAttrGet(m_object->const_optimize(), m_attr);
        }
    }

    Variable ExprAttrGet::eval(Scope& scope)
    {
        Variable o = m_object->eval(scope);
        return o.attr(m_attr);
    }

    Bytecode ExprAttrGet::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(OpCode::attr_get) << m_object->bytecode(var_name_map) << var_name_map.id_from_name(m_attr.name());
    }


    /// @brief  `ExprAttrSet` constructor.
    /// @param  object  Expression for the object.
    /// @param  attr    Attribute name.
    /// @param  value   Expression for the new value.
    ExprAttrSet::ExprAttrSet(Expression* object, VarName attr, Expression* value) :
        m_object(object),
        m_attr(attr),
        m_value(value)
    {

    }

    Expression* ExprAttrSet::clone() const
    {
        return new ExprAttrSet(m_object->clone(), m_attr, m_value->clone());
    }

    bool ExprAttrSet::is_const() const
    {
        return false;
    }

    Expression* ExprAttrSet::const_optimize() const
    {
        return new ExprAttrSet(m_object->const_optimize(), m_attr, m_value->const_optimize());
    }

    Variable ExprAttrSet::eval(Scope& scope)
    {
        Variable o = m_object->eval(scope);
        Variable v = m_value->eval(scope);
        return o.attr(m_attr, v);
    }

    Bytecode ExprAttrSet::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() <<
            static_cast<uint8_t>(OpCode::attr_set) <<
            m_object->bytecode(var_name_map) <<
            var_name_map.id_from_name(m_attr.name()) <<
            m_value->bytecode(var_name_map);
    }
}

