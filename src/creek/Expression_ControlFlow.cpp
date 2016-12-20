#include <creek/Expression_ControlFlow.hpp>

#include <creek/Exception.hpp>
#include <creek/Expression_DataTypes.hpp>
#include <creek/Scope.hpp>
#include <creek/Variable.hpp>
#include <creek/Void.hpp>
#include <iostream> // TODO: remove

namespace creek
{
    // @brief  `ExprBasicBlock` constructor.
    // @param  expressions  List of expressions to evaluate.
    ExprBasicBlock::ExprBasicBlock(const std::vector<Expression*>& expressions)
    {
        for (auto& expression : expressions)
        {
            m_expressions.emplace_back(expression);
        }
    }

    Expression* ExprBasicBlock::clone() const
    {
        std::vector<Expression*> new_exprs;
        for (auto& e : m_expressions)
        {
            new_exprs.push_back(e->clone());
        }
        return new ExprBasicBlock(new_exprs);
    }

    bool ExprBasicBlock::is_const() const
    {
        for (auto& e : m_expressions)
        {
            if (!e->is_const())
                return false;
        }
        return true;
    }

    Expression* ExprBasicBlock::const_optimize() const
    {
        if (m_expressions.size() == 0)
        {
            return new ExprVoid();
        }
        else if (is_const())
        {
            return m_expressions.back()->const_optimize();
        }
        else
        {
            std::vector<Expression*> new_exprs;
            for (auto& e : m_expressions)
            {
                new_exprs.push_back(e->const_optimize());
            }
            return new ExprBasicBlock(new_exprs);
        }
    }

    Variable ExprBasicBlock::eval(const SharedPointer<Scope>& scope)
    {
        // TODO: Verify which constructor is called for `result` in each three steps.
        Variable result;
        for (auto& expression : m_expressions)
        {
            if (scope->is_breaking())
                break;

            result = expression->eval(scope);
        }
        if (!result) // will return void if no expression was run
        {
            result.data(new Void());
        }
        return result;
    }

    Bytecode ExprBasicBlock::bytecode(VarNameMap& var_name_map) const
    {
        Bytecode b;
        b << static_cast<uint8_t>(OpCode::control_block) << static_cast<uint32_t>(m_expressions.size());
        for (auto& expr : m_expressions)
        {
            b << expr->bytecode(var_name_map);
        }
        return b;
    }


    // ExprDo constructor.
    // @param  value   Expression to evaluate inside new scope.
    ExprDo::ExprDo(Expression* value) :
        m_value(value)
    {

    }

    Expression* ExprDo::clone() const
    {
        return new ExprDo(m_value->clone());
    }

    bool ExprDo::is_const() const
    {
        return m_value->is_const();
    }

    Expression* ExprDo::const_optimize() const
    {
        if (is_const())
        {
            return m_value->const_optimize();
        }
        else
        {
            return new ExprDo(m_value->const_optimize());
        }
    }

    Variable ExprDo::eval(const SharedPointer<Scope>& scope)
    {
        auto new_scope = SharedPointer<LocalScope>::make(scope);
        return m_value->eval(new_scope);
    }

