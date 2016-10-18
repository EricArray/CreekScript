#include <creek/Expression_Variable.hpp>

#include <creek/GlobalScope.hpp>
#include <creek/Scope.hpp>
#include <creek/Variable.hpp>


namespace creek
{
    // @brief  `ExprCreateLocal` constructor.
    // @param  var_name    Variable name.
    // @param  expression  Expression to get value.
    ExprCreateLocal::ExprCreateLocal(VarName var_name, Expression* expression) :
        m_var_name(var_name),
        m_expression(expression)
    {

    }

    Variable ExprCreateLocal::eval(Scope& scope)
    {
        Variable new_value(m_expression->eval(scope));
        scope.create_local_var(m_var_name, new_value->copy());
        return new_value;
    }

    // @brief  `ExprLoadLocal` constructor.
    // @param  var_name    Variable name.
    ExprLoadLocal::ExprLoadLocal(VarName var_name) :
        m_var_name(var_name)
    {

    }

    Variable ExprLoadLocal::eval(Scope& scope)
    {
        return Variable(scope.find_var(m_var_name)->copy());
    }

    // @brief  `ExprStoreLocal` constructor.
    // @param  var_name    Variable name.
    // @param  expression  Expression to get value.
    ExprStoreLocal::ExprStoreLocal(VarName var_name, Expression* expression) :
        m_var_name(var_name),
        m_expression(expression)
    {

    }

    Variable ExprStoreLocal::eval(Scope& scope)
    {
        Variable new_value(m_expression->eval(scope));
        Variable& var = scope.find_var(m_var_name);
        var.data(new_value->copy());
        return new_value;
    }

    // @brief  `ExprCreateGlobal` constructor.
    // @param  var_name    Variable name.
    // @param  expression  Expression to get value.
    ExprCreateGlobal::ExprCreateGlobal(VarName var_name, Expression* expression) :
        m_var_name(var_name),
        m_expression(expression)
    {

    }

    Variable ExprCreateGlobal::eval(Scope& scope)
    {
        Variable new_value(m_expression->eval(scope));
        GlobalScope::instance.create_local_var(m_var_name, new_value->copy());
        return new_value;
    }

    // @brief  `ExprLoadGlobal` constructor.
    // @param  var_name    Variable name.
    ExprLoadGlobal::ExprLoadGlobal(VarName var_name) :
        m_var_name(var_name)
    {

    }

    Variable ExprLoadGlobal::eval(Scope& scope)
    {
        return Variable(GlobalScope::instance.find_var(m_var_name)->copy());
    }

    // @brief  `ExprStoreGlobal` constructor.
    // @param  var_name    Variable name.
    // @param  expression  Expression to get value.
    ExprStoreGlobal::ExprStoreGlobal(VarName var_name, Expression* expression) :
        m_var_name(var_name),
        m_expression(expression)
    {

    }

    Variable ExprStoreGlobal::eval(Scope& scope)
    {
        Variable new_value(m_expression->eval(scope));
        Variable& var = GlobalScope::instance.find_var(m_var_name);
        var.data(new_value->copy());
        return new_value;
    }
}
