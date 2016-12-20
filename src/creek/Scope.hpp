#pragma once

#include <map>

#include <creek/api_mode.hpp>
#include <creek/VarName.hpp>
#include <creek/Variable.hpp>
#include <creek/Object.hpp>
#include <creek/Shared.hpp>


namespace creek
{
    class Scope;
    class GlobalScope;


    /// @brief  Space for variable names.
    class CREEK_API Scope : public Shared
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


        // /// @brief  `Scope` constructor.
        // /// Scope with no parent.
        // Scope();

        /// @brief  `Scope` constructor.
        /// @param  parent  Parent scope.
        Scope(
            const SharedPointer<Shared>& sp,
            const SharedPointer<Scope>& parent);

        /// @brief  `Scope` constructor.
        /// @param  parent      Parent scope.
        /// @param  return_pt   Return point.
        /// @param  break_pt    Break point.
        Scope(
            const SharedPointer<Shared>& sp,
            const SharedPointer<Scope>& parent,
            const std::shared_ptr<ReturnPoint>& return_pt,
            const std::shared_ptr<BreakPoint>& break_pt);

        /// @brief  `Scope` constructor.
        /// @param  parent      Parent scope.
        /// @param  global      Global scope.
        /// @param  return_pt   Return point.
        /// @param  break_pt    Break point.
        Scope(
            const SharedPointer<Shared>& sp,
            const SharedPointer<Scope>& parent,
            const SharedPointer<GlobalScope>& global,
            const std::shared_ptr<ReturnPoint>& return_pt,
            const std::shared_ptr<BreakPoint>& break_pt);

        virtual ~Scope() = default;


        /// @brief  Get parent scope.
        const SharedPointer<Scope>& parent();

        /// @brief  Get global scope.
        const SharedPointer<GlobalScope>& global();

        /// @brief  Create a new variable in local scope.
        /// @param  var_name    Variable name.
        /// @param  data        Initial value.
        /// @return             A reference to the created variable.
        /// The returned reference remains valid until the scope is destroyed
        /// or the variable is deleted.
        virtual Variable& create_local_var(VarName var_name, Data* data) = 0;
        // Variable& create_local_var(VarName var_name, Data* data);

        /// @brief  Find a variable accessible from this scope.
        /// @param  var_name    Variable name.
        /// @return             A reference to the variable.
        /// The returned reference remains valid until the scope is destroyed
        /// or the variable is deleted.
        virtual Variable& find_var(VarName var_name) = 0;
        // Variable& find_var(VarName var_name);

        /// @brief  Check if variable was created.
        /// @param  var_name    Variable name.
        virtual bool has_var(VarName var_name) = 0;

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
        SharedPointer<Scope> m_parent;
        SharedPointer<GlobalScope> m_global;
        // std::map<VarName, Variable> m_vars;
        std::shared_ptr<ReturnPoint> m_return_point;
        std::shared_ptr<BreakPoint> m_break_point;
    };


    /// @brief  Empty scope, used for copmile time execution.
    class CREEK_API ConstScope : public Scope
    {
    public:
        ConstScope(const SharedPointer<Shared>& sp);

        /// @brief  Create a new variable in local scope.
        /// @param  var_name    Variable name.
        /// @param  data        Initial value.
        /// @return             A reference to the created variable.
        /// The returned reference remains valid until the scope is destroyed
        /// or the variable is deleted.
        Variable& create_local_var(VarName var_name, Data* data) override;

        /// @brief  Find a variable accessible from this scope.
        /// @param  var_name    Variable name.
        /// @return             A reference to the variable.
        /// The returned reference remains valid until the scope is destroyed
        /// or the variable is deleted.
        Variable& find_var(VarName var_name) override;

        /// @brief  Check if variable was created.
        /// @param  var_name    Variable name.
        bool has_var(VarName var_name) override;
    };


    /// @brief  Basic scope for functions, blocks, etc.
    class CREEK_API LocalScope : public Scope
    {
    public:
        /// @brief  `LocalScope` constructor.
        /// @param  parent      Parent scope (can be the global scope).
        LocalScope(const SharedPointer<Shared>& sp, const SharedPointer<Scope>& parent);

        /// @brief  `LocalScope` constructor.
        /// @param  parent      Parent scope.
        /// @param  return_pt   Return point.
        /// @param  break_pt    Break point.
        LocalScope(
            const SharedPointer<Shared>& sp,
            const SharedPointer<Scope>& parent,
            const std::shared_ptr<ReturnPoint>& return_pt,
            const std::shared_ptr<BreakPoint>& break_pt);

        /// @brief  `LocalScope` constructor.
        /// @param  parent      Parent scope.
        /// @param  global      Global scope.
        /// @param  return_pt   Return point.
        /// @param  break_pt    Break point.
        LocalScope(
            const SharedPointer<Shared>& sp,
            const SharedPointer<Scope>& parent,
            const SharedPointer<GlobalScope>& global,
            const std::shared_ptr<ReturnPoint>& return_pt,
            const std::shared_ptr<BreakPoint>& break_pt);

        /// @brief  Create a new variable in local scope.
        /// @param  var_name    Variable name.
        /// @param  data        Initial value.
        /// @return             A reference to the created variable.
        /// The returned reference remains valid until the scope is destroyed
        /// or the variable is deleted.
        Variable& create_local_var(VarName var_name, Data* data) override;

        /// @brief  Find a variable accessible from this scope.
        /// @param  var_name    Variable name.
        /// @return             A reference to the variable.
        /// The returned reference remains valid until the scope is destroyed
        /// or the variable is deleted.
        Variable& find_var(VarName var_name) override;

        /// @brief  Check if variable was created.
        /// @param  var_name    Variable name.
        bool has_var(VarName var_name) override;

        /// @brief  Get variable list.
        std::map<VarName, Variable>& vars();

    protected:
        LocalScope(const SharedPointer<Shared>& sp);

    private:
        std::map<VarName, Variable> m_vars;
    };



    /// @brief  Object scope for classes.
    class CREEK_API ObjectScope : public Scope
    {
    public:
        ObjectScope(const SharedPointer<Shared>& sp, const SharedPointer<Scope>& parent, Object* object);

        ObjectScope(
            const SharedPointer<Shared>& sp,
            const SharedPointer<Scope>& parent,
            const std::shared_ptr<ReturnPoint>& return_pt,
            const std::shared_ptr<BreakPoint>& break_pt,
            Object* object);

        /// @brief  Create a new variable in local scope.
        /// @param  var_name    Variable name.
        /// @param  data        Initial value.
        /// @return             A reference to the created variable.
        /// The returned reference remains valid until the scope is destroyed
        /// or the variable is deleted.
        Variable& create_local_var(VarName var_name, Data* data) override;

        /// @brief  Find a variable accessible from this scope.
        /// @param  var_name    Variable name.
        /// @return             A reference to the variable.
        /// The returned reference remains valid until the scope is destroyed
        /// or the variable is deleted.
        Variable& find_var(VarName var_name) override;

        /// @brief  Check if variable was created.
        /// @param  var_name    Variable name.
        bool has_var(VarName var_name) override;

    private:
        std::unique_ptr<Object> m_object;
    };
}
