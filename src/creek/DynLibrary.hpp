/// @file DynLibrary.hpp
/// Dynamically-loaded libraries.
#pragma once

#include <map>
#include <string>

#include <creek/api_mode.hpp>
#include <creek/CFunction.hpp>
#include <creek/Exception.hpp>
#include <creek/Resolver.hpp>


/// @defgroup   library_macros  Dynamic library macros
/// The following code generates a function interface named
/// `creek_func_my_print`:
/// @code
/// // my_print.hpp
/// CREEK_FUNC_HEADER(my_print);
///
/// // my_print.cpp
/// void my_print(std::string output) {
///     std::cout << output;
/// }
/// CREEK_FUNC_IMPL(my_print);
/// @endcode
///
/// The following code generates a class interface named `creek_class_MyClass`:
/// @code
/// // MyClass.hpp
/// CREEK_CLASS_HEADER(MyClass);
///
/// // MyClass.cpp
/// struct MyClass {
///     int value;
///     void set_value(int new_value) { value = new_value; }
///     int get_value() { return value; }
/// };
/// CREEK_CLASS_IMPL(MyClass) {
///     CREEK_CLASS_FUNC(MyClass, get_value),
///     CREEK_CLASS_FUNC(MyClass, set_value),
/// };
/// @endcode
/// @{

/// @brief  Header for a function interface in a dynamic library.
/// @param  FUNC    Function being mapped (identifier).
/// Will declare an extern variable with name `creek_func_<FUNC>`, where <FUNC>
/// is the identifier of the mapped function.
#define CREEK_FUNC_HEADER(FUNC) \
    extern "C" CREEK_EXPORT const creek::DynFunc creek_func_##FUNC

/// @brief  Implementation for a function interface in a dynamic library.
/// @param  FUNC    Function being mapped (identifier).
#define CREEK_FUNC_IMPL(FUNC) \
    const creek::DynFunc creek_func_##FUNC(&FUNC)

/// @brief  Header + implementation for a function interface in a dynamic library.
/// @param  FUNC    Function being mapped (identifier).
#define CREEK_FUNC(FUNC) \
    extern "C" CREEK_EXPORT const creek::DynFunc creek_func_##FUNC(&FUNC)

// /// @brief  Header for a class insterface in a library.
// /// @param  CLASS   Class being mapped (identifier).
// /// Will declare an extern variable with name `creek_class_CLASS`, where CLASS
// /// is the identifier of the mapped class.
// #define CREEK_CLASS_HEADER(CLASS) \
//     CREEK_EXPORT extern "C" const creek::DynClass creek_class_##CLASS

// /// @brief  Implementation for a class interface in a library.
// /// @param  CLASS   Class being mapped (identifier).
// /// Must be followed by an initializer list of CREEK_CLASS_FUNC.
// #define CREEK_CLASS_IMPL(CLASS) \
//     const creek::DynClass creek_class_##CLASS

// /// @brief  Definition of a class method for a class map.
// /// @param  CLASS   Class being mapped (identifier).
// /// @param  FUNC    Function being mapped (identifier).
// #define CREEK_MAP_CLASS_FUNC(CLASS, FUNC) \
//     { #FUNC, creek::Resolver::c_func_to_listener(&CLASS::FUNC) }

/// @}


namespace creek
{
    /// @brief  Definition of a class in a library.
    using DynClass = std::map<std::string, CFunction::Listener>;


    /// @brief  Dynamic-load function info.
    /// The source dynamic library must remain in scope.
    class CREEK_API DynFunc
    {
    public:
        /// @brief  `DynFunc` constructor.
        /// @param  argn        Argument number.
        /// @param  is_variadic Is this function variadic?
        /// @param  listener    CFunction listener.
        DynFunc(unsigned argn, bool is_variadic, CFunction::Listener m_listener);

        /// @brief  `DynFunc` constructor.
        /// @param  c_func  Any C or C++ function pointer.
        template<class R, class... Args>
        DynFunc(R(*c_func)(Args...));


        /// @brief  Get the name used for `func_name` in dynamic libraries.
        /// Appends `"creek_func_"` to the beginning.
        static std::string make_dyn_func_name(const std::string& func_name);


        /// @brief  Get argument number.
        unsigned argn() const;

        /// @brief  Get is variadic.
        bool is_variadic() const;

        /// @brief  Get listener.
        CFunction::Listener listener() const;

    private:
        unsigned m_argn;
        bool m_is_variadic;
        CFunction::Listener m_listener;
    };


    /// @brief  Handle for dinamically-loaded libraries.
    class CREEK_API DynLibrary
    {
    public:
        /// @brief  `DynLibrary` constructor.
        /// @param  path    Path to the library file.
        DynLibrary(const std::string& path);

        ~DynLibrary();


        /// @brief  Find a symbol from this library.
        /// @param  T       Type of the symbol.
        /// @param  symbol  Symbol to search.
        template<class T>
        T* find_symbol(const std::string& symbol);

        /// @brief  Find a listener function.
        /// @param  func_name   Name of the function.
        /// Search in this library for a global `DynFunc` variable named
        /// `creek_func_<func_name>` where <func_name> is the argument
        /// `func_name`.
        const DynFunc& find_dyn_func(const std::string& func_name);

    private:
        void* find_symbol_base(const std::string& symbol);

        void* m_handle;
    };


    /// Error opening dynamic library.
    class CREEK_API DynLibraryError : public Exception
    {
    public:
        /// @brief  `DynLibraryError` constructor.
        /// @param  path    Path to the file.
        DynLibraryError(const std::string& path);

        /// @brief  Get the path to the file.
        const std::string& path() const;

    private:
        std::string m_path;
    };


    /// Symbol not found in dynamic library.
    class CREEK_API DynSymbolNotFound : public Exception
    {
    public:
        /// @brief  `DynSymbolNotFound` constructor.
        /// @param  symbol  Symbol that was not found.
        DynSymbolNotFound(const std::string& symbol);

        /// @brief  Get the symbol that was not found.
        const std::string& symbol() const;

    private:
        std::string m_symbol;
    };


    // @brief  `DynFunc` constructor.
    // @param  c_func  Any C or C++ function pointer.
    template<class R, class... Args>
    DynFunc::DynFunc(R(*c_func)(Args...)) :
        DynFunc(sizeof...(Args), false, Resolver::c_func_to_listener(c_func))
    {

    }

    // @brief  Find a symbol from this library.
    // @param  T       Type of the symbol.
    // @param  symbol  Symbol to search.
    template<class T>
    T* DynLibrary::find_symbol(const std::string& symbol)
    {
        return reinterpret_cast<T*>(find_symbol_base(symbol));
    }
}
