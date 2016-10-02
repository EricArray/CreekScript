#include <creek/DynLibrary.hpp>

#ifdef CREEK_WINDOWS
# include <windows.h>
#else
# include <dlfcn.h>
#endif


namespace creek
{
    // @brief  `DynFunc` constructor.
    // @param  argn        Argument number.
    // @param  is_variadic Is this function variadic?
    // @param  listener    CFunction listener.
    DynFunc::DynFunc(unsigned argn, bool is_variadic, CFunction::Listener listener) :
        m_argn(argn),
        m_is_variadic(is_variadic),
        m_listener(listener)
    {

    }


    // @brief  Get the name used for `func_name` in dynamic libraries.
    // Appends `"creek_func_"` to the beginning.
    std::string DynFunc::make_dyn_func_name(const std::string& func_name)
    {
        static const std::string prefix = "creek_func_";
        return prefix + func_name;
    }


    // @brief  Get argument number.
    unsigned DynFunc::argn() const
    {
        return m_argn;
    }

    // @brief  Get is variadic.
    bool DynFunc::is_variadic() const
    {
        return m_is_variadic;
    }

    // @brief  Get listener.
    CFunction::Listener DynFunc::listener() const
    {
        return m_listener;
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
    // Search in this library for a global `DynFunc` variable named
    // `creek_func_<func_name>` where <func_name> is the argument
    // `func_name`.
    const DynFunc& DynLibrary::find_dyn_func(const std::string& func_name)
    {
        auto dyn_func_name = DynFunc::make_dyn_func_name(func_name);
        auto dyn_func = find_symbol<const DynFunc>(dyn_func_name);
        return *dyn_func;
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
