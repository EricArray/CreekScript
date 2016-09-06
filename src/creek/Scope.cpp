#include <creek/Scope.hpp>

#include <creek/Exception.hpp>


namespace creek
{
    // `Scope` constructor.
    Scope::Scope() : m_parent(nullptr)
    {

    }

    // `Scope` constructor.
    // @param  parent  Parent scope.
    Scope::Scope(Scope* parent) : m_parent(parent)
    {

    }

    // Create a new variable in local scope.
    // @param  var_name    Variable name.
    // @param  data        Initial value.
    Variable& Scope::create_local_var(VarName var_name, Data* data)
    {
        // check if name is in scope
        if (m_vars.count(var_name) != 0)
        {
            throw Exception();
        }

        // insert new variable
        auto emplaceo = m_vars.emplace(var_name, Variable(data));
        if (!emplaceo.second)   // not inserted
        {
            throw Exception();
        }
        return emplaceo.first->second;
    }

    // Find a variable accessible from this scope.
    // @param  var_name    Variable name.
    Variable& Scope::find_var(VarName var_name)
    {
        // check if name is in scope
        auto it = m_vars.find(var_name);
        if (it == m_vars.end())
        {
            if (m_parent)
            {
                // find var in parent scope
                return m_parent->find_var(var_name);
            }
            else
            {
                throw Exception();
            }
        }
        return it->second;
    }
}
