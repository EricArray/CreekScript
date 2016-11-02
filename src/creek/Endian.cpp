#include <creek/Endian.hpp>

#include <limits>


namespace creek
{
    // INDEXES 8 //
    constexpr const std::array<uint8_t, 1> _indexes8 = { 0 };

    const std::array<uint8_t, 1>& Endian::indexes8()
    {
        return _indexes8;
    }


    // INDEXES 16 //
#if CREEK_BYTECODE_ENDIAN == CREEK_BIG_ENDIAN
    // in big endian you get: 00 01; so the byte [0] is 00 and byte [1] is 01
    // in lil endian you get: 01 00; so the byte [0] is 01 and byte [1] is 00
    constexpr uint16_t _number16 = 0x0001;
#else
    // in big endian you get: 01 00; so the byte [0] is 01 and byte [1] is 00
    // in lil endian you get: 00 01; so the byte [0] is 00 and byte [1] is 01
    constexpr uint16_t _number16 = 0x0100;
#endif

    // reinterpret the number as a vector of 2 bytes
    constexpr const uint8_t* _pointer16 = reinterpret_cast<const uint8_t*>(&_number16);

    // get the indexes in an array
    const std::array<uint8_t, 2> _indexes16 { _pointer16[0], _pointer16[1] };


    const std::array<uint8_t, 2>& Endian::indexes16()
    {
        return _indexes16;
    }


    // INDEXES 32 //
#if CREEK_BYTECODE_ENDIAN == CREEK_BIG_ENDIAN
    // in big endian you get: 00 01 02 03; so the byte [0] is 00, byte [1] is 01, byte [2] is 02, byte [3] is 03
    // in lil endian you get: 03 02 01 00; so the byte [0] is 03, byte [1] is 02, byte [2] is 01, byte [3] is 00
    constexpr uint32_t _number32 = 0x00010203;
#else
    // in big endian you get: 03 02 01 00; so the byte [0] is 03, byte [1] is 02, byte [2] is 01, byte [3] is 00
    // in lil endian you get: 00 01 02 03; so the byte [0] is 00, byte [1] is 01, byte [2] is 02, byte [3] is 03
    constexpr uint32_t _number32 = 0x03020100;
#endif

    // reinterpret the number as a vector of 4 bytes
    constexpr const uint8_t* _pointer32 = reinterpret_cast<const uint8_t*>(&_number32);

    // get the indexes in an array
    const std::array<uint8_t, 4> _indexes32 = { _pointer32[0], _pointer32[1], _pointer32[2], _pointer32[3] };


    const std::array<uint8_t, 4>& Endian::indexes32()
    {
        return _indexes32;
    }


    // INDEXES 64 //
#if CREEK_BYTECODE_ENDIAN == CREEK_BIG_ENDIAN
    constexpr uint64_t _number64 = 0x0001020304050607;
#else
    constexpr uint64_t _number64 = 0x0706050403020100;
#endif

    // reinterpret the number as a vector of 8 bytes
    constexpr const uint8_t* _pointer64 = reinterpret_cast<const uint8_t*>(&_number64);

    // get the indexes in an array
    const std::array<uint8_t, 8> _indexes64 = { _pointer64[0], _pointer64[1], _pointer64[2], _pointer64[3],
                                                _pointer64[4], _pointer64[5], _pointer64[6], _pointer64[7] };

    const std::array<uint8_t, 8>& Endian::indexes64()
    {
        return _indexes64;
    }


    std::string Endian::sint8_to_bytes(int8_t sint8)
    {
        std::string bytes(1, '\0');
        bytes[0] = sint8;
        return bytes;
    }

    std::string Endian::sint16_to_bytes(int16_t sint16)
    {
        std::string bytes(2, '\0');
        int8_t* pointer = (int8_t*)(&sint16);
        bytes[0] = pointer[indexes16() [0]];
        bytes[1] = pointer[indexes16() [1]];
        return bytes;
    }

    std::string Endian::sint32_to_bytes(int32_t sint32)
    {
        std::string bytes(4, '\0');
        int8_t* pointer = (int8_t*)(&sint32);
        bytes[0] = pointer[indexes32() [0]];
        bytes[1] = pointer[indexes32() [1]];
        bytes[2] = pointer[indexes32() [2]];
        bytes[3] = pointer[indexes32() [3]];
        return bytes;
    }

