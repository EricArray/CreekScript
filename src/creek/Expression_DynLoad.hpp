#pragma once

#include <creek/Expression.hpp>

#include <vector>

#include <creek/api_mode.hpp>
#include <creek/VarName.hpp>


namespace creek
{
    /// @defgroup   expression_dyn_load Dynamic load operations
    /// @{

    /// @brief  Expression: Load variable from dynamic library.
    /// Returns a copy of the value at that variable.
    class CREEK_API ExprDynVar : public Expression
    {
    public:
        /// @brief  `ExprDynVar` constructor.
        /// @param  library_path    Path to the library.
        /// @param  var_name        Name of the variable.
        ExprDynVar(const std::string& library_path,
                   VarName var_name);

        Expression* clone() const override;

        Variable eval(const SharedPointer<Scope>& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::string m_library_path;
        VarName m_var_name;
    };


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

        Variable eval(const SharedPointer<Scope>& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::vector<VarName> m_arg_names;
        bool m_is_variadic;
        std::string m_library_path;
        std::string m_func_name;
    };


    /// @brief  Expression: Load class from dynamic library.
    /// Returns a new class filled with methods of type @c DynCFunction.
    class CREEK_API ExprDynClass : public Expression
    {
    public:
        /// @brief  Dynamic class method definition.
        struct MethodDef
        {
            MethodDef(const std::vector<VarName>& arg_names, bool is_variadic, VarName id) :
                arg_names(arg_names),
                is_variadic(is_variadic),
                id(id)
            {

            }

            std::vector<VarName> arg_names; ///< Argument names.
            bool is_variadic; ///< Is this method variadic?
            VarName id; ///< Method name.
        };

        /// @brief  Class static member definition.
        struct StaticDef
        {
            StaticDef(VarName id) :
                id(id)
            {

            }

            VarName id; ///< Member name.
        };


        /// @brief  `ExprDynClass` constructor.
        /// @param  id              Class name.
        /// @param  method_defs     List of method definitions.
        /// @param  static_defs     List of static member definitions.
        /// @param  library_path    Path to the library.
        ExprDynClass(VarName id, std::vector<MethodDef>& method_defs, std::vector<StaticDef>& static_defs, const std::string& library_path);

        Expression* clone() const override;

        Variable eval(const SharedPointer<Scope>& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        VarName m_id;
        std::vector<MethodDef> m_method_defs;
        std::vector<StaticDef> m_static_defs;
        std::string m_library_path;
    };

    /// @}
}
