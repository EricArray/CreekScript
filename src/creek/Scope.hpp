#pragma once

#include <map>

#include <creek/api_mode.hpp>
#include <creek/VarName.hpp>
#include <creek/Variable.hpp>


namespace creek
{
    /// Space for variable names.
    class CREEK_API Scope
    {
    public:
        /// `Scope` constructor.
        Scope();

        /// `Scope` constructor.
        /// @param  parent  Parent scope.
        Scope(Scope& parent);


        /// Create a new variable in local scope.
        /// The returned reference remains valid until the scope is destroyed
        /// or the variable is deleted.
        /// @param  var_name    Variable name.
        /// @param  data        Initial value.
        /// @return             A reference to the created variable.
        Variable& create_local_var(VarName var_name, Data* data);

        /// Find a variable accessible from this scope.
        /// The returned reference remains valid until the scope is destroyed
        /// or the variable is deleted.
        /// @param  var_name    Variable name.
        /// @return             A reference to the variable.
        Variable& find_var(VarName var_name);

        /// Get the global scope.
        Scope& global_scope();

    private:
        Scope* m_parent;
        Scope& m_global;
        std::map<VarName, Variable> m_vars;
    };
}
