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
        return Variable(new Number(l.data()->cmp(r.data())));
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
        return Variable(new Boolean(l.data()->cmp(r.data()) == 0));
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
        return Variable(new Boolean(l.data()->cmp(r.data()) != 0));
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
        return Variable(new Boolean(l.data()->cmp(r.data()) < 0));
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
        return Variable(new Boolean(l.data()->cmp(r.data()) <= 0));
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
        return Variable(new Boolean(l.data()->cmp(r.data()) > 0));
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
        return Variable(new Boolean(l.data()->cmp(r.data()) >= 0));
    }
}
