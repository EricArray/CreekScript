#include <creek/Expression.hpp>

#include <iostream>

#include <creek/Scope.hpp>
#include <creek/Variable.hpp>


namespace creek
{
    /////////////////////////////////////////////////////////////
    // Debug operation.

    // ExprPrint constructor.
    // @param  expression  Expression to get value.
    ExprPrint::ExprPrint(Expression* expression) : m_expression(expression)
    {

    }

    Variable ExprPrint::eval(Scope& scope)
    {
        // Data* data = m_expression->eval(scope);
        // std::cout << data->debug_text() << std::endl;
        // return data;
        Variable v(m_expression->eval(scope));
        std::cout << v->debug_text() << std::endl;
        return v;
    }



    /////////////////////////////////////////////////////////////
    // Control flow.

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
        Scope new_scope(&scope);

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



    /////////////////////////////////////////////////////////////
    // Variables.

    // ExprLocalVar constructor.
    // @param  var_name    Variable name.
    // @param  expression  Expression to get value.
    ExprLocalVar::ExprLocalVar(VarName var_name, Expression* expression) :
        m_var_name(var_name),
        m_expression(expression)
    {

    }

    Variable ExprLocalVar::eval(Scope& scope)
    {
        Variable new_value(m_expression->eval(scope));
        scope.create_local_var(m_var_name, new_value->copy());
        return new_value;
    }

    // ExprLoadVar constructor.
    // @param  var_name    Variable name.
    ExprLoadVar::ExprLoadVar(VarName var_name) : m_var_name(var_name)
    {

    }

    Variable ExprLoadVar::eval(Scope& scope)
    {
        return Variable(scope.find_var(m_var_name)->copy());
    }

    // ExprStoreVar constructor.
    // @param  var_name    Variable name.
    // @param  expression  Expression to get value.
    ExprStoreVar::ExprStoreVar(VarName var_name, Expression* expression) :
        m_var_name(var_name),
        m_expression(expression)
    {

    }

    Variable ExprStoreVar::eval(Scope& scope)
    {
        Variable new_value(m_expression->eval(scope));
        Variable& var = scope.find_var(m_var_name);
        var.data(new_value->copy());
        return new_value;
    }



    /////////////////////////////////////////////////////////////
    // Basic data types.

    // ExprVoid constructor.
    ExprVoid::ExprVoid()
    {

    }

    Variable ExprVoid::eval(Scope& scope)
    {
        return Variable(new Void());
    }

    // ExprNumber constructor.
    // @param  value       Number value.
    ExprNumber::ExprNumber(Number::Value value) : m_value(value)
    {

    }

    Variable ExprNumber::eval(Scope& scope)
    {
        return Variable(new Number(m_value));
    }

    // ExprString constructor.
    // @param  value       String value.
    ExprString::ExprString(String::Value value) : m_value(value)
    {

    }

    Variable ExprString::eval(Scope& scope)
    {
        return Variable(new String(m_value));
    }



    /////////////////////////////////////////////////////////////
    // Arithmetic operations.

    /// `ExprAdd` constructor.
    /// @param  lexpr       Expression for left parameter.
    /// @param  rexpr       Expression for right parameter.
    ExprAdd::ExprAdd(Expression* lexpr, Expression* rexpr) :
        m_lexpr(lexpr),
        m_rexpr(rexpr)
    {

    }

    Variable ExprAdd::eval(Scope& scope)
    {
        Variable l(m_lexpr->eval(scope));
        Variable r(m_rexpr->eval(scope));
        return l.add(r);
    }
}
