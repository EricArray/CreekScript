#include <creek/DynLibrary.hpp>

#ifdef CREEK_WINDOWS
# include <windows.h>
#else
# include <dlfcn.h>
#endif


namespace creek
{
    // @brief  `DynFuncDef` constructor.
    // @param  argn        Argument number.
    // @param  is_variadic Is this function variadic?
    // @param  listener    CFunction listener.
    DynFuncDef::DynFuncDef(unsigned argn, bool is_variadic, CFunction::Listener listener) :
        m_argn(argn),
        m_is_variadic(is_variadic),
        m_listener(listener)
    {

    }


    // @brief  Get the name used for `func_name` in dynamic libraries.
    // Appends `"creek_func_"` to the beginning.
    std::string DynFuncDef::make_dyn_func_name(const std::string& func_name)
    {
        static const std::string prefix = "creek_func_";
        return prefix + func_name;
    }


    // @brief  Get argument number.
    unsigned DynFuncDef::argn() const
    {
        return m_argn;
    }

    // @brief  Get is variadic.
    bool DynFuncDef::is_variadic() const
    {
        return m_is_variadic;
    }

    // @brief  Get listener.
    CFunction::Listener DynFuncDef::listener() const
    {
        return m_listener;
    }



    /// @brief  DynClassDef constructor.
    /// @param  name            Class name.
    /// @param  class_obj       Variable to save the class object.
    /// @param  methods         Method list.
    /// @see    CREEK_CLASS_HEADER
    /// @see    CREEK_CLASS_IMPL
    /// @see    CREEK_CLASS
    DynClassDef::DynClassDef(
        const std::string& name,
        Variable& class_obj,
        const std::map<std::string, DynFuncDef>& methods
    ) :
        m_name(name),
        m_class_obj(class_obj),
        m_methods(methods)
    {

    }

    // /// @brief  DynClassDef constructor.
    // /// @param  methods Method list.
    // DynClassDef::DynClassDef(std::initializer_list< std::map<std::string, DynFuncDef>::value_type > methods) :
    //     m_methods(methods)
    // {

    // }

    /// @brief  Get the class name.
    const std::string& DynClassDef::name() const
    {
        return m_name;
    }

    /// @brief  Get the Variable storing the class object.
    Variable& DynClassDef::class_obj() const
    {
        return m_class_obj;
    }

    /// @brief  Find a method in this class.
    /// @param  name    Method name.
    const DynFuncDef& DynClassDef::find_method(const std::string& name) const
    {
        auto iter = m_methods.find(name);
        if (iter == m_methods.end())
        {
            std::string m = std::string("Dynamic class method not found: ") + name;
            throw Exception(m);
        }
        return iter->second;
    }

    std::string DynClassDef::make_dyn_class_name(const std::string& class_name)
    {
        static const std::string prefix = "creek_class_";
        return prefix + class_name;
    }



    // @brief  `DynLibrary` constructor.
    // @param  path    Path to the library file.
    DynLibrary::DynLibrary(const std::string& path)
    {
        #ifdef CREEK_WINDOWS
            m_handle = LoadLibrary(path.c_str());
        #else
            m_handle = dlopen(path.c_str(), RTLD_LAZY);
        #endif
        if (!m_handle)
        {
            throw DynLibraryError(path);
        }
    }

    DynLibrary::~DynLibrary()
    {
        if (m_handle)
        {
            #ifdef CREEK_WINDOWS
                FreeLibrary(reinterpret_cast<HMODULE>(m_handle));
            #else
                dlclose(m_handle);
            #endif
        }
    }

    void* DynLibrary::find_symbol_base(const std::string& symbol)
    {
        #ifdef CREEK_WINDOWS
            void* sym = reinterpret_cast<void*>(GetProcAddress(reinterpret_cast<HMODULE>(m_handle), symbol.c_str()));
        #else
            void* sym = dlsym(symbol.c_str());
        #endif
        if (!sym)
        {
            throw DynSymbolNotFound(symbol);
        }
        return sym;
    }

    // @brief  Find a listener function.
    // @param  func_name   Name of the function.
    // Search in this library for a global `DynFuncDef` variable named
    // `creek_func_<func_name>` where <func_name> is the argument
    // `func_name`.
    const DynFuncDef& DynLibrary::find_dyn_func(const std::string& func_name)
    {
        auto dyn_func_name = DynFuncDef::make_dyn_func_name(func_name);
        auto dyn_func_def = find_symbol<const DynFuncDef>(dyn_func_name);
        return *dyn_func_def;
    }


    /// @brief  Find a class definition.
    /// @param  class_name  Name of the class
    /// Search in this library for a global `DynClassDef` variable named
    /// `creek_class_<class_name>` where @c <class> is the @p class_name.
    const DynClassDef& DynLibrary::find_dyn_class(const std::string& class_name)
    {
        auto dyn_class_name = DynClassDef::make_dyn_class_name(class_name);
        auto dyn_class_def = find_symbol<const DynClassDef>(dyn_class_name);
        return *dyn_class_def;
    }




    /// @brief  `DynLibraryError` constructor.
    /// @param  path    Path to the file.
    DynLibraryError::DynLibraryError(const std::string& path) : m_path(path)
    {
        stream() << "Error loading dynamic library \"" << path << "\"";
    }

    /// @brief  Get the path to the file.
    const std::string& DynLibraryError::path() const
    {
        return m_path;
    }


    // @brief  `DynSymbolNotFound` constructor.
    // @param  symbol  Symbol that was not found.
    DynSymbolNotFound::DynSymbolNotFound(const std::string& symbol) : m_symbol(symbol)
    {
        stream() << "Dynamic symbol `" << symbol << "` not found";
    }

    // @brief  Get the symbol that was not found.
    const std::string& DynSymbolNotFound::symbol() const
    {
        return m_symbol;
    }
}
