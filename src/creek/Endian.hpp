#pragma once

#include <array>
#include <string>
#include <cstdint>

#include <creek/api_mode.hpp>


#define CREEK_BIG_ENDIAN 0
#define CREEK_LIL_ENDIAN 1
#define CREEK_BYTECODE_ENDIAN CREEK_LIL_ENDIAN

namespace creek
{
    /// @brief  Cross platform integer and float storage.
    namespace Endian
    {
        /// @brief  Get the byte distribution in memory for an 8 bits variable.
        CREEK_API extern const std::array<uint8_t, 1>& indexes8();

        /// @brief  Get the byte distribution in memory for a 16 bits variable.
        CREEK_API extern const std::array<uint8_t, 2>& indexes16();

        /// @brief  Get the byte distribution in memory for a 32 bits variable.
        CREEK_API extern const std::array<uint8_t, 4>& indexes32();

        /// @brief  Get the byte distribution in memory for a 64 bits variable.
        CREEK_API extern const std::array<uint8_t, 8>& indexes64();


        /// @brief  Get the bytes of an 8 bits singed int.
        CREEK_API extern std::string sint8_to_bytes(int8_t sint8);

        /// @brief  Get the bytes of a 16 bits singed int.
        CREEK_API extern std::string sint16_to_bytes(int16_t sint16);

        /// @brief  Get the bytes of a 32 bits singed int.
        CREEK_API extern std::string sint32_to_bytes(int32_t sint32);

        /// @brief  Get the bytes of a 64 bits singed int.
        CREEK_API extern std::string sint64_to_bytes(int64_t sint64);

        /// @brief  Get the bytes of a 32 bits floating point number.
        CREEK_API extern std::string float32_to_bytes(float float32);

        /// @brief  Get the bytes of a 64 bits floating point number.
        CREEK_API extern std::string float64_to_bytes(double float64);


        /// @brief  Get an 8 bits singed int from bytes.
        CREEK_API extern int8_t   bytes_to_sint8(const std::string& bytes);

        /// @brief  Get a 16 bits singed int from bytes.
        CREEK_API extern int16_t  bytes_to_sint16(const std::string& bytes);

        /// @brief  Get a 32 bits singed int from bytes.
        CREEK_API extern int32_t  bytes_to_sint32(const std::string& bytes);

        /// @brief  Get a 64 bits singed int from bytes.
        CREEK_API extern int64_t  bytes_to_sint64(const std::string& bytes);

        /// @brief  Get a 32 floating point number.
        CREEK_API extern float bytes_to_float32(const std::string& bytes);

        /// @brief  Get a 64 floating point number.
        CREEK_API extern double bytes_to_float64(const std::string& bytes);
    }
}
