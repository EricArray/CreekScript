#include <creek/Expression_Arithmetic.hpp>

#include <creek/Scope.hpp>
#include <creek/Variable.hpp>


namespace creek
{
    // // `ExprAdd` constructor.
    // // @param  lexpr       Expression for left parameter.
    // // @param  rexpr       Expression for right parameter.
    // ExprAdd::ExprAdd(Expression* lexpr, Expression* rexpr) :
    //     m_lexpr(lexpr),
    //     m_rexpr(rexpr)
    // {

    // }

    // Expression* ExprAdd::clone()
    // {
    //     return new ExprAdd(m_lexpr->clone(), m_rexpr->clone());
    // }

    // bool ExprAdd::is_const() const
    // {
    //     return m_lexpr->is_const() && m_rexpr->is_const();
    // }

    // Expression* ExprAdd::const_optimize() const
    // {
    //     if (is_const())
    //     {
    //         Scope scope;
    //         return new ExprConst(eval(scope));
    //     }
    //     else
    //     {
    //         return new ExprAdd(m_lexpr->const_optimize(), m_rexpr->const_optimize());
    //     }
    // }

    // Variable ExprAdd::eval(Scope& scope)
    // {
    //     Variable l(m_lexpr->eval(scope));
    //     Variable r(m_rexpr->eval(scope));
    //     return l.add(r);
    // }

    // Bytecode ExprAdd::bytecode(VarNameMap& var_name_map) const
    // {
    //     return Bytecode() << static_cast<uint8_t>(OpCode::add) << m_lexpr->bytecode(var_name_map) << m_rexpr->bytecode(var_name_map);
    // }


    // // `ExprSub` constructor.
    // // @param  lexpr       Expression for left parameter.
    // // @param  rexpr       Expression for right parameter.
    // ExprSub::ExprSub(Expression* lexpr, Expression* rexpr) :
    //     m_lexpr(lexpr),
    //     m_rexpr(rexpr)
    // {

    // }

    // Expression* ExprSub::clone()
    // {
    //     return new ExprSub(m_lexpr->clone(), m_rexpr->clone());
    // }

    // bool ExprSub::is_const() const
    // {
    //     return m_lexpr->is_const() && m_rexpr->is_const();
    // }

    // Expression* ExprSub::const_optimize() const
    // {
    //     if (is_const())
    //     {
    //         Scope scope;
    //         return new ExprConst(eval(scope));
    //     }
    //     else
    //     {
    //         return new ExprSub(m_lexpr->const_optimize(), m_rexpr->const_optimize());
    //     }
    // }

    // Variable ExprSub::eval(Scope& scope)
    // {
    //     Variable l(m_lexpr->eval(scope));
    //     Variable r(m_rexpr->eval(scope));
    //     return l.sub(r);
    // }

    // Bytecode ExprSub::bytecode(VarNameMap& var_name_map) const
    // {
    //     return Bytecode() << static_cast<uint8_t>(OpCode::sub) << m_lexpr->bytecode(var_name_map) << m_rexpr->bytecode(var_name_map);
    // }


    // // `ExprMul` constructor.
    // // @param  lexpr       Expression for left parameter.
    // // @param  rexpr       Expression for right parameter.
    // ExprMul::ExprMul(Expression* lexpr, Expression* rexpr) :
    //     m_lexpr(lexpr),
    //     m_rexpr(rexpr)
    // {

    // }

    // Expression* ExprMul::clone()
    // {
    //     return new ExprMul(m_lexpr->clone(), m_rexpr->clone());
    // }

    // bool ExprMul::is_const() const
    // {
    //     return m_lexpr->is_const() && m_rexpr->is_const();
    // }

    // Expression* ExprMul::const_optimize() const
    // {
    //     if (is_const())
    //     {
    //         Scope scope;
    //         return new ExprConst(eval(scope));
    //     }
    //     else
    //     {
    //         return new ExprMul(m_lexpr->const_optimize(), m_rexpr->const_optimize());
    //     }
    // }

    // Variable ExprMul::eval(Scope& scope)
    // {
    //     Variable l(m_lexpr->eval(scope));
    //     Variable r(m_rexpr->eval(scope));
    //     return l.mul(r);
    // }

    // Bytecode ExprMul::bytecode(VarNameMap& var_name_map) const
    // {
    //     return Bytecode() << static_cast<uint8_t>(OpCode::mul) << m_lexpr->bytecode(var_name_map) << m_rexpr->bytecode(var_name_map);
    // }


    // // `ExprDiv` constructor.
    // // @param  lexpr       Expression for left parameter.
    // // @param  rexpr       Expression for right parameter.
    // ExprDiv::ExprDiv(Expression* lexpr, Expression* rexpr) :
    //     m_lexpr(lexpr),
    //     m_rexpr(rexpr)
    // {

