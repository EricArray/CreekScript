#include <creek/Expression_Boolean.hpp>

#include <creek/Boolean.hpp>
#include <creek/Expression_DataTypes.hpp>
#include <creek/OpCode.hpp>
#include <creek/Scope.hpp>
#include <creek/Variable.hpp>


namespace creek
{
    // `ExprBoolAnd` constructor.
    // @param  lexpr       Expression for left parameter.
    // @param  rexpr       Expression for right parameter.
    ExprBoolAnd::ExprBoolAnd(Expression* lexpr, Expression* rexpr) :
        m_lexpr(lexpr),
        m_rexpr(rexpr)
    {

    }

    Expression* ExprBoolAnd::clone() const
    {
        return new ExprBoolAnd(m_lexpr->clone(), m_rexpr->clone());
    }

    bool ExprBoolAnd::is_const() const
    {
        if (m_lexpr->is_const())
        {
            auto scope = SharedPointer<ConstScope>::make();
            Variable l(m_lexpr->eval(scope));
            if (l->bool_value(scope) == true)
            {
                return true;
            }
            else
            {
                return m_rexpr->is_const();
            }
        }
        return false;
    }

    Expression* ExprBoolAnd::const_optimize() const
    {
        if (m_lexpr->is_const())
        {
            auto scope = SharedPointer<ConstScope>::make();
            Variable l = m_lexpr->eval(scope);
            if (l->bool_value(scope) == true)
            {
                return m_lexpr->const_optimize();
            }
            else
            {
                return m_rexpr->const_optimize();
            }
        }
        else
        {
            return new ExprBoolAnd(m_lexpr->const_optimize(), m_rexpr->const_optimize());
        }
    }

    Variable ExprBoolAnd::eval(const SharedPointer<Scope>& scope)
    {
        Variable l(m_lexpr->eval(scope));
        if (l->bool_value(scope) == false)
        {
            return l;
        }
        else
        {
            Variable r(m_rexpr->eval(scope));
            return r;
        }
    }

    Bytecode ExprBoolAnd::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(OpCode::bool_and) << m_lexpr->bytecode(var_name_map) << m_rexpr->bytecode(var_name_map);
    }


    // `ExprBoolOr` constructor.
    // @param  lexpr       Expression for left parameter.
    // @param  rexpr       Expression for right parameter.
    ExprBoolOr::ExprBoolOr(Expression* lexpr, Expression* rexpr) :
        m_lexpr(lexpr),
        m_rexpr(rexpr)
    {

    }

    Expression* ExprBoolOr::clone() const
    {
        return new ExprBoolOr(m_lexpr->clone(), m_rexpr->clone());
    }

    bool ExprBoolOr::is_const() const
    {
        if (m_lexpr->is_const())
        {
            auto scope = SharedPointer<ConstScope>::make();
            Variable l(m_lexpr->eval(scope));
            if (l->bool_value(scope) == false)
            {
                return true;
            }
            else
            {
                return m_rexpr->is_const();
            }
        }
        return false;
    }

    Expression* ExprBoolOr::const_optimize() const
    {
        if (m_lexpr->is_const())
        {
            auto scope = SharedPointer<ConstScope>::make();
            Variable l = m_lexpr->eval(scope);
            if (l->bool_value(scope) == false)
            {
                return m_lexpr->const_optimize();
            }
            else
            {
                return m_rexpr->const_optimize();
            }
        }
        else
        {
            return new ExprBoolOr(m_lexpr->const_optimize(), m_rexpr->const_optimize());
        }
    }

    Variable ExprBoolOr::eval(const SharedPointer<Scope>& scope)
    {
        Variable l(m_lexpr->eval(scope));
        if (l->bool_value(scope) == true)
        {
            return l;
        }
        else
        {
            Variable r(m_rexpr->eval(scope));
            return r;
        }
    }

    Bytecode ExprBoolOr::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(OpCode::bool_or) << m_lexpr->bytecode(var_name_map) << m_rexpr->bytecode(var_name_map);
    }


    // `ExprBoolXor` constructor.
    // @param  lexpr       Expression for left parameter.
    // @param  rexpr       Expression for right parameter.
    ExprBoolXor::ExprBoolXor(Expression* lexpr, Expression* rexpr) :
        m_lexpr(lexpr),
        m_rexpr(rexpr)
    {

    }

    Expression* ExprBoolXor::clone() const
    {
        return new ExprBoolXor(m_lexpr->clone(), m_rexpr->clone());
    }

    bool ExprBoolXor::is_const() const
    {
        return m_lexpr->is_const() && m_rexpr->is_const();
    }

    Expression* ExprBoolXor::const_optimize() const
    {
        if (is_const())
        {
            auto scope = SharedPointer<ConstScope>::make();
            Variable l(m_lexpr->eval(scope));
            Variable r(m_rexpr->eval(scope));
            return new ExprBoolean(l->bool_value(scope) != r->bool_value(scope));
        }
        else
        {
            return new ExprBoolXor(m_lexpr->const_optimize(), m_rexpr->const_optimize());
        }
    }

    Variable ExprBoolXor::eval(const SharedPointer<Scope>& scope)
    {
        Variable l(m_lexpr->eval(scope));
        Variable r(m_rexpr->eval(scope));

        bool l_bool = l->bool_value(scope);
        bool r_bool = r->bool_value(scope);

        return Variable(new Boolean(l_bool != r_bool));
    }

    Bytecode ExprBoolXor::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(OpCode::bool_xor) << m_lexpr->bytecode(var_name_map) << m_rexpr->bytecode(var_name_map);
    }


    // `ExprBoolNot` constructor.
    // @param  expr        Expression to negate.
    ExprBoolNot::ExprBoolNot(Expression* expr) : m_expr(expr)
    {

    }

    Expression* ExprBoolNot::clone() const
    {
        return new ExprBoolNot(m_expr->clone());
    }

    bool ExprBoolNot::is_const() const
    {
        return m_expr->is_const();
    }

    Expression* ExprBoolNot::const_optimize() const
    {
        if (is_const())
        {
            auto scope = SharedPointer<ConstScope>::make();
            Variable v(m_expr->eval(scope));
            return new ExprBoolean(!v->bool_value(scope));
        }
        else
        {
            return new ExprBoolNot(m_expr->const_optimize());
        }
    }

    Variable ExprBoolNot::eval(const SharedPointer<Scope>& scope)
    {
        Variable l(m_expr->eval(scope));
        return Variable(new Boolean(!l->bool_value(scope)));
    }

    Bytecode ExprBoolNot::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(OpCode::bool_not) << m_expr->bytecode(var_name_map);
    }
}
