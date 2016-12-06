#include <creek/GlobalScope.hpp>

#include <creek/CFunction.hpp>
#include <creek/Exception.hpp>
#include <creek/Identifier.hpp>
#include <creek/Map.hpp>
#include <creek/Null.hpp>
#include <creek/Object.hpp>
#include <creek/Void.hpp>
#include <creek/utility.hpp>
#include <iostream> // TODO: remove

namespace creek
{
    // @brief  Global class: Boolean.
    Variable GlobalScope::class_Boolean;

    // @brief  Global class: Class.
    Variable GlobalScope::class_Class;

    // @brief  Global class: Data.
    Variable GlobalScope::class_Data;

    // @brief  Global class: Identifier.
    Variable GlobalScope::class_Identifier;

    // @brief  Global class: Map.
    Variable GlobalScope::class_Map;

    // @brief  Global class: Null.
    Variable GlobalScope::class_Null;

    // @brief  Global class: Number.
    Variable GlobalScope::class_Number;

    // @brief  Global class: Object.
    Variable GlobalScope::class_Object;

    // @brief  Global class: UserData.
    Variable GlobalScope::class_UserData;

    // @brief  Global class: String.
    Variable GlobalScope::class_String;

    // @brief  Global class: Vector.
    Variable GlobalScope::class_Vector;

    // @brief  Global class: Void.
    Variable GlobalScope::class_Void;


    // @brief  `GlobalScope` instance.
    GlobalScope GlobalScope::instance;


    // class methods; args = {self} where not specified; args = {self, other} for operations

