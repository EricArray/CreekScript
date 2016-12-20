#pragma once

#include <creek/api_mode.hpp>
#include <creek/Shared.hpp>


namespace creek
{
    class Scope;


    /// Load standard library.
    /// @param  scope   Scope where standard variables are created.
    CREEK_API extern void load_standard_library(const SharedPointer<Scope>& scope);
}
