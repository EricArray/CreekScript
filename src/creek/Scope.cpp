#include <creek/Scope.hpp>

#include <creek/Exception.hpp>


namespace creek
{
    // `Scope` constructor.
    Scope::Scope() : m_parent(nullptr), m_global(*this)
    {

    }

    // `Scope` constructor.
    // @param  parent  Parent scope.
    Scope::Scope(Scope& parent) : m_parent(&parent), m_global(parent.m_global)
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
            throw Exception(std::string("Variable ") + var_name.name() + std::string(" already exists"));
        }

        // insert new variable
        auto emplaceo = m_vars.emplace(var_name, Variable(data));
        if (!emplaceo.second)   // not inserted
        {
            throw Exception(std::string("Can't insert variable ") + var_name.name());
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
                throw Exception(std::string("Can't find variable ") + var_name.name());
            }
        }
        return it->second;
    }

    // Get the global scope.
    Scope& Scope::global_scope()
    {
        return m_global;
    }
}
