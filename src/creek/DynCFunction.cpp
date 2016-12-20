#include <creek/DynCFunction.hpp>

#include <creek/utility.hpp>


namespace creek
{
    // `DynCFunction` constructor.
    // @param  scope           Scope where this function was created.
    // @param  arg_names       Names of the arguments.
    // @param  is_variadic     Is this function variadic?
    // @param  library_path    File path to dynamic library.
    // @param  func_name       Name of the function in the library.
    DynCFunction::DynCFunction(const SharedPointer<Scope>& scope, const std::vector<VarName>& arg_names, bool is_variadic,
                               const std::string& library_path,
                               const std::string& func_name) :
        DynCFunction(scope,
                     arg_names, is_variadic,
                     std::make_shared<DynLibrary>(library_path),
                     func_name)
    {

    }

    // @brief  `DynCFunction` constructor.
    // @param  scope           Scope where this function was created.
    // @param  arg_names       Names of the arguments.
    // @param  is_variadic     Is this function variadic?
    // @param  dl              Shared dynamic library.
    // @param  func_name       Name of the function in the library.
    // Find in an shared library.
    DynCFunction::DynCFunction(const SharedPointer<Scope>& scope, const std::vector<VarName>& arg_names, bool is_variadic,
                               const std::shared_ptr<DynLibrary>& dl,
                               const std::string& func_name) :
        DynCFunction(scope,
                     arg_names, is_variadic,
                     dl, dl->find_dyn_func(func_name))
    {

    }

    // @brief  `DynCFunction` constructor.
    // @param  scope           Scope where this function was created.
    // @param  arg_names       Names of the arguments.
    // @param  is_variadic     Is this function variadic?
    // @param  dl              Shared dynamic library.
    // @param  dyn_func        Dynamic function.
    // Construct from dynamic function.
    DynCFunction::DynCFunction(const SharedPointer<Scope>& scope, const std::vector<VarName>& arg_names, bool is_variadic,
                               const std::shared_ptr<DynLibrary>& dl,
                               const DynFuncDef& df) :
        DynCFunction(dl, std::make_shared<Definition>(scope, df.argn(), df.is_variadic(), df.listener()))
    {
        if (is_variadic != df.is_variadic() ||
            arg_names.size() != df.argn())
        {
            throw WrongCFunctionHeader();
        }
    }

    // @brief  `DynCFunction` constructor.
    // @param  dl      Shared dynamic library.
    // @param  value   CFunction value.
    // Copy from an already loaded library.
    DynCFunction::DynCFunction(const std::shared_ptr<DynLibrary>& dl,
                               const Value& value) :
        CFunction(value),
        m_dl(dl)
    {

    }

    Data* DynCFunction::copy() const
    {
        return new DynCFunction(m_dl, CFunction::value());
    }

    std::string DynCFunction::class_name() const
    {
        return "DynCFunction";
    }

    std::string DynCFunction::debug_text() const
    {
        return std::string("DynCFunction(0x") +
               int_to_string(uintptr_t(CFunction::value().get()), 16, 8) +
               std::string(")");
    }


    WrongCFunctionHeader::WrongCFunctionHeader()
    {
        stream() << "Wrong dynamic c-function header";
    }
}