    // }

    // Expression* ExprDiv::clone()
    // {
    //     return new ExprDiv(m_lexpr->clone(), m_rexpr->clone());
    // }

    // bool ExprDiv::is_const() const
    // {
    //     return m_lexpr->is_const() && m_rexpr->is_const();
    // }

    // Expression* ExprDiv::const_optimize() const
    // {
    //     if (is_const())
    //     {
    //         Scope scope;
    //         return new ExprConst(eval(scope));
    //     }
    //     else
    //     {
    //         return new ExprDiv(m_lexpr->const_optimize(), m_rexpr->const_optimize());
    //     }
    // }

    // Variable ExprDiv::eval(Scope& scope)
    // {
    //     Variable l(m_lexpr->eval(scope));
    //     Variable r(m_rexpr->eval(scope));
    //     return l.div(r);
    // }

    // Bytecode ExprDiv::bytecode(VarNameMap& var_name_map) const
    // {
    //     return Bytecode() << static_cast<uint8_t>(OpCode::div) << m_lexpr->bytecode(var_name_map) << m_rexpr->bytecode(var_name_map);
    // }


    // // `ExprMod` constructor.
    // // @param  lexpr       Expression for left parameter.
    // // @param  rexpr       Expression for right parameter.
    // ExprMod::ExprMod(Expression* lexpr, Expression* rexpr) :
    //     m_lexpr(lexpr),
    //     m_rexpr(rexpr)
    // {

    // }

    // Expression* ExprMod::clone()
    // {
    //     return new ExprMod(m_lexpr->clone(), m_rexpr->clone());
    // }

    // bool ExprMod::is_const() const
    // {
    //     return m_lexpr->is_const() && m_rexpr->is_const();
    // }

    // Expression* ExprMod::const_optimize() const
    // {
    //     if (is_const())
    //     {
    //         Scope scope;
    //         return new ExprConst(eval(scope));
    //     }
    //     else
    //     {
    //         return new ExprMod(m_lexpr->const_optimize(), m_rexpr->const_optimize());
    //     }
    // }

    // Variable ExprMod::eval(Scope& scope)
    // {
    //     Variable l(m_lexpr->eval(scope));
    //     Variable r(m_rexpr->eval(scope));
    //     return l.mod(r);
    // }

    // Bytecode ExprMod::bytecode(VarNameMap& var_name_map) const
    // {
    //     return Bytecode() << static_cast<uint8_t>(OpCode::mod) << m_lexpr->bytecode(var_name_map) << m_rexpr->bytecode(var_name_map);
    // }


    // // `ExprExp` constructor.
    // // @param  lexpr       Expression for left parameter.
    // // @param  rexpr       Expression for right parameter.
    // ExprExp::ExprExp(Expression* lexpr, Expression* rexpr) :
    //     m_lexpr(lexpr),
    //     m_rexpr(rexpr)
    // {

    // }

    // Expression* ExprExp::clone()
    // {
    //     return new ExprExp(m_lexpr->clone(), m_rexpr->clone());
    // }

    // bool ExprExp::is_const() const
    // {
    //     return m_lexpr->is_const() && m_rexpr->is_const();
    // }

    // Expression* ExprExp::const_optimize() const
    // {
    //     if (is_const())
    //     {
    //         Scope scope;
    //         return new ExprConst(eval(scope));
    //     }
    //     else
    //     {
    //         return new ExprExp(m_lexpr->const_optimize(), m_rexpr->const_optimize());
    //     }
    // }

    // Variable ExprExp::eval(Scope& scope)
    // {
    //     Variable l(m_lexpr->eval(scope));
    //     Variable r(m_rexpr->eval(scope));
    //     return l.exp(r);
    // }

    // Bytecode ExprExp::bytecode(VarNameMap& var_name_map) const
    // {
    //     return Bytecode() << static_cast<uint8_t>(OpCode::exp) << m_lexpr->bytecode(var_name_map) << m_rexpr->bytecode(var_name_map);
    // }


    // // `ExprUnm` constructor.
    // // @param  expr         Expression to negate.
    // ExprUnm::ExprUnm(Expression* expr) : m_expr(expr)
    // {

    // }

    // Variable ExprUnm::eval(Scope& scope)
    // {
    //     Variable l(m_expr->eval(scope));
    //     return l.unm();
    // }

    // Bytecode ExprUnm::bytecode(VarNameMap& var_name_map) const
    // {
    //     return Bytecode() << static_cast<uint8_t>(OpCode::unm) << m_expr->bytecode(var_name_map);
    // }
}
