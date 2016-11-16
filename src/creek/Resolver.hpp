#pragma once

#include <functional>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <vector>

#include <creek/api_mode.hpp>
#include <creek/Boolean.hpp>
#include <creek/Number.hpp>
#include <creek/String.hpp>
#include <creek/Vector.hpp>
#include <creek/Void.hpp>
#include <creek/UserData.hpp>


namespace creek
{
    class Scope;


    /// @brief  Template for conversion between dynamic data and static values.
    struct CREEK_API Resolver
    {
        template<class T> struct data_to_value_struct
        {
            using ret = T&;
            static ret get(Data* data);
        };

        template<class T> struct value_to_data_struct
        {
            static Data* get(const T& value);
        };

        /// @brief  Convert a data object to a value.
        /// @param  T       Value type.
        /// @param  data    Data to convert.
        template<class T> static auto data_to_value(Data* data) -> typename data_to_value_struct<T>::ret;

        /// @brief  Convert a value into a data object.
        /// @param  T       Value type.
        /// @param  value   Value to convert.
        /// Can convert C function to CFunction objects.
        template<class T> static Data* value_to_data(const T& value);


        using DataVector = std::vector< std::unique_ptr<Data> >;
        using Iterator = DataVector::iterator;

        /// @brief  Convert a C function to the format used by `CFunction`.
        /// @param  c_func  C function to convert.
        template<class R, class... Args>
        static std::function<Data*(Scope& scope, DataVector&)> c_func_to_listener(
            std::function<R(Args...)> c_func
        ) {
            return [c_func](Scope& scope, DataVector& args) -> Data*
            {
                static const unsigned argn = sizeof...(Args);
                return runner<argn, R, Args...>::run(c_func, args.begin());
            };
        }

        // /// @brief  Convert a C function to the format used by `CFunction`.
        // /// @param  c_func  C function to convert.
        template<class R, class... Args>
        static std::function<Data*(Scope& scope, DataVector&)> c_func_to_listener(
            R(*c_func)(Args...)
        ) {
            return c_func_to_listener(std::function<R(Args...)>(c_func));
        }

        // /// @brief  Convert a C function to the format used by `CFunction`.
        // /// @param  c_func  C function to convert.
        template<class T, class R, class... Args>
        static std::function<Data*(Scope& scope, DataVector&)> c_func_to_listener(
            R(T::*c_func)(Args...)
        ) {
            return c_func_to_listener(std::function<R(T*, Args...)>(c_func));
        }

        /// @brief  Execute a C function from an argument vector.
        /// @sa     data_to_value
        template<unsigned unresolved, class R, class... Args> struct runner
        {
            template<class F, class... Resolved>
            static Data* run(F f, Iterator iter, Resolved... resolved);
        };
    };


    // Convert a data object to a value.
    // @param  T       Value type.
    // @param  data    Data to convert.
    template<class T> auto Resolver::data_to_value(Data* data) -> typename data_to_value_struct<T>::ret
    {
        return data_to_value_struct<T>::get(data);
    }

    // Convert a value into a data object.
    // Can convert C function to CFunction objects.
    // @param  T       Value type.
    // @param  value   Value to convert.
    template<class T> Data* Resolver::value_to_data(const T& value)
    {
        return value_to_data_struct<T>::get(value);
    }

    // data_to_value
    template<class T> auto Resolver::data_to_value_struct<T>::get(Data* data) -> ret
    {
//        throw Unimplemented(std::string("Resolver::data_to_value for C++ type ") + typeid(T).name());

//        auto ud = data->assert_cast< typename UserData<T>::base >();
//        return ud->reference();

        auto ud = data->assert_cast<typename UserData<T>::base>();
        return ud->reference();
    }

    template<class T> struct Resolver::data_to_value_struct<T*>
    {
        using ret = T*;
        static ret get(Data* data) {
            auto ud = data->assert_cast<typename UserData<T>::base>();
            return ud->pointer();
        }
    };

    template<class T> struct Resolver::data_to_value_struct<const T> :
        public Resolver::data_to_value_struct<T>
    {

    };

    template<> struct Resolver::data_to_value_struct<bool>
    {
        using ret = bool;
        static ret get(Data* data) { return data->bool_value(); }
    };

    template<> struct Resolver::data_to_value_struct<char>
    {
        using ret = char;
        static ret get(Data* data) { return data->char_value(); }
    };

    template<> struct Resolver::data_to_value_struct<uint8_t>
    {
        using ret = uint8_t;
        static ret get(Data* data) { return data->int_value(); }
    };

    template<> struct Resolver::data_to_value_struct<uint16_t>
    {
        using ret = uint16_t;
        static ret get(Data* data) { return data->int_value(); }
    };

    template<> struct Resolver::data_to_value_struct<uint32_t>
    {
        using ret = uint32_t;
        static ret get(Data* data) { return data->int_value(); }
    };

    template<> struct Resolver::data_to_value_struct<uint64_t>
    {
        using ret = uint64_t;
        static ret get(Data* data) { return data->int_value(); }
    };

    template<> struct Resolver::data_to_value_struct<int8_t>
    {
        using ret = int8_t;
        static ret get(Data* data) { return data->int_value(); }
    };

    template<> struct Resolver::data_to_value_struct<int16_t>
    {
        using ret = int16_t;
        static ret get(Data* data) { return data->int_value(); }
    };

    template<> struct Resolver::data_to_value_struct<int32_t>
    {
        using ret = int32_t;
        static ret get(Data* data) { return data->int_value(); }
    };

    template<> struct Resolver::data_to_value_struct<int64_t>
    {
        using ret = int64_t;
        static ret get(Data* data) { return data->int_value(); }
    };

