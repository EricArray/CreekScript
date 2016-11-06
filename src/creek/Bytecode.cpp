#include <creek/Bytecode.hpp>

#include <creek/Endian.hpp>


namespace creek
{
    Bytecode::Bytecode() :
        m_ss(std::ios_base::in|std::ios_base::out|std::ios_base::ate)
    {

    }

    Bytecode::Bytecode(const Bytecode& other) :
        m_ss(std::ios_base::in|std::ios_base::out|std::ios_base::ate)
    {
        write(other.m_ss.str());
    }

    Bytecode::Bytecode(Bytecode&& other) :
        m_ss(std::ios_base::in|std::ios_base::out|std::ios_base::ate)   //.m_ss.str(), std::ios_base::in|std::ios_base::out|std::ios_base::ate)
    {
        std::swap(m_ss, other.m_ss);
    }

    Bytecode::Bytecode(const std::string& bytes)
        :
        m_ss(std::ios_base::in|std::ios_base::out|std::ios_base::ate)
    {
        write(bytes);
    }

    /// @brief  `Bytecode` constructor.
    Bytecode::Bytecode(const std::stringstream& ss) : Bytecode()
    {
        m_ss.str(ss.str());
    }

    /// @brief  `Bytecode` constructor.
    Bytecode::Bytecode(std::stringstream&& ss) : Bytecode()
    {
        m_ss.swap(ss);
    }

    std::string Bytecode::bytes() const
    {
        return m_ss.str();
    }

    std::string Bytecode::bytes(unsigned pos, unsigned length) const
    {
        return m_ss.str().substr(pos, length);
    }

    void Bytecode::write(const std::string& bytes)
    {
        m_ss.write(&bytes.front(), bytes.size());
    }

    std::string Bytecode::read(unsigned count)
    {
        std::string bytes(count, '\0');
        m_ss.read(&bytes.front(), count);
        if (!m_ss)
            throw EmptyBytecode(count);
        return bytes;
    }

    Bytecode& Bytecode::operator<< (const Bytecode& other)
    {
        write(other.bytes());
        return *this;
    }

    Bytecode& Bytecode::operator<< (int8_t value)
    {
        write(Endian::sint8_to_bytes(value));
        return *this;
    }

    Bytecode& Bytecode::operator<< (int16_t value)
    {
        write(Endian::sint16_to_bytes(value));
        return *this;
    }

    Bytecode& Bytecode::operator<< (int32_t value)
    {
        write(Endian::sint32_to_bytes(value));
        return *this;
    }

    Bytecode& Bytecode::operator<< (int64_t value)
    {
        write(Endian::sint64_to_bytes(value));
        return *this;
    }

    Bytecode& Bytecode::operator<< (uint8_t value)
    {
        return *this << static_cast<int8_t>(value);
    }

    Bytecode& Bytecode::operator<< (uint16_t value)
    {
        return *this << static_cast<int16_t>(value);
    }

    Bytecode& Bytecode::operator<< (uint32_t value)
    {
        return *this << static_cast<int32_t>(value);
    }

    Bytecode& Bytecode::operator<< (uint64_t value)
    {
        return *this << static_cast<int64_t>(value);
    }

    Bytecode& Bytecode::operator<< (float value)
    {
        write(Endian::float32_to_bytes(value));
        return *this;
    }

    Bytecode& Bytecode::operator<< (double value)
    {
        write(Endian::float64_to_bytes(value));
        return *this;
    }

    Bytecode& Bytecode::operator<< (bool value)
    {
        write(Endian::sint8_to_bytes(value));
        return *this;
    }

    Bytecode& Bytecode::operator<< (const std::string& value)
    {
        *this << static_cast<int16_t>(value.size());
        for(auto& c : value)
        {
            *this << static_cast<int8_t>(c);
        }
        return *this;
    }

    Bytecode& Bytecode::operator>> (int8_t& value)
    {
        value = Endian::bytes_to_sint8(read(1));
        return *this;
    }

    Bytecode& Bytecode::operator>> (int16_t& value)
    {
        value = Endian::bytes_to_sint16(read(2));
        return *this;
    }

    Bytecode& Bytecode::operator>> (int32_t& value)
    {
        value = Endian::bytes_to_sint32(read(4));
        return *this;
    }

    Bytecode& Bytecode::operator>> (int64_t& value)
    {
        value = Endian::bytes_to_sint64(read(8));
        return *this;
    }

    Bytecode& Bytecode::operator>> (uint8_t& value)
    {
        int8_t svalue = 0;
        *this >> svalue;
        value = svalue;
        return *this;
    }

    Bytecode& Bytecode::operator>> (uint16_t& value)
    {
        int16_t svalue = 0;
        *this >> svalue;
        value = svalue;
        return *this;
    }

    Bytecode& Bytecode::operator>> (uint32_t& value)
    {
        int32_t svalue = 0;
        *this >> svalue;
        value = svalue;
        return *this;
    }

    Bytecode& Bytecode::operator>> (uint64_t& value)
    {
        int64_t svalue = 0;
        *this >> svalue;
        value = svalue;
        return *this;
    }

    Bytecode& Bytecode::operator>> (float& value)
    {
        value = Endian::bytes_to_float32(read(4));
        return *this;
    }

    Bytecode& Bytecode::operator>> (double& value)
    {
        value = Endian::bytes_to_float32(read(8));
        return *this;
    }

    Bytecode& Bytecode::operator>> (bool& value)
    {
        int8_t svalue = 0;
        *this >> svalue;
        value = svalue;
        return *this;
    }

    Bytecode& Bytecode::operator>> (std::string& value)
    {
        int16_t size = 0;
        *this >> size;
        value.resize(size, '\0');

        for(int16_t i = 0; i < size; ++i)
        {
            int8_t c = '\0';
            *this >> c;
            value[i] = static_cast<char>(c);
        }
        return *this;
    }

    Bytecode::operator bool() const
    {
        return m_ss.good();
    }
}

namespace creek
{
    EmptyBytecode::EmptyBytecode(unsigned extraction)
    {
        stream() << "Extracting " << extraction << " from empty bytecode";
    }
}
