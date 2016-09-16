#pragma once

#include <creek/Data.hpp>

#include <functional>
#include <vector>
#include <memory>

#include <creek/api_mode.hpp>
#include <creek/Exception.hpp>
#include <creek/Resolver.hpp>
#include <creek/VarName.hpp>


namespace creek
{
    class Expression;


    /// Data type: C or C++ function interface.
    class CREEK_API CFunction : public Data
    {
    public:
        /// Function header.
        using FunctionPointer = std::function<Data*(std::vector< std::unique_ptr<Data> >&)>;


        /// Shared function definition.
        struct Definition
        {
            Definition(int argn, bool is_variadic, FunctionPointer function_ptr) :
                argn(argn),
                is_variadic(is_variadic),
                function_ptr(function_ptr)
            {
                if (is_variadic && argn == 0)
                {
                     argn = 1;
                }
            }

            unsigned argn; ///< Number of arguments.
            bool is_variadic; ///< Is variadic function.
            FunctionPointer function_ptr; /// C or C++ function to call.
        };

        /// Stored value type.
        using Value = std::shared_ptr<Definition>;


        /// `CFunction` constructor.
        /// @param  value   CFunction value.
        CFunction(const Value& value);

        /// `CFunction` constructor.
        /// @param  argn            Number of arguments.
        /// @param  is_variadic     Is variadic.
        /// @param  function_ptr    Listener function to call.
        CFunction(int argn, bool is_variadic, FunctionPointer function_ptr);

        /// `CFunction` constructor.
        /// The C function must take argument as normal instead of a vector
        /// of data objects, and return a C value or void.
        /// @param  c_function      Any C function to call.
        template<class R, class...Args>
        CFunction(R(*c_function)(Args...));

//        /// `CFunction` constructor.
//        /// The C function must take argument as normal instead of a vector
//        /// of data objects, and return a C value or void.
//        /// @param  c_function      Any C function to call.
//        template<class T>
//        CFunction(T c_function);


        Data* copy() const override;
        std::string class_name() const override;
        std::string debug_text() const override;

        bool bool_value() const override;
        // void bool_value(bool new_value) override;
        // int int_value() const override;
        // void int_value(int new_value) override;
        // float float_value() const override;
        // void float_value(float new_value) override;
        // std::string string_value() const override;
        // void string_value(const std::string& new_value) override;

        // Data* index(Data* key) override;
        // Data* index(Data* key, Data* new_value) override;

        // Data* add(Data* other) override;
        // Data* sub(Data* other) override;
        // Data* mul(Data* other) override;
        // Data* div(Data* other) override;
        // Data* mod(Data* other) override;
        // Data* exp(Data* other) override;
        // Data* min() override;
        // Data* bit_and(Data* other) override;
        // Data* bit_or(Data* other) override;
        // Data* bit_xor(Data* other) override;
        // Data* bit_not() override;
        int cmp(Data* other) override;

        Data* call(std::vector< std::unique_ptr<Data> >& args) override;


    private:
        Value m_value;
    };


    template<class R, class... Args>
    CFunction::CFunction(R(*c_function)(Args...)) :
        CFunction(sizeof...(Args), false, Resolver::c_function_to_listener(std::function<R(Args...)>(c_function)))
    {

    }

//    template<class T>
//    CFunction::CFunction(T c_function) :
//        CFunction(sizeof...(Args), false, Resolver::c_function_to_listener(c_function))
//    {
//
//    }
}
