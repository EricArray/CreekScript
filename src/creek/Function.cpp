#include <creek/Function.hpp>

#include <creek/Expression.hpp>
#include <creek/Scope.hpp>
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
               int_to_string(uintptr_t(m_value->body.get()), 16, 8) +
               std::string(")");
    }


    bool Function::bool_value() const
    {
        return true;
    }

    int Function::cmp(Data* other)
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


    Data* Function::call(std::vector< std::unique_ptr<Data> >& args)
    {
        auto& arg_names = m_value->arg_names;

        if (arg_names.size() != args.size())
        {
            throw WrongArgNumber(arg_names.size(), args.size());
        }

        Scope new_scope(m_value->parent);
        for (size_t i = 0; i < arg_names.size(); ++i)
        {
            new_scope.create_local_var(arg_names[i], args[i].release());
        }
        Variable result = m_value->body->eval(new_scope);

        return result.release();
    }


    // `WrongArgNumber` constructor.
    // @param  expected    Number of expected arguments.
    // @param  passed      Number of passed arguments.
    WrongArgNumber::WrongArgNumber(int expected, int passed) :
        m_expected(expected),
        m_passed(passed)
    {
        stream() << "Wrong number of arguments: expected " << expected << ", passed " << passed;
    }
}
