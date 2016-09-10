#include <creek/Expression_Arithmetic.hpp>

#include <creek/Scope.hpp>
#include <creek/Variable.hpp>


namespace creek
{
    // `ExprAdd` constructor.
    // @param  lexpr       Expression for left parameter.
    // @param  rexpr       Expression for right parameter.
    ExprAdd::ExprAdd(Expression* lexpr, Expression* rexpr) :
        m_lexpr(lexpr),
        m_rexpr(rexpr)
    {

    }

    Variable ExprAdd::eval(Scope& scope)
    {
        Variable l(m_lexpr->eval(scope));
        Variable r(m_rexpr->eval(scope));
        return l.add(r);
    }


    // `ExprSub` constructor.
    // @param  lexpr       Expression for left parameter.
    // @param  rexpr       Expression for right parameter.
    ExprSub::ExprSub(Expression* lexpr, Expression* rexpr) :
        m_lexpr(lexpr),
        m_rexpr(rexpr)
    {

    }

    Variable ExprSub::eval(Scope& scope)
    {
        Variable l(m_lexpr->eval(scope));
        Variable r(m_rexpr->eval(scope));
        return l.sub(r);
    }


    // `ExprMul` constructor.
    // @param  lexpr       Expression for left parameter.
    // @param  rexpr       Expression for right parameter.
    ExprMul::ExprMul(Expression* lexpr, Expression* rexpr) :
        m_lexpr(lexpr),
        m_rexpr(rexpr)
    {

    }

    Variable ExprMul::eval(Scope& scope)
    {
        Variable l(m_lexpr->eval(scope));
        Variable r(m_rexpr->eval(scope));
        return l.mul(r);
    }


    // `ExprDiv` constructor.
    // @param  lexpr       Expression for left parameter.
    // @param  rexpr       Expression for right parameter.
    ExprDiv::ExprDiv(Expression* lexpr, Expression* rexpr) :
        m_lexpr(lexpr),
        m_rexpr(rexpr)
    {

    }

    Variable ExprDiv::eval(Scope& scope)
    {
        Variable l(m_lexpr->eval(scope));
        Variable r(m_rexpr->eval(scope));
        return l.div(r);
    }


    // `ExprMod` constructor.
    // @param  lexpr       Expression for left parameter.
    // @param  rexpr       Expression for right parameter.
    ExprMod::ExprMod(Expression* lexpr, Expression* rexpr) :
        m_lexpr(lexpr),
        m_rexpr(rexpr)
    {

    }

    Variable ExprMod::eval(Scope& scope)
    {
        Variable l(m_lexpr->eval(scope));
        Variable r(m_rexpr->eval(scope));
        return l.mod(r);
    }


    // `ExprExp` constructor.
    // @param  lexpr       Expression for left parameter.
    // @param  rexpr       Expression for right parameter.
    ExprExp::ExprExp(Expression* lexpr, Expression* rexpr) :
        m_lexpr(lexpr),
        m_rexpr(rexpr)
    {

    }

    Variable ExprExp::eval(Scope& scope)
    {
        Variable l(m_lexpr->eval(scope));
        Variable r(m_rexpr->eval(scope));
        return l.exp(r);
    }


    // `ExprUnm` constructor.
    // @param  expr         Expression to negate.
    ExprUnm::ExprUnm(Expression* expr) : m_expr(expr)
    {

    }

    Variable ExprUnm::eval(Scope& scope)
    {
        Variable l(m_expr->eval(scope));
        return l.unm();
    }
}
