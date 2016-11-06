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

    Expression* ExprCreateLocal::clone() const
    {
        return new ExprCreateLocal(m_var_name, m_expression->clone());
    }

    bool ExprCreateLocal::is_const() const
    {
        return false;
    }

    Expression* ExprCreateLocal::const_optimize() const
    {
        return new ExprCreateLocal(m_var_name, m_expression->const_optimize());
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

    Expression* ExprLoadLocal::clone() const
    {
        return new ExprLoadLocal(m_var_name);
    }

    bool ExprLoadLocal::is_const() const
    {
        return false;
    }

    Expression* ExprLoadLocal::const_optimize() const
    {
        return new ExprLoadLocal(m_var_name);
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

    Expression* ExprStoreLocal::clone() const
    {
        return new ExprStoreLocal(m_var_name, m_expression->clone());
    }

    bool ExprStoreLocal::is_const() const
    {
        return false;
    }

    Expression* ExprStoreLocal::const_optimize() const
    {
        return new ExprStoreLocal(m_var_name, m_expression->const_optimize());
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

    Expression* ExprCreateGlobal::clone() const
    {
        return new ExprCreateGlobal(m_var_name, m_expression->clone());
    }

    bool ExprCreateGlobal::is_const() const
    {
        return false;
    }

    Expression* ExprCreateGlobal::const_optimize() const
    {
        return new ExprCreateGlobal(m_var_name, m_expression->const_optimize());
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

    Expression* ExprLoadGlobal::clone() const
    {
        return new ExprLoadGlobal(m_var_name);
    }

    bool ExprLoadGlobal::is_const() const
    {
        return false;
    }

    Expression* ExprLoadGlobal::const_optimize() const
    {
        return new ExprLoadGlobal(m_var_name);
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

    Expression* ExprStoreGlobal::clone() const
    {
        return new ExprStoreGlobal(m_var_name, m_expression->clone());
    }

    bool ExprStoreGlobal::is_const() const
    {
        return false;
    }

    Expression* ExprStoreGlobal::const_optimize() const
    {
        return new ExprStoreGlobal(m_var_name, m_expression->const_optimize());
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
