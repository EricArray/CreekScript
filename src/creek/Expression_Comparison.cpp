#include <creek/Expression_Comparison.hpp>

#include <creek/Boolean.hpp>
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

    Variable ExprCmp::eval(Scope& scope)
    {
        Variable l(m_lexpr->eval(scope));
        Variable r(m_rexpr->eval(scope));
        return Variable(new Number(l->cmp(*r)));
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

    Variable ExprEQ::eval(Scope& scope)
    {
        Variable l(m_lexpr->eval(scope));
        Variable r(m_rexpr->eval(scope));
        return Variable(new Boolean(l->cmp(*r) == 0));
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

    Variable ExprNE::eval(Scope& scope)
    {
        Variable l(m_lexpr->eval(scope));
        Variable r(m_rexpr->eval(scope));
        return Variable(new Boolean(l->cmp(*r) != 0));
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

    Variable ExprLT::eval(Scope& scope)
    {
        Variable l(m_lexpr->eval(scope));
        Variable r(m_rexpr->eval(scope));
        return Variable(new Boolean(l->cmp(*r) < 0));
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

    Variable ExprLE::eval(Scope& scope)
    {
        Variable l(m_lexpr->eval(scope));
        Variable r(m_rexpr->eval(scope));
        return Variable(new Boolean(l->cmp(*r) <= 0));
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

    Variable ExprGT::eval(Scope& scope)
    {
        Variable l(m_lexpr->eval(scope));
        Variable r(m_rexpr->eval(scope));
        return Variable(new Boolean(l->cmp(*r) > 0));
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

    Variable ExprGE::eval(Scope& scope)
    {
        Variable l(m_lexpr->eval(scope));
        Variable r(m_rexpr->eval(scope));
        return Variable(new Boolean(l->cmp(*r) >= 0));
    }

    Bytecode ExprGE::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(OpCode::ge) << m_lexpr->bytecode(var_name_map) << m_rexpr->bytecode(var_name_map);
    }
}
