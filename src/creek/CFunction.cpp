#include <creek/CFunction.hpp>

#include <creek/Expression.hpp>
#include <creek/Scope.hpp>
#include <creek/Vector.hpp>
#include <creek/utility.hpp>


namespace creek
{
    // `CFunction` constructor.
    // @param  value   CFunction value.
    CFunction::CFunction(const Value& value) : m_value(value)
    {

    }

    // `CFunction` constructor.
    // @param  scope       Scope where this function was created.
    // @param  argn        Number of arguments.
    // @param  is_variadic Is variadic.
    // @param  listener    Listener function to call.
    CFunction::CFunction(Scope& scope, int argn, bool is_variadic, Listener listener) :
        CFunction(std::make_shared<Definition>(scope, argn, is_variadic, listener))
    {

    }


    // Get value.
    const CFunction::Value& CFunction::value() const
    {
        return m_value;
    }


    Data* CFunction::copy() const
    {
        return new CFunction(m_value);
    }

    std::string CFunction::class_name() const
    {
        return "CFunction";
    }

    std::string CFunction::debug_text() const
    {
        return std::string("CFunction(0x") +
               int_to_string(uintptr_t(m_value.get()), 16, 8) +
               std::string(")");
    }


    bool CFunction::bool_value() const
    {
        return m_value.get();
    }

    int CFunction::cmp(Data* other)
    {
        if (auto other_cfunction = dynamic_cast<CFunction*>(other))
        {
            return m_value == other_cfunction->m_value;
        }
        else
        {
            return false;
        }
    }


    Data* CFunction::call(std::vector< std::unique_ptr<Data> >& args)
    {
        // variadic arguments
        if (m_value->is_variadic)
        {
            Vector::Value vararg_vec = std::make_shared< std::vector<Variable> >();
            for (size_t i = m_value->argn - 1; i < args.size(); ++i)
            {
                vararg_vec->emplace_back(args[i].release());
            }
            args.resize(m_value->argn - 1);
            args.emplace_back(new Vector(vararg_vec));
        }

        // execution
        if (args.size() != m_value->argn)
        {
            throw WrongArgNumber(m_value->argn, args.size());
        }

        return m_value->listener(m_value->scope, args);
    }
}
