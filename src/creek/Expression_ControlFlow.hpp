#pragma once

#include <creek/Expression.hpp>

#include <memory>
#include <vector>


namespace creek
{
    /// @defgroup   expression_control_flow Control flow expressions
    /// @{

    /// Expression: Block of expressions.
    /// Begin a new scope and executes each expression.
    /// Returns result of last evaluated expression.
    class ExprBlock : public Expression
    {
    public:
        /// `ExprBlock` constructor.
        /// @param  expressions  List of expressions to evaluate.
        ExprBlock(std::vector<Expression*>&& expressions);

        Variable eval(Scope& scope) override;

    private:
        std::vector< std::unique_ptr<Expression> > m_expressions;
    };

    /// Expression: If-else block.
    /// Returns result of last evaluated branch, or void.
    class ExprIf : public Expression
    {
    public:
        /// `ExprIf` constructor.
        /// @param  condition       Contidion expression.
        /// @param  true_branch     Expression to evaluate when true.
        /// @param  false_branch    Expression to evaluate when false.
        ExprIf(Expression* condition, Expression* true_branch, Expression* false_branch);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_condition;
        std::unique_ptr<Expression> m_true_branch;
        std::unique_ptr<Expression> m_false_branch;
    };

    /// @}
}