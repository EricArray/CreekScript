#include <creek/Expression_DynLoad.hpp>

#include <creek/DynCFunction.hpp>
#include <creek/GlobalScope.hpp>
#include <creek/Identifier.hpp>


namespace creek
{
    /// @brief  `ExprDynVar` constructor.
    /// @param  library_path    Path to the library.
    /// @param  var_name        Name of the variable.
    ExprDynVar::ExprDynVar(const std::string& library_path, VarName var_name) :
        m_library_path(library_path),
        m_var_name(var_name)
    {

    }

    Expression* ExprDynVar::clone() const
    {
        return new ExprDynVar(m_library_path, m_var_name);
    }

    Variable ExprDynVar::eval(const SharedPointer<Scope>& scope)
    {
        DynLibrary dl(m_library_path);
        return dl.find_dyn_var(m_var_name.name())->copy();
    }

    Bytecode ExprDynVar::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() <<
            static_cast<uint8_t>(OpCode::dyn_var) <<
            m_library_path <<
            var_name_map.id_from_name(m_var_name.name());
    }


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

    Expression* ExprDynFunc::clone() const
    {
        return new ExprDynFunc(m_arg_names, m_is_variadic, m_library_path, m_func_name);
    }

    Variable ExprDynFunc::eval(const SharedPointer<Scope>& scope)
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



    // @brief  `ExprDynClass` constructor.
    // @param  id              Class name.
    // @param  method_defs     List of method definitions.
    // @param  static_defs     List of static member definitions.
    // @param  library_path    Path to the library.
    ExprDynClass::ExprDynClass(VarName id, std::vector<MethodDef>& method_defs, std::vector<StaticDef>& static_defs, const std::string& library_path) :
        m_id(id),
        m_library_path(library_path)
    {
        m_method_defs.swap(method_defs);
        m_static_defs.swap(static_defs);
    }

    /// @brief  Get a copy.
    Expression* ExprDynClass::clone() const
    {
        std::vector<MethodDef> new_method_defs;
        for (auto& d : m_method_defs)
        {
            new_method_defs.emplace_back(d.arg_names, d.is_variadic, d.id);
        }
        std::vector<StaticDef> new_static_defs;
        for (auto& d : m_static_defs)
        {
            new_static_defs.emplace_back(d.id);
        }
        return new ExprDynClass(m_id, new_method_defs, new_static_defs, m_library_path);
    }

    // bool ExprDynClass::is_const() const
    // {
    //     return false;
    // }

    // /// @brief  Get an optimized copy.
    // Expression* ExprDynClass::const_optimize() const
    // {
    //     std::vector<MethodDef> new_method_defs;
    //     for (auto& d : m_method_defs)
    //     {
    //         new_method_defs.emplace_back(d.id, d.arg_names, d.is_variadic);
    //     }
    //     return new ExprDynClass(m_id, new_method_defs);
    // }

    Variable ExprDynClass::eval(const SharedPointer<Scope>& scope)
    {
        Variable new_class;

        {
            Variable super_class = scope->global()->class_UserData;

            std::vector< std::unique_ptr<Data> > args;
            args.emplace_back(super_class->copy());
            args.emplace_back(new Identifier(m_id));

            Variable func_derive = scope->global()->class_Class.attr(scope, "derive");
            new_class = func_derive->call(scope, args);
        }

        auto dl = std::make_shared<DynLibrary>(m_library_path);
        auto& dyn_class_def = dl->find_dyn_class(m_id.name());

        for (auto& method_def : m_method_defs)
        {
            Variable method = new DynCFunction(
                scope,
                method_def.arg_names,
                method_def.is_variadic,
                dl,
                dyn_class_def.find_method(method_def.id.name())
            );
            new_class.attr(scope, method_def.id, method.release());
        }

        for (auto& static_def : m_static_defs)
        {
            auto& var = dyn_class_def.find_static(static_def.id.name());
            new_class.attr(scope, static_def.id, var.copy());
        }

        dyn_class_def.class_obj().reset(new_class->copy());

        return new_class;
    }

    Bytecode ExprDynClass::bytecode(VarNameMap& var_name_map) const
    {
        Bytecode b;
        b << static_cast<uint8_t>(OpCode::dyn_class);
        b << var_name_map.id_from_name(m_id.name());

        b << static_cast<uint32_t>(m_method_defs.size());
        for (auto& method_def : m_method_defs)
        {
            b << var_name_map.id_from_name(method_def.id.name());
            b << static_cast<uint32_t>(method_def.arg_names.size());
            for (auto& arg_name : method_def.arg_names)
            {
                b << var_name_map.id_from_name(arg_name.name());
            }
            b << method_def.is_variadic;
        }

        b << static_cast<uint32_t>(m_static_defs.size());
        for (auto& static_def : m_static_defs)
        {
            b << var_name_map.id_from_name(static_def.id.name());
        }

        b << m_library_path;
        return b;
    }
}
