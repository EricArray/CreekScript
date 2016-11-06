#pragma once

#include <creek/Expression.hpp>

#include <vector>

#include <creek/api_mode.hpp>
#include <creek/VarName.hpp>


namespace creek
{
    /// @defgroup   expression_dyn_load Dynamic load operations
    /// @{

    /// @brief  Expression: Load function from dynamic library.
    /// Returns a new `DynCFunction`.
    class CREEK_API ExprDynFunc : public Expression
    {
    public:
        /// @brief  `ExprDynFunc` constructor.
        /// @param  arg_names       Names of the arguments.
        /// @param  is_variadic     Is this function variadic?
        /// @param  library_path    Path to the library.
        /// @param  func_name       Name of the function.
        ExprDynFunc(const std::vector<VarName>& arg_names, bool is_variadic,
                    const std::string& library_path,
                    const std::string& func_name);

        Expression* clone() const override;
        
        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::vector<VarName> m_arg_names;
        bool m_is_variadic;
        std::string m_library_path;
        std::string m_func_name;
    };

    /// @}
}
