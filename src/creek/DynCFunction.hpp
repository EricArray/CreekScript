#pragma once

#include <creek/CFunction.hpp>

#include <creek/api_mode.hpp>
#include <creek/DynLibrary.hpp>
#include <creek/Exception.hpp>


namespace creek
{
    /// Data type: Dynamically loaded C or C++ function.
    class CREEK_API DynCFunction : public CFunction
    {
    public:
        /// @brief  `DynCFunction` constructor.
        /// @param  scope           Scope where this function was created.
        /// @param  arg_names       Names of the arguments.
        /// @param  is_variadic     Is this function variadic?
        /// @param  library_path    File path to dynamic library.
        /// @param  func_name       Name of the function in the library.
        /// Load a new library.
        DynCFunction(Scope& scope,
                     const std::vector<VarName>& arg_names, bool is_variadic,
                     const std::string& library_path,
                     const std::string& func_name);

        /// @brief  `DynCFunction` constructor.
        /// @param  scope       Scope where this function was created.
        /// @param  arg_names   Names of the arguments.
        /// @param  is_variadic Is this function variadic?
        /// @param  dl          Shared dynamic library.
        /// @param  func_name   Name of the function in the library.
        /// Find in an shared library.
        DynCFunction(Scope& scope,
                     const std::vector<VarName>& arg_names, bool is_variadic,
                     const std::shared_ptr<DynLibrary>& dl,
                     const std::string& func_name);

        /// @brief  `DynCFunction` constructor.
        /// @param  scope       Scope where this function was created.
        /// @param  arg_names   Names of the arguments.
        /// @param  is_variadic Is this function variadic?
        /// @param  dl          Shared dynamic library.
        /// @param  dyn_func    Dynamic function.
        /// Construct from dynamic function.
        DynCFunction(Scope& scope,
                     const std::vector<VarName>& arg_names, bool is_variadic,
                     const std::shared_ptr<DynLibrary>& dl,
                     const DynFunc& dyn_func);

        /// @brief  `DynCFunction` constructor.
        /// @param  dl      Shared dynamic library.
        /// @param  value   CFunction value.
        /// Copy from an already loaded library.
        DynCFunction(const std::shared_ptr<DynLibrary>& dl,
                     const Value& value);


        Data* copy() const override;
        std::string class_name() const override;
        std::string debug_text() const override;

    private:
        std::shared_ptr<DynLibrary> m_dl;
    };


    /// @brief  Wrong dynamic c-function header.
    class WrongCFunctionHeader : public Exception
    {
    public:
        /// @brief  `WrongCFunctionHeader` constructor.
        WrongCFunctionHeader();
    };
}
