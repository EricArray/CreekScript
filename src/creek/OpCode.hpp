#pragma once

#include <cstdio>


namespace creek
{
    /// @brief  Bytecode op-codes.
    enum class OpCode : uint8_t
    {
        // debug
        nop                     = 0x00,
        print                   = 0x01,

        // arithmetic
        add                     = 0x10,
        sub                     = 0x11,
        mul                     = 0x12,
        div                     = 0x13,
        mod                     = 0x14,
        exp                     = 0x15,
        unm                     = 0x16,

        // bitwise
        bit_and                 = 0x17,
        bit_or                  = 0x18,
        bit_xor                 = 0x19,
        bit_not                 = 0x1A,
        bit_left_shift          = 0x1B,
        bit_right_shift         = 0x1C,

        // boolean
        bool_and                = 0x1D,
        bool_or                 = 0x1E,
        bool_xor                = 0x1F,
        bool_not                = 0x20,

        // comparison
        cmp                     = 0x21,
        eq                      = 0x22,
        ne                      = 0x23,
        lt                      = 0x24,
        le                      = 0x25,
        gt                      = 0x26,
        ge                      = 0x27,

        // data types
        data_void               = 0x30,
        data_null               = 0x31,
        data_boolean            = 0x32,
        data_number             = 0x33,
        data_string             = 0x34,
        data_identifier         = 0x35,
        data_vector             = 0x36,
        data_map                = 0x37,
        data_function           = 0x38,
        data_class              = 0x39,

        // control flow
        control_block           = 0x40,
        control_do              = 0x41,
        control_if              = 0x42,
        control_switch          = 0x43,
        control_loop            = 0x44,
        control_while           = 0x45,
        control_for             = 0x46,
        control_for_in          = 0x47,
        control_try             = 0x48,
        control_throw           = 0x49,
        control_return          = 0x4A,
        control_break           = 0x4B,

        // general
        call                    = 0x50,
        variadic_call           = 0x51,
        call_method             = 0x52,
        variadic_call_method    = 0x53,
        index_get               = 0x54,
        index_set               = 0x55,
        attr_get                = 0x56,
        attr_set                = 0x57,

        // variable
        var_create_local        = 0x60,
        var_load_local          = 0x61,
        var_store_local         = 0x62,
        var_create_global       = 0x63,
        var_load_global         = 0x64,
        var_store_global        = 0x65,

        // dynamic load
        dyn_func                = 0x70,
        dyn_class               = 0x71,
    };
}
