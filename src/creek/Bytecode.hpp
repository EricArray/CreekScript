#pragma once

#include <sstream>

#include <creek/api_mode.hpp>
#include <creek/Exception.hpp>


namespace creek
{
    /// @brief  Portable bynary storage (FIFO).
    class CREEK_API Bytecode
    {
    public:
        /// @brief  `Bytecode` constructor.
        Bytecode();

        /// @brief  `Bytecode` constructor.
        Bytecode(const Bytecode& other);

        /// @brief  `Bytecode` constructor.
        Bytecode(Bytecode&& other);

        /// @brief  `Bytecode` constructor.
        Bytecode(const std::string& bytes);

        /// @brief  `Bytecode` constructor.
        Bytecode(const std::stringstream& ss);

        /// @brief  `Bytecode` constructor.
        Bytecode(std::stringstream&& ss);


        /// @brief  Get bytes.
        std::string bytes() const;

        /// @brief  Get bytes.
        /// @param  pos Initial byte.
        /// @param  length Number of bytes to get.
        std::string bytes(unsigned pos, unsigned length) const;


        /// @brief  Insert bytes at the end of the bytecode.
        void write(const std::string& bytes);

        /// @brief  Extract bytes from the beginning of the bytecode.
        /// @param  count Number of bytes to read.
        std::string read(unsigned count);


        /// @brief  Append another bytecode.
        Bytecode& operator<< (const Bytecode& other);


        /// @brief  Insert an 8-bit signed integer.
        Bytecode& operator<< (int8_t value);

        /// @brief  Insert a 16-bit signed integer.
        Bytecode& operator<< (int16_t value);

        /// @brief  Insert a 32-bit signed integer.
        Bytecode& operator<< (int32_t value);

        /// @brief  Insert a 64-bit signed integer.
        Bytecode& operator<< (int64_t value);

        /// @brief  Insert an 8-bit unsigned integer.
        Bytecode& operator<< (uint8_t value);

        /// @brief  Insert a 16-bit unsigned integer.
        Bytecode& operator<< (uint16_t value);

        /// @brief  Insert a 32-bit unsigned integer.
        Bytecode& operator<< (uint32_t value);

        /// @brief  Insert a 64-bit unsigned integer.
        Bytecode& operator<< (uint64_t value);

        /// @brief  Insert a 32-bit floating point number.
        Bytecode& operator<< (float value);

        /// @brief  Insert a 64-bit floating point number.
        Bytecode& operator<< (double value);

        /// @brief  Insert a boolean.
        Bytecode& operator<< (bool value);

        /// @brief  Insert a string.
        Bytecode& operator<< (const std::string& value);


        /// @brief  Extract an 8-bit signed integer.
        Bytecode& operator>> (int8_t& value);

        /// @brief  Extract a 16-bit signed integer.
        Bytecode& operator>> (int16_t& value);

        /// @brief  Extract a 32-bit signed integer.
        Bytecode& operator>> (int32_t& value);

        /// @brief  Extract a 64-bit signed integer.
        Bytecode& operator>> (int64_t& value);

        /// @brief  Extract an 8-bit unsigned integer.
        Bytecode& operator>> (uint8_t& value);

        /// @brief  Extract a 16-bit unsigned integer.
        Bytecode& operator>> (uint16_t& value);

        /// @brief  Extract a 32-bit unsigned integer.
        Bytecode& operator>> (uint32_t& value);

        /// @brief  Extract a 64-bit unsigned integer.
        Bytecode& operator>> (uint64_t& value);

        /// @brief  Extract a 32-bit floating point number.
        Bytecode& operator>> (float& value);

        /// @brief  Extract a 64-bit floating point number.
        Bytecode& operator>> (double& value);

        /// @brief  Extract a boolean.
        Bytecode& operator>> (bool& value);

        /// @brief  Extract a string.
        Bytecode& operator>> (std::string& value);


        /// @brief  Check if can extract from this bytecode.
        operator bool() const;


    private:
        std::stringstream m_ss;
    };
}

namespace creek
{
    /// @brief  Extracting from empty bytecode.
    class EmptyBytecode : public Exception
    {
    public:
        /// @brief  `EmptyBytecode` constructor.
        EmptyBytecode(unsigned extraction);
    };
}
