#include <creek/Expression_DynLoad.hpp>

#include <creek/DynCFunction.hpp>


namespace creek
{
    // `ExprDynFunc` constructor.
    // @param  arg_names       Names of the arguments.
    // @param  is_variadic     Is this function variadic?
    // @param  library_path    Path to the library.
    // @param  func_name       Name of the function.
    ExprDynFunc::ExprDynFunc(const std::vector<VarName>& arg_names, bool is_variadic,
                             const std::string& library_path,
                             const std::string& func_name) :
        m_arg_names(arg_names),
        m_is_variadic(is_variadic),
        m_library_path(library_path),
        m_func_name(func_name)
    {

    }

    Variable ExprDynFunc::eval(Scope& scope)
    {
        return Variable(new DynCFunction(scope, m_arg_names, m_is_variadic, m_library_path, m_func_name));
    }

    Bytecode ExprDynFunc::bytecode(VarNameMap& var_name_map) const
    {
        Bytecode b;
        b << static_cast<uint8_t>(OpCode::dyn_func);
        b << static_cast<uint32_t>(m_arg_names.size());
        for (auto& arg_name : m_arg_names)
        {
            b << var_name_map.id_from_name(arg_name.name());
        }
        b << m_is_variadic;
        b << m_library_path;
        b << m_func_name;
        return b;
    }
}
