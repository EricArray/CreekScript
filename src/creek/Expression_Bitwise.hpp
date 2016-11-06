#pragma once

#include <creek/Expression_General.hpp>

#include <memory>

#include <creek/api_mode.hpp>


namespace creek
{
    /// @defgroup   expression_bitwise  Bitwise operations
    /// @{

    /// Expression: Bitwise AND two values.
    /// Returns L & R.
    using ExprBitAnd = ExprBinary<OpCode::bit_and, &Data::bit_and>;

    /// Expression: Bitwise OR two values.
    /// Returns L | R.
    using ExprBitOr = ExprBinary<OpCode::bit_or, &Data::bit_or>;

    /// Expression: Bitwise XOR two values.
    /// Returns L ^ R.
    using ExprBitXor = ExprBinary<OpCode::bit_xor, &Data::bit_xor>;

    /// Expression: Bitwise NOT one value.
    /// Returns ~L.
    using ExprBitNot = ExprUnary<OpCode::bit_not, &Data::bit_not>;

    /// Expression: Bitwise left shift two values.
    /// Returns L << R.
    using ExprBitLeftShift = ExprBinary<OpCode::bit_left_shift, &Data::bit_left_shift>;

    /// Expression: Bitwise right shift two values.
    /// Returns L >> R.
    using ExprBitRightShift = ExprBinary<OpCode::bit_right_shift, &Data::bit_right_shift>;


    // /// Expression: Bitwise AND two values.
    // /// Returns L & R.
    // class CREEK_API ExprBitAnd : public Expression
    // {
    // public:
    //     /// `ExprBitAnd` constructor.
    //     /// @param  lexpr       Expression for left parameter.
    //     /// @param  rexpr       Expression for right parameter.
    //     ExprBitAnd(Expression* lexpr, Expression* rexpr);

    //     Variable eval(Scope& scope) override;
    //     Bytecode bytecode(VarNameMap& var_name_map) const override;

    // private:
    //     std::unique_ptr<Expression> m_lexpr;
    //     std::unique_ptr<Expression> m_rexpr;
    // };


    // /// Expression: Bitwise OR two values.
    // /// Returns L | R.
    // class CREEK_API ExprBitOr : public Expression
    // {
    // public:
    //     /// `ExprBitOr` constructor.
    //     /// @param  lexpr       Expression for left parameter.
    //     /// @param  rexpr       Expression for right parameter.
    //     ExprBitOr(Expression* lexpr, Expression* rexpr);

    //     Variable eval(Scope& scope) override;
    //     Bytecode bytecode(VarNameMap& var_name_map) const override;

    // private:
    //     std::unique_ptr<Expression> m_lexpr;
    //     std::unique_ptr<Expression> m_rexpr;
    // };


    // /// Expression: Bitwise XOR two values.
    // /// Returns L ^ R.
    // class CREEK_API ExprBitXor : public Expression
    // {
    // public:
    //     /// `ExprBitXor` constructor.
    //     /// @param  lexpr       Expression for left parameter.
    //     /// @param  rexpr       Expression for right parameter.
    //     ExprBitXor(Expression* lexpr, Expression* rexpr);

    //     Variable eval(Scope& scope) override;
    //     Bytecode bytecode(VarNameMap& var_name_map) const override;

    // private:
    //     std::unique_ptr<Expression> m_lexpr;
    //     std::unique_ptr<Expression> m_rexpr;
    // };


    // /// Expression: Bitwise NOT one value.
    // /// Returns ~L.
    // class CREEK_API ExprBitNot : public Expression
    // {
    // public:
    //     /// `ExprBitNot` constructor.
    //     /// @param  expr        Expression to bitwise negate.
    //     ExprBitNot(Expression* expr);

    //     Variable eval(Scope& scope) override;
    //     Bytecode bytecode(VarNameMap& var_name_map) const override;

    // private:
    //     std::unique_ptr<Expression> m_expr;
    // };


    // /// Expression: Bitwise left shift two values.
    // /// Returns L << R.
    // class CREEK_API ExprBitLeftShift : public Expression
    // {
    // public:
    //     /// `ExprBitLeftShift` constructor.
    //     /// @param  lexpr       Expression for left parameter.
    //     /// @param  rexpr       Expression for right parameter.
    //     ExprBitLeftShift(Expression* lexpr, Expression* rexpr);

    //     Variable eval(Scope& scope) override;
    //     Bytecode bytecode(VarNameMap& var_name_map) const override;

    // private:
    //     std::unique_ptr<Expression> m_lexpr;
    //     std::unique_ptr<Expression> m_rexpr;
    // };


    // /// Expression: Bitwise right shift two values.
    // /// Returns L >> R.
    // class CREEK_API ExprBitRightShift : public Expression
    // {
    // public:
    //     /// `ExprBitRightShift` constructor.
    //     /// @param  lexpr       Expression for left parameter.
    //     /// @param  rexpr       Expression for right parameter.
    //     ExprBitRightShift(Expression* lexpr, Expression* rexpr);

    //     Variable eval(Scope& scope) override;
    //     Bytecode bytecode(VarNameMap& var_name_map) const override;

    // private:
    //     std::unique_ptr<Expression> m_lexpr;
    //     std::unique_ptr<Expression> m_rexpr;
    // };

    /// @}
}
