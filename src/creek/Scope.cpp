#include <creek/Scope.hpp>

#include <creek/Exception.hpp>


namespace creek
{
    // // `Scope` constructor.
    // Scope::Scope() :
    //     m_parent(nullptr),
    //     m_global(*this),
    //     m_return_point(new ReturnPoint()),
    //     m_break_point(new BreakPoint())
    // {

    // }

    /// @brief  `Scope` constructor.
    /// @param  parent  Parent scope.
    Scope::Scope(const SharedPointer<Shared>& sp, const SharedPointer<Scope>& parent) :
        Scope(
            sp,
            parent,
            parent ? parent->m_return_point : std::make_shared<ReturnPoint>(),
            parent ? parent->m_break_point : std::make_shared<BreakPoint>()
        )
    {

    }

    /// @brief  `Scope` constructor.
    /// @param  parent      Parent scope (can be the global scope).
    /// @param  return_pt   Return point.
    /// @param  break_pt    Break point.
    Scope::Scope(const SharedPointer<Shared>& sp, const SharedPointer<Scope>& parent,
                 const std::shared_ptr<ReturnPoint>& return_pt,
                 const std::shared_ptr<BreakPoint>& break_pt) :
        Scope(
            sp,
            parent,
            parent ? parent->global() : nullptr,
            return_pt,
            break_pt
        )
    {

    }

    /// @brief  `Scope` constructor.
    /// @param  parent      Parent scope (can be the global scope).
    /// @param  return_pt   Return point.
    /// @param  break_pt    Break point.
    Scope::Scope(const SharedPointer<Shared>& sp, const SharedPointer<Scope>& parent,
                 const SharedPointer<GlobalScope>& global,
                 const std::shared_ptr<ReturnPoint>& return_pt,
                 const std::shared_ptr<BreakPoint>& break_pt) :
        Shared(sp),
        m_parent(parent),
        m_global(global),
        m_return_point(return_pt),
        m_break_point(break_pt)
    {

    }

    const SharedPointer<Scope>& Scope::parent()
    {
        return m_parent;
    }

    const SharedPointer<GlobalScope>& Scope::global()
    {
        return m_global;
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



    ConstScope::ConstScope(const SharedPointer<Shared>& sp) : Scope(sp, nullptr)
    {

    }

    /// @brief  Create a new variable in local scope.
    /// @param  var_name    Variable name.
    /// @param  data        Initial value.
    /// @return             A reference to the created variable.
    /// The returned reference remains valid until the scope is destroyed
    /// or the variable is deleted.
    Variable& ConstScope::create_local_var(VarName var_name, Data* data)
    {
        throw Exception("Can't create local variable in compile time");
    }

    /// @brief  Find a variable accessible from this scope.
    /// @param  var_name    Variable name.
    /// @return             A reference to the variable.
    /// The returned reference remains valid until the scope is destroyed
    /// or the variable is deleted.
    Variable& ConstScope::find_var(VarName var_name)
    {
        throw Exception("Can't read variable in compile time");
    }

    /// @brief  Check if variable was created.
    /// @param  var_name    Variable name.
    bool ConstScope::has_var(VarName var_name)
    {
        throw Exception("Can't read variable in compile time");
    }



    LocalScope::LocalScope(const SharedPointer<Shared>& sp) :
        Scope(sp, nullptr)
    {

    }

    /// @brief  `LocalScope` constructor.
    /// @param  parent      Parent scope (can be the global scope).
    LocalScope::LocalScope(const SharedPointer<Shared>& sp, const SharedPointer<Scope>& parent) :
        Scope(sp, parent)
    {

    }

    /// @brief  `LocalScope` constructor.
    /// @param  parent      Parent scope.
    /// @param  return_pt   Return point.
    /// @param  break_pt    Break point.
    LocalScope::LocalScope(
            const SharedPointer<Shared>& sp,
            const SharedPointer<Scope>& parent,
            const std::shared_ptr<ReturnPoint>& return_pt,
            const std::shared_ptr<BreakPoint>& break_pt) :
        Scope(sp, parent, return_pt, break_pt)
    {

    }

    /// @brief  `LocalScope` constructor.
    /// @param  parent      Parent scope.
    /// @param  global      Global scope.
    /// @param  return_pt   Return point.
    /// @param  break_pt    Break point.
    LocalScope::LocalScope(
            const SharedPointer<Shared>& sp,
            const SharedPointer<Scope>& parent,
            const SharedPointer<GlobalScope>& global,
            const std::shared_ptr<ReturnPoint>& return_pt,
            const std::shared_ptr<BreakPoint>& break_pt) :
        Scope(sp, parent, global, return_pt, break_pt)
    {

    }

    // Create a new variable in local scope.
    // @param  var_name    Variable name.
    // @param  data        Initial value.
    Variable& LocalScope::create_local_var(VarName var_name, Data* data)
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
    Variable& LocalScope::find_var(VarName var_name)
    {
        // check if name is in scope
        auto it = m_vars.find(var_name);
        if (it == m_vars.end())
        {
            if (parent())
            {
                // find var in parent scope
                return parent()->find_var(var_name);
            }
            else
            {
                throw Exception(std::string("Can't find variable ") + var_name.name());
            }
        }
        return it->second;
    }

    /// @brief  Check if variable was created.
    /// @param  var_name    Variable name.
    bool LocalScope::has_var(VarName var_name)
    {
        return m_vars.find(var_name) != m_vars.end();
    }

    /// @brief  Get variable list.
    std::map<VarName, Variable>& LocalScope::vars()
    {
        return m_vars;
    }



    ObjectScope::ObjectScope(
            const SharedPointer<Shared>& sp,
            const SharedPointer<Scope>& parent,
            const std::shared_ptr<ReturnPoint>& return_pt,
            const std::shared_ptr<BreakPoint>& break_pt,
            Object* object) :
        Scope(sp, parent, return_pt, break_pt),
        m_object(object)
    {

    }

    ObjectScope::ObjectScope(
            const SharedPointer<Shared>& sp,
            const SharedPointer<Scope>& parent,
            Object* object) :
        Scope(
            sp,
            parent,
            parent ? parent->return_point() : std::make_shared<ReturnPoint>(),
            parent ? parent->break_point() : std::make_shared<BreakPoint>()
        ),
        m_object(object)
    {

    }

    /// @brief  Create a new variable in local scope.
    /// @param  var_name    Variable name.
    /// @param  data        Initial value.
    /// @return             A reference to the created variable.
    /// The returned reference remains valid until the scope is destroyed
    /// or the variable is deleted.
    Variable& ObjectScope::create_local_var(VarName var_name, Data* new_data)
    {
        auto& var = m_object->value()->attrs[var_name];
        var.reset(new_data);
        return var;
    }

    /// @brief  Find a variable accessible from this scope.
    /// @param  var_name    Variable name.
    /// @return             A reference to the variable.
    /// The returned reference remains valid until the scope is destroyed
    /// or the variable is deleted.
    Variable& ObjectScope::find_var(VarName var_name)
    {
        // check if name is in scope
        auto it = m_object->value()->attrs.find(var_name);
        if (it == m_object->value()->attrs.end())
        {
            if (parent())
            {
                // find var in parent scope
                return parent()->find_var(var_name);
            }
            else
            {
                throw Exception(std::string("Can't find variable ") + var_name.name());
            }
        }
        return it->second;
    }

    /// @brief  Check if variable was created.
    /// @param  var_name    Variable name.
    bool ObjectScope::has_var(VarName var_name)
    {
        return m_object->value()->attrs.find(var_name) != m_object->value()->attrs.end();
    }
}
