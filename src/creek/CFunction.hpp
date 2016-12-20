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
    /// @brief  Data type: C or C++ function interface.
    class CREEK_API CFunction : public Data
    {
    public:
        /// @brief  Listener function pointer when this object is called.
        /// Receives the scope where this function was created and the list of
        /// arguments passed to it. Must return a pointer to a new `Data`; this
        /// is the returned value when called from script.
        using Listener = std::function<Data*(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >&)>;


        /// @brief  Shared function definition.
        struct Definition
        {
            Definition(const SharedPointer<Scope>& scope, int argn, bool is_variadic, Listener listener) :
                scope(scope),
                argn(argn),
                is_variadic(is_variadic),
                listener(listener)
            {
                if (is_variadic && argn == 0)
                {
                     argn = 1;
                }
            }

            SharedPointer<Scope> scope; ///< Scope where this function was created.
            unsigned argn; ///< Number of arguments.
            bool is_variadic; ///< Is variadic function.
            Listener listener; /// C or C++ function to call.
        };

        /// @brief  Stored value type.
        using Value = std::shared_ptr<Definition>;


        /// @brief  `CFunction` constructor.
        /// @param  value   CFunction value.
        CFunction(const Value& value);

        /// @brief  `CFunction` constructor.
        /// @param  scope       Scope where this function was created.
        /// @param  argn        Number of arguments.
        /// @param  is_variadic Is variadic.
        /// @param  listener    Listener function to call.
        CFunction(const SharedPointer<Scope>& scope, int argn, bool is_variadic, Listener listener);

        /// @brief  `CFunction` constructor.
        /// @param  c_func  Any C function to call.
        /// The C function must take argument as normal instead of a vector
        /// of data objects, and return a C value or void.
        template<class R, class...Args>
        CFunction(const SharedPointer<Scope>& scope, R(*c_func)(Args...));


        /// @brief  Get value.
        const Value& value() const;


        Data* copy() const override;
        std::string class_name() const override;
        std::string debug_text() const override;

        bool bool_value(const SharedPointer<Scope>& scope) const override;
        // void bool_value(bool new_value) override;
        // int int_value(const SharedPointer<Scope>& scope) const override;
        // void int_value(int new_value) override;
        // double double_value(const SharedPointer<Scope>& scope) const override;
        // void float_value(float new_value) override;
        // std::string string_value(const SharedPointer<Scope>& scope) const override;
        // void string_value(const std::string& new_value) override;

        // Data* index(const SharedPointer<Scope>& scope, Data* key) override;
        // Data* index(const SharedPointer<Scope>& scope, Data* key, Data* new_value) override;

        // Data* add(const SharedPointer<Scope>& scope, Data* other) override;
        // Data* sub(const SharedPointer<Scope>& scope, Data* other) override;
        // Data* mul(const SharedPointer<Scope>& scope, Data* other) override;
        // Data* div(const SharedPointer<Scope>& scope, Data* other) override;
        // Data* mod(const SharedPointer<Scope>& scope, Data* other) override;
        // Data* exp(const SharedPointer<Scope>& scope, Data* other) override;
        // Data* min() override;
        // Data* bit_and(const SharedPointer<Scope>& scope, Data* other) override;
        // Data* bit_or(const SharedPointer<Scope>& scope, Data* other) override;
        // Data* bit_xor(const SharedPointer<Scope>& scope, Data* other) override;
        // Data* bit_not(const SharedPointer<Scope>& scope) override;
        int cmp(const SharedPointer<Scope>& scope, Data* other) override;

        Data* call(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args) override;


    private:
        Value m_value;
    };


    template<class R, class... Args>
    CFunction::CFunction(const SharedPointer<Scope>& scope, R(*c_func)(Args...)) :
        CFunction(
            scope,
            sizeof...(Args),
            false,
            Resolver::c_func_to_listener(std::function<R(Args...)>(c_func))
        )
    {

    }
}
