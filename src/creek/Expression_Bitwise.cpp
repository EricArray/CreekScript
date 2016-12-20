#include <creek/Expression_Bitwise.hpp>

#include <creek/OpCode.hpp>
#include <creek/Scope.hpp>
#include <creek/Variable.hpp>


namespace creek
{
    // // `ExprBitAnd` constructor.
    // // @param  lexpr       Expression for left parameter.
    // // @param  rexpr       Expression for right parameter.
    // ExprBitAnd::ExprBitAnd(Expression* lexpr, Expression* rexpr) :
    //     m_lexpr(lexpr),
    //     m_rexpr(rexpr)
    // {

    // }

    // Variable ExprBitAnd::eval(const SharedPointer<Scope>& scope)
    // {
    //     Variable l(m_lexpr->eval(scope));
    //     Variable r(m_rexpr->eval(scope));
    //     return l.bit_and(scope, r);
    // }

    // Bytecode ExprBitAnd::bytecode(VarNameMap& var_name_map) const
    // {
    //     return Bytecode() << static_cast<uint8_t>(OpCode::bit_and) << m_lexpr->bytecode(var_name_map) << m_rexpr->bytecode(var_name_map);
    // }


    // // `ExprBitOr` constructor.
    // // @param  lexpr       Expression for left parameter.
    // // @param  rexpr       Expression for right parameter.
    // ExprBitOr::ExprBitOr(Expression* lexpr, Expression* rexpr) :
    //     m_lexpr(lexpr),
    //     m_rexpr(rexpr)
    // {

    // }

    // Variable ExprBitOr::eval(const SharedPointer<Scope>& scope)
    // {
    //     Variable l(m_lexpr->eval(scope));
    //     Variable r(m_rexpr->eval(scope));
    //     return l.bit_or(scope, r);
    // }

    // Bytecode ExprBitOr::bytecode(VarNameMap& var_name_map) const
    // {
    //     return Bytecode() << static_cast<uint8_t>(OpCode::bit_or) << m_lexpr->bytecode(var_name_map) << m_rexpr->bytecode(var_name_map);
    // }


    // // `ExprBitXor` constructor.
    // // @param  lexpr       Expression for left parameter.
    // // @param  rexpr       Expression for right parameter.
    // ExprBitXor::ExprBitXor(Expression* lexpr, Expression* rexpr) :
    //     m_lexpr(lexpr),
    //     m_rexpr(rexpr)
    // {

    // }

    // Variable ExprBitXor::eval(const SharedPointer<Scope>& scope)
    // {
    //     Variable l(m_lexpr->eval(scope));
    //     Variable r(m_rexpr->eval(scope));
    //     return l.bit_xor(scope, r);
    // }

    // Bytecode ExprBitXor::bytecode(VarNameMap& var_name_map) const
    // {
    //     return Bytecode() << static_cast<uint8_t>(OpCode::bit_xor) << m_lexpr->bytecode(var_name_map) << m_rexpr->bytecode(var_name_map);
    // }


    // // `ExprBitNot` constructor.
    // // @param  expr        Expression to negate.
    // ExprBitNot::ExprBitNot(Expression* expr) : m_expr(expr)
    // {

    // }

    // Variable ExprBitNot::eval(const SharedPointer<Scope>& scope)
    // {
    //     Variable l(m_expr->eval(scope));
    //     return l.bit_not(scope);
    // }

    // Bytecode ExprBitNot::bytecode(VarNameMap& var_name_map) const
    // {
    //     return Bytecode() << static_cast<uint8_t>(OpCode::bit_not) << m_expr->bytecode(var_name_map);
    // }


    // // `ExprBitLeftShift` constructor.
    // // @param  lexpr       Expression for left parameter.
    // // @param  rexpr       Expression for right parameter.
    // ExprBitLeftShift::ExprBitLeftShift(Expression* lexpr, Expression* rexpr) :
    //     m_lexpr(lexpr),
    //     m_rexpr(rexpr)
    // {

    // }

    // Variable ExprBitLeftShift::eval(const SharedPointer<Scope>& scope)
    // {
    //     Variable l(m_lexpr->eval(scope));
    //     Variable r(m_rexpr->eval(scope));
    //     return l.bit_left_shift(scope, r);
    // }

    // Bytecode ExprBitLeftShift::bytecode(VarNameMap& var_name_map) const
    // {
    //     return Bytecode() << static_cast<uint8_t>(OpCode::bit_left_shift) << m_lexpr->bytecode(var_name_map) << m_rexpr->bytecode(var_name_map);
    // }


    // // `ExprBitRightShift` constructor.
    // // @param  lexpr       Expression for left parameter.
    // // @param  rexpr       Expression for right parameter.
    // ExprBitRightShift::ExprBitRightShift(Expression* lexpr, Expression* rexpr) :
    //     m_lexpr(lexpr),
    //     m_rexpr(rexpr)
    // {

    // }

    // Variable ExprBitRightShift::eval(const SharedPointer<Scope>& scope)
    // {
    //     Variable l(m_lexpr->eval(scope));
    //     Variable r(m_rexpr->eval(scope));
    //     return l.bit_right_shift(scope, r);
    // }

    // Bytecode ExprBitRightShift::bytecode(VarNameMap& var_name_map) const
    // {
    //     return Bytecode() << static_cast<uint8_t>(OpCode::bit_right_shift) << m_lexpr->bytecode(var_name_map) << m_rexpr->bytecode(var_name_map);
    // }
}
