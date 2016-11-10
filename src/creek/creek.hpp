/// @file creek.hpp
/// Main header.
/// Includes every other header file.
#pragma once

#include <creek/api_mode.hpp>
#include <creek/Boolean.hpp>
#include <creek/Bytecode.hpp>
#include <creek/BytecodeInterpreter.hpp>
#include <creek/CFunction.hpp>
#include <creek/Data.hpp>
#include <creek/DynCFunction.hpp>
#include <creek/DynLibrary.hpp>
#include <creek/Endian.hpp>
#include <creek/Exception.hpp>
#include <creek/Expression.hpp>
#include <creek/Expression_Arithmetic.hpp>
#include <creek/Expression_Bitwise.hpp>
#include <creek/Expression_Boolean.hpp>
#include <creek/Expression_Comparison.hpp>
#include <creek/Expression_ControlFlow.hpp>
#include <creek/Expression_DataTypes.hpp>
#include <creek/Expression_Debug.hpp>
#include <creek/Expression_DynLoad.hpp>
#include <creek/Expression_General.hpp>
#include <creek/Expression_Variable.hpp>
#include <creek/Function.hpp>
#include <creek/GlobalScope.hpp>
#include <creek/Identifier.hpp>
#include <creek/Interpreter.hpp>
#include <creek/Map.hpp>
#include <creek/Null.hpp>
#include <creek/Number.hpp>
#include <creek/Object.hpp>
#include <creek/OpCode.hpp>
#include <creek/Resolver.hpp>
#include <creek/Scope.hpp>
#include <creek/StandardLibrary.hpp>
#include <creek/String.hpp>
#include <creek/Token.hpp>
#include <creek/utility.hpp>
#include <creek/Variable.hpp>
#include <creek/VarName.hpp>
#include <creek/VarNameMap.hpp>
#include <creek/Vector.hpp>
#include <creek/Version.hpp>
#include <creek/Void.hpp>
