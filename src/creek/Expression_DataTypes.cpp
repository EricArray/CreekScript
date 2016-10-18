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

    Variable ExprVoid::eval(Scope& scope)
    {
        return Variable(new Void());
    }


    // `ExprNull` constructor.
    ExprNull::ExprNull()
    {

    }

    Variable ExprNull::eval(Scope& scope)
    {
        return Variable(new Null());
    }


    // `ExprBoolean` constructor.
    // @param  value       Boolean value.
    ExprBoolean::ExprBoolean(Boolean::Value value) : m_value(value)
    {

    }

    Variable ExprBoolean::eval(Scope& scope)
    {
        return Variable(new Boolean(m_value));
    }


    // `ExprNumber` constructor.
    // @param  value       Number value.
    ExprNumber::ExprNumber(Number::Value value) : m_value(value)
    {

    }

    Variable ExprNumber::eval(Scope& scope)
    {
        return Variable(new Number(m_value));
    }


    // `ExprString` constructor.
    // @param  value       String value.
    ExprString::ExprString(String::Value value) : m_value(value)
    {

    }

    Variable ExprString::eval(Scope& scope)
    {
        return Variable(new String(m_value));
    }


    // `ExprIdentifier` constructor.
    // @param  value       Identifier value.
    ExprIdentifier::ExprIdentifier(Identifier::Value value) : m_value(value)
    {

    }

    Variable ExprIdentifier::eval(Scope& scope)
    {
        return Variable(new Identifier(m_value));
    }


    /// @brief  `ExprVector` constructor.
    /// @param  values  List of initial values.
    ExprVector::ExprVector(std::vector<Expression*> values)
    {
        for (auto& v : values)
        {
            m_values.emplace_back(v);
        }
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

    Variable ExprFunction::eval(Scope& scope)
    {
        Function::Definition* def = new Function::Definition(scope, m_arg_names, m_variadic, m_body);
        Function::Value new_value(def);
        return Variable(new Function(new_value));
    }


    // `ExprCFunction` constructor.
    // @param  argn        Number of arguments.
    // @param  variadic    Create a variadic function.
    // @param  listener    Listener function to call.
    ExprCFunction::ExprCFunction(unsigned argn, bool variadic, CFunction::Listener listener) :
        m_argn(argn),
        m_variadic(variadic),
        m_listener(listener)
    {

    }

    Variable ExprCFunction::eval(Scope& scope)
    {
        CFunction::Definition* def = new CFunction::Definition(scope, m_argn, m_variadic, m_listener);
        CFunction::Value new_value(def);
        return Variable(new CFunction(new_value));
    }


    // @brief  `ExprClass` constructor.
    // @param  id          Class name.
    // @param  super_class Expression for the super class.
    // @param  method_defs List of method definitions.
    ExprClass::ExprClass(VarName id, Expression* super_class, std::vector<MethodDef>& method_defs) :
        m_id(id),
        m_super_class(super_class)
    {
        m_method_defs.swap(method_defs);
    }

    Variable ExprClass::eval(Scope& scope)
    {
        Variable new_class;

        {
            Variable super_class = m_super_class->eval(scope);

            std::vector< std::unique_ptr<Data> > args;
            args.emplace_back(super_class->copy());
            args.emplace_back(new Identifier(m_id));

            Variable func_derive = GlobalScope::class_Class.index(new Identifier("derive"));
            new_class = func_derive->call(args);
        }

        for (auto& method_def : m_method_defs)
        {
            Function::Definition* def = new Function::Definition(scope, method_def.arg_names, method_def.is_variadic, method_def.body);
            Function::Value new_value(def);
            Variable method = new Function(new_value);
            new_class.index(new Identifier(method_def.id), method.release());
        }

        return new_class;
    }
}
