#include <creek/Expression_ControlFlow.hpp>

#include <creek/Scope.hpp>
#include <creek/Variable.hpp>
#include <creek/Void.hpp>


namespace creek
{
    // ExprBlock constructor.
    // @param  expressions  List of expressions to evaluate.
    ExprBlock::ExprBlock(std::vector<Expression*>&& expressions)
    {
        for (auto& expression : expressions)
        {
            m_expressions.emplace_back(expression);
        }
    }

    Variable ExprBlock::eval(Scope& scope)
    {
        Scope new_scope(scope);

        // TODO: Verify which constructor is called for `result` in each three steps.
        Variable result(new Void()); // will return void if no expression was run
        for (auto& expression : m_expressions)
        {
            result = expression->eval(new_scope);
        }
        return result;
    }


    // `ExprIf` constructor.
    // @param  condition       Contidion expression.
    // @param  true_branch     Expression to evaluate when true.
    // @param  false_branch    Expression to evaluate when false.
    ExprIf::ExprIf(Expression* condition, Expression* true_branch, Expression* false_branch) :
        m_condition(condition),
        m_true_branch(true_branch),
        m_false_branch(false_branch)
    {

    }

    Variable ExprIf::eval(Scope& scope)
    {
        Variable condition_result(m_condition->eval(scope));
        if (condition_result->bool_value())
        {
            return m_true_branch ? m_true_branch->eval(scope) : Variable(new Void());
        }
        else
        {
            return m_false_branch ? m_false_branch->eval(scope) : Variable(new Void());
        }
    }
}
