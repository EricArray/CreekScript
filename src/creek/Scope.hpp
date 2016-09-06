#pragma once

#include <map>

#include <creek/VarName.hpp>
#include <creek/Variable.hpp>


namespace creek
{
    /// Space for variable names.
    class Scope
    {
    public:
        /// `Scope` constructor.
        Scope();

        /// `Scope` constructor.
        /// @param  parent  Parent scope.
        Scope(Scope* parent);


        /// Create a new variable in local scope.
        /// @param  var_name    Variable name.
        /// @param  data        Initial value.
        Variable& create_local_var(VarName var_name, Data* data);

        /// Find a variable accessible from this scope.
        /// @param  var_name    Variable name.
        Variable& find_var(VarName var_name);

    private:
        Scope* m_parent;
        std::map<VarName, Variable> m_vars;
    };
}