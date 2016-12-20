#include <creek/Expression_Comparison.hpp>

#include <creek/Boolean.hpp>
#include <creek/Expression_DataTypes.hpp>
#include <creek/Number.hpp>
#include <creek/Scope.hpp>
#include <creek/Variable.hpp>


namespace creek
{
    // `ExprCmp` constructor.
    // @param  lexpr   Expression for left parameter.
    // @param  rexpr   Expression for right parameter.
    ExprCmp::ExprCmp(Expression* lexpr, Expression* rexpr) : m_lexpr(lexpr), m_rexpr(rexpr)
    {

    }

    Expression* ExprCmp::clone() const
    {
        return new ExprCmp(m_lexpr->clone(), m_rexpr->clone());
    }

    bool ExprCmp::is_const() const
    {
        return m_lexpr->is_const() && m_rexpr->is_const();
    }

    Expression* ExprCmp::const_optimize() const
    {
        if (is_const())
        {
            auto scope = SharedPointer<ConstScope>::make();
            Variable l(m_lexpr->eval(scope));
            Variable r(m_rexpr->eval(scope));
            return new ExprNumber(l->cmp(scope, *r));
        }
        else
        {
            return new ExprCmp(m_lexpr->const_optimize(), m_rexpr->const_optimize());
        }
    }

    Variable ExprCmp::eval(const SharedPointer<Scope>& scope)
    {
        Variable l(m_lexpr->eval(scope));
        Variable r(m_rexpr->eval(scope));
        return Variable(new Number(l->cmp(scope, *r)));
    }

