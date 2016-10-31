#pragma once

#include <creek/Expression.hpp>

#include <memory>

#include <creek/api_mode.hpp>


namespace creek
{
    /// @defgroup   expression_arithmetic   Arithmetic operations
    /// @{

    /// Expression: Add two values.
    /// Returns L + R.
    class CREEK_API ExprAdd : public Expression
    {
    public:
        /// `ExprAdd` constructor.
        /// @param  lexpr       Expression for left parameter.
        /// @param  rexpr       Expression for right parameter.
        ExprAdd(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };


    /// Expression: Subtract two values.
    /// Returns L - R.
    class CREEK_API ExprSub : public Expression
    {
    public:
        /// `ExprSub` constructor.
        /// @param  lexpr       Expression for left parameter.
        /// @param  rexpr       Expression for right parameter.
        ExprSub(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };


    /// Expression: Multiply two values.
    /// Returns L * R.
    class CREEK_API ExprMul : public Expression
    {
    public:
        /// `ExprMul` constructor.
        /// @param  lexpr       Expression for left parameter.
        /// @param  rexpr       Expression for right parameter.
        ExprMul(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };


    /// Expression: Divide two values.
    /// Returns L / R.
    class CREEK_API ExprDiv : public Expression
    {
    public:
        /// `ExprDiv` constructor.
        /// @param  lexpr       Expression for left parameter.
        /// @param  rexpr       Expression for right parameter.
        ExprDiv(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };



    /// Expression: Modulo two values.
    /// Returns L % R.
    class CREEK_API ExprMod : public Expression
    {
    public:
        /// `ExprMod` constructor.
        /// @param  lexpr       Expression for left parameter.
        /// @param  rexpr       Expression for right parameter.
        ExprMod(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };


    /// Expression: Exponentiate two values.
    /// Returns L ** R.
    class CREEK_API ExprExp : public Expression
    {
    public:
        /// `ExprExp` constructor.
        /// @param  lexpr       Expression for left parameter.
        /// @param  rexpr       Expression for right parameter.
        ExprExp(Expression* lexpr, Expression* rexpr);

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };


    /// Expression: Negate one values.
    /// Returns -L.
    class CREEK_API ExprUnm : public Expression
    {
    public:
        /// `ExprUnm` constructor.
        /// @param  expr        Expression to negate.
        ExprUnm(Expression* expr);

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_expr;
    };

    /// @}
}
