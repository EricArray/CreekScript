#include <creek/OpCode.hpp>

namespace creek
{
    const std::map<OpCode, std::string> op_code_names {
        // debug
        { OpCode::nop,                      "nop" },
        { OpCode::print,                    "print" },

        // arithmetic
        { OpCode::add,                      "add" },
        { OpCode::sub,                      "sub" },
        { OpCode::mul,                      "mul" },
        { OpCode::div,                      "div" },
        { OpCode::mod,                      "mod" },
        { OpCode::exp,                      "exp" },
        { OpCode::unm,                      "unm" },

        // bitwise
        { OpCode::bit_and,                  "bit_and" },
        { OpCode::bit_or,                   "bit_or" },
        { OpCode::bit_xor,                  "bit_xor" },
        { OpCode::bit_not,                  "bit_not" },
        { OpCode::bit_left_shift,           "bit_left_shift" },
        { OpCode::bit_right_shift,          "bit_right_shift" },

        // boolean
        { OpCode::bool_and,                 "bool_and" },
        { OpCode::bool_or,                  "bool_or" },
        { OpCode::bool_xor,                 "bool_xor" },
        { OpCode::bool_not,                 "bool_not" },

        // comparison
        { OpCode::cmp,                      "cmp" },
        { OpCode::eq,                       "eq" },
        { OpCode::ne,                       "ne" },
        { OpCode::lt,                       "lt" },
        { OpCode::le,                       "le" },
        { OpCode::gt,                       "gt" },
        { OpCode::ge,                       "ge" },

        // data types
        { OpCode::data_void,                "data_void" },
        { OpCode::data_null,                "data_null" },
        { OpCode::data_boolean,             "data_boolean" },
        { OpCode::data_number,              "data_number" },
        { OpCode::data_string,              "data_string" },
        { OpCode::data_identifier,          "data_identifier" },
        { OpCode::data_vector,              "data_vector" },
        { OpCode::data_map,                 "data_map" },
        { OpCode::data_function,            "data_function" },
        { OpCode::data_class,               "data_class" },
        { OpCode::data_module,              "data_module" },

        // control flow
        { OpCode::control_block,            "control_block" },
        { OpCode::control_do,               "control_do" },
        { OpCode::control_if,               "control_if" },
        { OpCode::control_switch,           "control_switch" },
        { OpCode::control_loop,             "control_loop" },
        { OpCode::control_while,            "control_while" },
        { OpCode::control_for,              "control_for" },
        { OpCode::control_for_in,           "control_for_in" },
        { OpCode::control_try,              "control_try" },
        { OpCode::control_throw,            "control_throw" },
        { OpCode::control_return,           "control_return" },
        { OpCode::control_break,            "control_break" },

        // general
        { OpCode::call,                     "call" },
        { OpCode::variadic_call,            "variadic_call" },
        { OpCode::call_method,              "call_method" },
        { OpCode::variadic_call_method,     "variadic_call_method" },
        { OpCode::index_get,                "index_get" },
        { OpCode::index_set,                "index_set" },
        { OpCode::attr_get,                 "attr_get" },
        { OpCode::attr_set,                 "attr_set" },

        // variable
        { OpCode::var_create_local,         "var_create_local" },
        { OpCode::var_load_local,           "var_load_local" },
        { OpCode::var_store_local,          "var_store_local" },
        { OpCode::var_create_global,        "var_create_global" },
        { OpCode::var_load_global,          "var_load_global" },
        { OpCode::var_store_global,         "var_store_global" },

        // dynamic load
        { OpCode::dyn_var,                  "dyn_var" },
        { OpCode::dyn_func,                 "dyn_func" },
        { OpCode::dyn_class,                "dyn_class" },
    };
}