    std::string Endian::sint64_to_bytes(int64_t sint64)
    {
        std::string bytes(8, '\0');
        int8_t* pointer = (int8_t*)(&sint64);
        bytes[0] = pointer[indexes64() [0]];
        bytes[1] = pointer[indexes64() [1]];
        bytes[2] = pointer[indexes64() [2]];
        bytes[3] = pointer[indexes64() [3]];
        bytes[4] = pointer[indexes64() [4]];
        bytes[5] = pointer[indexes64() [5]];
        bytes[6] = pointer[indexes64() [6]];
        bytes[7] = pointer[indexes64() [7]];
        return bytes;
    }

    std::string Endian::float32_to_bytes(float float32)
    {
        // TODO: Extend support to other floats standars.
        static_assert(std::numeric_limits<float>::is_iec559, "Only IEC 559/IEEE 754 floating-points are supported");

        std::string bytes(4, '\0');
        int8_t* pointer = (int8_t*)(&float32);
        bytes[0] = pointer[indexes32() [0]];
        bytes[1] = pointer[indexes32() [1]];
        bytes[2] = pointer[indexes32() [2]];
        bytes[3] = pointer[indexes32() [3]];
        return bytes;
    }

    std::string Endian::float64_to_bytes(double float64)
    {
        // TODO: Extend support to other floats standars.
        static_assert(std::numeric_limits<double>::is_iec559, "Only IEC 559/IEEE 754 floating-points are supported");

        std::string bytes(8, '\0');
        int8_t* pointer = (int8_t*)(&float64);
        bytes[0] = pointer[indexes64() [0]];
        bytes[1] = pointer[indexes64() [1]];
        bytes[2] = pointer[indexes64() [2]];
        bytes[3] = pointer[indexes64() [3]];
        bytes[4] = pointer[indexes64() [4]];
        bytes[5] = pointer[indexes64() [5]];
        bytes[6] = pointer[indexes64() [6]];
        bytes[7] = pointer[indexes64() [7]];
        return bytes;
    }


    int8_t Endian::bytes_to_sint8(const std::string& bytes)
    {
        return (int8_t)(bytes[0]);
    }

    int16_t Endian::bytes_to_sint16(const std::string& bytes)
    {
        int16_t sint16 = 0;
        int8_t* pointer = reinterpret_cast<int8_t*>(&sint16);
        pointer[indexes16() [0]] = bytes[0];
        pointer[indexes16() [1]] = bytes[1];
        return sint16;
    }

    int32_t Endian::bytes_to_sint32(const std::string& bytes)
    {
        int32_t sint32 = 0;
        int8_t* pointer = reinterpret_cast<int8_t*>(&sint32);
        pointer[indexes32() [0]] = bytes[0];
        pointer[indexes32() [1]] = bytes[1];
        pointer[indexes32() [2]] = bytes[2];
        pointer[indexes32() [3]] = bytes[3];
        return sint32;
    }

    int64_t Endian::bytes_to_sint64(const std::string& bytes)
    {
        int64_t sint64 = 0;
        int8_t* pointer = reinterpret_cast<int8_t*>(&sint64);
        pointer[indexes64() [0]] = bytes[0];
        pointer[indexes64() [1]] = bytes[1];
        pointer[indexes64() [2]] = bytes[2];
        pointer[indexes64() [3]] = bytes[3];
        pointer[indexes64() [4]] = bytes[4];
        pointer[indexes64() [5]] = bytes[5];
        pointer[indexes64() [6]] = bytes[6];
        pointer[indexes64() [7]] = bytes[7];
        return sint64;
    }

    float Endian::bytes_to_float32(const std::string& bytes)
    {
        // TODO: Extend support to other floats standars.
        static_assert(std::numeric_limits<float>::is_iec559, "Only IEC 559/IEEE 754 floating-points are supported");

        float float32 = 0;
        int8_t* pointer = reinterpret_cast<int8_t*>(&float32);
        pointer[indexes32() [0]] = bytes[0];
        pointer[indexes32() [1]] = bytes[1];
        pointer[indexes32() [2]] = bytes[2];
        pointer[indexes32() [3]] = bytes[3];
        return float32;
    }

    double Endian::bytes_to_float64(const std::string& bytes)
    {
        // TODO: Extend support to other floats standars.
        static_assert(std::numeric_limits<float>::is_iec559, "Only IEC 559/IEEE 754 floating-points are supported");

        double float64 = 0;
        int8_t* pointer = reinterpret_cast<int8_t*>(&float64);
        pointer[indexes64() [0]] = bytes[0];
        pointer[indexes64() [1]] = bytes[1];
        pointer[indexes64() [2]] = bytes[2];
        pointer[indexes64() [3]] = bytes[3];
        pointer[indexes64() [4]] = bytes[4];
        pointer[indexes64() [5]] = bytes[5];
        pointer[indexes64() [6]] = bytes[6];
        pointer[indexes64() [7]] = bytes[7];
        return float64;
    }
}
