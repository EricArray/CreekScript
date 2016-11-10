#include <creek/BytecodeInterpreter.hpp>

#include <fstream>

#include <creek/Expression.hpp>
#include <creek/Expression_Arithmetic.hpp>
#include <creek/Expression_DataTypes.hpp>
#include <creek/Expression_Bitwise.hpp>
#include <creek/Expression_Boolean.hpp>
#include <creek/Expression_Comparison.hpp>
#include <creek/Expression_ControlFlow.hpp>
#include <creek/Expression_Debug.hpp>
#include <creek/Expression_DynLoad.hpp>
#include <creek/Expression_General.hpp>
#include <creek/Expression_Variable.hpp>
#include <creek/OpCode.hpp>
#include <creek/utility.hpp>


namespace creek
{
    const std::string BytecodeInterpreter::magic_number = {0x00, 0x11, 0x22, 'C', 'R', 'E', 'E', 'K'};


    /// @brief  `Interpreter` constructor..
    BytecodeInterpreter::BytecodeInterpreter()
    {

    }


    /// Compile to bytecode file.
    /// @param  path        Path to the bytecode file.
    /// @param  program     Expression to save.
    void BytecodeInterpreter::save_file(const std::string& path, const Expression* program)
    {
        Bytecode bytecode;

        // translate
        VarNameMap var_name_map;
        auto program_bytecode = program->bytecode(var_name_map);

        // magic
        bytecode.write(magic_number);

        // pointer length in bytes
        bytecode << static_cast<uint8_t>(sizeof(intptr_t));

        // var name map
        bytecode << static_cast<uint32_t>(var_name_map.map().size());
        for (auto& i : var_name_map.map())
        {
            bytecode << i.second << i.first;
        }

        // program bytecode
        bytecode << program_bytecode;

        // file
        std::ofstream file(path, std::ios_base::binary|std::ios_base::trunc);
        if (file.fail())
        {
            throw Exception("Can't open output file");
        }
        auto bytes = bytecode.bytes();
        file.write(bytes.c_str(), bytes.size());
    }

    /// Interpret a source file.
    /// @param  path        Path to the source file.
    Expression* BytecodeInterpreter::load_file(const std::string& path)
    {
        auto bytecode = load(path);

        auto expression = parse(bytecode);

        return expression;
    }

    /// Interpret a bytecode.
    /// @param  bytecode    Bytecode.
    Expression* BytecodeInterpreter::load_bytecode(Bytecode& bytecode)
    {
        auto expression = parse(bytecode);

        return expression;
    }

    Bytecode BytecodeInterpreter::load(const std::string& path)
    {
        // open file
        std::ifstream file(path, std::ios::binary);
        if (file.fail())
        {
            throw Exception("Can't open bytecode file");
        }

        // read whole file
        std::stringstream ss;
        std::copy(std::istreambuf_iterator<char>(file),
                  std::istreambuf_iterator<char>(),
                  std::ostreambuf_iterator<char>(ss));

        // close file
        file.close();

        return Bytecode(ss);
    }

    Expression* BytecodeInterpreter::parse(Bytecode& bytecode)
    {
        // magic number
        std::string magic = bytecode.read(magic_number.size());
        if (magic != magic_number)
        {
            throw InvalidBytecode();
        }

        // pointer length in bytes
        uint8_t ptr_len = 0;
        bytecode >> ptr_len;
        if (ptr_len != sizeof(intptr_t))
        {
            std::string msg = std::string("Bytecode architecture is ") + int_to_string(ptr_len * 8) + std::string("-bit, using ") + int_to_string(sizeof(intptr_t) * 8);
            throw Exception(msg);
        }

        // var name map
        uint32_t nvar = 0;
        bytecode >> nvar;
        VarNameMap var_name_map;
        for (uint32_t i = 0; i < nvar; i += 1)
        {
            VarName::Id id = 0;
            VarName::Name name;
            bytecode >> id >> name;
            var_name_map.register_name(id, name);
        }

        // parse each expression
        auto e = parse_expression(bytecode, var_name_map);
        return e ? e : new ExprVoid();

        // uint32_t nexpr = 0;
        // bytecode >> nexpr;
        // std::vector<Expression*> expressions(nexpr);
        // for (uint32_t i = 0; i < nexpr; i += 1)
        // {
        //     if (auto e = parse_expression(bytecode, var_name_map))
        //     {
        //         expressions.push_back(e);
        //     }
        // }

        // return expressions;
    }

