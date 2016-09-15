#pragma once

#include <functional>
#include <string>
#include <typeinfo>
#include <vector>

#include <creek/Boolean.hpp>
#include <creek/Number.hpp>
#include <creek/String.hpp>
#include <creek/Vector.hpp>
#include <creek/Void.hpp>


namespace creek
{
    // interfaces
    /// Template for conversion between dynamic data and static values.
    namespace Resolver
    {
        /// Convert a data object to a value.
        /// @param  T       Value type.
        /// @param  data    Data to convert.
        template<class T> T data_to_value(Data* data);

        /// Convert a value into a data object.
        /// Can convert C function to CFunction objects.
        /// @param  T       Value type.
        /// @param  value   Value to convert.
        template<class T> Data* value_to_data(const T& value);


        template<class T> struct data_to_value_struct
        {
            static T get(Data* data);
        };

        template<class T> struct value_to_data_struct
        {
            static Data* get(const T& value);
        };


        using DataVector = std::vector< std::unique_ptr<Data> >;
        using Iterator = DataVector::iterator;

        /// Convert a C function to the format used by `CFunction`.
        /// @param  c_function  Function to convert.
        template<class R, class... Args>
        std::function<Data*(DataVector&)> c_function_to_listener(std::function<R(Args...)> c_function);

        /// Execute a C function from an argument vector, used by `data_to_value`.
        template<unsigned unresolved, class R, class... Args> struct runner
        {
            template<class F, class... Resolved>
            static Data* run(F f, Iterator iter, Resolved... resolved);
        };
    }


    // implementations
    namespace Resolver
    {
        // Convert a data object to a value.
        // @param  T       Value type.
        // @param  data    Data to convert.
        template<class T> T data_to_value(Data* data)
        {
            return data_to_value_struct<T>::get(data);
        }

        // Convert a value into a data object.
        // Can convert C function to CFunction objects.
        // @param  T       Value type.
        // @param  value   Value to convert.
        template<class T> Data* value_to_data(const T& value)
        {
            return value_to_data_struct<T>::get(value);
        }

        // data_to_value
        template<class T> T data_to_value_struct<T>::get(Data* data)
        {
            throw Unimplemented(std::string("Resolver::data_to_value for type ") + typeid(T).name());
        }

        template<> struct data_to_value_struct<bool>
        {
            static bool get(Data* data) { return data->bool_value(); }
        };

        template<> struct data_to_value_struct<char>
        {
            static char get(Data* data) { return data->char_value(); }
        };

        template<> struct data_to_value_struct<int>
        {
            static int get(Data* data) { return data->int_value(); }
        };

        template<> struct data_to_value_struct<float>
        {
            static float get(Data* data) { return data->float_value(); }
        };

        template<> struct data_to_value_struct<std::string>
        {
            static std::string get(Data* data) { return data->string_value(); }
        };

        template<class T> struct data_to_value_struct<std::vector<T>>
        {
            static std::vector<T> get(Data* data)
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
        template<class T> Data* value_to_data_struct<T>::get(const T& value)
        {
            throw Unimplemented(std::string("Resolver::value_to_data for type ") + typeid(T).name());
        }

        template<> struct value_to_data_struct<bool>
        {
            static Data* get(const bool& value) { return new Boolean(value); }
        };

        template<> struct value_to_data_struct<char>
        {
            static Data* get(const char& value) { return new String(std::string(1, value)); }
        };

        template<> struct value_to_data_struct<int>
        {
            static Data* get(const int& value) { return new Number(value); }
        };

        template<> struct value_to_data_struct<float>
        {
            static Data* get(const float& value) { return new Number(value); }
        };

        template<> struct value_to_data_struct<std::string>
        {
            static Data* get(const std::string& value) { return new String(value); }
        };

        template<class T> struct value_to_data_struct< std::vector<T> >
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


        // c function
        template<class R, class... Args>
        std::function<Data*(DataVector&)> c_function_to_listener(std::function<R(Args...)> c_function)
        {
            return [c_function](DataVector& args) -> Data*
            {
                static const unsigned argn = sizeof...(Args);
                return runner<argn, R, Args...>::run(c_function, args.begin());
            };
        }

        template<unsigned unresolved, class R, class... Args>
        template<class F, class... Resolved>
        Data* runner<unresolved, R, Args...>::run(F f, Iterator iter, Resolved... resolved)
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
        struct runner<0, R, Args...>
        {
            template<class F> static Data* run(F f, Iterator iter, Args... resolved)
            {
                return value_to_data<R>(f(resolved...));
            }
        };

        template<class... Args>
        struct runner<0, void, Args...>
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
}
