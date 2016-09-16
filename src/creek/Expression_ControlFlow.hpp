#pragma once

#include <creek/Expression.hpp>

#include <memory>
#include <vector>

#include <creek/api_mode.hpp>
#include <creek/VarName.hpp>


namespace creek
{
    /// @defgroup   expression_control_flow Control flow expressions
    /// @{

    /// Expression: Block of expressions.
    /// Begin a new scope and executes each expression.
    /// Returns result of last evaluated expression.
    class CREEK_API ExprBlock : public Expression
    {
    public:
        /// `ExprBlock` constructor.
        /// @param  expressions  List of expressions to evaluate.
        ExprBlock(const std::vector<Expression*>& expressions);

        Variable eval(Scope& scope) override;

    private:
        std::vector< std::unique_ptr<Expression> > m_expressions;
    };


    /// Expression: If-else block.
    /// Returns result of last evaluated branch, or void.
    class CREEK_API ExprIf : public Expression
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


    /// Expression: Infinite loop block.
    /// Returns result of last evaluated expression.
    class CREEK_API ExprLoop : public Expression
    {
    public:
        /// `ExprLoop` constructor.
        /// @param  body        Expression to execute in each loop.
        ExprLoop(Expression* body);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_body;
    };


    /// Expression: Conditional while block.
    /// Returns result of last evaluated expression in the body, or void.
    class CREEK_API ExprWhile : public Expression
    {
    public:
        /// `ExprWhile` constructor.
        /// @param  condition   Contidion expression.
        /// @param  body        Expression to execute in each loop.
        ExprWhile(Expression* condition, Expression* body);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_condition;
        std::unique_ptr<Expression> m_body;
    };


    /// Expression: Value based for loop.
    /// Returns result of last evaluated expression in the body, or void.
    class CREEK_API ExprFor : public Expression
    {
    public:
        /// `ExprFor` constructor.
        /// @param  var_name        Variable name for the iterator.
        /// @param  initial_value   Initial value of the iterator.
        /// @param  max_value       Iterator must be less-than this.
        /// @param  step_value      Iterator increment.
        /// @param  body            Expression to execute in each loop.
        ExprFor(VarName var_name, Expression* initial_value, Expression* max_value,
                Expression* step_value, Expression* body);

        Variable eval(Scope& scope) override;

    private:
        VarName m_var_name;
        std::unique_ptr<Expression> m_initial_value;
        std::unique_ptr<Expression> m_max_value;
        std::unique_ptr<Expression> m_step_value;
        std::unique_ptr<Expression> m_body;
    };


    /// Expression: Range based for loop.
    /// Returns result of last evaluated expression in the body, or void.
    class CREEK_API ExprForIn : public Expression
    {
    public:
        /// `ExprForIn` constructor.
        /// @param  var_name        Variable name for the iterator.
        /// @param  range           Range expression.
        /// @param  body            Expression to execute in each loop.
        ExprForIn(VarName var_name, Expression* range, Expression* body);

        Variable eval(Scope& scope) override;

    private:
        VarName m_var_name;
        std::unique_ptr<Expression> m_range;
        std::unique_ptr<Expression> m_body;
    };


    /// Expression: Try-catch block.
    /// Returns result of last expression from the try block if didn't throw;
    /// else from the catch block.
    class CREEK_API ExprTry : public Expression
    {
    public:
        /// `ExprTry` constructor.
        /// @param  try_body    Expression to try.
        /// @param  catch_body  Expression to execute when catching an exception.
        ExprTry(Expression* try_body, Expression* catch_body);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_try_body;
        std::unique_ptr<Expression> m_catch_body;
    };


    /// Expression: Throw an exception.
    /// Closes scopes until a try-catch block is reached; else program is terminated.
    class CREEK_API ExprThrow : public Expression
    {
    public:
        /// `ExprThrow` constructor.
        /// @param  value       Value to throw.
        ExprThrow(Expression* value);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_value;
    };


    /// Expression: Return from a function.
    /// Closes scopes until a function block is closed.
    class CREEK_API ExprReturn : public Expression
    {
    public:
        /// `ExprReturn` constructor.
        /// @param  value       Value to return.
        ExprReturn(Expression* value);

        Variable eval(Scope& scope) override;

    private:
        std::unique_ptr<Expression> m_value;
    };


    /// @}
}
