#include <creek/Void.hpp>

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
}
