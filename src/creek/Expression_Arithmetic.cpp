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

    Expression* ExprAdd::to_const() const
    {
        
    }

    Bytecode ExprAdd::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(OpCode::add) << m_lexpr->bytecode(var_name_map) << m_rexpr->bytecode(var_name_map);
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

    Expression* ExprSub::to_const() const
    {
        
    }

    Bytecode ExprSub::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(OpCode::sub) << m_lexpr->bytecode(var_name_map) << m_rexpr->bytecode(var_name_map);
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

    Expression* ExprMul::to_const() const
    {
        
    }

    Bytecode ExprMul::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(OpCode::mul) << m_lexpr->bytecode(var_name_map) << m_rexpr->bytecode(var_name_map);
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

    Expression* ExprDiv::to_const() const
    {
        
    }

    Bytecode ExprDiv::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(OpCode::div) << m_lexpr->bytecode(var_name_map) << m_rexpr->bytecode(var_name_map);
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

    Expression* ExprMod::to_const() const
    {
        
    }

    Bytecode ExprMod::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(OpCode::mod) << m_lexpr->bytecode(var_name_map) << m_rexpr->bytecode(var_name_map);
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

    Expression* ExprExp::to_const() const
    {
        
    }

    Bytecode ExprExp::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(OpCode::exp) << m_lexpr->bytecode(var_name_map) << m_rexpr->bytecode(var_name_map);
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

    Expression* ExprUnm::to_const() const
    {
        
    }

    Bytecode ExprUnm::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(OpCode::unm) << m_expr->bytecode(var_name_map);
    }
}
