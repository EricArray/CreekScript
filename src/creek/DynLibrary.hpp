/// @file DynLibrary.hpp
/// Dynamically-loaded libraries.
#pragma once

#include <functional>
#include <map>
#include <string>

#include <creek/api_mode.hpp>
#include <creek/CFunction.hpp>
#include <creek/Exception.hpp>
#include <creek/Resolver.hpp>
#include <creek/UserData.hpp>
#include <creek/Scope.hpp>


/// @defgroup   library_macros  Dynamic library macros
/// The following code generates a variable interface named
/// `creek_var_my_var`:
/// @code
/// // my_var.hpp
/// CREEK_VAR(my_var,   "Hello, world!");
/// @endcode
///
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
/// CREEK_FUNC_IMPL(my_print, &my_print);
///
/// // or in one file
/// void my_print(std::string output) {
///     std::cout << output;
/// }
/// CREEK_FUNC(my_print, &my_print);
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
///     static const int zero;
///     void set_value(int new_value) { value = new_value; }
///     int get_value() { return value; }
/// };
/// CREEK_CLASS_IMPL(MyClass, MyClass) (
///     CREEK_ATTR(value,   &MyClass::value),           // getter + setter
///     CREEK_STATIC(zero,  MyClass::zero),             // copied by value
///     CREEK_METHOD(get_value, &MyClass::get_value),
///     CREEK_METHOD(set_value, &MyClass::set_value)
/// );
/// @endcode
/// @{

/// @brief  Header for a variable interface in a dynamic library.
/// @param  NAME    Name for the variable (identifier).
/// Will declare an extern variable with name `creek_var_NAME`.
/// @see CREEK_VAR_HEADER
/// @see CREEK_VAR_IMPL
/// @see CREEK_VAR
#define CREEK_VAR_HEADER(NAME) \
    extern "C" CREEK_EXPORT const creek::Variable creek_var_##NAME

/// @brief  Implementation for a variable interface in a dynamic library.
/// @param  NAME    Name for the variable (identifier).
/// @param  VALUE   C++ value for the variable.
/// @see CREEK_VAR_HEADER
/// @see CREEK_VAR_IMPL
/// @see CREEK_VAR
#define CREEK_VAR_IMPL(NAME, VALUE) \
    const creek::Variable creek_var_##NAME(creek::Resolver::value_to_data(VALUE))

/// @brief  Header + implementation for a variable interface in a dynamic library.
/// @param  NAME    Name for the variable (identifier).
/// @param  VALUE   C++ value for the variable.
/// @see CREEK_VAR_HEADER
/// @see CREEK_VAR_IMPL
/// @see CREEK_VAR
#define CREEK_VAR(NAME, VALUE) \
    CREEK_VAR_HEADER(NAME); \
    CREEK_VAR_IMPL(NAME, VALUE)

/// @brief  Header for a function interface in a dynamic library.
/// @param  NAME    Name for the function (identifier).
/// Will declare an extern variable with name `creek_func_NAME`.
/// @see CREEK_FUNC_HEADER
/// @see CREEK_FUNC_IMPL
/// @see CREEK_FUNC
/// @see CREEK_FUNC_IMPL_X
/// @see CREEK_FUNC_X
#define CREEK_FUNC_HEADER(NAME) \
    extern "C" CREEK_EXPORT const creek::DynFuncDef creek_func_##NAME

/// @brief  Implementation for a function interface in a dynamic library.
/// @param  NAME    Name for the function (identifier).
/// @param  FUNC    Pointer to the function being mapped.
/// @see CREEK_FUNC_HEADER
/// @see CREEK_FUNC_IMPL
/// @see CREEK_FUNC
/// @see CREEK_FUNC_IMPL_X
/// @see CREEK_FUNC_X
#define CREEK_FUNC_IMPL(NAME, FUNC) \
    const creek::DynFuncDef creek_func_##NAME(FUNC)

/// @brief  Implementation for a function interface in a dynamic library.
/// @param  NAME        Name for the function (identifier).
/// @param  ARITY       Arity; argument number.
/// @param  IS_VARIADIC Is the function variadic?
/// @param  LISTENER    CFunction listener.
/// @see CREEK_FUNC_HEADER
/// @see CREEK_FUNC_IMPL
/// @see CREEK_FUNC
/// @see CREEK_FUNC_IMPL_X
/// @see CREEK_FUNC_X
#define CREEK_FUNC_IMPL_X(NAME, ARITY, IS_VARIADIC, LISTENER) \
    const creek::DynFuncDef creek_func_##NAME(ARITY, IS_VARIADIC, LISTENER)

