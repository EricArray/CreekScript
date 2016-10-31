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

    Bytecode ExprCreateLocal::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() <<
            static_cast<uint8_t>(OpCode::var_create_local) <<
            var_name_map.id_from_name(m_var_name.name()) <<
            m_expression->bytecode(var_name_map);
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

    Bytecode ExprLoadLocal::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() <<
            static_cast<uint8_t>(OpCode::var_load_local) <<
            var_name_map.id_from_name(m_var_name.name());
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

    Bytecode ExprStoreLocal::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() <<
            static_cast<uint8_t>(OpCode::var_store_local) <<
            var_name_map.id_from_name(m_var_name.name()) <<
            m_expression->bytecode(var_name_map);
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

    Bytecode ExprCreateGlobal::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() <<
            static_cast<uint8_t>(OpCode::var_create_global) <<
            var_name_map.id_from_name(m_var_name.name()) <<
            m_expression->bytecode(var_name_map);
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

    Bytecode ExprLoadGlobal::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() <<
            static_cast<uint8_t>(OpCode::var_load_global) <<
            var_name_map.id_from_name(m_var_name.name());
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

    Bytecode ExprStoreGlobal::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() <<
            static_cast<uint8_t>(OpCode::var_store_global) <<
            var_name_map.id_from_name(m_var_name.name()) <<
            m_expression->bytecode(var_name_map);
    }
}
