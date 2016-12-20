#pragma once

#include <creek/Scope.hpp>

#include <creek/api_mode.hpp>


namespace creek
{
    /// @brief  Global scope.
    /// Has shortcuts to fundamental classes.
    class CREEK_API GlobalScope : public LocalScope
    {
    public:
        /// @brief  `GlobalScope` constructor.
        GlobalScope(const SharedPointer<Shared>& sp);

        GlobalScope(const GlobalScope& other) = delete;
        GlobalScope(GlobalScope&& other) = delete;


        /// @brief  Spread garbage collector trace mark.
        void spread_garbage_trace();


        /// @brief  Global class: Boolean.
        Variable class_Boolean;

        /// @brief  Global class: Class.
        Variable class_Class;

        /// @brief  Global class: Data.
        Variable class_Data;

        /// @brief  Global class: Identifier.
        Variable class_Identifier;

        /// @brief  Global class: Map.
        Variable class_Map;

        /// @brief  Global class: Module.
        Variable class_Module;

        /// @brief  Global class: Null.
        Variable class_Null;

        /// @brief  Global class: Number.
        Variable class_Number;

        /// @brief  Global class: Object.
        Variable class_Object;

        /// @brief  Global class: String.
        Variable class_String;

        /// @brief  Global class: UserData.
        Variable class_UserData;

        /// @brief  Global class: Vector.
        Variable class_Vector;

        /// @brief  Global class: Void.
        Variable class_Void;

        // /// @brief  `GlobalScope` instance.
        // GlobalScope instance;
    };
}