/// @brief  Header + implementation for a function interface in a dynamic library.
/// @param  NAME    Name for the function (identifier).
/// @param  FUNC    Pointer to the function being mapped.
/// @see CREEK_FUNC_HEADER
/// @see CREEK_FUNC_IMPL
/// @see CREEK_FUNC
/// @see CREEK_FUNC_IMPL_X
/// @see CREEK_FUNC_X
#define CREEK_FUNC(NAME, FUNC) \
    CREEK_FUNC_HEADER(NAME); \
    CREEK_FUNC_IMPL(NAME, FUNC)

/// @brief  Header + implementation for a function interface in a dynamic library.
/// @param  NAME        Name for the function (identifier).
/// @param  ARITY       Arity; argument number.
/// @param  IS_VARIADIC Is the function variadic?
/// @param  LISTENER    CFunction listener.
/// @see CREEK_FUNC_HEADER
/// @see CREEK_FUNC_IMPL
/// @see CREEK_FUNC
/// @see CREEK_FUNC_IMPL_X
/// @see CREEK_FUNC_X
#define CREEK_FUNC_X(NAME, ARITY, IS_VARIADIC, LISTENER) \
    CREEK_FUNC_HEADER(NAME); \
    CREEK_FUNC_IMPL_X(NAME, ARITY, IS_VARIADIC, LISTENER)


/// @brief  Header for a class interface in a dynamic library.
/// @param  NAME    Name for the class (identifier).
/// Will declare an extern variable with name `creek_class_NAME`.
/// @see    CREEK_CLASS_HEADER
/// @see    CREEK_CLASS_IMPL
/// @see    CREEK_CLASS
/// @see    CREEK_METHOD
/// @see    CREEK_METHOD_X
/// @see    CREEK_STATIC
/// @see    CREEK_ATTR
#define CREEK_CLASS_HEADER(NAME) \
    extern "C" CREEK_EXPORT const creek::DynClassDef creek_class_##NAME

