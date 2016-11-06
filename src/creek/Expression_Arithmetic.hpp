#pragma once

#include <memory>

#include <creek/Expression_General.hpp>
#include <creek/api_mode.hpp>


namespace creek
{
    /// @defgroup   expression_arithmetic   Arithmetic operations
    /// @{

    /// @brief  Expression: Add two values.
    using ExprAdd = ExprBinary<OpCode::add, &Data::add>;

    /// Expression: Subtract two values.
    using ExprSub = ExprBinary<OpCode::sub, &Data::sub>;

    /// Expression: Multiply two values.
    using ExprMul = ExprBinary<OpCode::mul, &Data::mul>;

    /// Expression: Divide two values.
    using ExprDiv = ExprBinary<OpCode::div, &Data::div>;

    /// Expression: Modulo two values.
    using ExprMod = ExprBinary<OpCode::mod, &Data::mod>;

    /// Expression: Exponentiate two values.
    using ExprExp = ExprBinary<OpCode::exp, &Data::exp>;

    /// Expression: Negate one values.
    using ExprUnm = ExprUnary<OpCode::unm, &Data::unm>;


    // /// @brief  Expression: Add two values.
    // /// Returns L + R.
    // class CREEK_API ExprAdd : public Expression
    // {
    // public:
    //     /// @brief  `ExprAdd` constructor.
    //     /// @param  lexpr       Expression for left parameter.
    //     /// @param  rexpr       Expression for right parameter.
    //     ExprAdd(Expression* lexpr, Expression* rexpr);

    //     Variable eval(Scope& scope) override;
    //     Expression* to_const() const override;
    //     Bytecode bytecode(VarNameMap& var_name_map) const override;

    // private:
    //     std::unique_ptr<Expression> m_lexpr;
    //     std::unique_ptr<Expression> m_rexpr;
    // };


    // /// Expression: Subtract two values.
    // /// Returns L - R.
    // class CREEK_API ExprSub : public Expression
    // {
    // public:
    //     /// `ExprSub` constructor.
    //     /// @param  lexpr       Expression for left parameter.
    //     /// @param  rexpr       Expression for right parameter.
    //     ExprSub(Expression* lexpr, Expression* rexpr);

    //     Variable eval(Scope& scope) override;
    //     Expression* to_const() const override;
    //     Bytecode bytecode(VarNameMap& var_name_map) const override;

    // private:
    //     std::unique_ptr<Expression> m_lexpr;
    //     std::unique_ptr<Expression> m_rexpr;
    // };


    // /// Expression: Multiply two values.
    // /// Returns L * R.
    // class CREEK_API ExprMul : public Expression
    // {
    // public:
    //     /// `ExprMul` constructor.
    //     /// @param  lexpr       Expression for left parameter.
    //     /// @param  rexpr       Expression for right parameter.
    //     ExprMul(Expression* lexpr, Expression* rexpr);

    //     Variable eval(Scope& scope) override;
    //     Expression* to_const() const override;
    //     Bytecode bytecode(VarNameMap& var_name_map) const override;

    // private:
    //     std::unique_ptr<Expression> m_lexpr;
    //     std::unique_ptr<Expression> m_rexpr;
    // };


    // /// Expression: Divide two values.
    // /// Returns L / R.
    // class CREEK_API ExprDiv : public Expression
    // {
    // public:
    //     /// `ExprDiv` constructor.
    //     /// @param  lexpr       Expression for left parameter.
    //     /// @param  rexpr       Expression for right parameter.
    //     ExprDiv(Expression* lexpr, Expression* rexpr);

    //     Variable eval(Scope& scope) override;
    //     Expression* to_const() const override;
    //     Bytecode bytecode(VarNameMap& var_name_map) const override;

    // private:
    //     std::unique_ptr<Expression> m_lexpr;
    //     std::unique_ptr<Expression> m_rexpr;
    // };



    // /// Expression: Modulo two values.
    // /// Returns L % R.
    // class CREEK_API ExprMod : public Expression
    // {
    // public:
    //     /// `ExprMod` constructor.
    //     /// @param  lexpr       Expression for left parameter.
    //     /// @param  rexpr       Expression for right parameter.
    //     ExprMod(Expression* lexpr, Expression* rexpr);

    //     Variable eval(Scope& scope) override;
    //     Expression* to_const() const override;
    //     Bytecode bytecode(VarNameMap& var_name_map) const override;

    // private:
    //     std::unique_ptr<Expression> m_lexpr;
    //     std::unique_ptr<Expression> m_rexpr;
    // };


    // /// Expression: Exponentiate two values.
    // /// Returns L ** R.
    // class CREEK_API ExprExp : public Expression
    // {
    // public:
    //     /// `ExprExp` constructor.
    //     /// @param  lexpr       Expression for left parameter.
    //     /// @param  rexpr       Expression for right parameter.
    //     ExprExp(Expression* lexpr, Expression* rexpr);

    //     Variable eval(Scope& scope) override;
    //     Expression* to_const() const override;
    //     Bytecode bytecode(VarNameMap& var_name_map) const override;

    // private:
    //     std::unique_ptr<Expression> m_lexpr;
    //     std::unique_ptr<Expression> m_rexpr;
    // };


    // /// Expression: Negate one values.
    // /// Returns -L.
    // class CREEK_API ExprUnm : public Expression
    // {
    // public:
    //     /// `ExprUnm` constructor.
    //     /// @param  expr        Expression to negate.
    //     ExprUnm(Expression* expr);

    //     Variable eval(Scope& scope) override;
    //     Expression* to_const() const override;
    //     Bytecode bytecode(VarNameMap& var_name_map) const override;

    // private:
    //     std::unique_ptr<Expression> m_expr;
    // };

    /// @}
}
