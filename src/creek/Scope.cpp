#include <creek/Scope.hpp>

#include <creek/Exception.hpp>


namespace creek
{
    // `Scope` constructor.
    Scope::Scope() :
        m_parent(nullptr),
        m_return_point(new ReturnPoint()),
        m_break_point(new BreakPoint())
    {

    }

    // `Scope` constructor.
    // @param  parent  Parent scope.
    Scope::Scope(Scope& parent) :
        Scope(parent, parent.m_return_point, parent.m_break_point)
    {

    }

    /// @brief  `Scope` constructor.
    /// @param  parent      Parent scope (can be the global scope).
    /// @param  return_pt   Return point.
    /// @param  break_pt    Break point.
    Scope::Scope(Scope& parent,
                 const std::shared_ptr<ReturnPoint>& return_pt,
                 const std::shared_ptr<BreakPoint>& break_pt) :
        m_parent(&parent),
        m_return_point(return_pt),
        m_break_point(break_pt)
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

    // @brief  Is the function returning?
    bool Scope::is_returning() const
    {
        return m_return_point->is_returning;
    }

    // @brief  Is the loop breaking?
    bool Scope::is_breaking() const
    {
        return m_break_point->is_breaking || m_return_point->is_returning;
    }

    // @brief  Get the return point.
    const std::shared_ptr<Scope::ReturnPoint>& Scope::return_point() const
    {
        return m_return_point;
    }

    // @brief  Get the break point.
    const std::shared_ptr<Scope::BreakPoint>& Scope::break_point() const
    {
        return m_break_point;
    }
}
