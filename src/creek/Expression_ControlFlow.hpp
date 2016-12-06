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

    /// @brief  Expression: List of expressions without own scope.
    /// Executes each expression without beginning a new scope.
    /// Returns result of last evaluated expression.
    class CREEK_API ExprBasicBlock : public Expression
    {
    public:
        /// @brief  `ExprBasicBlock` constructor..
        /// @param  expressions  List of expressions to evaluate.
        ExprBasicBlock(const std::vector<Expression*>& expressions);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::vector< std::unique_ptr<Expression> > m_expressions;
    };

    /// @brief  Expression: Do block.
    /// Begin a new scope and evaluates the expression.
    class CREEK_API ExprDo : public Expression
    {
    public:
        /// @brief `ExprDo` constructor.
        /// @param value    Expression to evaluate inside new scope.
        ExprDo(Expression* value);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_value;
    };


    /// @brief  Expression: If-else block.
    /// Returns result of evaluated branch, or void.
    class CREEK_API ExprIf : public Expression
    {
    public:
        /// @brief  `ExprIf` constructor..
        /// @param  condition       Contidion expression.
        /// @param  true_branch     Expression to evaluate when true.
        /// @param  false_branch    Expression to evaluate when false.
        ExprIf(Expression* condition, Expression* true_branch, Expression* false_branch);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_condition;
        std::unique_ptr<Expression> m_true_branch;
        std::unique_ptr<Expression> m_false_branch;
    };


    /// @brief  Expression: Switch-case block.
    /// Returns result of evaluated branch, or void.
    class CREEK_API ExprSwitch : public Expression
    {
    public:
        /// @brief  Switch case branch.
        struct CaseBranch
        {
            CaseBranch(const std::vector<Expression*>& values, Expression* body) :
                body(body)
            {
                for (auto& v : values)
                {
                    this->values.emplace_back(v);
                }
            }

            std::vector< std::unique_ptr<Expression> > values; ///< Values to campare to the condition.
            std::unique_ptr<Expression> body; ///< Expression to execute.
        };

        /// @brief  `ExprSwitch` constructor.
        /// @param  condition       Value to compare.
        /// @param  case_branches   List of case branches.
        /// @param  default_branch  Default branch.
        ExprSwitch(Expression* condition, std::vector<CaseBranch>& case_branches, Expression* default_branch);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_condition;
        std::vector<CaseBranch> m_case_branches;
        std::unique_ptr<Expression> m_default_branch;
    };


    /// @brief  Expression: Infinite loop block.
    /// Returns result of last evaluated expression.
    class CREEK_API ExprLoop : public Expression
    {
    public:
        /// @brief  `ExprLoop` constructor..
        /// @param  body        Expression to execute in each loop.
        ExprLoop(Expression* body);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_body;
    };


    /// @brief  Expression: Conditional while block.
    /// Returns result of last evaluated expression in the body, or void.
    class CREEK_API ExprWhile : public Expression
    {
    public:
        /// @brief  `ExprWhile` constructor..
        /// @param  condition   Contidion expression.
        /// @param  body        Expression to execute in each loop.
        ExprWhile(Expression* condition, Expression* body);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_condition;
        std::unique_ptr<Expression> m_body;
    };


    /// @brief  Expression: Value based for loop.
    /// Returns result of last evaluated expression in the body, or void.
    class CREEK_API ExprFor : public Expression
    {
    public:
        /// @brief  `ExprFor` constructor..
        /// @param  var_name        Variable name for the iterator.
        /// @param  initial_value   Initial value of the iterator.
        /// @param  max_value       Iterator must be less-than this.
        /// @param  step_value      Iterator increment.
        /// @param  body            Expression to execute in each loop.
        ExprFor(VarName var_name, Expression* initial_value, Expression* max_value,
                Expression* step_value, Expression* body);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        VarName m_var_name;
        std::unique_ptr<Expression> m_initial_value;
        std::unique_ptr<Expression> m_max_value;
        std::unique_ptr<Expression> m_step_value;
        std::unique_ptr<Expression> m_body;
    };


    /// @brief  Expression: Range based for loop.
    /// Returns result of last evaluated expression in the body, or void.
    class CREEK_API ExprForIn : public Expression
    {
    public:
        /// @brief  `ExprForIn` constructor..
        /// @param  var_name        Variable name for the iterator.
        /// @param  range           Range expression.
        /// @param  body            Expression to execute in each loop.
        ExprForIn(VarName var_name, Expression* range, Expression* body);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        VarName m_var_name;
        std::unique_ptr<Expression> m_range;
        std::unique_ptr<Expression> m_body;
    };


    /// @brief  Expression: Try-catch block.
    /// Returns result of last expression from the try block if didn't throw;
    /// else from the catch block.
    class CREEK_API ExprTry : public Expression
    {
    public:
        /// @brief  `ExprTry` constructor..
        /// @param  try_body    Expression to try.
        /// @param  id          Variable name for the caught exception.
        /// @param  catch_body  Expression to execute when catching an exception.
        ExprTry(Expression* try_body, VarName id, Expression* catch_body);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_try_body;
        VarName m_id;
        std::unique_ptr<Expression> m_catch_body;
    };


    /// @brief  Expression: Throw an exception.
    /// Closes scopes until a try-catch block is reached; else program is terminated.
    class CREEK_API ExprThrow : public Expression
    {
    public:
        /// @brief  `ExprThrow` constructor..
        /// @param  value       Value to throw.
        ExprThrow(Expression* value);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_value;
    };


    /// @brief  Expression: Return from a function.
    /// Closes scopes until a function block is closed.
    class CREEK_API ExprReturn : public Expression
    {
    public:
        /// @brief  `ExprReturn` constructor..
        /// @param  value       Value to return.
        ExprReturn(Expression* value);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_value;
    };


    /// @brief  Expression: Break from a loop.
    /// Closes scopes until a loop block is closed.
    /// Can yield a value, just like returning.
    class CREEK_API ExprBreak : public Expression
    {
    public:
        /// @brief  `ExprBreak` constructor..
        /// @param  value       Value to yield.
        ExprBreak(Expression* value);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;
        
        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_value;
    };

    /// @}
}
