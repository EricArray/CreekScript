#include <creek/Expression_Bitwise.hpp>

#include <creek/Scope.hpp>
#include <creek/Variable.hpp>


namespace creek
{
    // `ExprBitAnd` constructor.
    // @param  lexpr       Expression for left parameter.
    // @param  rexpr       Expression for right parameter.
    ExprBitAnd::ExprBitAnd(Expression* lexpr, Expression* rexpr) :
        m_lexpr(lexpr),
        m_rexpr(rexpr)
    {

    }

    Variable ExprBitAnd::eval(Scope& scope)
    {
        Variable l(m_lexpr->eval(scope));
        Variable r(m_rexpr->eval(scope));
        return l.bit_and(r);
    }


    // `ExprBitOr` constructor.
    // @param  lexpr       Expression for left parameter.
    // @param  rexpr       Expression for right parameter.
    ExprBitOr::ExprBitOr(Expression* lexpr, Expression* rexpr) :
        m_lexpr(lexpr),
        m_rexpr(rexpr)
    {

    }

    Variable ExprBitOr::eval(Scope& scope)
    {
        Variable l(m_lexpr->eval(scope));
        Variable r(m_rexpr->eval(scope));
        return l.bit_or(r);
    }


    // `ExprBitXor` constructor.
    // @param  lexpr       Expression for left parameter.
    // @param  rexpr       Expression for right parameter.
    ExprBitXor::ExprBitXor(Expression* lexpr, Expression* rexpr) :
        m_lexpr(lexpr),
        m_rexpr(rexpr)
    {

    }

    Variable ExprBitXor::eval(Scope& scope)
    {
        Variable l(m_lexpr->eval(scope));
        Variable r(m_rexpr->eval(scope));
        return l.bit_xor(r);
    }


    // `ExprBitNot` constructor.
    // @param  expr        Expression to negate.
    ExprBitNot::ExprBitNot(Expression* expr) : m_expr(expr)
    {

    }

    Variable ExprBitNot::eval(Scope& scope)
    {
        Variable l(m_expr->eval(scope));
        return l.bit_not();
    }


    // `ExprBitLeftShift` constructor.
    // @param  lexpr       Expression for left parameter.
    // @param  rexpr       Expression for right parameter.
    ExprBitLeftShift::ExprBitLeftShift(Expression* lexpr, Expression* rexpr) :
        m_lexpr(lexpr),
        m_rexpr(rexpr)
    {

    }

    Variable ExprBitLeftShift::eval(Scope& scope)
    {
        Variable l(m_lexpr->eval(scope));
        Variable r(m_rexpr->eval(scope));
        return l.bit_left_shift(r);
    }


    // `ExprBitRightShift` constructor.
    // @param  lexpr       Expression for left parameter.
    // @param  rexpr       Expression for right parameter.
    ExprBitRightShift::ExprBitRightShift(Expression* lexpr, Expression* rexpr) :
        m_lexpr(lexpr),
        m_rexpr(rexpr)
    {

    }

    Variable ExprBitRightShift::eval(Scope& scope)
    {
        Variable l(m_lexpr->eval(scope));
        Variable r(m_rexpr->eval(scope));
        return l.bit_right_shift(r);
    }
}
