#pragma once

#include <cassert>
#include <cmath>
#include <string>

#include <creek/api_mode.hpp>
#include <creek/Exception.hpp>


namespace creek
{
    /// Transform an integer into a string.
    /// @param  integer The number to transform.
    /// @param  base    Any numeric base (eg. 2, 8, 10, 16, 5, 7).
    /// @param  psign   Use positive sign.
    /// @param  digits  Add leading zeros if less that this digits long.
    template<class T>
    std::string int_to_string(T integer, unsigned base = 10, unsigned digits = 0, bool psign = false);

    /// Transform a floating-point number into a string.
    /// @param  floatnum    The floating-point number to transform.
    /// @param  base        Any numeric base (eg. 2, 8, 10, 16, 5, 7).
    template<class T>
    std::string float_to_string(T floatnum, unsigned base = 10);


    /// @defgroup   utility_string_escape   String escape and unescape utility
    /// Function for escaping and unescaping string using back-slash (\\).
    /// Implemented escape characters:
    /// | Escaped character | Description          | Byte in ASCII encoding |
    /// | ----------------- | -------------------- | ---------------------: |
    /// | \\'               | single quote         | 0x27                   |
    /// | \\"               | double quote         | 0x22                   |
    /// | \\?               | question mark        | 0x3f                   |
    /// | \\\\              | backslash            | 0x5c                   |
    /// | \\a               | audible bell         | 0x07                   |
    /// | \\b               | backspace            | 0x08                   |
    /// | \\f               | form feed - new page | 0x0c                   |
    /// | \\n               | line feed - new line | 0x0a                   |
    /// | \\r               | carriage return      | 0x0d                   |
    /// | \\t               | horizontal tab       | 0x09                   |
    /// | \\v               | vertical tab         | 0x0b                   |
    /// @{

    /// Translates unescaped character.
    /// Does not add starting and ending quotes.
    /// @param  source  Character to escape.
    /// @return         Escaped first two characters if needed, else the first character.
    CREEK_API extern std::string escape_char(char source);

    /// Translates escaped character.
    /// Does not remove starting and ending quotes.
    /// @param  source  String containing a single character or an escape sequence.
    /// @param  pos     Position to start from the string.
    /// @param  len     Pointer to return number of characters taken from source.
    /// @return         Unescaped character where needed, else same character.
    CREEK_API extern char unescape_char(const std::string& source, unsigned pos = 0, unsigned* len = nullptr);

    /// Translates unescaped characters.
    /// Does not add starting and ending quotes.
    /// @param  source  String to escape.
    /// @return         Escaped string where needed, else same string.
    CREEK_API extern std::string escape_string(const std::string& source);

    /// Translates escaped characters.
    /// Does not remove starting and ending quotes.
    /// @param  source  String containing normal characters or escaped sequences.
    /// @return         Unescaped string where needed, else same string.
    CREEK_API extern std::string unescape_string(const std::string& source);

    /// Bad character escape.
    class CREEK_API BadCharacterEscape : public Exception
    {
    public:
        /// `BadCharacterEscape` constructor.
        /// @param  source  Escaped source string.
        /// @param  pos     Position of the bad escape in source.
        BadCharacterEscape(const std::string& source, unsigned pos);

        /// Get escaped source.
        const std::string& source() const;

        /// Get escape position.
        unsigned pos() const;

    private:
        std::string m_source;
        unsigned m_pos;
    };

    /// @}


    /// Clear command line screen.
    CREEK_API extern void clear_screen();
}


namespace creek
{
    // Transform an integer into a string.
    // @param  integer The number to transform.
    // @param  base    Any numeric base (eg. 2, 8, 10, 16, 5, 7).
    // @param  psign   Use positive sign.
    // @param  digits  Add leading zeros if less that this digits long.
    template<class T> std::string int_to_string(T integer, unsigned base, unsigned digits, bool psign)
    {
        std::string string = "";

        T unprocessed = std::abs(integer);
        do
        {
            T unit = unprocessed % base;

            char digit = '0';
            if(unit < 10)
                digit = '0' + unit;
            else
                digit = 'A' + unit - 10;

            string = digit + string;

            unprocessed /= base;
        }
        while(unprocessed > 0);

        if(string.size() < digits)
            string = std::string(digits - string.size(), '0') + string;

        if(integer < 0)
        {
            string = std::string("-") + string;
        }
        else if(psign)
        {
            if (integer > 0)
                string = std::string(1, '+') + string;
            else
                string = std::string(1, char(241)) + string;
        }

        return string;
    }


    // Transform a floating-point number into a string.
    // @param  floatnum    The floating-point number to transform.
    // @param  base        Any numeric base (eg. 2, 8, 10, 16, 5, 7).
    template<class T> std::string float_to_string(T floatnum, unsigned base)
    {
        // TODO: float to string
        std::stringstream ss;
        ss << floatnum;
        return ss.str();
    }
}
