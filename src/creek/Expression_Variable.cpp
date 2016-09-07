#include <creek/Expression_Variable.hpp>

#include <creek/Scope.hpp>
#include <creek/Variable.hpp>


namespace creek
{
    // ExprLocalVar constructor.
    // @param  var_name    Variable name.
    // @param  expression  Expression to get value.
    ExprLocalVar::ExprLocalVar(VarName var_name, Expression* expression) :
        m_var_name(var_name),
        m_expression(expression)
    {

    }

    Variable ExprLocalVar::eval(Scope& scope)
    {
        Variable new_value(m_expression->eval(scope));
        scope.create_local_var(m_var_name, new_value->copy());
        return new_value;
    }

    // ExprLoadVar constructor.
    // @param  var_name    Variable name.
    ExprLoadVar::ExprLoadVar(VarName var_name) : m_var_name(var_name)
    {

    }

    Variable ExprLoadVar::eval(Scope& scope)
    {
        return Variable(scope.find_var(m_var_name)->copy());
    }

    // ExprStoreVar constructor.
    // @param  var_name    Variable name.
    // @param  expression  Expression to get value.
    ExprStoreVar::ExprStoreVar(VarName var_name, Expression* expression) :
        m_var_name(var_name),
        m_expression(expression)
    {

    }

    Variable ExprStoreVar::eval(Scope& scope)
    {
        Variable new_value(m_expression->eval(scope));
        Variable& var = scope.find_var(m_var_name);
        var.data(new_value->copy());
        return new_value;
    }
}