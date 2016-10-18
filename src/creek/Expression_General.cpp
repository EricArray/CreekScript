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

    Variable ExprConst::eval(Scope& scope)
    {
        return m_data->copy();
    }


    // `ExprCall` constructor.
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


    // `ExprVariadicCall` constructor.
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


    // `ExprCallMethod` constructor.
    // @param  object      Object expression.
    // @param  index       Index to the method.
    // @param  args        Arguments to pass to the method.
    ExprCallMethod::ExprCallMethod(Expression* object, Expression* index, const std::vector<Expression*>& args) :
        m_object(object),
        m_index(index)
    {
        for (auto& arg : args)
        {
            m_args.emplace_back(arg);
        }
    }

    Variable ExprCallMethod::eval(Scope& scope)
    {
        Variable object = m_object->eval(scope);
        Variable class_obj = object->get_class();
        Variable index = m_index->eval(scope);
        Variable method = class_obj->index(*index);

        std::vector< std::unique_ptr<Data> > args;
        args.emplace_back(object->copy());
        for (auto& a : m_args)
        {
            args.emplace_back(a->eval(scope).release());
        }

        return method->call(args);
    }


    // `ExprVariadicCallMethod` constructor.
    // @param  object      Object expression.
    // @param  index       Index to the method.
    // @param  args        Arguments to pass to the method.
    // @param  vararg      Argument to expand before calling.
    ExprVariadicCallMethod::ExprVariadicCallMethod(Expression* object, Expression* index, const std::vector<Expression*>& args, Expression* vararg) :
        m_object(object),
        m_index(index),
        m_vararg(vararg)
    {
        for (auto& arg : args)
        {
            m_args.emplace_back(arg);
        }
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
        Variable index = m_index->eval(scope);
        Variable method = class_obj->index(*index);
        return method->call(args);
    }


    // `ExprIndexGet` constructor.
    // @param  array   Expression for the array object.
    // @param  index   Expression for the index.
    ExprIndexGet::ExprIndexGet(Expression* array, Expression* index) :
        m_array(array),
        m_index(index)
    {

    }

    Variable ExprIndexGet::eval(Scope& scope)
    {
        Variable a = m_array->eval(scope);
        Variable i = m_index->eval(scope);
        return a.index(i);
    }


    // `ExprIndexSet` constructor.
    // @param  array       Expression for the array object.
    // @param  index       Expression for the index.
    // @param  value       Expression for the new value.
    ExprIndexSet::ExprIndexSet(Expression* array, Expression* index, Expression* value) :
        m_array(array),
        m_index(index),
        m_value(value)
    {

    }

    Variable ExprIndexSet::eval(Scope& scope)
    {
        Variable a = m_array->eval(scope);
        Variable i = m_index->eval(scope);
        Variable v = m_value->eval(scope);
        return a.index(i, v);
    }
}
