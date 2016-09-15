#pragma once

namespace creek
{
    class Scope;


    /// Load standard library.
    /// @param  scope   Scope where standard variables are created.
    void load_standard_library(Scope& scope);
}