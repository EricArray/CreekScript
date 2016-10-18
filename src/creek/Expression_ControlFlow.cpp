#include <creek/Expression_ControlFlow.hpp>

#include <creek/Exception.hpp>
#include <creek/Scope.hpp>
#include <creek/Variable.hpp>
#include <creek/Void.hpp>
#include <iostream> // TODO: remove

namespace creek
{
    // `ExprBasicBlock` constructor.
    // @param  expressions  List of expressions to evaluate.
    ExprBasicBlock::ExprBasicBlock(const std::vector<Expression*>& expressions)
    {
        for (auto& expression : expressions)
        {
            m_expressions.emplace_back(expression);
        }
    }

    Variable ExprBasicBlock::eval(Scope& scope)
    {
        // TODO: Verify which constructor is called for `result` in each three steps.
        Variable result;
        for (auto& expression : m_expressions)
        {
            if (scope.is_breaking())
                break;

            result = expression->eval(scope);
        }
        if (!result) // will return void if no expression was run
        {
            result.data(new Void());
        }
        return result;
    }


    // ExprDo constructor.
    // @param  value   Expression to evaluate inside new scope.
    ExprDo::ExprDo(Expression* value) :
        m_value(value)
    {

    }

    Variable ExprDo::eval(Scope& scope)
    {
        Scope new_scope(scope);
        return m_value->eval(new_scope);
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
        Scope new_scope(scope);

        Variable condition_result(m_condition->eval(new_scope));
        if (condition_result->bool_value())
        {
            return m_true_branch ? m_true_branch->eval(new_scope) : Variable(new Void());
        }
        else
        {
            return m_false_branch ? m_false_branch->eval(new_scope) : Variable(new Void());
        }
    }


    /// @brief  `ExprSwitch` constructor.
    /// @param  condition       Value to compare.
    /// @param  case_branches   List of case branches.
    /// @param  default_branch  Default branch.
    ExprSwitch::ExprSwitch(Expression* condition, std::vector<CaseBranch>& case_branches, Expression* default_branch) :
        m_condition(condition),
        m_default_branch(default_branch)
    {
        m_case_branches.swap(case_branches);
    }

    Variable ExprSwitch::eval(Scope& scope)
    {
        Scope new_scope(scope);

        Variable condition(m_condition->eval(new_scope));
        for (auto& case_branch : m_case_branches)
        {
            for (auto& case_value : case_branch.values)
            {
                Variable v = case_value->eval(new_scope);
                if (condition.cmp(v) == 0)
                {
                    return case_branch.body->eval(new_scope);
                }
            }
        }

        return m_default_branch ? m_default_branch->eval(new_scope) : Variable(new Void());
    }


    // `ExprLoop` constructor.
    // @param  block       Expression to execute in each loop.
    ExprLoop::ExprLoop(Expression* body) : m_body(body)
    {

    }

    Variable ExprLoop::eval(Scope& scope)
    {
        Variable result;

        Scope outer_scope(scope, scope.return_point(), std::make_shared<Scope::BreakPoint>());
        while (true)
        {
            Scope inner_scope(outer_scope);
            result = m_body->eval(inner_scope);
            if (outer_scope.is_breaking())
            {
                break;
            }
        }

        if (!result)
        {
            result = new Void();
        }
        return result;
    }


    // `ExprWhile` constructor.
    // @param  condition   Contidion expression.
    // @param  block       Expression to execute in each loop.
    ExprWhile::ExprWhile(Expression* condition, Expression* body) :
        m_condition(condition),
        m_body(body)
    {

    }