/// @brief  Implementation for a class interface in a dynamic library.
/// @param  NAME            Name for the class (identifier).
/// @param  CLASS           Class being mapped (identifier).
/// @see    CREEK_CLASS_HEADER
/// @see    CREEK_CLASS_IMPL
/// @see    CREEK_CLASS
/// @see    CREEK_METHOD
/// @see    CREEK_METHOD_X
/// @see    CREEK_STATIC
/// @see    CREEK_ATTR
#define CREEK_CLASS_IMPL(NAME, CLASS) \
    namespace creek { \
        template class UserData_base<CLASS>; \
        template<> Variable UserData_base<CLASS>::class_obj = nullptr; \
        template<> const DynClassDef* UserData_base<CLASS>::class_def = &creek_class_##NAME; \
    } \
    const creek::DynClassDef creek_class_##NAME = \
        creek::DynClassDef::Factory(#NAME, creek::UserData<CLASS>::class_obj)

/// @brief  Header + implementation for a function interface in a dynamic library.
/// @param  NAME    Name for the class (identifier).
/// @param  CLASS   Class being mapped (identifier).
/// @see    CREEK_CLASS_HEADER
/// @see    CREEK_CLASS_IMPL
/// @see    CREEK_CLASS
/// @see    CREEK_METHOD
/// @see    CREEK_METHOD_X
/// @see    CREEK_STATIC
/// @see    CREEK_ATTR
#define CREEK_CLASS(NAME, CLASS) \
    CREEK_CLASS_HEADER(NAME); \
    CREEK_CLASS_IMPL(NAME, CLASS)

/// @brief  Method definition for a class interface.
/// @param  NAME    Name for the method (identifier).
/// @param  FUNC    Pointer to the function/class method (function pointer).
/// @p FUNC can be C function pointer or a C++ class method pointer.
/// @see    CREEK_CLASS_HEADER
/// @see    CREEK_CLASS_IMPL
/// @see    CREEK_CLASS
/// @see    CREEK_METHOD
/// @see    CREEK_METHOD_X
/// @see    CREEK_STATIC
/// @see    CREEK_ATTR
#define CREEK_METHOD(NAME, FUNC) \
    creek::DynClassDef::Factory::MethodDef(#NAME, creek::DynClassDef::Method(new creek::DynFuncDef(FUNC)))

/// @brief  Method definition for a class interface.
/// @param  NAME        Name for the method (identifier).
/// @param  ARITY       Arity; argument number.
/// @param  IS_VARIADIC Is the function variadic?
/// @param  LISTENER    CFunction listener.
/// @see    CREEK_CLASS_HEADER
/// @see    CREEK_CLASS_IMPL
/// @see    CREEK_CLASS
/// @see    CREEK_METHOD
/// @see    CREEK_METHOD_X
/// @see    CREEK_STATIC
/// @see    CREEK_ATTR
#define CREEK_METHOD_X(NAME, ARITY, IS_VARIADIC, LISTENER) \
    creek::DynClassDef::Factory::MethodDef(#NAME, creek::DynClassDef::Method(new creek::DynFuncDef(ARITY, IS_VARIADIC, LISTENER)))

/// @brief  Static variable definition for a class interface.
/// @param  NAME        Name for the static variable (identifier).
/// @param  VALUE       C++ value for the static variable.
/// @see    CREEK_CLASS_HEADER
/// @see    CREEK_CLASS_IMPL
/// @see    CREEK_CLASS
/// @see    CREEK_METHOD
/// @see    CREEK_METHOD_X
/// @see    CREEK_STATIC
/// @see    CREEK_ATTR
#define CREEK_STATIC(NAME, VALUE) \
    creek::DynClassDef::Factory::StaticDef(#NAME, creek::DynClassDef::Static(creek::Resolver::value_to_data(VALUE)))

/// @brief  C++ struct public attribute getter & setter definition for a class interface.
/// @param  NAME        Name for the attribute (identifier).
/// @param  ATTR        Pointer to C++ struct public attribute.
/// @see    CREEK_CLASS_HEADER
/// @see    CREEK_CLASS_IMPL
/// @see    CREEK_CLASS
/// @see    CREEK_METHOD
/// @see    CREEK_METHOD_X
/// @see    CREEK_STATIC
/// @see    CREEK_ATTR
#define CREEK_ATTR(NAME, ATTR) \
    creek::DynClassDef::Factory::AttrDef(#NAME, creek::DynClassDef::Attr(creek::Resolver::attr_getter(ATTR), creek::Resolver::attr_setter(ATTR)))

/// @}


namespace creek
{
//    /// @brief  Definition of a class in a library.
//    using DynClass = std::map<std::string, CFunction::Listener>;


    /// @brief  Dynamic-load function definition.
    /// The source dynamic library must remain in scope.
    /// @see    CREEK_FUNC_HEADER
    /// @see    CREEK_FUNC_IMPL
    /// @see    CREEK_FUNC
    class CREEK_API DynFuncDef
    {
    public:
        /// @brief  `DynFuncDef` constructor.
        /// @param  argn        Argument number.
        /// @param  is_variadic Is this function variadic?
        /// @param  listener    CFunction listener.
        DynFuncDef(unsigned argn, bool is_variadic, CFunction::Listener m_listener);

        /// @brief  `DynFuncDef` constructor.
        /// @param  R       Returned type.
        /// @param  Args    Arguments type pack.
        /// @param  c_func  Any C function pointer.
        template<class R, class... Args>
        DynFuncDef(R(*c_func)(Args...));

        /// @brief  `DynFuncDef` constructor.
        /// @param  T           Class owning the method.
        /// @param  R           Returned type.
        /// @param  Args        Arguments type pack.
        /// @param  cpp_method  Any C++ class method pointer.
        template<class T, class R, class... Args>
        DynFuncDef(R(T::*cpp_method)(Args...));


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


    /// @brief  Dynamic-load class definition.
    /// @see    CREEK_CLASS_HEADER
    /// @see    CREEK_CLASS_IMPL
    /// @see    CREEK_CLASS
    class CREEK_API DynClassDef
    {
    public:
        struct Attr
        {
            Attr(
                    std::function<Data*(const SharedPointer<Scope>&, Data*)> getter,
                    std::function<Data*(const SharedPointer<Scope>&, Data*, Data*)> setter) :
                getter(getter),
                setter(setter)
            {

            }

            std::function<Data*(const SharedPointer<Scope>&, Data*)> getter;
            std::function<Data*(const SharedPointer<Scope>&, Data*, Data*)> setter;
        };

        using Method = std::shared_ptr<DynFuncDef>;

        using Static = std::shared_ptr<Data>;

//         struct Attr {
//             using Getter = std::function<Data*(Data*)>;
//             Attr(Getter getter) : getter(getter) { }
//             Attr(const Attr& o) : getter(o.getter) { }
//             Attr(Attr&& o) : getter(nullptr) { std::swap(getter, o.getter); }
//             Attr& operator=(const Attr& o) { getter = o.getter; return *this; }
//             Attr& operator=(Attr&& o) { std::swap(getter, o.getter); return *this; }
//             Getter getter;
//         };

//         struct Method {
//             Method(DynFuncDef* func_def) : func_def(func_def) { }
//             // Method(const Method& o) : func_def(o.func_def) { }
//             Method(Method&& o) : func_def(nullptr) { std::swap(func_def, o.func_def); }
// //            Method& operator=(const Method& o) { func_def = o.func_def; return *this; }
//             Method& operator=(Method&& o) { std::swap(func_def, o.func_def); return *this; }
//             std::unique_ptr<DynFuncDef> func_def;
//         };

//         struct Static {
//             Static(Data* data) : data(data) { }
//             Static(Static&& o) : data(nullptr) { std::swap(data, o.data); }
// //            Static& operator=(const Static& o) { data = o.data; return *this; }
//             Static& operator=(Static&& o) { std::swap(data, o.data); return *this; }
//             std::unique_ptr<Data> data;
//         };

        using AttrList   = std::map<std::string, Attr>;
        using MethodList = std::map<std::string, Method>;
        using StaticList = std::map<std::string, Static>;


        /// @brief  Helper struct for CREEK_CLASS_IMPL.
        /// For syntatic sugar on class definition.
        /// @see    CREEK_CLASS_IMPL
        struct Factory {
            using AttrDef   = std::pair<std::string, Attr>;
            using MethodDef = std::pair<std::string, Method>;
            using StaticDef = std::pair<std::string, Static>;

            // struct AttrDef {
            //     AttrDef(const std::string& name, Attr::Getter getter) : name(name), def(getter) { }
            //     AttrDef(AttrDef&& o) : name(), def(nullptr) { std::swap(name, o.name); std::swap(def, o.def); }
            //     std::string name;
            //     Attr def;
            // };

            // struct MethodDef {
            //     MethodDef(const std::string& name, DynFuncDef* func_def) : name(name), def(func_def) { }
            //     MethodDef(MethodDef&& o) : name(), def(nullptr) { std::swap(name, o.name); std::swap(def, o.def); }
            //     std::string name;
            //     Method def;
            // };

            // struct StaticDef {
            //     StaticDef(const std::string& name, Data* data) : name(name), def(data) { }
            //     StaticDef(StaticDef&& o) : name(), def(nullptr) { std::swap(name, o.name); std::swap(def, o.def); }
            //     std::string name;
            //     Static def;
            // };

            template<class... Members> struct Helper;

            Factory(const std::string& name, Variable& class_obj) :
                name(name),
                class_obj(class_obj)
            {

            }

            /// @param  members Should be of types AttrDef, MethodDef or StaticDef
            template<class... Members> DynClassDef operator() (Members... members) {
                AttrList attrs;
                MethodList methods;
                StaticList statics;
                return Helper<Members...>::get(name, class_obj, attrs, methods, statics, members...);
                // return DynClassDef(name, class_obj, std::move(members));
            }

            std::string name;
            Variable& class_obj;
        };


        /// @brief  DynClassDef constructor.
        /// @param  name        Class name.
        /// @param  class_obj   Variable to save the class object.
        /// @see    CREEK_CLASS_HEADER
        /// @see    CREEK_CLASS_IMPL
        /// @see    CREEK_CLASS
        DynClassDef(const std::string& name, Variable& class_obj, AttrList& attrs, MethodList& methods, StaticList& statics);

        // /// @brief  DynClassDef constructor.
        // /// @param  methods Method list.
        // /// @see    CREEK_CLASS_IMPL
        // DynClassDef(std::initializer_list< std::map<std::string, DynFuncDef>::value_type > methods);


        /// @brief  Get the class name.
        const std::string& name() const;

        /// @brief  Get the Variable storing the class object.
        Variable& class_obj() const;

        /// @brief  Find a attr in this class.
        /// @param  name    Attr name.
        const Attr& find_attr(const std::string& name) const;

        /// @brief  Find a method in this class.
        /// @param  name    Method name.
        const DynFuncDef& find_method(const std::string& name) const;

        /// @brief  Find a static var in this class.
        /// @param  name    Var name
        const Data& find_static(const std::string& name) const;


        /// @brief  Get the name used for `class_name` in dynamic libraries.
        /// Appends `"creek_class_"` to the beginning.
        static std::string make_dyn_class_name(const std::string& class_name);


    private:
        std::string m_name;
        Variable& m_class_obj;
        AttrList m_attrs;
        MethodList m_methods;
        StaticList m_statics;
    };

    template<> struct DynClassDef::Factory::Helper<> {
        static DynClassDef get(
            const std::string& name,
            Variable& class_obj,
            AttrList& attrs,
            MethodList& methods,
            StaticList& statics
        ) {
            return DynClassDef(name, class_obj, attrs, methods, statics);
        }
    };

    template<class... Tail> struct DynClassDef::Factory::Helper<DynClassDef::Factory::AttrDef, Tail...> {
        static DynClassDef get(
            const std::string& name,
            Variable& class_obj,
            AttrList& attrs,
            MethodList& methods,
            StaticList& statics,
            const AttrDef& def,
            Tail... tail
        ) {
            attrs.emplace(def.first, Attr(def.second.getter, def.second.setter));
            return DynClassDef::Factory::Helper<Tail...>::get(name, class_obj, attrs, methods, statics, tail...);
        }
    };

    template<class... Tail> struct DynClassDef::Factory::Helper<DynClassDef::Factory::MethodDef, Tail...> {
        static DynClassDef get(
            const std::string& name,
            Variable& class_obj,
            AttrList& attrs,
            MethodList& methods,
            StaticList& statics,
            const MethodDef& def,
            Tail... tail
        ) {
            methods.emplace(def.first, def.second);
            return DynClassDef::Factory::Helper<Tail...>::get(name, class_obj, attrs, methods, statics, tail...);
        }
    };

    template<class... Tail> struct DynClassDef::Factory::Helper<DynClassDef::Factory::StaticDef, Tail...> {
        static DynClassDef get(
            const std::string& name,
            Variable& class_obj,
            AttrList& attrs,
            MethodList& methods,
            StaticList& statics,
            const StaticDef& def,
            Tail... tail
        ) {
            statics.emplace(def.first, def.second);
            return DynClassDef::Factory::Helper<Tail...>::get(name, class_obj, attrs, methods, statics, tail...);
        }
    };


    /// @brief  Handle for dinamically-loaded libraries.
    /// Internally used to track DLL/SO files usage.
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

        /// @brief  Find a varible.
        /// @param  var_name    Name of the variable.
        /// Search in this library for a global `Variable` variable named
        /// `creek_var_<var_name>` where @c <var_name> is the @p var_name.
        const Variable& find_dyn_var(const std::string& var_name);

        /// @brief  Find a listener function.
        /// @param  func_name   Name of the function.
        /// Search in this library for a global `DynFuncDef` variable named
        /// `creek_func_<func_name>` where @c <func_name> is the @p func_name.
        const DynFuncDef& find_dyn_func(const std::string& func_name);

        /// @brief  Find a class definition.
        /// @param  class_name  Name of the class
        /// Search in this library for a global `DynClassDef` variable named
        /// `creek_class_<class_name>` where @c <class> is the @p class_name.
        const DynClassDef& find_dyn_class(const std::string& class_name);


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


    // @brief  `DynFuncDef` constructor.
    // @param  c_func  Any C or C++ function pointer.
    template<class R, class... Args>
    DynFuncDef::DynFuncDef(R(*c_func)(Args...)) :
        DynFuncDef(sizeof...(Args), false, Resolver::c_func_to_listener(c_func))
    {

    }

    // @brief  `DynFuncDef` constructor.
    // @param  T           Class owning the method.
    // @param  R           Returned type.
    // @param  Args        Arguments type pack.
    // @param  cpp_method  Any C++ class method pointer.
    template<class T, class R, class... Args>
    DynFuncDef::DynFuncDef(R(T::*cpp_method)(Args...)) :
        DynFuncDef(sizeof...(Args) + 1, false, Resolver::c_func_to_listener(cpp_method))
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


    template<class T> Data* UserData_base<T>::attr(const SharedPointer<Scope>& scope, VarName key)
    {
        if (!class_def)
        {
            throw Exception("Dynamic class not yet loaded");
        }
        auto getter = class_def->find_attr(key.name()).getter;
        return getter(scope, this);
    }

    template<class T> Data* UserData_base<T>::attr(const SharedPointer<Scope>& scope, VarName key, Data* new_data)
    {
        if (!class_def)
        {
            throw Exception("Dynamic class not yet loaded");
        }
        auto setter = class_def->find_attr(key.name()).setter;
        return setter(scope, this, new_data);
    }
}
