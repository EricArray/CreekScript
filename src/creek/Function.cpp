#include <creek/Function.hpp>

#include <creek/Expression.hpp>
#include <creek/Expression_DataTypes.hpp>
#include <creek/Scope.hpp>
#include <creek/Vector.hpp>
#include <creek/utility.hpp>


namespace creek
{
    // `Function` constructor.
    // @param  value   Function value.
    Function::Function(const Value& value) : m_value(value)
    {

    }


    Data* Function::copy() const
    {
        return new Function(m_value);
    }

    std::string Function::class_name() const
    {
        return "Function";
    }

    std::string Function::debug_text() const
    {
        return std::string("Function(0x") +
               int_to_string(uintptr_t(m_value.get()), 16, 8) +
               std::string(")");
    }

    Expression* Function::to_expression() const
    {
        return new ExprFunction(m_value->arg_names, m_value->is_variadic, m_value->body);
    }


    bool Function::bool_value(const SharedPointer<Scope>& scope) const
    {
        return m_value.get();
    }

    int Function::cmp(const SharedPointer<Scope>& scope, Data* other)
    {
        if (auto other_function = dynamic_cast<Function*>(other))
        {
            return m_value == other_function->m_value;
        }
        else
        {
            return false;
        }
    }


    Data* Function::call(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto& arg_names = m_value->arg_names;

        // variadic arguments
        if (m_value->is_variadic)
        {
            Vector::Value vararg_vec = std::make_shared< std::vector<Variable> >();
            for (size_t i = arg_names.size() - 1; i < args.size(); ++i)
            {
                vararg_vec->emplace_back(args[i].release());
            }
            args.resize(arg_names.size() - 1);
            args.emplace_back(new Vector(vararg_vec));
        }

        // execution
        if (args.size() != arg_names.size())
        {
            throw WrongArgNumber(arg_names.size(), args.size());
        }

        // TODO: break point in function?
        auto new_scope = SharedPointer<LocalScope>::make(
            m_value->parent,
            std::make_shared<Scope::ReturnPoint>(),
            std::make_shared<Scope::BreakPoint>());

        for (size_t i = 0; i < arg_names.size(); ++i)
        {
            new_scope->create_local_var(arg_names[i], args[i].release());
        }
        Variable result = m_value->body->eval(new_scope);

        return result.release();
    }
}