    Variable ExprWhile::eval(Scope& scope)
    {
        Variable result;

        Scope outer_scope(scope, scope.return_point(), std::make_shared<Scope::BreakPoint>());
        while (true)
        {
            Scope inner_scope(outer_scope);

            Variable condition_result(m_condition->eval(inner_scope));
            if (condition_result->bool_value())
            {
                result = m_body->eval(inner_scope);

                if (outer_scope.is_breaking())
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }

        if (!result)
        {
            result.data(new Void());
        }
        return result;
    }


    // `ExprFor` constructor.
    // @param  var_name        Variable name for the iterator.
    // @param  initial_value   Initial value of the iterator.
    // @param  max_value       Iterator must be less-than this.
    // @param  step_value      Iterator increment.
    // @param  body            Expression to execute in each loop.
    ExprFor::ExprFor(VarName var_name, Expression* initial_value, Expression* max_value,
                     Expression* step_value, Expression* body) :
        m_var_name(var_name),
        m_initial_value(initial_value),
        m_max_value(max_value),
        m_step_value(step_value),
        m_body(body)
    {

    }

    Variable ExprFor::eval(Scope& scope)
    {
        Variable result;

        Scope outer_scope(scope, scope.return_point(), std::make_shared<Scope::BreakPoint>());
        // variable with initial value
        auto& i = outer_scope.create_local_var(m_var_name, m_initial_value->eval(outer_scope).release());
        while (true)
        {
            // check maximum
            {
                Variable max = m_max_value->eval(outer_scope);
                if (i.cmp(max) >= 0)    // ge
                {
                    break;
                }
            }

            // execute body block
            {
                Scope inner_scope(outer_scope);
                result = m_body->eval(inner_scope);
                if (inner_scope.is_breaking())
                {
                    break;
                }
            }

            // add step
            {
                Variable step = m_step_value->eval(outer_scope);
                i = i + step;
            }
        }

        if (!result)
        {
            result.data(new Void());
        }
        return result;
    }


    // `ExprForIn` constructor.
    // @param  var_name        Variable name for the iterator.
    // @param  range           Range expression.
    // @param  body            Expression to execute in each loop.
    ExprForIn::ExprForIn(VarName var_name, Expression* range, Expression* body) :
        m_var_name(var_name),
        m_range(range),
        m_body(body)
    {

    }

    Variable ExprForIn::eval(Scope& scope)
    {
        Variable result;
        Variable range(m_range->eval(scope));

        throw Unimplemented("range based for");
        // Scope outer_scope(scope);
        // auto& i = outer_scope.create_local_var(m_var_name, m_initial_value->eval(outer_scope));
        // while (true)
        // {
        //     // check maximum
        //     {
        //         Variable max = m_max_value->eval(outer_scope);
        //         Variable lt = i.lt(max);
        //         if (!lt->bool_value())
        //         {
        //             break;
        //         }
        //     }

        //     // execute body block
        //     {
        //         Scope inner_scope(outer_scope);
        //         result = m_body->eval(inner_scope);
        //     }

        //     // add step
        //     {
        //         Variable step = m_step_value->eval(outer_scope);
        //         i = i + step;
        //     }
        // }
        if (!result)
        {
            result.data(new Void());
        }
        return result;
    }


    // `ExprTry` constructor.
    // @param  try_body    Expression to try.
    // @param  catch_body  Expression to execute when catching an exception.
    ExprTry::ExprTry(Expression* try_body, Expression* catch_body) :
        m_try_body(try_body),
        m_catch_body(catch_body)
    {

    }

    Variable ExprTry::eval(Scope& scope)
    {
        try
        {
            return m_try_body->eval(scope);
        }
        catch (const Exception& e)
        {
            return m_catch_body->eval(scope);
        }
    }


    // `ExprThrow` constructor.
    // @param  value       Value to throw.
    ExprThrow::ExprThrow(Expression* value) : m_value(value)
    {

    }

    Variable ExprThrow::eval(Scope& scope)
    {
        throw m_value->eval(scope);
        return new Void(); // just in case
    }


    // `ExprReturn` constructor.
    // @param  value       Value to return.
    ExprReturn::ExprReturn(Expression* value) : m_value(value)
    {

    }

    Variable ExprReturn::eval(Scope& scope)
    {
        Variable v = m_value->eval(scope);
        scope.return_point()->is_returning = true;
        return v.release();
    }


    // @brief  `ExprBreak` constructor.
    // @param  value       Value to yield.
    ExprBreak::ExprBreak(Expression* value) : m_value(value)
    {

    }

    Variable ExprBreak::eval(Scope& scope)
    {
        Variable v = m_value->eval(scope);
        scope.break_point()->is_breaking = true;
        return v.release();
    }
}
