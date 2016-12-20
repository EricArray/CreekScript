#include <creek/Null.hpp>

#include <creek/Expression_DataTypes.hpp>
#include <creek/GlobalScope.hpp>


namespace creek
{
    /// @brief  `Null` Constructor.
    Null::Null()
    {

    }


    Data* Null::copy() const
    {
        return new Null();
    }

    std::string Null::class_name() const
    {
        return "Null";
    }

    std::string Null::debug_text() const
    {
        return "null";
    }

    Expression* Null::to_expression() const
    {
        return new ExprNull();
    }


    bool Null::bool_value(const SharedPointer<Scope>& scope) const
    {
        return false;
    }

    int Null::int_value(const SharedPointer<Scope>& scope) const
    {
        return 0;
    }

    double Null::double_value(const SharedPointer<Scope>& scope) const
    {
        return 0.0f;
    }

    const std::string& Null::string_value(const SharedPointer<Scope>& scope) const
    {
        static std::string str = "null";
        return str;
    }


    int Null::cmp(const SharedPointer<Scope>& scope, Data* other)
    {
        if (Null* other_null = dynamic_cast<Null*>(other))
        {
            return true;
        }
        return false;
    }

    Data* Null::get_class(const SharedPointer<Scope>& scope) const
    {
        return scope->global()->class_Null->copy();
    }
}