    Bytecode ExprCmp::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(OpCode::cmp) << m_lexpr->bytecode(var_name_map) << m_rexpr->bytecode(var_name_map);
    }


    // `ExprEQ` constructor.
    // @param  lexpr   Expression for left parameter.
    // @param  rexpr   Expression for right parameter.
    ExprEQ::ExprEQ(Expression* lexpr, Expression* rexpr) : m_lexpr(lexpr), m_rexpr(rexpr)
    {

    }

    Expression* ExprEQ::clone() const
    {
        return new ExprEQ(m_lexpr->clone(), m_rexpr->clone());
    }

    bool ExprEQ::is_const() const
    {
        return m_lexpr->is_const() && m_rexpr->is_const();
    }

    Expression* ExprEQ::const_optimize() const
    {
        if (is_const())
        {
            auto scope = SharedPointer<ConstScope>::make();
            Variable l(m_lexpr->eval(scope));
            Variable r(m_rexpr->eval(scope));
            return new ExprBoolean(l->cmp(scope, *r) == 0);
        }
        else
        {
            return new ExprEQ(m_lexpr->const_optimize(), m_rexpr->const_optimize());
        }
    }

    Variable ExprEQ::eval(const SharedPointer<Scope>& scope)
    {
        Variable l(m_lexpr->eval(scope));
        Variable r(m_rexpr->eval(scope));
        return Variable(new Boolean(l->cmp(scope, *r) == 0));
    }

    Bytecode ExprEQ::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(OpCode::eq) << m_lexpr->bytecode(var_name_map) << m_rexpr->bytecode(var_name_map);
    }


    // `ExprNE` constructor.
    // @param  lexpr   Expression for left parameter.
    // @param  rexpr   Expression for right parameter.
    ExprNE::ExprNE(Expression* lexpr, Expression* rexpr) : m_lexpr(lexpr), m_rexpr(rexpr)
    {

    }

    Expression* ExprNE::clone() const
    {
        return new ExprNE(m_lexpr->clone(), m_rexpr->clone());
    }

    bool ExprNE::is_const() const
    {
        return m_lexpr->is_const() && m_rexpr->is_const();
    }

    Expression* ExprNE::const_optimize() const
    {
        if (is_const())
        {
            auto scope = SharedPointer<ConstScope>::make();
            Variable l(m_lexpr->eval(scope));
            Variable r(m_rexpr->eval(scope));
            return new ExprBoolean(l->cmp(scope, *r) != 0);
        }
        else
        {
            return new ExprNE(m_lexpr->const_optimize(), m_rexpr->const_optimize());
        }
    }

    Variable ExprNE::eval(const SharedPointer<Scope>& scope)
    {
        Variable l(m_lexpr->eval(scope));
        Variable r(m_rexpr->eval(scope));
        return Variable(new Boolean(l->cmp(scope, *r) != 0));
    }

    Bytecode ExprNE::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(OpCode::ne) << m_lexpr->bytecode(var_name_map) << m_rexpr->bytecode(var_name_map);
    }


    // `ExprLT` constructor.
    // @param  lexpr   Expression for left parameter.
    // @param  rexpr   Expression for right parameter.
    ExprLT::ExprLT(Expression* lexpr, Expression* rexpr) : m_lexpr(lexpr), m_rexpr(rexpr)
    {

    }

    Expression* ExprLT::clone() const
    {
        return new ExprLT(m_lexpr->clone(), m_rexpr->clone());
    }

    bool ExprLT::is_const() const
    {
        return m_lexpr->is_const() && m_rexpr->is_const();
    }

    Expression* ExprLT::const_optimize() const
    {
        if (is_const())
        {
            auto scope = SharedPointer<ConstScope>::make();
            Variable l(m_lexpr->eval(scope));
            Variable r(m_rexpr->eval(scope));
            return new ExprBoolean(l->cmp(scope, *r) < 0);
        }
        else
        {
            return new ExprLT(m_lexpr->const_optimize(), m_rexpr->const_optimize());
        }
    }

    Variable ExprLT::eval(const SharedPointer<Scope>& scope)
    {
        Variable l(m_lexpr->eval(scope));
        Variable r(m_rexpr->eval(scope));
        return Variable(new Boolean(l->cmp(scope, *r) < 0));
    }

    Bytecode ExprLT::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(OpCode::lt) << m_lexpr->bytecode(var_name_map) << m_rexpr->bytecode(var_name_map);
    }


    // `ExprLE` constructor.
    // @param  lexpr   Expression for left parameter.
    // @param  rexpr   Expression for right parameter.
    ExprLE::ExprLE(Expression* lexpr, Expression* rexpr) : m_lexpr(lexpr), m_rexpr(rexpr)
    {

    }

    Expression* ExprLE::clone() const
    {
        return new ExprLE(m_lexpr->clone(), m_rexpr->clone());
    }

    bool ExprLE::is_const() const
    {
        return m_lexpr->is_const() && m_rexpr->is_const();
    }

    Expression* ExprLE::const_optimize() const
    {
        if (is_const())
        {
            auto scope = SharedPointer<ConstScope>::make();
            Variable l(m_lexpr->eval(scope));
            Variable r(m_rexpr->eval(scope));
            return new ExprBoolean(l->cmp(scope, *r) <= 0);
        }
        else
        {
            return new ExprLE(m_lexpr->const_optimize(), m_rexpr->const_optimize());
        }
    }

    Variable ExprLE::eval(const SharedPointer<Scope>& scope)
    {
        Variable l(m_lexpr->eval(scope));
        Variable r(m_rexpr->eval(scope));
        return Variable(new Boolean(l->cmp(scope, *r) <= 0));
    }

    Bytecode ExprLE::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(OpCode::le) << m_lexpr->bytecode(var_name_map) << m_rexpr->bytecode(var_name_map);
    }


    // `ExprGT` constructor.
    // @param  lexpr   Expression for left parameter.
    // @param  rexpr   Expression for right parameter.
    ExprGT::ExprGT(Expression* lexpr, Expression* rexpr) : m_lexpr(lexpr), m_rexpr(rexpr)
    {

    }

    Expression* ExprGT::clone() const
    {
        return new ExprGT(m_lexpr->clone(), m_rexpr->clone());
    }

    bool ExprGT::is_const() const
    {
        return m_lexpr->is_const() && m_rexpr->is_const();
    }

    Expression* ExprGT::const_optimize() const
    {
        if (is_const())
        {
            auto scope = SharedPointer<ConstScope>::make();
            Variable l(m_lexpr->eval(scope));
            Variable r(m_rexpr->eval(scope));
            return new ExprBoolean(l->cmp(scope, *r) > 0);
        }
        else
        {
            return new ExprGT(m_lexpr->const_optimize(), m_rexpr->const_optimize());
        }
    }

    Variable ExprGT::eval(const SharedPointer<Scope>& scope)
    {
        Variable l(m_lexpr->eval(scope));
        Variable r(m_rexpr->eval(scope));
        return Variable(new Boolean(l->cmp(scope, *r) > 0));
    }

    Bytecode ExprGT::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(OpCode::gt) << m_lexpr->bytecode(var_name_map) << m_rexpr->bytecode(var_name_map);
    }


    // `ExprGE` constructor.
    // @param  lexpr   Expression for left parameter.
    // @param  rexpr   Expression for right parameter.
    ExprGE::ExprGE(Expression* lexpr, Expression* rexpr) : m_lexpr(lexpr), m_rexpr(rexpr)
    {

    }

    Expression* ExprGE::clone() const
    {
        return new ExprGE(m_lexpr->clone(), m_rexpr->clone());
    }

    bool ExprGE::is_const() const
    {
        return m_lexpr->is_const() && m_rexpr->is_const();
    }

    Expression* ExprGE::const_optimize() const
    {
        if (is_const())
        {
            auto scope = SharedPointer<ConstScope>::make();
            Variable l(m_lexpr->eval(scope));
            Variable r(m_rexpr->eval(scope));
            return new ExprBoolean(l->cmp(scope, *r) >= 0);
        }
        else
        {
            return new ExprGE(m_lexpr->const_optimize(), m_rexpr->const_optimize());
        }
    }

    Variable ExprGE::eval(const SharedPointer<Scope>& scope)
    {
        Variable l(m_lexpr->eval(scope));
        Variable r(m_rexpr->eval(scope));
        return Variable(new Boolean(l->cmp(scope, *r) >= 0));
    }

    Bytecode ExprGE::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(OpCode::ge) << m_lexpr->bytecode(var_name_map) << m_rexpr->bytecode(var_name_map);
    }
}