    template<> struct Resolver::data_to_value_struct<float>
    {
        using ret = float;
        static ret get(Data* data) { return data->float_value(); }
    };

    template<> struct Resolver::data_to_value_struct<double>
    {
        using ret = double;
        static ret get(Data* data) { return data->float_value(); }
    };

    template<> struct Resolver::data_to_value_struct<const char*>
    {
        using ret = const char*;
        static ret get(Data* data) { return data->string_value().c_str(); }
    };

    template<> struct Resolver::data_to_value_struct<std::string>
    {
        using ret = std::string;
        static ret get(Data* data) { return data->string_value(); }
    };

    template<class T> struct Resolver::data_to_value_struct<std::vector<T>>
    {
        using ret = std::vector<T>;
        static ret get(Data* data)
        {
            std::vector<T> ret;
            for (auto& item : data->vector_value())
            {
                ret.push_back(data_to_value<T>(item));
            }
            return ret;
        }
    };


    // value_to_data
    template<class T> Data* Resolver::value_to_data_struct<T>::get(const T& value)
    {
//        throw Unimplemented(std::string("Resolver::value_to_data for type ") + typeid(T).name());
        return new UserData<T>(new T(value));
    }

    template<> struct Resolver::value_to_data_struct<bool>
    {
        static Data* get(const bool& value) { return new Boolean(value); }
    };

    template<> struct Resolver::value_to_data_struct<char>
    {
        static Data* get(const char& value) { return new String(std::string(1, value)); }
    };

    template<> struct Resolver::value_to_data_struct<uint8_t>
    {
        static Data* get(const uint8_t& value) { return new Number(value); }
    };

    template<> struct Resolver::value_to_data_struct<uint16_t>
    {
        static Data* get(const uint16_t& value) { return new Number(value); }
    };

    template<> struct Resolver::value_to_data_struct<uint32_t>
    {
        static Data* get(const uint32_t& value) { return new Number(value); }
    };

    template<> struct Resolver::value_to_data_struct<uint64_t>
    {
        static Data* get(const uint64_t& value) { return new Number(value); }
    };

    template<> struct Resolver::value_to_data_struct<int8_t>
    {
        static Data* get(const int8_t& value) { return new Number(value); }
    };

    template<> struct Resolver::value_to_data_struct<int16_t>
    {
        static Data* get(const int16_t& value) { return new Number(value); }
    };

    template<> struct Resolver::value_to_data_struct<int32_t>
    {
        static Data* get(const int32_t& value) { return new Number(value); }
    };

    template<> struct Resolver::value_to_data_struct<int64_t>
    {
        static Data* get(const int64_t& value) { return new Number(value); }
    };

    template<> struct Resolver::value_to_data_struct<float>
    {
        static Data* get(const float& value) { return new Number(value); }
    };

    template<> struct Resolver::value_to_data_struct<double>
    {
        static Data* get(const double& value) { return new Number(value); }
    };

    template<> struct Resolver::value_to_data_struct<const char*>
    {
        static Data* get(const char* value) { return new String(std::string(value)); }
    };

    template<> struct Resolver::value_to_data_struct<std::string>
    {
        static Data* get(const std::string& value) { return new String(value); }
    };

    template<class T> struct Resolver::value_to_data_struct< std::vector<T> >
    {
        static Data* get(const std::vector<T>& value)
        {
            Vector::Value data_vec = std::make_shared< std::vector<Variable> >();
            for (auto& item : value)
            {
                data_vec->emplace_back(value_to_data<T>(item));
            }
            return new Vector(data_vec);
        }
    };


//        template<class R, class... Args>
//        struct value_to_data_struct< std::function<R(Args...)> >
//        {
//            static Data* get(const std::function<R(Args...)>& value)
//            {
//                static const bool variadic = false;
//                static const unsigned argn = sizeof...(Args);
//                CFunction::FunctionPointer function_ptr = [value](DataVector& args) -> Data*
//                {
//                    static const unsigned argn = sizeof...(Args);
//                    return runner<argn, R, Args...>::run(value, args.begin());
//                };
//
//                return new CFunction(argn, variadic, function_ptr);
//            }
//        };


    // runner
    template<unsigned unresolved, class R, class... Args>
    template<class F, class... Resolved>
    Data* Resolver::runner<unresolved, R, Args...>::run(F f, Iterator iter, Resolved... resolved)
    {
        static const unsigned arg_pos = sizeof...(Args) - unresolved;
        using type = typename std::tuple_element<arg_pos, std::tuple<Args...>>::type;
        return runner<unresolved - 1, R, Args...>::run(
            f,
            iter + 1,
            resolved...,
            data_to_value<type>(iter->get())
        );
    }

    template<class R, class... Args>
    struct Resolver::runner<0, R, Args...>
    {
        template<class F> static Data* run(F f, Iterator iter, Args... resolved)
        {
            return value_to_data<R>(f(resolved...));
        }
    };

    template<class... Args>
    struct Resolver::runner<0, void, Args...>
    {
        template<class F>
        static Data* run(F f, Iterator iter, Args... resolved)
        {
            f(resolved...);
            return new Void();
        }
    };

//        template<unsigned unresolved, class R, class... Args>
//        template<class F>
//        Data* runner<unresolved, R, Args...>::run(F f, Iterator iter)
//        {
//            static const unsigned arg_pos = sizeof...(Args) - unresolved;
//            using type = typename std::tuple_element<arg_pos, std::tuple<Args...>>::type;
//            return runner<unresolved - 1, R, Args...>::run(
//                f,
//                iter + 1,
//                data_to_value<type>::get(*iter)
//            );
//        }
}