    Bytecode ExprDo::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(OpCode::control_do) << m_value->bytecode(var_name_map);
    }


    // @brief  `ExprIf` constructor.
    // @param  condition       Contidion expression.
    // @param  true_branch     Expression to evaluate when true.
    // @param  false_branch    Expression to evaluate when false.
    ExprIf::ExprIf(Expression* condition, Expression* true_branch, Expression* false_branch) :
        m_condition(condition),
        m_true_branch(true_branch),
        m_false_branch(false_branch)
    {

    }

    Expression* ExprIf::clone() const
    {
        return new ExprIf(m_condition->clone(), m_true_branch->clone(), m_false_branch->clone());
    }

    bool ExprIf::is_const() const
    {
        if (m_condition->is_const())
        {
            auto scope = SharedPointer<ConstScope>::make();
            Variable c = m_condition->eval(scope);
            if (c->bool_value(scope) == true)
            {
                return m_true_branch->is_const();
            }
            else
            {
                return m_false_branch->is_const();
            }
        }
        else
        {
            return false;
        }
    }

    Expression* ExprIf::const_optimize() const
    {
        if (m_condition->is_const())
        {
            auto scope = SharedPointer<ConstScope>::make();
            Variable c = m_condition->eval(scope);
            if (c->bool_value(scope) == true)
            {
                return m_true_branch->const_optimize();
            }
            else
            {
                return m_false_branch->const_optimize();
            }
        }
        else return new ExprIf(m_condition->const_optimize(),
                               m_true_branch->const_optimize(),
                               m_false_branch->const_optimize());
    }

    Variable ExprIf::eval(const SharedPointer<Scope>& scope)
    {
        auto new_scope = SharedPointer<LocalScope>::make(scope);

        Variable condition_result(m_condition->eval(new_scope));
        if (condition_result->bool_value(scope))
        {
            return m_true_branch ? m_true_branch->eval(new_scope) : Variable(new Void());
        }
        else
        {
            return m_false_branch ? m_false_branch->eval(new_scope) : Variable(new Void());
        }
    }

    Bytecode ExprIf::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() <<
            static_cast<uint8_t>(OpCode::control_if) <<
            m_condition->bytecode(var_name_map) <<
            m_true_branch->bytecode(var_name_map) <<
            m_false_branch->bytecode(var_name_map);
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

    Expression* ExprSwitch::clone() const
    {
        std::vector<CaseBranch> new_case_branches;
        for (auto& b : m_case_branches)
        {
            std::vector<Expression*> new_values;
            for (auto& v : b.values)
            {
                new_values.push_back(v->clone());
            }
            new_case_branches.emplace_back(new_values, b.body->clone());
        }
        return new ExprSwitch(m_condition->clone(), new_case_branches, m_default_branch->clone());
    }

    bool ExprSwitch::is_const() const
    {
        // check condition const, then compare to case values until
        // a non-const value is reached, or default
        if (m_condition->is_const())
        {
            auto scope = SharedPointer<ConstScope>::make();
            Variable c = m_condition->eval(scope);
            for (auto& b : m_case_branches)
            {
                for (auto& v : b.values)
                {
                    if (!v->is_const())
                    {
                        return false;
                    }

                    Variable e = v->eval(scope);
                    if (c.cmp(scope, e) == 0)
                    {
                        return b.body->is_const();
                    }
                }
            }
            return m_default_branch->is_const();
        }
        else return false;
    }

    Expression* ExprSwitch::const_optimize() const
    {
        // check condition const, then compare to case values until
        // a non-const value is reached, or default
        if (is_const())
        {
            auto scope = SharedPointer<ConstScope>::make();
            Variable c = m_condition->eval(scope);
            for (auto& b : m_case_branches)
            {
                for (auto& v : b.values)
                {
                    Variable e = v->eval(scope);
                    if (c.cmp(scope, e) == 0)
                    {
                        return b.body->const_optimize();
                    }
                }
            }
            return m_default_branch->const_optimize();
        }
        else
        {
            std::vector<CaseBranch> new_case_branches;
            for (auto& b : m_case_branches)
            {
                std::vector<Expression*> new_values;
                for (auto& v : b.values)
                {
                    new_values.push_back(v->const_optimize());
                }
                new_case_branches.emplace_back(new_values, b.body->const_optimize());
            }
            return new ExprSwitch(m_condition->const_optimize(),
                                  new_case_branches,
                                  m_default_branch->const_optimize());
        }
    }

    Variable ExprSwitch::eval(const SharedPointer<Scope>& scope)
    {
        auto new_scope = SharedPointer<LocalScope>::make(scope);

        Variable condition(m_condition->eval(new_scope));
        for (auto& case_branch : m_case_branches)
        {
            for (auto& case_value : case_branch.values)
            {
                Variable v = case_value->eval(new_scope);
                if (condition.cmp(scope, v) == 0)
                {
                    return case_branch.body->eval(new_scope);
                }
            }
        }

        return m_default_branch ? m_default_branch->eval(new_scope) : Variable(new Void());
    }

    Bytecode ExprSwitch::bytecode(VarNameMap& var_name_map) const
    {
        Bytecode b;
        b << static_cast<uint8_t>(OpCode::control_switch);
        b << m_condition->bytecode(var_name_map);

        b << static_cast<uint32_t>(m_case_branches.size());
        for (auto& case_branch : m_case_branches)
        {
            b << static_cast<uint32_t>(case_branch.values.size());
            for (auto& value : case_branch.values)
            {
                b << value->bytecode(var_name_map);
            }
            b << case_branch.body->bytecode(var_name_map);
        }

        b << m_default_branch->bytecode(var_name_map);

        return b;
    }


    // @brief  `ExprLoop` constructor.
    // @param  block       Expression to execute in each loop.
    ExprLoop::ExprLoop(Expression* body) : m_body(body)
    {

    }

    Expression* ExprLoop::clone() const
    {
        return new ExprLoop(m_body->clone());
    }

    bool ExprLoop::is_const() const
    {
        return false;
    }

    Expression* ExprLoop::const_optimize() const
    {
        return new ExprLoop(m_body->const_optimize());
    }

    Variable ExprLoop::eval(const SharedPointer<Scope>& scope)
    {
        Variable result;

        auto outer_scope = SharedPointer<LocalScope>::make(scope, scope->return_point(), std::make_shared<Scope::BreakPoint>());
        while (true)
        {
            auto inner_scope = SharedPointer<LocalScope>::make(outer_scope);
            result = m_body->eval(inner_scope);
            if (outer_scope->is_breaking())
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

    Bytecode ExprLoop::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(OpCode::control_loop) << m_body->bytecode(var_name_map);
    }


    // @brief  `ExprWhile` constructor.
    // @param  condition   Contidion expression.
    // @param  block       Expression to execute in each loop.
    ExprWhile::ExprWhile(Expression* condition, Expression* body) :
        m_condition(condition),
        m_body(body)
    {

    }

    Expression* ExprWhile::clone() const
    {
        return new ExprWhile(m_condition->clone(), m_body->clone());
    }

    bool ExprWhile::is_const() const
    {
        if (m_condition->is_const())
        {
            auto scope = SharedPointer<ConstScope>::make();
            Variable c(m_condition->eval(scope));
            if (c->bool_value(scope) == false)
            {
                return true;
            }
        }
        return false;
    }

    Expression* ExprWhile::const_optimize() const
    {
        if (m_condition->is_const())
        {
            auto scope = SharedPointer<ConstScope>::make();
            Variable c(m_condition->eval(scope));
            if (c->bool_value(scope) == false)
            {
                return new ExprVoid();
            }
        }
        else
        {
            return new ExprWhile(m_condition->const_optimize(), m_body->const_optimize());
        }
    }

    Variable ExprWhile::eval(const SharedPointer<Scope>& scope)
    {
        Variable result;

        auto outer_scope = SharedPointer<LocalScope>::make(scope, scope->return_point(), std::make_shared<Scope::BreakPoint>());
        while (true)
        {
            auto inner_scope = SharedPointer<LocalScope>::make(outer_scope);

            Variable condition_result(m_condition->eval(inner_scope));
            if (condition_result->bool_value(scope))
            {
                result = m_body->eval(inner_scope);

                if (outer_scope->is_breaking())
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }

        return result ? result : new Void();
    }

    Bytecode ExprWhile::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() <<
            static_cast<uint8_t>(OpCode::control_while) <<
            m_condition->bytecode(var_name_map) <<
            m_body->bytecode(var_name_map);
    }


    // @brief  `ExprFor` constructor.
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

    Expression* ExprFor::clone() const
    {
        return new ExprFor(
            m_var_name,
            m_initial_value->clone(),
            m_max_value->clone(),
            m_step_value->clone(),
            m_body->clone()
        );
    }

    bool ExprFor::is_const() const
    {
        return false;
    }

    Expression* ExprFor::const_optimize() const
    {
        return new ExprFor(
            m_var_name,
            m_initial_value->const_optimize(),
            m_max_value->const_optimize(),
            m_step_value->const_optimize(),
            m_body->const_optimize()
        );
    }

    Variable ExprFor::eval(const SharedPointer<Scope>& scope)
    {
        Variable result;

        auto outer_scope = SharedPointer<LocalScope>::make(scope, scope->return_point(), std::make_shared<Scope::BreakPoint>());
        // variable with initial value
        auto& i = outer_scope->create_local_var(m_var_name, m_initial_value->eval(outer_scope).release());
        while (true)
        {
            // check maximum
            {
                Variable max = m_max_value->eval(outer_scope);
                if (i.cmp(scope, max) >= 0)    // ge
                {
                    break;
                }
            }

            // execute body block
            {
                auto inner_scope = SharedPointer<LocalScope>::make(outer_scope);
                result = m_body->eval(inner_scope);
                if (inner_scope->is_breaking())
                {
                    break;
                }
            }

            // add step
            {
                Variable step = m_step_value->eval(outer_scope);
                // i = i + step;
                i.reset(i->add(scope, *step));
            }
        }

        return result ? result : new Void();
    }

    Bytecode ExprFor::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() <<
            static_cast<uint8_t>(OpCode::control_for) <<
            var_name_map.id_from_name(m_var_name.name()) <<
            m_initial_value->bytecode(var_name_map) <<
            m_max_value->bytecode(var_name_map) <<
            m_step_value->bytecode(var_name_map) <<
            m_body->bytecode(var_name_map);
    }


    // @brief  `ExprForIn` constructor.
    // @param  var_name        Variable name for the iterator.
    // @param  range           Range expression.
    // @param  body            Expression to execute in each loop.
    ExprForIn::ExprForIn(VarName var_name, Expression* range, Expression* body) :
        m_var_name(var_name),
        m_range(range),
        m_body(body)
    {

    }

    Expression* ExprForIn::clone() const
    {
        return new ExprForIn(m_var_name, m_range->clone(), m_body->clone());
    }

    bool ExprForIn::is_const() const
    {
        return false;
    }

    Expression* ExprForIn::const_optimize() const
    {
        return new ExprForIn(
            m_var_name,
            m_range->const_optimize(),
            m_body->const_optimize()
        );
    }

    Variable ExprForIn::eval(const SharedPointer<Scope>& scope)
    {
        Variable result;
        Variable range(m_range->eval(scope));
        Variable keys(range->call_method(scope, "keys", {}));

        auto outer_scope = SharedPointer<LocalScope>::make(scope);
        auto& item = outer_scope->create_local_var(m_var_name, nullptr);
        for (auto& key : keys->vector_value(scope))
        {
            item = range.index(scope, key);

            auto inner_scope = SharedPointer<LocalScope>::make(outer_scope);
            result = m_body->eval(inner_scope);
        }

        return result ? result : new Void();
    }

    Bytecode ExprForIn::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() <<
            static_cast<uint8_t>(OpCode::control_for_in) <<
            var_name_map.id_from_name(m_var_name.name()) <<
            m_range->bytecode(var_name_map) <<
            m_body->bytecode(var_name_map);
    }


    // @brief  `ExprTry` constructor.
    // @param  try_body    Expression to try.
    // @param  id          Variable name for the catched exception.
    // @param  catch_body  Expression to execute when catching an exception.
    ExprTry::ExprTry(Expression* try_body, VarName id, Expression* catch_body) :
        m_try_body(try_body),
        m_id(id),
        m_catch_body(catch_body)
    {

    }

    Expression* ExprTry::clone() const
    {
        return new ExprTry(m_try_body->clone(), m_id, m_catch_body->clone());
    }

    bool ExprTry::is_const() const
    {
        return false;
    }

    Expression* ExprTry::const_optimize() const
    {
        return new ExprTry(m_try_body->const_optimize(), m_id, m_catch_body->const_optimize());
    }

    Variable ExprTry::eval(const SharedPointer<Scope>& scope)
    {
        try
        {
            return m_try_body->eval(scope);
        }
        catch (Variable& v)
        {
            auto inner = SharedPointer<LocalScope>::make(scope);
            inner->create_local_var(m_id, v.release());
            return m_catch_body->eval(inner);
        }
        catch (const Exception& e)
        {
            auto inner = SharedPointer<LocalScope>::make(scope);
            inner->create_local_var(m_id, new String(e.message()));
            return m_catch_body->eval(inner);
        }
        catch (const std::exception& e)
        {
            auto inner = SharedPointer<LocalScope>::make(scope);
            inner->create_local_var(m_id, new String(e.what()));
            return m_catch_body->eval(scope);
        }
        catch (...)
        {
            auto inner = SharedPointer<LocalScope>::make(scope);
            inner->create_local_var(m_id, new Null());
            return m_catch_body->eval(scope);
        }
    }

    Bytecode ExprTry::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode()
            << static_cast<uint8_t>(OpCode::control_try)
            << m_try_body->bytecode(var_name_map)
            << var_name_map.id_from_name(m_id.name())
            << m_catch_body->bytecode(var_name_map);
    }


    // @brief  `ExprThrow` constructor.
    // @param  value       Value to throw.
    ExprThrow::ExprThrow(Expression* value) : m_value(value)
    {

    }

    Expression* ExprThrow::clone() const
    {
        return new ExprThrow(m_value->clone());
    }

    bool ExprThrow::is_const() const
    {
        return false;
    }

    Expression* ExprThrow::const_optimize() const
    {
        return new ExprThrow(m_value->const_optimize());
    }

    Variable ExprThrow::eval(const SharedPointer<Scope>& scope)
    {
        throw m_value->eval(scope);
        return new Void(); // just in case
    }

    Bytecode ExprThrow::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(OpCode::control_throw) << m_value->bytecode(var_name_map);
    }


    // @brief  `ExprReturn` constructor.
    // @param  value       Value to return.
    ExprReturn::ExprReturn(Expression* value) : m_value(value)
    {

    }

    Expression* ExprReturn::clone() const
    {
        return new ExprReturn(m_value->clone());
    }

    bool ExprReturn::is_const() const
    {
        return false;
    }

    Expression* ExprReturn::const_optimize() const
    {
        return new ExprReturn(m_value->const_optimize());
    }

    Variable ExprReturn::eval(const SharedPointer<Scope>& scope)
    {
        Variable v = m_value->eval(scope);
        scope->return_point()->is_returning = true;
        return v.release();
    }

    Bytecode ExprReturn::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(OpCode::control_return) << m_value->bytecode(var_name_map);
    }


    // @brief  `ExprBreak` constructor.
    // @param  value       Value to yield.
    ExprBreak::ExprBreak(Expression* value) : m_value(value)
    {

    }

    Expression* ExprBreak::clone() const
    {
        return new ExprBreak(m_value->clone());
    }

    bool ExprBreak::is_const() const
    {
        return false;
    }

    Expression* ExprBreak::const_optimize() const
    {
        return new ExprBreak(m_value->const_optimize());
    }

    Variable ExprBreak::eval(const SharedPointer<Scope>& scope)
    {
        Variable v = m_value->eval(scope);
        scope->break_point()->is_breaking = true;
        return v.release();
    }

    Bytecode ExprBreak::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(OpCode::control_break) << m_value->bytecode(var_name_map);
    }
}
