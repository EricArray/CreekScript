#include <creek/GlobalScope.hpp>

#include <creek/CFunction.hpp>
#include <creek/Exception.hpp>
#include <creek/Identifier.hpp>
#include <creek/GarbageCollectable.hpp>
#include <creek/Map.hpp>
#include <creek/Null.hpp>
#include <creek/Object.hpp>
#include <creek/Void.hpp>
#include <creek/utility.hpp>
#include <iostream> // TODO: remove

namespace creek
{
    void GlobalScope::spread_garbage_trace()
    {
        for (auto& v : vars())
        {
            v.second->garbage_trace();
        }
    }


    // // @brief  Global class: Boolean.
    // Variable scope->global()->class_Boolean;

    // // @brief  Global class: Class.
    // Variable scope->global()->class_Class;

    // // @brief  Global class: Data.
    // Variable scope->global()->class_Data;

    // // @brief  Global class: Identifier.
    // Variable scope->global()->class_Identifier;

    // // @brief  Global class: Map.
    // Variable scope->global()->class_Map;

    // // @brief  Global class: Null.
    // Variable scope->global()->class_Null;

    // // @brief  Global class: Number.
    // Variable scope->global()->class_Number;

    // // @brief  Global class: Object.
    // Variable scope->global()->class_Object;

    // // @brief  Global class: UserData.
    // Variable scope->global()->class_UserData;

    // // @brief  Global class: String.
    // Variable scope->global()->class_String;

    // // @brief  Global class: Vector.
    // Variable scope->global()->class_Vector;

    // // @brief  Global class: Void.
    // Variable scope->global()->class_Void;


    // // @brief  `GlobalScope` instance.
    // GlobalScope GlobalScope::instance;


    // class methods; args = {self} where not specified; args = {self, other} for operations

