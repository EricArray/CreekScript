#pragma once

#include <creek/Expression_General.hpp>

#include <memory>

#include <creek/api_mode.hpp>


namespace creek
{
    /// @defgroup   expression_bitwise  Bitwise operations
    /// @{

    /// @brief  Expression: Bitwise AND two values.
    /// Returns L & R.
    using ExprBitAnd = ExprBinary<OpCode::bit_and, &Data::bit_and>;

    /// @brief  Expression: Bitwise OR two values.
    /// Returns L | R.
    using ExprBitOr = ExprBinary<OpCode::bit_or, &Data::bit_or>;

    /// @brief  Expression: Bitwise XOR two values.
    /// Returns L ^ R.
    using ExprBitXor = ExprBinary<OpCode::bit_xor, &Data::bit_xor>;

    /// @brief  Expression: Bitwise NOT one value.
    /// Returns ~L.
    using ExprBitNot = ExprUnary<OpCode::bit_not, &Data::bit_not>;

    /// @brief  Expression: Bitwise left shift two values.
    /// Returns L << R.
    using ExprBitLeftShift = ExprBinary<OpCode::bit_left_shift, &Data::bit_left_shift>;

    /// @brief  Expression: Bitwise right shift two values.
    /// Returns L >> R.
    using ExprBitRightShift = ExprBinary<OpCode::bit_right_shift, &Data::bit_right_shift>;


    // /// @brief  Expression: Bitwise AND two values.
    // /// Returns L & R.
    // class CREEK_API ExprBitAnd : public Expression
    // {
    // public:
    //     /// @brief  `ExprBitAnd` constructor..
    //     /// @param  lexpr       Expression for left parameter.
    //     /// @param  rexpr       Expression for right parameter.
    //     ExprBitAnd(Expression* lexpr, Expression* rexpr);

    //     Variable eval(Scope& scope) override;
    //     Bytecode bytecode(VarNameMap& var_name_map) const override;

    // private:
    //     std::unique_ptr<Expression> m_lexpr;
    //     std::unique_ptr<Expression> m_rexpr;
    // };


    // /// @brief  Expression: Bitwise OR two values.
    // /// Returns L | R.
    // class CREEK_API ExprBitOr : public Expression
    // {
    // public:
    //     /// @brief  `ExprBitOr` constructor..
    //     /// @param  lexpr       Expression for left parameter.
    //     /// @param  rexpr       Expression for right parameter.
    //     ExprBitOr(Expression* lexpr, Expression* rexpr);

    //     Variable eval(Scope& scope) override;
    //     Bytecode bytecode(VarNameMap& var_name_map) const override;

    // private:
    //     std::unique_ptr<Expression> m_lexpr;
    //     std::unique_ptr<Expression> m_rexpr;
    // };


    // /// @brief  Expression: Bitwise XOR two values.
    // /// Returns L ^ R.
    // class CREEK_API ExprBitXor : public Expression
    // {
    // public:
    //     /// @brief  `ExprBitXor` constructor..
    //     /// @param  lexpr       Expression for left parameter.
    //     /// @param  rexpr       Expression for right parameter.
    //     ExprBitXor(Expression* lexpr, Expression* rexpr);

    //     Variable eval(Scope& scope) override;
    //     Bytecode bytecode(VarNameMap& var_name_map) const override;

    // private:
    //     std::unique_ptr<Expression> m_lexpr;
    //     std::unique_ptr<Expression> m_rexpr;
    // };


    // /// @brief  Expression: Bitwise NOT one value.
    // /// Returns ~L.
    // class CREEK_API ExprBitNot : public Expression
    // {
    // public:
    //     /// @brief  `ExprBitNot` constructor..
    //     /// @param  expr        Expression to bitwise negate.
    //     ExprBitNot(Expression* expr);

    //     Variable eval(Scope& scope) override;
    //     Bytecode bytecode(VarNameMap& var_name_map) const override;

    // private:
    //     std::unique_ptr<Expression> m_expr;
    // };


    // /// @brief  Expression: Bitwise left shift two values.
    // /// Returns L << R.
    // class CREEK_API ExprBitLeftShift : public Expression
    // {
    // public:
    //     /// @brief  `ExprBitLeftShift` constructor..
    //     /// @param  lexpr       Expression for left parameter.
    //     /// @param  rexpr       Expression for right parameter.
    //     ExprBitLeftShift(Expression* lexpr, Expression* rexpr);

    //     Variable eval(Scope& scope) override;
    //     Bytecode bytecode(VarNameMap& var_name_map) const override;

    // private:
    //     std::unique_ptr<Expression> m_lexpr;
    //     std::unique_ptr<Expression> m_rexpr;
    // };


    // /// @brief  Expression: Bitwise right shift two values.
    // /// Returns L >> R.
    // class CREEK_API ExprBitRightShift : public Expression
    // {
    // public:
    //     /// @brief  `ExprBitRightShift` constructor..
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
