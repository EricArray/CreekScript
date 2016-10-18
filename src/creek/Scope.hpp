#pragma once

#include <map>

#include <creek/api_mode.hpp>
#include <creek/VarName.hpp>
#include <creek/Variable.hpp>


namespace creek
{
    /// @brief  Space for variable names.
    class CREEK_API Scope
    {
    public:
        /// @brief  Return marker shared between scopes of a function.
        /// When `is_returning` is `true`, blocks sharing this struct will end
        /// and yield the last evaluated expression.
        struct ReturnPoint
        {
            bool is_returning = false; ///< Is the function returning?
        };

        /// @brief  Break marker shared between scopes of a loop.
        /// When `is_breaking` is `true`, blocks sharing this struct will end
        /// and yield the last evaluated expression.
        struct BreakPoint
        {
            bool is_breaking = false; ///< Is the loop breaking?
        };


        /// @brief  `Scope` constructor.
        /// Scope with no parent.
        Scope();

        /// @brief  `Scope` constructor.
        /// @param  parent  Parent scope (can be the global scope).
        Scope(Scope& parent);

        /// @brief  `Scope` constructor.
        /// @param  parent      Parent scope (can be the global scope).
        /// @param  return_pt   Return point.
        /// @param  break_pt    Break point.
        Scope(Scope& parent,
              const std::shared_ptr<ReturnPoint>& return_pt,
              const std::shared_ptr<BreakPoint>& break_pt);

        Scope(const Scope& other) = delete;
        Scope(Scope&& other) = delete;


        /// @brief  Create a new variable in local scope.
        /// @param  var_name    Variable name.
        /// @param  data        Initial value.
        /// @return             A reference to the created variable.
        /// The returned reference remains valid until the scope is destroyed
        /// or the variable is deleted.
        Variable& create_local_var(VarName var_name, Data* data);

        /// @brief  Find a variable accessible from this scope.
        /// @param  var_name    Variable name.
        /// @return             A reference to the variable.
        /// The returned reference remains valid until the scope is destroyed
        /// or the variable is deleted.
        Variable& find_var(VarName var_name);

        /// @brief  Is the function returning?
        /// @return `true` if the shared return point is marked as returning.
        bool is_returning() const;

        /// @brief  Is the loop breaking or the function returning?
        /// Returns `true` if either the shared return point is marked as
        /// returning or the shared break point is marked as breaking.
        bool is_breaking() const;

        /// @brief  Get the return point.
        const std::shared_ptr<ReturnPoint>& return_point() const;

        /// @brief  Get the break point.
        const std::shared_ptr<BreakPoint>& break_point() const;


    private:
        Scope* m_parent;
        std::map<VarName, Variable> m_vars;
        std::shared_ptr<ReturnPoint> m_return_point;
        std::shared_ptr<BreakPoint> m_break_point;
    };
}