    // class Data
    // {
        Data* func_Data_type_name(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_class_id(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_class_name(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_debug_text(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_class(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_mem_address(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_clone(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_to_boolean(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_to_number(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_to_string(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_index_get(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_index_set(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_attr_get(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_attr_set(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_add(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_sub(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_mul(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_div(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_mod(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_exp(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_unm(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_bit_and(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_bit_or(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_bit_xor(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_bit_not(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_bit_left_shift(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_bit_right_shift(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_cmp(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_call(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
    // }

    // class Object
    // {
        Data* func_Object_attrs(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {class, init_args...}
        Data* func_Object_instantiate(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_init(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_to_boolean(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_to_number(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_to_string(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_index_get(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_index_set(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_add(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_sub(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_mul(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_div(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_mod(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_exp(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_unm(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_bit_and(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_bit_or(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_bit_xor(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_bit_not(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_bit_left_shift(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_bit_right_shift(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_cmp(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_call(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_call_method(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
    // }

    // class Class
    // {
        // args = {self, id}
        Data* func_Class_derive(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, super_class, id}
        Data* func_Class_init(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, init_args...}
        Data* func_Class_new(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Class_call(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
    // }

    // class Number
    // {
        std::string func_Number_format(int number, int base);
    // }

    // class String
    // {
        // args = {self, base}
        Data* func_String_to_number(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);

        int func_String_size(std::string string);
        // args = {self, string}
        Data* func_String_push(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_String_pop(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, pos, string}
        Data* func_String_insert(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, pos, len}
        Data* func_String_erase(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, pos, len, string}
        Data* func_String_replace(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, new_size}
        Data* func_String_resize(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_String_clear(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, pos}
        Data* func_String_at(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);

        // args = {self, string, pos}
        Data* func_String_find(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, string, pos}
        Data* func_String_rfind(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, string, pos}
        Data* func_String_find_first_of(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, string, pos}
        Data* func_String_find_last_of(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, string, pos}
        Data* func_String_find_first_not_of(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, string, pos}
        Data* func_String_find_last_not_of(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, pos, len}
        Data* func_String_substr(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
    // }

    // class UserData
    // {
        // args = {self, init_args...}
        Data* func_UserData_instantiate(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
    // }

    // class Vector
    // {
        Data* func_Vector_keys(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, key}
        Data* func_Vector_has_key(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);

        Data* func_Vector_size(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, new_size, new_val}
        Data* func_Vector_resize(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);

        Data* func_Vector_at(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Vector_front(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Vector_back(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);

        // args = {self, new_val}
        Data* func_Vector_push(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Vector_pop(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, key, new_val}
        Data* func_Vector_insert(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, key}
        Data* func_Vector_erase(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Vector_clear(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
    // }

    // class Map
    // {
        Data* func_Map_keys(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, key}
        Data* func_Map_has_key(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);

        Data* func_Map_size(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);

        // args = {self, key}
        Data* func_Map_at(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);

        // args = {self, key, new_val}
        Data* func_Map_insert(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, key}
        Data* func_Map_erase(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Map_clear(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
    // }

    // class Module
    // {
        // args = {self, name}
        Data* func_Module_init(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args);
    // }


    // @brief  `GlobalScope` constructor.
    GlobalScope::GlobalScope(const SharedPointer<Shared>& sp) :
        LocalScope(
            sp,
            nullptr,
            sp,
            std::make_shared<ReturnPoint>(),
            std::make_shared<BreakPoint>()
        )
    {
        // manually created classes
        {
            std::map<VarName, Variable> attrs;

            // class Data
            {
                attrs["id"]             = new Identifier("Data");
                attrs["super_class"]    = new Null();
                attrs["mem_address"]    = new CFunction(sp, 1, false, &func_Data_mem_address);
                attrs["clone"]          = new CFunction(sp, 1, false, &func_Data_clone);
                attrs["type_name"]      = new CFunction(sp, 1, false, &func_Data_type_name);
                attrs["class"]          = new CFunction(sp, 1, false, &func_Data_class);
                attrs["class_id"]       = new CFunction(sp, 1, false, &func_Data_class_id);
                attrs["class_name"]     = new CFunction(sp, 1, false, &func_Data_class_name);
                attrs["debug_text"]     = new CFunction(sp, 1, false, &func_Data_debug_text);
                attrs["to_boolean"]     = new CFunction(sp, 1, false, &func_Data_to_boolean);
                attrs["to_number"]      = new CFunction(sp, 1, false, &func_Data_to_number);
                attrs["to_string"]      = new CFunction(sp, 1, false, &func_Data_to_string);
                attrs["index_get"]      = new CFunction(sp, 2, false, &func_Data_index_get);
                attrs["index_set"]      = new CFunction(sp, 3, false, &func_Data_index_set);
                attrs["add"]                = new CFunction(sp, 2, false, &func_Data_add);
                attrs["sub"]                = new CFunction(sp, 2, false, &func_Data_sub);
                attrs["mul"]                = new CFunction(sp, 2, false, &func_Data_mul);
                attrs["div"]                = new CFunction(sp, 2, false, &func_Data_div);
                attrs["mod"]                = new CFunction(sp, 2, false, &func_Data_mod);
                attrs["exp"]                = new CFunction(sp, 2, false, &func_Data_exp);
                attrs["unm"]                = new CFunction(sp, 1, false, &func_Data_unm);
                attrs["bit_and"]            = new CFunction(sp, 2, false, &func_Data_bit_and);
                attrs["bit_or"]             = new CFunction(sp, 2, false, &func_Data_bit_or);
                attrs["bit_xor"]            = new CFunction(sp, 2, false, &func_Data_bit_xor);
                attrs["bit_not"]            = new CFunction(sp, 1, false, &func_Data_bit_not);
                attrs["bit_left_shift"]     = new CFunction(sp, 2, false, &func_Data_bit_left_shift);
                attrs["bit_right_shift"]    = new CFunction(sp, 2, false, &func_Data_bit_right_shift);
                attrs["cmp"]                = new CFunction(sp, 2, false, &func_Data_cmp);
                attrs["call"]               = new CFunction(sp, 2, true, &func_Data_call);
                class_Data = Object::make(nullptr, attrs);
            }

            // class Object
            {
                attrs["id"]             = new Identifier("Object");
                attrs["super_class"]    = class_Data->copy();
                attrs["instantiate"]    = new CFunction(sp, 2, true,  &func_Object_instantiate);
                attrs["init"]           = new CFunction(sp, 1, false, &func_Object_init);
                attrs["attrs"]          = new CFunction(sp, 1, false, &func_Object_attrs);
                attrs["to_boolean"]     = new CFunction(sp, 1, false, &func_Object_to_boolean);
                attrs["to_number"]      = new CFunction(sp, 1, false, &func_Object_to_number);
                attrs["to_string"]      = new CFunction(sp, 1, false, &func_Object_to_string);
                attrs["index_get"]      = new CFunction(sp, 2, false, &func_Object_index_get);
                attrs["index_set"]      = new CFunction(sp, 3, false, &func_Object_index_set);
                attrs["add"]                = new CFunction(sp, 2, false, &func_Object_add);
                attrs["sub"]                = new CFunction(sp, 2, false, &func_Object_sub);
                attrs["mul"]                = new CFunction(sp, 2, false, &func_Object_mul);
                attrs["div"]                = new CFunction(sp, 2, false, &func_Object_div);
                attrs["mod"]                = new CFunction(sp, 2, false, &func_Object_mod);
                attrs["exp"]                = new CFunction(sp, 2, false, &func_Object_exp);
                attrs["unm"]                = new CFunction(sp, 1, false, &func_Object_unm);
                attrs["bit_and"]            = new CFunction(sp, 2, false, &func_Object_bit_and);
                attrs["bit_or"]             = new CFunction(sp, 2, false, &func_Object_bit_or);
                attrs["bit_xor"]            = new CFunction(sp, 2, false, &func_Object_bit_xor);
                attrs["bit_not"]            = new CFunction(sp, 1, false, &func_Object_bit_not);
                attrs["bit_left_shift"]     = new CFunction(sp, 2, false, &func_Object_bit_left_shift);
                attrs["bit_right_shift"]    = new CFunction(sp, 2, false, &func_Object_bit_right_shift);
                attrs["cmp"]                = new CFunction(sp, 2, false, &func_Object_cmp);
                attrs["call"]               = new CFunction(sp, 2, true, &func_Object_call);
                attrs["call_method"]        = new CFunction(sp, 3, true, &func_Object_call_method);
                class_Object = Object::make(nullptr, attrs);
            }

            // class Class
            {
                attrs["id"]             = new Identifier("Class");
                attrs["super_class"]    = class_Object->copy();
                attrs["derive"]         = new CFunction(sp, 2, false, &func_Class_derive);
                attrs["new"]            = new CFunction(sp, 2, true,  &func_Class_new);
                attrs["call"]           = new CFunction(sp, 2, true,  &func_Class_call);
                attrs["init"]           = new CFunction(sp, 2, false, &func_Class_init);
                class_Class = Object::make(nullptr, attrs);
            }

            static_cast<Object*>(*class_Data)->set_class(class_Class->copy());
            static_cast<Object*>(*class_Object)->set_class(class_Class->copy());
            static_cast<Object*>(*class_Class)->set_class(class_Class->copy());
        }

        // class_Boolean
        {
            std::vector< std::unique_ptr<Data> > args;
            args.emplace_back(class_Data->copy());
            args.emplace_back(new Identifier("Boolean"));
            class_Boolean = func_Class_derive(sp, args);
        }

        // class_Identifier
        {
            std::vector< std::unique_ptr<Data> > args;
            args.emplace_back(class_Data->copy());
            args.emplace_back(new Identifier("Identifier"));
            class_Identifier = func_Class_derive(sp, args);
        }

        // class_Map
        {
            std::vector< std::unique_ptr<Data> > args;
            args.emplace_back(class_Data->copy());
            args.emplace_back(new Identifier("Map"));
            class_Map = func_Class_derive(sp, args);
            class_Map.attr(sp, VarName("keys"),     new CFunction(sp, 1, false, &func_Map_keys));
            class_Map.attr(sp, VarName("has_key"),  new CFunction(sp, 2, false, &func_Map_has_key));
            class_Map.attr(sp, VarName("size"),     new CFunction(sp, 1, false, &func_Map_size));
            class_Map.attr(sp, VarName("at"),       new CFunction(sp, 2, false, &func_Map_at));
            class_Map.attr(sp, VarName("insert"),   new CFunction(sp, 3, false, &func_Map_insert));
            class_Map.attr(sp, VarName("erase"),    new CFunction(sp, 2, false, &func_Map_erase));
            class_Map.attr(sp, VarName("clear"),    new CFunction(sp, 1, false, &func_Map_clear));
        }

        // class_Null
        {
            std::vector< std::unique_ptr<Data> > args;
            args.emplace_back(class_Data->copy());
            args.emplace_back(new Identifier("Null"));
            class_Null = func_Class_derive(sp, args);
        }

        // class_Number
        {
            std::vector< std::unique_ptr<Data> > args;
            args.emplace_back(class_Data->copy());
            args.emplace_back(new Identifier("Number"));
            class_Number = func_Class_derive(sp, args);
            class_Number.attr(sp, VarName("format"), new CFunction(sp, &func_Number_format));
        }

        // class_String
        {
            std::vector< std::unique_ptr<Data> > args;
            args.emplace_back(class_Data->copy());
            args.emplace_back(new Identifier("String"));
            class_String = func_Class_derive(sp, args);
            class_String.attr(sp, VarName("to_number"), new CFunction(sp, 2, false, &func_String_to_number));

            class_String.attr(sp, VarName("size"),      new CFunction(sp, &func_String_size));

            class_String.attr(sp, VarName("push"),      new CFunction(sp, 2, false, &func_String_push));
            class_String.attr(sp, VarName("pop"),       new CFunction(sp, 1, false, &func_String_pop));
            class_String.attr(sp, VarName("insert"),    new CFunction(sp, 3, false, &func_String_insert));
            class_String.attr(sp, VarName("erase"),     new CFunction(sp, 3, false, &func_String_erase));
            class_String.attr(sp, VarName("replace"),   new CFunction(sp, 4, false, &func_String_replace));
            class_String.attr(sp, VarName("resize"),    new CFunction(sp, 2, false, &func_String_resize));
            class_String.attr(sp, VarName("clear"),     new CFunction(sp, 1, false, &func_String_clear));
            class_String.attr(sp, VarName("at"),        new CFunction(sp, 2, false, &func_String_at));

            class_String.attr(sp, VarName("find"),              new CFunction(sp, 3, false, &func_String_find));
            class_String.attr(sp, VarName("rfind"),             new CFunction(sp, 3, false, &func_String_rfind));
            class_String.attr(sp, VarName("find_first_of"),     new CFunction(sp, 3, false, &func_String_find_first_of));
            class_String.attr(sp, VarName("find_last_of"),      new CFunction(sp, 3, false, &func_String_find_last_of));
            class_String.attr(sp, VarName("find_first_not_of"), new CFunction(sp, 3, false, &func_String_find_first_not_of));
            class_String.attr(sp, VarName("find_last_not_of"),  new CFunction(sp, 3, false, &func_String_find_last_not_of));
            class_String.attr(sp, VarName("substr"),            new CFunction(sp, 3, false, &func_String_substr));
        }

        // class_UserData
        {
            std::vector< std::unique_ptr<Data> > args;
            args.emplace_back(class_Data->copy());
            args.emplace_back(new Identifier("UserData"));
            class_UserData = func_Class_derive(sp, args);
            class_UserData.attr(sp, VarName("instantiate"), new CFunction(sp, 2, true, &func_UserData_instantiate));
        }

        // class_Vector
        {
            std::vector< std::unique_ptr<Data> > args;
            args.emplace_back(class_Data->copy());
            args.emplace_back(new Identifier("Vector"));
            class_Vector = func_Class_derive(sp, args);

            class_Vector.attr(sp, VarName("keys"),      new CFunction(sp, 1, false, &func_Vector_keys));
            class_Vector.attr(sp, VarName("has_key"),   new CFunction(sp, 1, false, &func_Vector_has_key));

            class_Vector.attr(sp, VarName("size"),      new CFunction(sp, 1, false, &func_Vector_size));
            class_Vector.attr(sp, VarName("resize"),    new CFunction(sp, 3, false, &func_Vector_resize));

            class_Vector.attr(sp, VarName("at"),        new CFunction(sp, 1, false, &func_Vector_at));
            class_Vector.attr(sp, VarName("front"),     new CFunction(sp, 1, false, &func_Vector_front));
            class_Vector.attr(sp, VarName("back"),      new CFunction(sp, 1, false, &func_Vector_back));

            class_Vector.attr(sp, VarName("push"),      new CFunction(sp, 2, false, &func_Vector_push));
            class_Vector.attr(sp, VarName("pop"),       new CFunction(sp, 1, false, &func_Vector_pop));
            class_Vector.attr(sp, VarName("insert"),    new CFunction(sp, 3, false, &func_Vector_insert));
            class_Vector.attr(sp, VarName("erase"),     new CFunction(sp, 2, false, &func_Vector_erase));
            class_Vector.attr(sp, VarName("clear"),     new CFunction(sp, 1, false, &func_Vector_clear));
        }

        // class_Void
        {
            std::vector< std::unique_ptr<Data> > args;
            args.emplace_back(class_Data->copy());
            args.emplace_back(new Identifier("Void"));
            class_Void = func_Class_derive(sp, args);
        }

        // class_Module
        {
            std::vector< std::unique_ptr<Data> > args;
            args.emplace_back(class_Object->copy());
            args.emplace_back(new Identifier("Module"));
            class_Module = func_Class_derive(sp, args);
            class_Module.attr(sp, VarName("init"),   new CFunction(sp, 2, false, &func_Module_init));
        }

        create_local_var(VarName("Boolean"),    class_Boolean->copy());
        create_local_var(VarName("Class"),      class_Class->copy());
        create_local_var(VarName("Data"),       class_Data->copy());
        create_local_var(VarName("Identifier"), class_Identifier->copy());
        create_local_var(VarName("Map"),        class_Map->copy());
        create_local_var(VarName("Module"),     class_Module->copy());
        create_local_var(VarName("Null"),       class_Null->copy());
        create_local_var(VarName("Number"),     class_Number->copy());
        create_local_var(VarName("Object"),     class_Object->copy());
        create_local_var(VarName("String"),     class_String->copy());
        create_local_var(VarName("Vector"),     class_Vector->copy());
        create_local_var(VarName("Void"),       class_Void->copy());
    }



    // class Data
    // {
        Data* func_Data_type_name(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            return new String(args[0]->class_name());
        }

        Data* func_Data_class_id(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            Variable class_obj(args[0]->get_class(scope));
            return class_obj->attr(scope, VarName("id"));
        }

        Data* func_Data_class_name(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            Variable class_obj(args[0]->get_class(scope));
            Variable id(class_obj->attr(scope, VarName("id")));
            return new String(id->string_value(scope));
        }

        Data* func_Data_debug_text(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            return new String(args[0]->debug_text());
        }

        Data* func_Data_class(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            return args[0]->get_class(scope);
        }

        Data* func_Data_mem_address(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            if (Object* self = dynamic_cast<Object*>(args[0].get()))
            {
                return new Number(uintptr_t(self->value().get()));
            }
            return new Null();
        }

        Data* func_Data_clone(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            return args[0]->clone();
        }

        Data* func_Data_to_boolean(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            return new Boolean(args[0]->bool_value(scope));
        }

        Data* func_Data_to_number(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            return new Number(args[0]->double_value(scope));
        }

        Data* func_Data_to_string(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            return new String(args[0]->string_value(scope));
        }

        Data* func_Data_index_get(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            return args[0]->index(scope, args[1].get());
        }

        Data* func_Data_index_set(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            return args[0]->index(scope, args[1].get(), args[2].release());
        }

        Data* func_Data_attr_get(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            return args[0]->attr(scope, args[1]->identifier_value(scope));
        }

        Data* func_Data_attr_set(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            return args[0]->attr(scope, args[1]->identifier_value(scope), args[2].release());
        }

        Data* func_Data_add(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            return args[0]->add(scope, args[1].get());
        }

        Data* func_Data_sub(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            return args[0]->sub(scope, args[1].get());
        }

        Data* func_Data_mul(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            return args[0]->mul(scope, args[1].get());
        }

        Data* func_Data_div(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            return args[0]->div(scope, args[1].get());
        }

        Data* func_Data_mod(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            return args[0]->mod(scope, args[1].get());
        }

        Data* func_Data_exp(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            return args[0]->exp(scope, args[1].get());
        }

        Data* func_Data_unm(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            return args[0]->unm(scope);
        }

        Data* func_Data_bit_and(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            return args[0]->bit_and(scope, args[1].get());
        }

        Data* func_Data_bit_or(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            return args[0]->bit_or(scope, args[1].get());
        }

        Data* func_Data_bit_xor(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            return args[0]->bit_xor(scope, args[1].get());
        }

        Data* func_Data_bit_not(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            return args[0]->bit_not(scope);
        }

        Data* func_Data_bit_left_shift(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            return args[0]->bit_left_shift(scope, args[1].get());
        }

        Data* func_Data_bit_right_shift(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            return args[0]->bit_right_shift(scope, args[1].get());
        }

        Data* func_Data_cmp(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            return new Number(args[0]->cmp(scope, args[1].get()));
        }

        Data* func_Data_call(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            std::vector< std::unique_ptr<Data> > call_args;
            for (auto& i : args[1]->vector_value(scope))
            {
                call_args.emplace_back(i->copy());
            }
            return args[0]->call(scope, call_args);
        }
    // }


    // class Object
    // {
        // args = {class, init_args...}
        Data* func_Object_instantiate(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            Variable c(args[0].release());
            Variable instance = new Object(c->copy(), {});
            Variable func_init = c.attr(scope, VarName("init"));

            std::vector< std::unique_ptr<Data> > init_args;
            init_args.emplace_back(instance->copy());
            for (auto& i : args[1]->vector_value(scope))
            {
                init_args.emplace_back(i->copy());
            }
            delete func_init->call(scope, init_args);
            return instance.release();
        }

        Data* func_Object_init(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            return new Void();
        }

        Data* func_Object_attrs(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            if (Object* self = dynamic_cast<Object*>(args[0].get()))
            {
                Vector::Value new_value = std::make_shared< std::vector<Variable> >();
                for (auto& attr : self->value()->attrs)
                {
                    new_value->emplace_back(new Identifier(attr.first));
                }
                return new Vector(new_value);
            }
            else
            {
                return new Null();
            }
        }

        Data* func_Object_to_boolean(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            return new Boolean(true);
        }

        Data* func_Object_to_number(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            throw Undefined("Object conversion to number");
        }

        Data* func_Object_to_string(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            throw Undefined("Object conversion to string");
        }

        Data* func_Object_index_get(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            throw Undefined("Object element index_get");
        }

        Data* func_Object_index_set(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            throw Undefined("Object element index_set");
        }

        Data* func_Object_add(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            throw Undefined("Object operation add");
        }

        Data* func_Object_sub(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            throw Undefined("Object operation sub");
        }

        Data* func_Object_mul(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            throw Undefined("Object operation mul");
        }

        Data* func_Object_div(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            throw Undefined("Object operation div");
        }

        Data* func_Object_mod(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            throw Undefined("Object operation mod");
        }

        Data* func_Object_exp(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            throw Undefined("Object operation exp");
        }

        Data* func_Object_unm(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            throw Undefined("Object operation unm");
        }

        Data* func_Object_bit_and(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            throw Undefined("Object operation bit_and");
        }

        Data* func_Object_bit_or(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            throw Undefined("Object operation bit_or");
        }

        Data* func_Object_bit_xor(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            throw Undefined("Object operation bit_xor");
        }

        Data* func_Object_bit_not(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            throw Undefined("Object operation bit_not");
        }

        Data* func_Object_bit_left_shift(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            throw Undefined("Object operation bit_left_shift");
        }

        Data* func_Object_bit_right_shift(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            throw Undefined("Object operation bit_right_shift");
        }

        Data* func_Object_cmp(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            throw Undefined("Object operation cmp");
        }

        Data* func_Object_call(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            throw Undefined("Object operation call");
        }

        Data* func_Object_call_method(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            Variable self = args[0].release();

            Variable class_obj = self->get_class(scope);
            Variable method = class_obj->attr(scope, args[1]->identifier_value(scope));

            std::vector< std::unique_ptr<Data> > call_args;
            call_args.emplace_back(self->copy());
            for (auto& i : args[2]->vector_value(scope))
            {
                call_args.emplace_back(i->copy());
            }

            return method->call(scope, call_args);
        }
    // }


    // class Class
    // {
        // args = {self, id}
        Data* func_Class_derive(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            Variable c(args[0]->clone());

            std::vector< std::unique_ptr<Data> > init_args;
            init_args.emplace_back(c->copy());
            init_args.emplace_back(args[0].release());
            init_args.emplace_back(args[1].release());
            delete func_Class_init(scope, init_args);

            return c.release();
        }

        // args = {self, super_class, id}
        Data* func_Class_init(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            Variable self(args[0].release());
            self.attr(scope, VarName("super_class"),   args[1].release());
            self.attr(scope, VarName("id"),            args[2].release());
            return new Void();
        }

        // args = {self, init_args...}
        Data* func_Class_new(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            // TODO: make other static identifiers.
            static VarName vn_instantiate = VarName("instantiate");

            Variable instantiate = args[0]->attr(scope, vn_instantiate);
            std::vector< std::unique_ptr<Data> > instantiate_args;
            instantiate_args.emplace_back(args[0]->copy());
            for (auto& i : args[1]->vector_value(scope))
            {
                instantiate_args.emplace_back(i->copy());
            }
            return instantiate->call(scope, instantiate_args);
        }

        Data* func_Class_call(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            return func_Class_new(scope, args);
        }
    // }


    // class Number
    // {
        std::string func_Number_format(int number, int base)
        {
            return int_to_string(number, base);
        }
    // }


    // class String
    // {
        // args = {self, base}
        Data* func_String_to_number(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            // TODO: string to number base
            return new Number(stof<Number::Value>(args[0]->string_value(scope), nullptr));//, args[1]->int_value(scope)));
        }

        int func_String_size(std::string string)
        {
            return string.size();
        }

        // args = {self, string}
        Data* func_String_push(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto str = args[0]->assert_cast<String>();
            str->value() += args[1]->string_value(scope);
            return new Void();
        }
        Data* func_String_pop(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto str = args[0]->assert_cast<String>();
            str->value().pop_back();
            return new Void();
        }
        // args = {self, pos, string}
        Data* func_String_insert(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto str = args[0]->assert_cast<String>();
            str->value().insert(args[1]->int_value(scope), args[2]->string_value(scope));
            return new Void();
        }
        // args = {self, pos, len}
        Data* func_String_erase(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto str = args[0]->assert_cast<String>();
            str->value().erase(args[1]->int_value(scope), args[2]->int_value(scope));
            return new Void();
        }
        // args = {self, pos, len, string}
        Data* func_String_replace(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto str = args[0]->assert_cast<String>();
            str->value().replace(
                args[1]->int_value(scope),
                args[2]->int_value(scope),
                args[3]->string_value(scope)
            );
            return new Void();
        }
        // args = {self, new_size}
        Data* func_String_resize(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto str = args[0]->assert_cast<String>();
            str->value().resize(args[1]->int_value(scope));
            return new Void();
        }
        Data* func_String_clear(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto str = args[0]->assert_cast<String>();
            str->value().clear();
            return new Void();
        }
        // args = {self, pos}
        Data* func_String_at(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto str = args[0]->assert_cast<String>();
            return new String(std::string(1, str->value().at(args[1]->int_value(scope))));
        }

        // args = {self, string, pos}
        Data* func_String_find(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto str = args[0]->assert_cast<String>();
            auto r = str->value().find(args[1]->string_value(scope), args[2]->int_value(scope));
            return new Number(r == std::string::npos ? -1.0f : r);
        }
        // args = {self, string, pos}
        Data* func_String_rfind(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto str = args[0]->assert_cast<String>();
            auto r = str->value().rfind(args[1]->string_value(scope), args[2]->int_value(scope));
            return new Number(r == std::string::npos ? -1.0 : r);
        }
        // args = {self, string, pos}
        Data* func_String_find_first_of(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto str = args[0]->assert_cast<String>();
            auto r = str->value().find_first_of(args[1]->string_value(scope), args[2]->int_value(scope));
            return new Number(r == std::string::npos ? -1.0 : r);
        }
        // args = {self, string, pos}
        Data* func_String_find_last_of(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto str = args[0]->assert_cast<String>();
            auto r = str->value().find_last_of(args[1]->string_value(scope), args[2]->int_value(scope));
            return new Number(r == std::string::npos ? -1.0 : r);
        }
        // args = {self, string, pos}
        Data* func_String_find_first_not_of(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto str = args[0]->assert_cast<String>();
            auto r = str->value().find_first_not_of(args[1]->string_value(scope), args[2]->int_value(scope));
            return new Number(r == std::string::npos ? -1.0 : r);
        }
        // args = {self, string, pos}
        Data* func_String_find_last_not_of(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto str = args[0]->assert_cast<String>();
            auto r = str->value().find_last_not_of(args[1]->string_value(scope), args[2]->int_value(scope));
            return new Number(r == std::string::npos ? -1.0 : r);
        }
        // args = {self, pos, len}
        Data* func_String_substr(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto str = args[0]->assert_cast<String>();
            auto r = str->value().substr(args[1]->int_value(scope), args[2]->int_value(scope));
            return new String(r);
        }
    // }


    // class UserData
    // {
        // args = {self, init_args...}
        Data* func_UserData_instantiate(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            Variable func_new = args[0]->attr(scope, VarName("new"));
            std::vector< std::unique_ptr<Data> > init_args;
            for (auto& i : args[1]->vector_value(scope))
            {
                init_args.emplace_back(i->copy());
            }
            return func_new->call(scope, init_args);
        }
    // }


    // class Vector
    // {
        Data* func_Vector_keys(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto vec = args[0]->assert_cast<Vector>();
            Vector::Value value = std::make_shared< std::vector<Variable> >();

            size_t size = vec->value()->size();
            for (size_t i = 0; i < size; ++i)
            {
                value->push_back(new Number(i));
            }

            return new Vector(value);
        }

        // args = {self, key}
        Data* func_Vector_has_key(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto vec = args[0]->assert_cast<Vector>();
            return new Boolean(args[1]->int_value(scope) < vec->value()->size());
        }

        Data* func_Vector_size(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto vec = args[0]->assert_cast<Vector>();
            return new Number(vec->value()->size());
        }

        // args = {self, new_size, new_val}
        Data* func_Vector_resize(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto vec = args[0]->assert_cast<Vector>();
            vec->value()->resize(args[1]->int_value(scope));
            return new Void();
        }

        Data* func_Vector_push(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto vec = args[0]->assert_cast<Vector>();
            vec->value()->emplace_back(args[1].release());
            return new Void();
        }

        Data* func_Vector_pop(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto vec = args[0]->assert_cast<Vector>();
            vec->value()->pop_back();
            return new Void();
        }

        Data* func_Vector_at(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto vec = args[0]->assert_cast<Vector>();
            return vec->value()->at(args[1]->int_value(scope))->copy();
        }

        Data* func_Vector_front(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto vec = args[0]->assert_cast<Vector>();
            return vec->value()->front()->copy();
        }

        Data* func_Vector_back(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto vec = args[0]->assert_cast<Vector>();
            return vec->value()->back()->copy();
        }

        // args = {self, key, new_val}
        Data* func_Vector_insert(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto vec = args[0]->assert_cast<Vector>();
            auto iter = vec->value()->begin() + args[1]->int_value(scope);
            vec->value()->insert(iter, args[2].release());
            return new Void();
        }

        // args = {self, key}
        Data* func_Vector_erase(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto vec = args[0]->assert_cast<Vector>();
            auto iter = vec->value()->begin() + args[1]->int_value(scope);
            vec->value()->erase(iter);
            return new Void();
        }

        Data* func_Vector_clear(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto vec = args[0]->assert_cast<Vector>();
            vec->value()->clear();
            return new Void();
        }
    // }


    // class Map
    // {
        Data* func_Map_keys(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto map = args[0]->assert_cast<Map>();
            Vector::Value value = std::make_shared< std::vector<Variable> >();

            value->reserve(map->value()->size());
            for (auto& pair : *map->value())
            {
                value->emplace_back(pair.first->copy());
            }

            return new Vector(value);
        }

        // args = {self, key}
        Data* func_Map_has_key(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto map = args[0]->assert_cast<Map>();
            return new Boolean(map->value()->count(Map::Key(scope, args[1].release())) >= 1);
        }

        Data* func_Map_size(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto map = args[0]->assert_cast<Map>();
            return new Number(map->value()->size());
        }

        // args = {self, key}
        Data* func_Map_at(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto map = args[0]->assert_cast<Map>();
            return map->value()->at(Map::Key(scope, args[1].release()))->copy();
        }

        // args = {self, key, new_val}
        Data* func_Map_insert(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto map = args[0]->assert_cast<Map>();
            auto r = map->value()->insert(std::make_pair(
                Map::Key(scope, args[1].release()),
                Variable(args[2].release())
            ));
            return new Boolean(r.second);
        }

        // args = {self, key}
        Data* func_Map_erase(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto map = args[0]->assert_cast<Map>();
            auto r = map->value()->erase(Map::Key(scope, args[1].release()));
            return new Number(r);
        }

        Data* func_Map_clear(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            auto map = args[0]->assert_cast<Map>();
            map->value()->clear();
            return new Void();
        }
    // }


    // class Module
    // {
        // args = {self, name}
        Data* func_Module_init(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
        {
            args[0]->attr(scope, VarName("name"), args[1].release());
        }
    // }
}
