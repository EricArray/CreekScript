/// @file Library.hpp
/// Utilities for creation of libraries.
#pragma once

#include <map>
#include <string>

#include <creek/CFunction.hpp>
#include <creek/Resolver.hpp>


/// Header for a class map in a library.
/// @param  CLASS   Class being mapped (identifier).
/// Will declare a variable with name `class_map_CLASS`, where CLASS is
/// the identifier of the mapped class.
/// Must be initialized with a list of pairs of method-name and CFuntion
/// listener.
/// The following code generates a class map named `class_map_MyClass`:
/// @code
/// struct MyClass {
///     int value;
///     void set_value(int new_value) { value = new_value; }
///     int get_value() { return value; }
/// };
/// CREEK_MAP_CLASS(MyClass) {
///     CREEK_MAP_CLASS_METHOD(MyClass, get_value),
///     CREEK_MAP_CLASS_METHOD(MyClass, set_value),
/// };
/// @endcode
/// @sa CREEK_MAP_CLASS_METHOD
#define CREEK_MAP_CLASS(CLASS) \
    CREEK_API extern "C" const creek::LibraryClassMap class_map_##CLASS


/// Definition of a class method in a class map.
/// @param  CLASS   Class being mapped (identifier).
/// @param  METHOD  Method being mapped (identifier).
/// @sa CREEK_MAP_CLASS
#define CREEK_MAP_CLASS_METHOD(CLASS, METHOD) \
    { #METHOD, creek::Resolver::c_function_to_listener(&CLASS::METHOD) }


namespace creek
{
    /// Definition of a class in a library.
    using LibraryClassMap = std::map<std::string, creek::CFunction::FunctionPointer>;
}