    Expression* BytecodeInterpreter::parse_expression(Bytecode& bytecode, const VarNameMap& var_name_map)
    {
        uint8_t op_code = static_cast<uint8_t>(OpCode::nop);
        bytecode >> op_code;
        switch (static_cast<OpCode>(op_code))
        {
            // debug
            case OpCode::nop:                       //< 0x00
            {
                return nullptr;
            }
            case OpCode::print:                     //< 0x01
            {
                return new ExprPrint(parse_expression(bytecode, var_name_map));
            }


            // arithmetic
            case OpCode::add:                       //< 0x10
            {
                Expression* l = parse_expression(bytecode, var_name_map);
                Expression* r = parse_expression(bytecode, var_name_map);
                return new ExprAdd(l, r);
            }
            case OpCode::sub:                       //< 0x11
            {
                Expression* l = parse_expression(bytecode, var_name_map);
                Expression* r = parse_expression(bytecode, var_name_map);
                return new ExprSub(l, r);
            }
            case OpCode::mul:                       //< 0x12
            {
                Expression* l = parse_expression(bytecode, var_name_map);
                Expression* r = parse_expression(bytecode, var_name_map);
                return new ExprMul(l, r);
            }
            case OpCode::div:                       //< 0x13
            {
                Expression* l = parse_expression(bytecode, var_name_map);
                Expression* r = parse_expression(bytecode, var_name_map);
                return new ExprDiv(l, r);
            }
            case OpCode::mod:                       //< 0x14
            {
                Expression* l = parse_expression(bytecode, var_name_map);
                Expression* r = parse_expression(bytecode, var_name_map);
                return new ExprMod(l, r);
            }
            case OpCode::exp:                       //< 0x15
            {
                Expression* l = parse_expression(bytecode, var_name_map);
                Expression* r = parse_expression(bytecode, var_name_map);
                return new ExprExp(l, r);
            }
            case OpCode::unm:                       //< 0x16
            {
                Expression* v = parse_expression(bytecode, var_name_map);
                return new ExprUnm(v);
            }


            // bitwise
            case OpCode::bit_and:                   //< 0x17
            {
                Expression* l = parse_expression(bytecode, var_name_map);
                Expression* r = parse_expression(bytecode, var_name_map);
                return new ExprBitAnd(l, r);
            }
            case OpCode::bit_or:                    //< 0x18
            {
                Expression* l = parse_expression(bytecode, var_name_map);
                Expression* r = parse_expression(bytecode, var_name_map);
                return new ExprBitOr(l, r);
            }
            case OpCode::bit_xor:                   //< 0x19
            {
                Expression* l = parse_expression(bytecode, var_name_map);
                Expression* r = parse_expression(bytecode, var_name_map);
                return new ExprBitXor(l, r);
            }
            case OpCode::bit_not:                   //< 0x1A
            {
                Expression* v = parse_expression(bytecode, var_name_map);
                return new ExprBitNot(v);
            }
            case OpCode::bit_left_shift:            //< 0x1B
            {
                Expression* l = parse_expression(bytecode, var_name_map);
                Expression* r = parse_expression(bytecode, var_name_map);
                return new ExprBitLeftShift(l, r);
            }
            case OpCode::bit_right_shift:           //< 0x1C
            {
                Expression* l = parse_expression(bytecode, var_name_map);
                Expression* r = parse_expression(bytecode, var_name_map);
                return new ExprBitRightShift(l, r);
            }


            // boolean
            case OpCode::bool_and:                  //< 0x1D
            {
                Expression* l = parse_expression(bytecode, var_name_map);
                Expression* r = parse_expression(bytecode, var_name_map);
                return new ExprBoolAnd(l, r);
            }
            case OpCode::bool_or:                   //< 0x1E
            {
                Expression* l = parse_expression(bytecode, var_name_map);
                Expression* r = parse_expression(bytecode, var_name_map);
                return new ExprBoolOr(l, r);
            }
            case OpCode::bool_xor:                  //< 0x1F
            {
                Expression* l = parse_expression(bytecode, var_name_map);
                Expression* r = parse_expression(bytecode, var_name_map);
                return new ExprBoolXor(l, r);
            }
            case OpCode::bool_not:                  //< 0x20
            {
                Expression* v = parse_expression(bytecode, var_name_map);
                return new ExprBoolNot(v);
            }


            // comparison
            case OpCode::cmp:                       //< 0x21
            {
                Expression* l = parse_expression(bytecode, var_name_map);
                Expression* r = parse_expression(bytecode, var_name_map);
                return new ExprCmp(l, r);
            }
            case OpCode::eq:                        //< 0x22
            {
                Expression* l = parse_expression(bytecode, var_name_map);
                Expression* r = parse_expression(bytecode, var_name_map);
                return new ExprEQ(l, r);
            }
            case OpCode::ne:                        //< 0x23
            {
                Expression* l = parse_expression(bytecode, var_name_map);
                Expression* r = parse_expression(bytecode, var_name_map);
                return new ExprNE(l, r);
            }
            case OpCode::lt:                        //< 0x24
            {
                Expression* l = parse_expression(bytecode, var_name_map);
                Expression* r = parse_expression(bytecode, var_name_map);
                return new ExprLT(l, r);
            }
            case OpCode::le:                        //< 0x25
            {
                Expression* l = parse_expression(bytecode, var_name_map);
                Expression* r = parse_expression(bytecode, var_name_map);
                return new ExprLE(l, r);
            }
            case OpCode::gt:                        //< 0x26
            {
                Expression* l = parse_expression(bytecode, var_name_map);
                Expression* r = parse_expression(bytecode, var_name_map);
                return new ExprGT(l, r);
            }
            case OpCode::ge:                        //< 0x27
            {
                Expression* l = parse_expression(bytecode, var_name_map);
                Expression* r = parse_expression(bytecode, var_name_map);
                return new ExprGE(l, r);
            }


            // data types
            case OpCode::data_void:                 //< 0x30
            {
                return new ExprVoid();
            }
            case OpCode::data_null:                 //< 0x31
            {
                return new ExprNull();
            }
            case OpCode::data_boolean:              //< 0x32
            {
                Boolean::Value value = false;
                bytecode >> value;
                return new ExprBoolean(value);
            }
            case OpCode::data_number:               //< 0x33
            {
                Number::Value value = 0.0f;
                bytecode >> value;
                return new ExprNumber(value);
            }
            case OpCode::data_string:               //< 0x34
            {
                String::Value value;
                bytecode >> value;
                return new ExprString(value);
            }
            case OpCode::data_identifier:           //< 0x35
            {
                VarName var_name = parse_var_name(bytecode, var_name_map);
                return new ExprIdentifier(var_name);
            }
            case OpCode::data_vector:               //< 0x36
            {
                uint32_t size = 0;
                bytecode >> size;

                std::vector<Expression*> values(size);
                for (uint32_t i = 0; i < size; i += 1)
                {
                    values[i] = parse_expression(bytecode, var_name_map);
                }

                return new ExprVector(values);
            }
            case OpCode::data_map:                  //< 0x37
            {
                uint32_t size = 0;
                bytecode >> size;

                std::vector<ExprMap::Pair> pairs;
                pairs.reserve(size);
                for (uint32_t i = 0; i < size; i += 1)
                {
                    auto key = parse_expression(bytecode, var_name_map);
                    auto value = parse_expression(bytecode, var_name_map);
                    pairs.emplace_back(key, value);
                }

                return new ExprMap(pairs);
            }
            case OpCode::data_function:             //< 0x38
            {
                uint32_t nargs = 0;
                bytecode >> nargs;

                std::vector<VarName> arg_names(nargs);
                for (uint32_t i = 0; i < nargs; i += 1)
                {
                    arg_names[i] = parse_var_name(bytecode, var_name_map);
                }

                bool variadic = false;
                bytecode >> variadic;

                Expression* body = nullptr;
                body = parse_expression(bytecode, var_name_map);

                return new ExprFunction(arg_names, variadic, body);
            }
            case OpCode::data_class:                //< 0x39
            {
                VarName class_name = parse_var_name(bytecode, var_name_map);
                Expression* super_class = parse_expression(bytecode, var_name_map);

                uint32_t nmethods = 0;
                bytecode >> nmethods;

                std::vector<ExprClass::MethodDef> method_defs;
                for (uint32_t i = 0; i < nmethods; i += 1)
                {
                    VarName id = parse_var_name(bytecode, var_name_map);

                    uint32_t narg = 0;
                    bytecode >> narg;
                    std::vector<VarName> arg_names(narg);
                    for (uint32_t iarg = 0; iarg < narg; iarg += 1)
                    {
                        arg_names[iarg] = parse_var_name(bytecode, var_name_map);
                    }

                    bool is_variadic = false;
                    bytecode >> is_variadic;

                    auto body = parse_expression(bytecode, var_name_map);

                    method_defs.emplace_back(id, arg_names, is_variadic, body);
                }

                return new ExprClass(class_name, super_class, method_defs);
            }


            // control flow
            case OpCode::control_block:             //< 0x40
            {
                uint32_t nexpr = 0;
                bytecode >> nexpr;
                std::vector<Expression*> exprs(nexpr);
                for (uint32_t i = 0; i < nexpr; i += 1)
                {
                    exprs[i] = parse_expression(bytecode, var_name_map);
                }
                return new ExprBasicBlock(exprs);
            }
            case OpCode::control_do:                //< 0x41
            {
                return new ExprDo(parse_expression(bytecode, var_name_map));
            }
            case OpCode::control_if:                //< 0x42
            {
                auto condition = parse_expression(bytecode, var_name_map);
                auto true_branch = parse_expression(bytecode, var_name_map);
                auto false_branch = parse_expression(bytecode, var_name_map);
                return new ExprIf(condition, true_branch, false_branch);
            }
            case OpCode::control_switch:            //< 0x43
            {
                auto condition = parse_expression(bytecode, var_name_map);

                uint32_t nbranch = 0;
                bytecode >> nbranch;
                std::vector<ExprSwitch::CaseBranch> branches;
                for (uint32_t i = 0; i < nbranch; i += 1)
                {
                    uint32_t nvalue = 0;
                    bytecode >> nvalue;
                    std::vector<Expression*> values(nvalue);
                    for (uint32_t ivalue = 0; ivalue < nvalue; ivalue += 1)
                    {
                        values[ivalue] = parse_expression(bytecode, var_name_map);
                    }

                    auto body = parse_expression(bytecode, var_name_map);

                    branches.emplace_back(values, body);
                }

                auto default_branch = parse_expression(bytecode, var_name_map);

                return new ExprSwitch(condition, branches, default_branch);
            }
            case OpCode::control_loop:              //< 0x44
            {
                return new ExprLoop(parse_expression(bytecode, var_name_map));
            }
            case OpCode::control_while:             //< 0x45
            {
                auto condition = parse_expression(bytecode, var_name_map);
                auto body = parse_expression(bytecode, var_name_map);
                return new ExprWhile(condition, body);
            }
            case OpCode::control_for:               //< 0x46
            {
                auto var_name = parse_var_name(bytecode, var_name_map);
                auto initial_value = parse_expression(bytecode, var_name_map);
                auto max_value = parse_expression(bytecode, var_name_map);
                auto step_value = parse_expression(bytecode, var_name_map);
                auto body = parse_expression(bytecode, var_name_map);
                return new ExprFor(var_name, initial_value, max_value, step_value, body);
            }
            case OpCode::control_for_in:            //< 0x46
            {
                auto var_name = parse_var_name(bytecode, var_name_map);
                auto range = parse_expression(bytecode, var_name_map);
                auto body = parse_expression(bytecode, var_name_map);
                return new ExprForIn(var_name, range, body);
            }
            case OpCode::control_try:               //< 0x47
            {
                auto try_body = parse_expression(bytecode, var_name_map);
                auto catch_body = parse_expression(bytecode, var_name_map);
                return new ExprTry(try_body, catch_body);
            }
            case OpCode::control_throw:             //< 0x48
            {
                return new ExprThrow(parse_expression(bytecode, var_name_map));
            }
            case OpCode::control_return:            //< 0x49
            {
                return new ExprReturn(parse_expression(bytecode, var_name_map));
            }
            case OpCode::control_break:             //< 0x4A
            {
                return new ExprBreak(parse_expression(bytecode, var_name_map));
            }


            // general
            case OpCode::call:                      //< 0x50
            {
                auto function = parse_expression(bytecode, var_name_map);

                uint32_t narg = 0;
                bytecode >> narg;
                std::vector<Expression*> args(narg);
                for (uint32_t i = 0; i < narg; i += 1)
                {
                    args[i] = parse_expression(bytecode, var_name_map);
                }

                return new ExprCall(function, args);
            }
            case OpCode::variadic_call:             //< 0x51
            {
                auto function = parse_expression(bytecode, var_name_map);

                uint32_t narg = 0;
                bytecode >> narg;
                std::vector<Expression*> args(narg);
                for (uint32_t i = 0; i < narg; i += 1)
                {
                    args[i] = parse_expression(bytecode, var_name_map);
                }

                auto vararg = parse_expression(bytecode, var_name_map);

                return new ExprVariadicCall(function, args, vararg);
            }
            case OpCode::call_method:               //< 0x52
            {
                auto object = parse_expression(bytecode, var_name_map);
//                auto index = parse_expression(bytecode, var_name_map);
                auto method_name = parse_var_name(bytecode, var_name_map);

                uint32_t narg = 0;
                bytecode >> narg;
                std::vector<Expression*> args(narg);
                for (uint32_t i = 0; i < narg; i += 1)
                {
                    args[i] = parse_expression(bytecode, var_name_map);
                }

                return new ExprCallMethod(object, method_name, args);
            }
            case OpCode::variadic_call_method:      //< 0x53
            {
                auto object = parse_expression(bytecode, var_name_map);
//                auto index = parse_expression(bytecode, var_name_map);
                auto method_name = parse_var_name(bytecode, var_name_map);

                uint32_t narg = 0;
                bytecode >> narg;
                std::vector<Expression*> args(narg);
                for (uint32_t i = 0; i < narg; i += 1)
                {
                    args[i] = parse_expression(bytecode, var_name_map);
                }

                auto vararg = parse_expression(bytecode, var_name_map);

                return new ExprVariadicCallMethod(object, method_name, args, vararg);
            }
            case OpCode::index_get:                 //< 0x54
            {
                auto array = parse_expression(bytecode, var_name_map);
                auto index = parse_expression(bytecode, var_name_map);
                return new ExprIndexGet(array, index);
            }
            case OpCode::index_set:                 //< 0x55
            {
                auto array = parse_expression(bytecode, var_name_map);
                auto index = parse_expression(bytecode, var_name_map);
                auto value = parse_expression(bytecode, var_name_map);
                return new ExprIndexSet(array, index, value);
            }
            case OpCode::attr_get:                  //< 0x56
            {
                auto object = parse_expression(bytecode, var_name_map);
                auto attr   = parse_var_name(bytecode, var_name_map);
                return new ExprAttrGet(object, attr);
            }
            case OpCode::attr_set:                  //< 0x57
            {
                auto object = parse_expression(bytecode, var_name_map);
                auto attr   = parse_var_name(bytecode, var_name_map);
                auto value  = parse_expression(bytecode, var_name_map);
                return new ExprAttrSet(object, attr, value);
            }


            // variable
            case OpCode::var_create_local:          //< 0x60
            {
                auto var_name = parse_var_name(bytecode, var_name_map);
                auto value = parse_expression(bytecode, var_name_map);
                return new ExprCreateLocal(var_name, value);
            }
            case OpCode::var_load_local:            //< 0x61
            {
                return new ExprLoadLocal(parse_var_name(bytecode, var_name_map));
            }
            case OpCode::var_store_local:           //< 0x62
            {
                auto var_name = parse_var_name(bytecode, var_name_map);
                auto value = parse_expression(bytecode, var_name_map);
                return new ExprStoreLocal(var_name, value);
            }
            case OpCode::var_create_global:         //< 0x63
            {
                auto var_name = parse_var_name(bytecode, var_name_map);
                auto value = parse_expression(bytecode, var_name_map);
                return new ExprCreateGlobal(var_name, value);
            }
            case OpCode::var_load_global:           //< 0x64
            {
                return new ExprLoadGlobal(parse_var_name(bytecode, var_name_map));
            }
            case OpCode::var_store_global:          //< 0x65
            {
                auto var_name = parse_var_name(bytecode, var_name_map);
                auto value = parse_expression(bytecode, var_name_map);
                return new ExprStoreGlobal(var_name, value);
            }


            // dynamic load
            case OpCode::dyn_func:                  //< 0x70
            {
                uint32_t argn = 0;
                bytecode >> argn;
                std::vector<VarName> arg_names(argn);
                for (uint32_t i = 0; i < argn; i += 1)
                {
                    arg_names[i] = parse_var_name(bytecode, var_name_map);
                }

                bool is_variadic = false;
                bytecode >> is_variadic;

                std::string library_path;
                bytecode >> library_path;

                std::string func_name;
                bytecode >> func_name;

                return new ExprDynFunc(arg_names, is_variadic, library_path, func_name);
            }


            // invalid
            default:
            {
                throw InvalidBytecode();
            }
        }
    }

    VarName BytecodeInterpreter::parse_var_name(Bytecode& bytecode, const VarNameMap& var_name_map)
    {
        VarName::Id local_id;
        bytecode >> local_id;

        VarName::Id global_id = var_name_map.global_from_local(local_id);
        return VarName::from_id(global_id);
    }


    InvalidBytecode::InvalidBytecode() : Exception("Invalid bytecode")
    {

    }
}
