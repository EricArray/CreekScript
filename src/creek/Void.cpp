#include <creek/Void.hpp>

#include <creek/GlobalScope.hpp>


namespace creek
{
    Data* Void::copy() const
    {
        return new Void();
    }

    std::string Void::class_name() const
    {
        return "Void";
    }

    std::string Void::debug_text() const
    {
        return "void";
    }

    bool Void::bool_value() const
    {
        return false;
    }

    Data* Void::get_class()
    {
        return GlobalScope::class_Void->copy();
    }
}
