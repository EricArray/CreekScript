#include <creek/Expression_DataTypes.hpp>

#include <creek/GlobalScope.hpp>
#include <creek/Scope.hpp>
#include <creek/Variable.hpp>


namespace creek
{
    // `ExprVoid` constructor.
    ExprVoid::ExprVoid()
    {

    }

    Expression* ExprVoid::clone() const
    {
        return new ExprVoid();
    }

    bool ExprVoid::is_const() const
    {
        return true;
    }

    Variable ExprVoid::eval(Scope& scope)
    {
        return Variable(new Void());
    }

    Bytecode ExprVoid::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(OpCode::data_void);
    }


    // `ExprNull` constructor.
    ExprNull::ExprNull()
    {

    }

    Expression* ExprNull::clone() const
    {
        return new ExprNull();
    }

    bool ExprNull::is_const() const
    {
        return true;
    }

    Variable ExprNull::eval(Scope& scope)
    {
        return Variable(new Null());
    }

    Bytecode ExprNull::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(OpCode::data_null);
    }


    // `ExprBoolean` constructor.
    // @param  value       Boolean value.
    ExprBoolean::ExprBoolean(Boolean::Value value) : m_value(value)
    {

    }

    Expression* ExprBoolean::clone() const
    {
        return new ExprBoolean(m_value);
    }

    bool ExprBoolean::is_const() const
    {
        return true;
    }

    Variable ExprBoolean::eval(Scope& scope)
    {
        return Variable(new Boolean(m_value));
    }

    Bytecode ExprBoolean::bytecode(VarNameMap& var_name_map) const
    {
        Bytecode b;
        b << static_cast<uint8_t>(OpCode::data_boolean);
        b << m_value;
        return b;
    }


    // `ExprNumber` constructor.
    // @param  value       Number value.
    ExprNumber::ExprNumber(Number::Value value) : m_value(value)
    {

    }

    Expression* ExprNumber::clone() const
    {
        return new ExprNumber(m_value);
    }

    bool ExprNumber::is_const() const
    {
        return true;
    }

    Variable ExprNumber::eval(Scope& scope)
    {
        return Variable(new Number(m_value));
    }

    Bytecode ExprNumber::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(OpCode::data_number) << m_value;
    }


    // `ExprString` constructor.
    // @param  value       String value.
    ExprString::ExprString(String::Value value) : m_value(value)
    {

    }

    Expression* ExprString::clone() const
    {
        return new ExprString(m_value);
    }

    bool ExprString::is_const() const
    {
        return true;
    }

    Variable ExprString::eval(Scope& scope)
    {
        return Variable(new String(m_value));
    }

    Bytecode ExprString::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(OpCode::data_string) << m_value;
    }


    // `ExprIdentifier` constructor.
    // @param  value       Identifier value.
    ExprIdentifier::ExprIdentifier(Identifier::Value value) : m_value(value)
    {

    }

    Expression* ExprIdentifier::clone() const
    {
        return new ExprIdentifier(m_value);
    }

    bool ExprIdentifier::is_const() const
    {
        return true;
    }

    Variable ExprIdentifier::eval(Scope& scope)
    {
        return Variable(new Identifier(m_value));
    }

    Bytecode ExprIdentifier::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(OpCode::data_identifier) << var_name_map.id_from_name(m_value.name());
    }


    /// @brief  `ExprVector` constructor.
    /// @param  values  List of initial values.
    ExprVector::ExprVector(const std::vector<Expression*>& values)
    {
        for (auto& v : values)
        {
            m_values.emplace_back(v);
        }
    }

    Expression* ExprVector::clone() const
    {
        std::vector<Expression*> new_values;
        for (auto& v : m_values)
        {
            new_values.push_back(v->clone());
        }
        return new ExprVector(new_values);
    }

    bool ExprVector::is_const() const
    {
        for (auto& v : m_values)
        {
            if (v->is_const() == false)
                return false;
        }
        return true;
    }

    Expression* ExprVector::const_optimize() const
    {
        std::vector<Expression*> new_values;
        for (auto& v : m_values)
        {
            new_values.push_back(v->const_optimize());
        }
        return new ExprVector(new_values);
    }

    Variable ExprVector::eval(Scope& scope)
    {
        Vector::Value new_value = std::make_shared< std::vector<Variable> >();
        for (auto& v : m_values)
        {
            new_value->emplace_back(v->eval(scope));
        }
        return Variable(new Vector(new_value));
    }

    Bytecode ExprVector::bytecode(VarNameMap& var_name_map) const
    {
        Bytecode b;
        b << static_cast<uint8_t>(OpCode::data_vector);
        b << static_cast<uint32_t>(m_values.size());
        for (auto& value : m_values)
        {
            b << value->bytecode(var_name_map);
        }
        return b;
    }


    /// @brief  `ExprMap` constructor.
    /// @param  values  List of initial values.
    ExprMap::ExprMap(std::vector<Pair>& pairs)
    {
        m_pairs.swap(pairs);
    }

    Expression* ExprMap::clone() const
    {
        std::vector<Pair> new_pairs;
        new_pairs.reserve(m_pairs.size());
        for (auto& p : m_pairs)
        {
            new_pairs.emplace_back(p.key->clone(), p.value->clone());
        }
        return new ExprMap(new_pairs);
    }

    bool ExprMap::is_const() const
    {
        for (auto& p : m_pairs)
        {
            if (!p.key->is_const() or !p.value->is_const())
                return false;
        }
        return true;
    }

    Expression* ExprMap::const_optimize() const
    {
        std::vector<Pair> new_pairs;
        new_pairs.reserve(m_pairs.size());
        for (auto& p : m_pairs)
        {
            new_pairs.emplace_back(p.key->const_optimize(), p.value->const_optimize());
        }
        return new ExprMap(new_pairs);
    }

    Variable ExprMap::eval(Scope& scope)
    {
        Map::Value new_value = std::make_shared<Map::Definition>();
        for (auto& p : m_pairs)
        {
            Variable key = p.key->eval(scope);
            Variable value = p.value->eval(scope);
            (*new_value)[Map::Key(key.release())] = value;
        }
        return Variable(new Map(new_value));
    }

    Bytecode ExprMap::bytecode(VarNameMap& var_name_map) const
    {
        Bytecode b;
        b << static_cast<uint8_t>(OpCode::data_map);
        b << static_cast<uint32_t>(m_pairs.size());
        for (auto& p : m_pairs)
        {
            b << p.key->bytecode(var_name_map);
            b << p.value->bytecode(var_name_map);
        }
        return b;
    }


    // `ExprFunction` constructor.
    // @param  arg_names   Names of arguments.
    // @param  variadic    Create a variadic function.
    // @param  body        Function body block.
    ExprFunction::ExprFunction(const std::vector<VarName>& arg_names, bool variadic, Expression* body) :
        m_arg_names(arg_names),
        m_variadic(variadic),
        m_body(body)
    {

    }

    // `ExprFunction` constructor.
    // @param  arg_names   Names of arguments.
    // @param  variadic    Create a variadic function.
    // @param  body        Function body block.
    ExprFunction::ExprFunction(const std::vector<VarName>& arg_names, bool variadic, std::shared_ptr<Expression> body) :
        m_arg_names(arg_names),
        m_variadic(variadic),
        m_body(body)
    {

    }

    Expression* ExprFunction::clone() const
    {
        return new ExprFunction(m_arg_names, m_variadic, m_body);
    }

    bool ExprFunction::is_const() const
    {
        return true;
    }

    Expression* ExprFunction::const_optimize() const
    {
        return new ExprFunction(m_arg_names, m_variadic, m_body->const_optimize());
    }

    Variable ExprFunction::eval(Scope& scope)
    {
        Function::Definition* def = new Function::Definition(scope, m_arg_names, m_variadic, m_body);
        Function::Value new_value(def);
        return Variable(new Function(new_value));
    }

    Bytecode ExprFunction::bytecode(VarNameMap& var_name_map) const
    {
        Bytecode b;
        b << static_cast<uint8_t>(OpCode::data_function);
        b << static_cast<uint32_t>(m_arg_names.size());
        for (auto& arg_name : m_arg_names)
        {
            b << var_name_map.id_from_name(arg_name.name());
        }
        b << m_variadic;
        b << m_body->bytecode(var_name_map);
        return b;
    }


    // // `ExprCFunction` constructor.
    // // @param  argn        Number of arguments.
    // // @param  variadic    Create a variadic function.
    // // @param  listener    Listener function to call.
    // ExprCFunction::ExprCFunction(unsigned argn, bool variadic, CFunction::Listener listener) :
    //     m_argn(argn),
    //     m_variadic(variadic),
    //     m_listener(listener)
    // {

    // }

    // Variable ExprCFunction::eval(Scope& scope)
    // {
    //     CFunction::Definition* def = new CFunction::Definition(scope, m_argn, m_variadic, m_listener);
    //     CFunction::Value new_value(def);
    //     return Variable(new CFunction(new_value));
    // }

    // Bytecode ExprCFunction::bytecode(VarNameMap& var_name_map) const
    // {
    //     return Bytecode() << static_cast<uint8_t>(OpCode::expr_c_function)
    // }


    // @brief  `ExprClass` constructor.
    // @param  id          Class name.
    // @param  super_class Expression for the super class.
    // @param  method_defs List of method definitions.
    ExprClass::ExprClass(VarName id, Expression* super_class, std::vector<MethodDef>& method_defs, std::vector<StaticDef>& static_defs) :
        m_id(id),
        m_super_class(super_class)
    {
        m_method_defs.swap(method_defs);
        m_static_defs.swap(static_defs);
    }

    /// @brief  Get a copy.
    /// The cloned expression shares the body expression.
    Expression* ExprClass::clone() const
    {
        std::vector<MethodDef> new_method_defs;
        for (auto& d : m_method_defs)
        {
            new_method_defs.emplace_back(d.id, d.arg_names, d.is_variadic, d.body);
        }
        std::vector<StaticDef> new_static_defs;
        for (auto& d : m_static_defs)
        {
            new_static_defs.emplace_back(d.id);
        }
        return new ExprClass(m_id, m_super_class->clone(), new_method_defs, new_static_defs);
    }

    bool ExprClass::is_const() const
    {
        return false;
    }

    /// @brief  Get an optimized copy.
    /// The cloned expression has an optimized body expression.
    Expression* ExprClass::const_optimize() const
    {
        std::vector<MethodDef> new_method_defs;
        for (auto& d : m_method_defs)
        {
            new_method_defs.emplace_back(d.id, d.arg_names, d.is_variadic, d.body->const_optimize());
        }
        std::vector<StaticDef> new_static_defs;
        for (auto& d : m_static_defs)
        {
            new_static_defs.emplace_back(d.id);
        }
        return new ExprClass(m_id, m_super_class->const_optimize(), new_method_defs, new_static_defs);
    }

    Variable ExprClass::eval(Scope& scope)
    {
        Variable new_class;

        {
            Variable super_class = m_super_class->eval(scope);

            std::vector< std::unique_ptr<Data> > args;
            args.emplace_back(super_class->copy());
            args.emplace_back(new Identifier(m_id));

            Variable func_derive = GlobalScope::class_Class.attr("derive");
            new_class = func_derive->call(args);
        }

        for (auto& method_def : m_method_defs)
        {
            Function::Definition* def = new Function::Definition(scope, method_def.arg_names, method_def.is_variadic, method_def.body);
            Function::Value new_value(def);
            Variable method = new Function(new_value);
            new_class.attr(method_def.id, method.release());
        }

        // for (auto& static_def : m_static_defs)
        // {
        //     Function::Definition* def = new Function::Definition(scope, method_def.arg_names, method_def.is_variadic, method_def.body);
        //     Function::Value new_value(def);
        //     Variable method = new Function(new_value);
        //     new_class.attr(method_def.id, method.release());
        // }

        return new_class;
    }

    Bytecode ExprClass::bytecode(VarNameMap& var_name_map) const
    {
        Bytecode b;
        b << static_cast<uint8_t>(OpCode::data_class);
        b << var_name_map.id_from_name(m_id.name());
        b << m_super_class->bytecode(var_name_map);
        
        b << static_cast<uint32_t>(m_method_defs.size());
        for (auto& method_def : m_method_defs)
        {
            b << var_name_map.id_from_name(method_def.id.name());
            b << static_cast<uint32_t>(method_def.arg_names.size());
            for (auto& arg_name : method_def.arg_names)
            {
                b << var_name_map.id_from_name(arg_name.name());
            }
            b << method_def.is_variadic;
            b << method_def.body->bytecode(var_name_map);
        }

        return b;
    }
}
