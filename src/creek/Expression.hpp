#pragma once


namespace creek
{
    class Scope;
    class Variable;


    /// Expression statement in a program.
    class Expression
    {
    public:
        virtual ~Expression() = default;

        /// Evaluate this expression.
        /// @return Result of the expression; may be `nullptr`.
        virtual Variable eval(Scope& scope) = 0;
    };
}