    // class Data
    // {
        Data* func_Data_type_name(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_class_id(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_class_name(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_debug_text(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_get_class(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_mem_address(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_clone(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_to_boolean(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_to_number(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_to_string(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_index_get(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_index_set(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_attr_get(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_attr_set(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_add(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_sub(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_mul(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_div(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_mod(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_exp(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_unm(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_bit_and(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_bit_or(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_bit_xor(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_bit_not(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_bit_left_shift(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_bit_right_shift(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_cmp(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Data_call(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
    // }

    // class Object
    // {
        Data* func_Object_attrs(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {class, init_args...}
        Data* func_Object_instantiate(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_init(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_to_boolean(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_to_number(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_to_string(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_index_get(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_index_set(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_add(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_sub(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_mul(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_div(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_mod(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_exp(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_unm(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_bit_and(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_bit_or(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_bit_xor(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_bit_not(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_bit_left_shift(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_bit_right_shift(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_cmp(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_call(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Object_call_method(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
    // }

    // class Class
    // {
        // args = {self, id}
        Data* func_Class_derive(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, super_class, id}
        Data* func_Class_init(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, init_args...}
        Data* func_Class_new(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Class_call(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
    // }

    // class Number
    // {
        std::string func_Number_format(int number, int base);
    // }

    // class String
    // {
        // args = {self, base}
        Data* func_String_to_number(Scope& scope, std::vector< std::unique_ptr<Data> >& args);

        int func_String_size(std::string string);
        // args = {self, string}
        Data* func_String_push(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_String_pop(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, pos, string}
        Data* func_String_insert(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, pos, len}
        Data* func_String_erase(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, pos, len, string}
        Data* func_String_replace(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, new_size}
        Data* func_String_resize(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_String_clear(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, pos}
        Data* func_String_at(Scope& scope, std::vector< std::unique_ptr<Data> >& args);

        // args = {self, string, pos}
        Data* func_String_find(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, string, pos}
        Data* func_String_rfind(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, string, pos}
        Data* func_String_find_first_of(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, string, pos}
        Data* func_String_find_last_of(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, string, pos}
        Data* func_String_find_first_not_of(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, string, pos}
        Data* func_String_find_last_not_of(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, pos, len}
        Data* func_String_substr(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
    // }

    // class UserData
    // {
        // args = {self, init_args...}
        Data* func_UserData_instantiate(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
    // }

    // class Vector
    // {
        Data* func_Vector_keys(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, key}
        Data* func_Vector_has_key(Scope& scope, std::vector< std::unique_ptr<Data> >& args);

        Data* func_Vector_size(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, new_size, new_val}
        Data* func_Vector_resize(Scope& scope, std::vector< std::unique_ptr<Data> >& args);

        Data* func_Vector_at(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Vector_front(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Vector_back(Scope& scope, std::vector< std::unique_ptr<Data> >& args);

        // args = {self, new_val}
        Data* func_Vector_push(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Vector_pop(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, key, new_val}
        Data* func_Vector_insert(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, key}
        Data* func_Vector_erase(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Vector_clear(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
    // }

    // class Map
    // {
        Data* func_Map_keys(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, key}
        Data* func_Map_has_key(Scope& scope, std::vector< std::unique_ptr<Data> >& args);

        Data* func_Map_size(Scope& scope, std::vector< std::unique_ptr<Data> >& args);

        // args = {self, key}
        Data* func_Map_at(Scope& scope, std::vector< std::unique_ptr<Data> >& args);

        // args = {self, key, new_val}
        Data* func_Map_insert(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        // args = {self, key}
        Data* func_Map_erase(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
        Data* func_Map_clear(Scope& scope, std::vector< std::unique_ptr<Data> >& args);
    // }


    // @brief  `GlobalScope` constructor.
    GlobalScope::GlobalScope()
    {
        // manually created classes
        {
            std::map<VarName, Variable> attrs;

            // class Data
            {
                attrs["id"]             = new Identifier("Data");
                attrs["super_class"]    = new Null();
                attrs["mem_address"]    = new CFunction(*this, 1, false, &func_Data_mem_address);
                attrs["clone"]          = new CFunction(*this, 1, false, &func_Data_clone);
                attrs["type_name"]      = new CFunction(*this, 1, false, &func_Data_type_name);
                attrs["get_class"]      = new CFunction(*this, 1, false, &func_Data_get_class);
                attrs["class_id"]       = new CFunction(*this, 1, false, &func_Data_class_id);
                attrs["class_name"]     = new CFunction(*this, 1, false, &func_Data_class_name);
                attrs["debug_text"]     = new CFunction(*this, 1, false, &func_Data_debug_text);
                attrs["to_boolean"]     = new CFunction(*this, 1, false, &func_Data_to_boolean);
                attrs["to_number"]      = new CFunction(*this, 1, false, &func_Data_to_number);
                attrs["to_string"]      = new CFunction(*this, 1, false, &func_Data_to_string);
                attrs["index_get"]      = new CFunction(*this, 2, false, &func_Data_index_get);
                attrs["index_set"]      = new CFunction(*this, 3, false, &func_Data_index_set);
                attrs["add"]                = new CFunction(*this, 2, false, &func_Data_add);
                attrs["sub"]                = new CFunction(*this, 2, false, &func_Data_sub);
                attrs["mul"]                = new CFunction(*this, 2, false, &func_Data_mul);
                attrs["div"]                = new CFunction(*this, 2, false, &func_Data_div);
                attrs["mod"]                = new CFunction(*this, 2, false, &func_Data_mod);
                attrs["exp"]                = new CFunction(*this, 2, false, &func_Data_exp);
                attrs["unm"]                = new CFunction(*this, 1, false, &func_Data_unm);
                attrs["bit_and"]            = new CFunction(*this, 2, false, &func_Data_bit_and);
                attrs["bit_or"]             = new CFunction(*this, 2, false, &func_Data_bit_or);
                attrs["bit_xor"]            = new CFunction(*this, 2, false, &func_Data_bit_xor);
                attrs["bit_not"]            = new CFunction(*this, 1, false, &func_Data_bit_not);
                attrs["bit_left_shift"]     = new CFunction(*this, 2, false, &func_Data_bit_left_shift);
                attrs["bit_right_shift"]    = new CFunction(*this, 2, false, &func_Data_bit_right_shift);
                attrs["cmp"]                = new CFunction(*this, 2, false, &func_Data_cmp);
                attrs["call"]               = new CFunction(*this, 2, true, &func_Data_call);
                class_Data = Object::make(nullptr, attrs);
            }

            // class Object
            {
                attrs["id"]             = new Identifier("Object");
                attrs["super_class"]    = class_Data->copy();
                attrs["instantiate"]    = new CFunction(*this, 2, true,  &func_Object_instantiate);
                attrs["init"]           = new CFunction(*this, 1, false, &func_Object_init);
                attrs["attrs"]          = new CFunction(*this, 1, false, &func_Object_attrs);
                attrs["to_boolean"]     = new CFunction(*this, 1, false, &func_Object_to_boolean);
                attrs["to_number"]      = new CFunction(*this, 1, false, &func_Object_to_number);
                attrs["to_string"]      = new CFunction(*this, 1, false, &func_Object_to_string);
                attrs["index_get"]      = new CFunction(*this, 2, false, &func_Object_index_get);
                attrs["index_set"]      = new CFunction(*this, 3, false, &func_Object_index_set);
                attrs["add"]                = new CFunction(*this, 2, false, &func_Object_add);
                attrs["sub"]                = new CFunction(*this, 2, false, &func_Object_sub);
                attrs["mul"]                = new CFunction(*this, 2, false, &func_Object_mul);
                attrs["div"]                = new CFunction(*this, 2, false, &func_Object_div);
                attrs["mod"]                = new CFunction(*this, 2, false, &func_Object_mod);
                attrs["exp"]                = new CFunction(*this, 2, false, &func_Object_exp);
                attrs["unm"]                = new CFunction(*this, 1, false, &func_Object_unm);
                attrs["bit_and"]            = new CFunction(*this, 2, false, &func_Object_bit_and);
                attrs["bit_or"]             = new CFunction(*this, 2, false, &func_Object_bit_or);
                attrs["bit_xor"]            = new CFunction(*this, 2, false, &func_Object_bit_xor);
                attrs["bit_not"]            = new CFunction(*this, 1, false, &func_Object_bit_not);
                attrs["bit_left_shift"]     = new CFunction(*this, 2, false, &func_Object_bit_left_shift);
                attrs["bit_right_shift"]    = new CFunction(*this, 2, false, &func_Object_bit_right_shift);
                attrs["cmp"]                = new CFunction(*this, 2, false, &func_Object_cmp);
                attrs["call"]               = new CFunction(*this, 2, true, &func_Object_call);
                attrs["call_method"]        = new CFunction(*this, 3, true, &func_Object_call_method);
                class_Object = Object::make(nullptr, attrs);
            }

            // class Class
            {
                attrs["id"]             = new Identifier("Class");
                attrs["super_class"]    = class_Object->copy();
                attrs["derive"]         = new CFunction(*this, 2, false, &func_Class_derive);
                attrs["new"]            = new CFunction(*this, 2, true,  &func_Class_new);
                attrs["call"]           = new CFunction(*this, 2, true,  &func_Class_call);
                attrs["init"]           = new CFunction(*this, 2, false, &func_Class_init);
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
            class_Boolean = func_Class_derive(*this, args);
        }

        // class_Identifier
        {
            std::vector< std::unique_ptr<Data> > args;
            args.emplace_back(class_Data->copy());
            args.emplace_back(new Identifier("Identifier"));
            class_Identifier = func_Class_derive(*this, args);
        }

        // class_Map
        {
            std::vector< std::unique_ptr<Data> > args;
            args.emplace_back(class_Data->copy());
            args.emplace_back(new Identifier("Map"));
            class_Map = func_Class_derive(*this, args);
            class_Map.attr(VarName("keys"),     new CFunction(*this, 1, false, &func_Map_keys));
            class_Map.attr(VarName("has_key"),  new CFunction(*this, 2, false, &func_Map_has_key));
            class_Map.attr(VarName("size"),     new CFunction(*this, 1, false, &func_Map_size));
            class_Map.attr(VarName("at"),       new CFunction(*this, 2, false, &func_Map_at));
            class_Map.attr(VarName("insert"),   new CFunction(*this, 3, false, &func_Map_insert));
            class_Map.attr(VarName("erase"),    new CFunction(*this, 2, false, &func_Map_erase));
            class_Map.attr(VarName("clear"),    new CFunction(*this, 1, false, &func_Map_clear));
        }

        // class_Null
        {
            std::vector< std::unique_ptr<Data> > args;
            args.emplace_back(class_Data->copy());
            args.emplace_back(new Identifier("Null"));
            class_Null = func_Class_derive(*this, args);
        }

        // class_Number
        {
            std::vector< std::unique_ptr<Data> > args;
            args.emplace_back(class_Data->copy());
            args.emplace_back(new Identifier("Number"));
            class_Number = func_Class_derive(*this, args);
            class_Number.attr(VarName("format"), new CFunction(*this, &func_Number_format));
        }

        // class_String
        {
            std::vector< std::unique_ptr<Data> > args;
            args.emplace_back(class_Data->copy());
            args.emplace_back(new Identifier("String"));
            class_String = func_Class_derive(*this, args);
            class_String.attr(VarName("to_number"), new CFunction(*this, 2, false, &func_String_to_number));

            class_String.attr(VarName("size"),      new CFunction(*this, &func_String_size));

            class_String.attr(VarName("push"),      new CFunction(*this, 2, false, &func_String_push));
            class_String.attr(VarName("pop"),       new CFunction(*this, 1, false, &func_String_pop));
            class_String.attr(VarName("insert"),    new CFunction(*this, 3, false, &func_String_insert));
            class_String.attr(VarName("erase"),     new CFunction(*this, 3, false, &func_String_erase));
            class_String.attr(VarName("replace"),   new CFunction(*this, 4, false, &func_String_replace));
            class_String.attr(VarName("resize"),    new CFunction(*this, 2, false, &func_String_resize));
            class_String.attr(VarName("clear"),     new CFunction(*this, 1, false, &func_String_clear));
            class_String.attr(VarName("at"),        new CFunction(*this, 2, false, &func_String_at));

            class_String.attr(VarName("find"),              new CFunction(*this, 3, false, &func_String_find));
            class_String.attr(VarName("rfind"),             new CFunction(*this, 3, false, &func_String_rfind));
            class_String.attr(VarName("find_first_of"),     new CFunction(*this, 3, false, &func_String_find_first_of));
            class_String.attr(VarName("find_last_of"),      new CFunction(*this, 3, false, &func_String_find_last_of));
            class_String.attr(VarName("find_first_not_of"), new CFunction(*this, 3, false, &func_String_find_first_not_of));
            class_String.attr(VarName("find_last_not_of"),  new CFunction(*this, 3, false, &func_String_find_last_not_of));
            class_String.attr(VarName("substr"),            new CFunction(*this, 3, false, &func_String_substr));
        }

        // class_UserData
        {
            std::vector< std::unique_ptr<Data> > args;
            args.emplace_back(class_Data->copy());
            args.emplace_back(new Identifier("UserData"));
            class_UserData = func_Class_derive(*this, args);
            class_UserData.attr(VarName("instantiate"), new CFunction(*this, 2, true, &func_UserData_instantiate));
        }

        // class_Vector
        {
            std::vector< std::unique_ptr<Data> > args;
            args.emplace_back(class_Data->copy());
            args.emplace_back(new Identifier("Vector"));
            class_Vector = func_Class_derive(*this, args);

            class_Vector.attr(VarName("keys"),      new CFunction(*this, 1, false, &func_Vector_keys));
            class_Vector.attr(VarName("has_key"),   new CFunction(*this, 1, false, &func_Vector_has_key));

            class_Vector.attr(VarName("size"),      new CFunction(*this, 1, false, &func_Vector_size));
            class_Vector.attr(VarName("resize"),    new CFunction(*this, 3, false, &func_Vector_resize));

            class_Vector.attr(VarName("at"),        new CFunction(*this, 1, false, &func_Vector_at));
            class_Vector.attr(VarName("front"),     new CFunction(*this, 1, false, &func_Vector_front));
            class_Vector.attr(VarName("back"),      new CFunction(*this, 1, false, &func_Vector_back));

            class_Vector.attr(VarName("push"),      new CFunction(*this, 2, false, &func_Vector_push));
            class_Vector.attr(VarName("pop"),       new CFunction(*this, 1, false, &func_Vector_pop));
            class_Vector.attr(VarName("insert"),    new CFunction(*this, 3, false, &func_Vector_insert));
            class_Vector.attr(VarName("erase"),     new CFunction(*this, 2, false, &func_Vector_erase));
            class_Vector.attr(VarName("clear"),     new CFunction(*this, 1, false, &func_Vector_clear));
        }

        // class_Void
        {
            std::vector< std::unique_ptr<Data> > args;
            args.emplace_back(class_Data->copy());
            args.emplace_back(new Identifier("Void"));
            class_Void = func_Class_derive(*this, args);
        }

        create_local_var(VarName("Boolean"),    class_Boolean->copy());
        create_local_var(VarName("Class"),      class_Class->copy());
        create_local_var(VarName("Data"),       class_Data->copy());
        create_local_var(VarName("Identifier"), class_Identifier->copy());
        create_local_var(VarName("Map"),        class_Map->copy());
        create_local_var(VarName("Null"),       class_Null->copy());
        create_local_var(VarName("Number"),     class_Number->copy());
        create_local_var(VarName("Object"),     class_Object->copy());
        create_local_var(VarName("String"),     class_String->copy());
        create_local_var(VarName("Vector"),     class_Vector->copy());
        create_local_var(VarName("Void"),       class_Void->copy());
    }



    // class Data
    // {
    Data* func_Data_type_name(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        return new String(args[0]->class_name());
    }

    Data* func_Data_class_id(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        Variable class_obj(args[0]->get_class());
        return class_obj->attr(VarName("id"));
    }

    Data* func_Data_class_name(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        Variable class_obj(args[0]->get_class());
        Variable id(class_obj->attr(VarName("id")));
        return new String(id->string_value());
    }

    Data* func_Data_debug_text(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        return new String(args[0]->debug_text());
    }

    Data* func_Data_get_class(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        return args[0]->get_class();
    }

    Data* func_Data_mem_address(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        if (Object* self = dynamic_cast<Object*>(args[0].get()))
        {
            return new Number(uintptr_t(self->value().get()));
        }
        return new Null();
    }

    Data* func_Data_clone(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        return args[0]->clone();
    }

    Data* func_Data_to_boolean(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        return new Boolean(args[0]->bool_value());
    }

    Data* func_Data_to_number(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        return new Number(args[0]->double_value());
    }

    Data* func_Data_to_string(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        return new String(args[0]->string_value());
    }

    Data* func_Data_index_get(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        return args[0]->index(args[1].get());
    }

    Data* func_Data_index_set(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        return args[0]->index(args[1].get(), args[2].release());
    }

    Data* func_Data_attr_get(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        return args[0]->attr(args[1]->identifier_value());
    }

    Data* func_Data_attr_set(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        return args[0]->attr(args[1]->identifier_value(), args[2].release());
    }

    Data* func_Data_add(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        return args[0]->add(args[1].get());
    }

    Data* func_Data_sub(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        return args[0]->sub(args[1].get());
    }

    Data* func_Data_mul(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        return args[0]->mul(args[1].get());
    }

    Data* func_Data_div(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        return args[0]->div(args[1].get());
    }

    Data* func_Data_mod(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        return args[0]->mod(args[1].get());
    }

    Data* func_Data_exp(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        return args[0]->exp(args[1].get());
    }

    Data* func_Data_unm(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        return args[0]->unm();
    }

    Data* func_Data_bit_and(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        return args[0]->bit_and(args[1].get());
    }

    Data* func_Data_bit_or(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        return args[0]->bit_or(args[1].get());
    }

    Data* func_Data_bit_xor(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        return args[0]->bit_xor(args[1].get());
    }

    Data* func_Data_bit_not(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        return args[0]->bit_not();
    }

    Data* func_Data_bit_left_shift(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        return args[0]->bit_left_shift(args[1].get());
    }

    Data* func_Data_bit_right_shift(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        return args[0]->bit_right_shift(args[1].get());
    }

    Data* func_Data_cmp(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        return new Number(args[0]->cmp(args[1].get()));
    }

    Data* func_Data_call(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        std::vector< std::unique_ptr<Data> > call_args;
        for (auto& i : args[1]->vector_value())
        {
            call_args.emplace_back(i->copy());
        }
        return args[0]->call(call_args);
    }

    // }


    // class Object
    // {
    // args = {class, init_args...}
    Data* func_Object_instantiate(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        Variable c(args[0].release());
        Variable instance = new Object(c->copy(), {});
        Variable func_init = c.attr(VarName("init"));

        std::vector< std::unique_ptr<Data> > init_args;
        init_args.emplace_back(instance->copy());
        for (auto& i : args[1]->vector_value())
        {
            init_args.emplace_back(i->copy());
        }
        delete func_init->call(init_args);
        return instance.release();
    }

    Data* func_Object_init(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        return new Void();
    }

    Data* func_Object_attrs(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
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

    Data* func_Object_to_boolean(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        return new Boolean(true);
    }

    Data* func_Object_to_number(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        throw Undefined("Object conversion to number");
    }

    Data* func_Object_to_string(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        throw Undefined("Object conversion to string");
    }

    Data* func_Object_index_get(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        throw Undefined("Object element index_get");
    }

    Data* func_Object_index_set(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        throw Undefined("Object element index_set");
    }

    Data* func_Object_add(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        throw Undefined("Object operation add");
    }

    Data* func_Object_sub(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        throw Undefined("Object operation sub");
    }

    Data* func_Object_mul(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        throw Undefined("Object operation mul");
    }

    Data* func_Object_div(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        throw Undefined("Object operation div");
    }

    Data* func_Object_mod(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        throw Undefined("Object operation mod");
    }

    Data* func_Object_exp(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        throw Undefined("Object operation exp");
    }

    Data* func_Object_unm(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        throw Undefined("Object operation unm");
    }

    Data* func_Object_bit_and(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        throw Undefined("Object operation bit_and");
    }

    Data* func_Object_bit_or(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        throw Undefined("Object operation bit_or");
    }

    Data* func_Object_bit_xor(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        throw Undefined("Object operation bit_xor");
    }

    Data* func_Object_bit_not(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        throw Undefined("Object operation bit_not");
    }

    Data* func_Object_bit_left_shift(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        throw Undefined("Object operation bit_left_shift");
    }

    Data* func_Object_bit_right_shift(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        throw Undefined("Object operation bit_right_shift");
    }

    Data* func_Object_cmp(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        throw Undefined("Object operation cmp");
    }

    Data* func_Object_call(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        throw Undefined("Object operation call");
    }

    Data* func_Object_call_method(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        Variable self = args[0].release();

        Variable class_obj = self->get_class();
        Variable method = class_obj->attr(args[1]->identifier_value());

        std::vector< std::unique_ptr<Data> > call_args;
        call_args.emplace_back(self->copy());
        for (auto& i : args[2]->vector_value())
        {
            call_args.emplace_back(i->copy());
        }

        return method->call(call_args);
    }
    // }


    // class Class
    // {
    // args = {self, id}
    Data* func_Class_derive(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
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
    Data* func_Class_init(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        Variable self(args[0].release());
        self.attr(VarName("super_class"),   args[1].release());
        self.attr(VarName("id"),            args[2].release());
        return new Void();
    }

    // args = {self, init_args...}
    Data* func_Class_new(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        // TODO: make other static identifiers.
        static VarName vn_instantiate = VarName("instantiate");

        Variable instantiate = args[0]->attr(vn_instantiate);
        std::vector< std::unique_ptr<Data> > instantiate_args;
        instantiate_args.emplace_back(args[0]->copy());
        for (auto& i : args[1]->vector_value())
        {
            instantiate_args.emplace_back(i->copy());
        }
        return instantiate->call(instantiate_args);
    }

    Data* func_Class_call(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
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
    Data* func_String_to_number(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        // TODO: string to number base
        return new Number(stof<Number::Value>(args[0]->string_value(), nullptr));//, args[1]->int_value()));
    }

    int func_String_size(std::string string)
    {
        return string.size();
    }

    // args = {self, string}
    Data* func_String_push(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto str = args[0]->assert_cast<String>();
        str->value() += args[1]->string_value();
        return new Void();
    }
    Data* func_String_pop(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto str = args[0]->assert_cast<String>();
        str->value().pop_back();
        return new Void();
    }
    // args = {self, pos, string}
    Data* func_String_insert(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto str = args[0]->assert_cast<String>();
        str->value().insert(args[1]->int_value(), args[2]->string_value());
        return new Void();
    }
    // args = {self, pos, len}
    Data* func_String_erase(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto str = args[0]->assert_cast<String>();
        str->value().erase(args[1]->int_value(), args[2]->int_value());
        return new Void();
    }
    // args = {self, pos, len, string}
    Data* func_String_replace(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto str = args[0]->assert_cast<String>();
        str->value().replace(
            args[1]->int_value(),
            args[2]->int_value(),
            args[3]->string_value()
        );
        return new Void();
    }
    // args = {self, new_size}
    Data* func_String_resize(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto str = args[0]->assert_cast<String>();
        str->value().resize(args[1]->int_value());
        return new Void();
    }
    Data* func_String_clear(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto str = args[0]->assert_cast<String>();
        str->value().clear();
        return new Void();
    }
    // args = {self, pos}
    Data* func_String_at(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto str = args[0]->assert_cast<String>();
        return new String(std::string(1, str->value().at(args[1]->int_value())));
    }

    // args = {self, string, pos}
    Data* func_String_find(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto str = args[0]->assert_cast<String>();
        auto r = str->value().find(args[1]->string_value(), args[2]->int_value());
        return new Number(r == std::string::npos ? -1.0f : r);
    }
    // args = {self, string, pos}
    Data* func_String_rfind(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto str = args[0]->assert_cast<String>();
        auto r = str->value().rfind(args[1]->string_value(), args[2]->int_value());
        return new Number(r == std::string::npos ? -1.0 : r);
    }
    // args = {self, string, pos}
    Data* func_String_find_first_of(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto str = args[0]->assert_cast<String>();
        auto r = str->value().find_first_of(args[1]->string_value(), args[2]->int_value());
        return new Number(r == std::string::npos ? -1.0 : r);
    }
    // args = {self, string, pos}
    Data* func_String_find_last_of(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto str = args[0]->assert_cast<String>();
        auto r = str->value().find_last_of(args[1]->string_value(), args[2]->int_value());
        return new Number(r == std::string::npos ? -1.0 : r);
    }
    // args = {self, string, pos}
    Data* func_String_find_first_not_of(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto str = args[0]->assert_cast<String>();
        auto r = str->value().find_first_not_of(args[1]->string_value(), args[2]->int_value());
        return new Number(r == std::string::npos ? -1.0 : r);
    }
    // args = {self, string, pos}
    Data* func_String_find_last_not_of(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto str = args[0]->assert_cast<String>();
        auto r = str->value().find_last_not_of(args[1]->string_value(), args[2]->int_value());
        return new Number(r == std::string::npos ? -1.0 : r);
    }
    // args = {self, pos, len}
    Data* func_String_substr(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto str = args[0]->assert_cast<String>();
        auto r = str->value().substr(args[1]->int_value(), args[2]->int_value());
        return new String(r);
    }
    // }


    // class UserData
    // {
    // args = {self, init_args...}
    Data* func_UserData_instantiate(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        Variable func_new = args[0]->attr(VarName("new"));
        std::vector< std::unique_ptr<Data> > init_args;
        for (auto& i : args[1]->vector_value())
        {
            init_args.emplace_back(i->copy());
        }
        return func_new->call(init_args);
    }
    // }


    // class Vector
    // {
    Data* func_Vector_keys(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
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
    Data* func_Vector_has_key(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto vec = args[0]->assert_cast<Vector>();
        return new Boolean(args[1]->int_value() < vec->value()->size());
    }

    Data* func_Vector_size(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto vec = args[0]->assert_cast<Vector>();
        return new Number(vec->value()->size());
    }

    // args = {self, new_size, new_val}
    Data* func_Vector_resize(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto vec = args[0]->assert_cast<Vector>();
        vec->value()->resize(args[1]->int_value());
        return new Void();
    }

    Data* func_Vector_push(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto vec = args[0]->assert_cast<Vector>();
        vec->value()->emplace_back(args[1].release());
        return new Void();
    }

    Data* func_Vector_pop(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto vec = args[0]->assert_cast<Vector>();
        vec->value()->pop_back();
        return new Void();
    }

    Data* func_Vector_at(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto vec = args[0]->assert_cast<Vector>();
        return vec->value()->at(args[1]->int_value())->copy();
    }

    Data* func_Vector_front(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto vec = args[0]->assert_cast<Vector>();
        return vec->value()->front()->copy();
    }

    Data* func_Vector_back(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto vec = args[0]->assert_cast<Vector>();
        return vec->value()->back()->copy();
    }

    // args = {self, key, new_val}
    Data* func_Vector_insert(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto vec = args[0]->assert_cast<Vector>();
        auto iter = vec->value()->begin() + args[1]->int_value();
        vec->value()->insert(iter, args[2].release());
        return new Void();
    }

    // args = {self, key}
    Data* func_Vector_erase(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto vec = args[0]->assert_cast<Vector>();
        auto iter = vec->value()->begin() + args[1]->int_value();
        vec->value()->erase(iter);
        return new Void();
    }

    Data* func_Vector_clear(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto vec = args[0]->assert_cast<Vector>();
        vec->value()->clear();
        return new Void();
    }
    // }


    // class Map
    // {
    Data* func_Map_keys(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
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
    Data* func_Map_has_key(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto map = args[0]->assert_cast<Map>();
        return new Boolean(map->value()->count(Map::Key(args[1].release())) >= 1);
    }

    Data* func_Map_size(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto map = args[0]->assert_cast<Map>();
        return new Number(map->value()->size());
    }

    // args = {self, key}
    Data* func_Map_at(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto map = args[0]->assert_cast<Map>();
        return map->value()->at(Map::Key(args[1].release()))->copy();
    }

    // args = {self, key, new_val}
    Data* func_Map_insert(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto map = args[0]->assert_cast<Map>();
        auto r = map->value()->insert(std::make_pair(
            Map::Key(args[1].release()),
            Variable(args[2].release())
        ));
        return new Boolean(r.second);
    }

    // args = {self, key}
    Data* func_Map_erase(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto map = args[0]->assert_cast<Map>();
        auto r = map->value()->erase(Map::Key(args[1].release()));
        return new Number(r);
    }

    Data* func_Map_clear(Scope& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        auto map = args[0]->assert_cast<Map>();
        map->value()->clear();
        return new Void();
    }
    // }
}
