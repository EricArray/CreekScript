#pragma once

#include <creek/Scope.hpp>

#include <creek/api_mode.hpp>


namespace creek
{
    /// @brief  Global scope.
    /// Has shortcuts to fundamental classes.
    class CREEK_API GlobalScope : public Scope
    {
    public:
        /// @brief  Global class: Boolean.
        static Variable class_Boolean;

        /// @brief  Global class: Class.
        static Variable class_Class;

        /// @brief  Global class: Data.
        static Variable class_Data;

        /// @brief  Global class: Identifier.
        static Variable class_Identifier;

        /// @brief  Global class: Map.
        static Variable class_Map;

        /// @brief  Global class: Null.
        static Variable class_Null;

        /// @brief  Global class: Number.
        static Variable class_Number;

        /// @brief  Global class: Object.
        static Variable class_Object;

        /// @brief  Global class: String.
        static Variable class_String;

        /// @brief  Global class: UserData.
        static Variable class_UserData;

        /// @brief  Global class: Vector.
        static Variable class_Vector;

        /// @brief  Global class: Void.
        static Variable class_Void;

        /// @brief  `GlobalScope` instance.
        static GlobalScope instance;


    private:
        /// @brief  `GlobalScope` constructor.
        GlobalScope();

        GlobalScope(const GlobalScope& other) = delete;
        GlobalScope(GlobalScope&& other) = delete;
    };
}
