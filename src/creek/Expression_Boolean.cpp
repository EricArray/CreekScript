#include <creek/Expression_Boolean.hpp>

#include <creek/Boolean.hpp>
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

    Variable ExprBoolAnd::eval(Scope& scope)
    {
        Variable l(m_lexpr->eval(scope));
        if (l->bool_value() == false)
        {
            return l;
        }
        else
        {
            Variable r(m_rexpr->eval(scope));
            return r;
        }
    }


    // `ExprBoolOr` constructor.
    // @param  lexpr       Expression for left parameter.
    // @param  rexpr       Expression for right parameter.
    ExprBoolOr::ExprBoolOr(Expression* lexpr, Expression* rexpr) :
        m_lexpr(lexpr),
        m_rexpr(rexpr)
    {

    }

    Variable ExprBoolOr::eval(Scope& scope)
    {
        Variable l(m_lexpr->eval(scope));
        if (l->bool_value() == true)
        {
            return l;
        }
        else
        {
            Variable r(m_rexpr->eval(scope));
            return r;
        }
    }


    // `ExprBoolXor` constructor.
    // @param  lexpr       Expression for left parameter.
    // @param  rexpr       Expression for right parameter.
    ExprBoolXor::ExprBoolXor(Expression* lexpr, Expression* rexpr) :
        m_lexpr(lexpr),
        m_rexpr(rexpr)
    {

    }

    Variable ExprBoolXor::eval(Scope& scope)
    {
        Variable l(m_lexpr->eval(scope));
        Variable r(m_rexpr->eval(scope));

        bool l_bool = l->bool_value();
        bool r_bool = r->bool_value();

        return Variable(new Boolean(l_bool != r_bool));
    }


    // `ExprBoolNot` constructor.
    // @param  expr        Expression to negate.
    ExprBoolNot::ExprBoolNot(Expression* expr) : m_expr(expr)
    {

    }

    Variable ExprBoolNot::eval(Scope& scope)
    {
        Variable l(m_expr->eval(scope));
        return Variable(new Boolean(!l->bool_value()));
    }
}
