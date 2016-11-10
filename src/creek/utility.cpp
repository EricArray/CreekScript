#include <creek/utility.hpp>

#include <iostream>
#include <map>
#include <sstream>


namespace creek
{
    /// Find correct std::stoi function
    template<> int stoi(const std::string& source, std::size_t* pos, int base)
    {
        return std::stoi(source, pos, base);
    }

    template<> long stoi(const std::string& source, std::size_t* pos, int base)
    {
        return std::stol(source, pos, base);
    }

    template<> long long stoi(const std::string& source, std::size_t* pos, int base)
    {
        return std::stoll(source, pos, base);
    }


    /// Find correct std::stof function
    template<> float stof(const std::string& source, std::size_t* pos)
    {
        return std::stof(source, pos);
    }

    template<> double stof(const std::string& source, std::size_t* pos)
    {
        return std::stod(source, pos);
    }

    template<> long double stof(const std::string& source, std::size_t* pos)
    {
        return std::stold(source, pos);
    }


    // @defgroup   utility_string_escape   String escape and unescape utility
    // Function for escaping and unescaping string using back-slash (\).
    // Implemented escape characters:
    // | Escaped character | Description          | Byte in ASCII encoding |
    // | ----------------- | -------------------- | ---------------------: |
    // | \'                | single quote         | 0x27                   |
    // | \"                | double quote         | 0x22                   |
    // | \?                | question mark        | 0x3f                   |
    // | \\                | backslash            | 0x5c                   |
    // | \a                | audible bell         | 0x07                   |
    // | \b                | backspace            | 0x08                   |
    // | \f                | form feed - new page | 0x0c                   |
    // | \n                | line feed - new line | 0x0a                   |
    // | \r                | carriage return      | 0x0d                   |
    // | \t                | horizontal tab       | 0x09                   |
    // | \v                | vertical tab         | 0x0b                   |
    // @{

    // Translates unescaped character.
    // Does not add starting and ending quotes.
    // @param  source  Character to escape.
    // @return         Escaped first two characters if needed, else the first character.
    std::string escape_char(char source)
    {
        switch(source)
        {
            case '\'': return "\\\'";   // single quote         byte 0x27 in ASCII encoding
            case '\"': return "\\\"";   // double quote         byte 0x22 in ASCII encoding
            case '\?': return "\\\?";   // question mark        byte 0x3f in ASCII encoding
            case '\\': return "\\\\";   // backslash            byte 0x5c in ASCII encoding
            case '\a': return "\\a";    // audible bell         byte 0x07 in ASCII encoding
            case '\b': return "\\b";    // backspace            byte 0x08 in ASCII encoding
            case '\f': return "\\f";    // form feed - new page byte 0x0c in ASCII encoding
            case '\n': return "\\n";    // line feed - new line byte 0x0a in ASCII encoding
            case '\r': return "\\r";    // carriage return      byte 0x0d in ASCII encoding
            case '\t': return "\\t";    // horizontal tab       byte 0x09 in ASCII encoding
            case '\v': return "\\v";    // vertical tab         byte 0x0b in ASCII encoding

            default:
            {
                if(source > 127)
                    return std::string("\\x") + int_to_string(source, 0x10, 2);
                else
                    return std::string(1, source);
            }
        }
    }

    // Translates escaped character.
    // Does not remove starting and ending quotes.
    // @param  source  String containing a single character or an escape sequence.
    // @param  pos     Position to start from the string.
    // @param  len     Pointer to return number of characters taken from source.
    // @return         Unescaped character where needed, else same character.
    char unescape_char(const std::string& source, unsigned pos, unsigned* len)
    {
        if(len) *len = 0;

        if(source[pos+0] == '\\')
        {
            // character is escaped
            switch(source[pos+1])
            {
                case '\'':  if(len) *len = 2;  return '\'';     // single quote         byte 0x27 in ASCII encoding
                case '\"':  if(len) *len = 2;  return '\"';     // double quote         byte 0x22 in ASCII encoding
                case '\?':  if(len) *len = 2;  return '\?';     // question mark        byte 0x3f in ASCII encoding
                case '\\':  if(len) *len = 2;  return '\\';     // backslash            byte 0x5c in ASCII encoding
                case 'a':   if(len) *len = 2;  return '\a';     // audible bell         byte 0x07 in ASCII encoding
                case 'b':   if(len) *len = 2;  return '\b';     // backspace            byte 0x08 in ASCII encoding
                case 'f':   if(len) *len = 2;  return '\f';     // form feed - new page byte 0x0c in ASCII encoding
                case 'n':   if(len) *len = 2;  return '\n';     // line feed - new line byte 0x0a in ASCII encoding
                case 'r':   if(len) *len = 2;  return '\r';     // carriage return      byte 0x0d in ASCII encoding
                case 't':   if(len) *len = 2;  return '\t';     // horizontal tab       byte 0x09 in ASCII encoding
                case 'v':   if(len) *len = 2;  return '\v';     // vertical tab         byte 0x0b in ASCII encoding

                // hexadecimal byte
                case 'x':
                {
                    std::size_t processed = 0;
                    int integer = std::stoi(source.substr(pos+1, 2), &processed, 0x10);
                    if(processed < 2)
                        throw BadCharacterEscape(source, pos);
                    if(len) *len = 2 + processed;
                    return integer;
                }

                // unicode
                case 'u':
                case 'U':
                {
                    // TODO: unicode escaping
                    throw Undefined("Unicode escaping in strings");
                }

                default:    return source[pos+1];
            }

            // check for octal and null
            if('0' <= source[pos+1] && source[pos+1] <= '7')
            {
                std::size_t processed = 0;
                int integer = std::stoi(source.substr(pos+1, 3), &processed, 010);
                if((processed == 1 && source[pos+1] != '0') || (processed == 2))
                    throw BadCharacterEscape(source, pos);
                if(len) *len = 1 + processed;
                return integer;
            }
        }

        // character is not escaped
        else
        {
            if(len) *len = 1;
            return source[pos+0];
        }
    }

    // Translates unescaped characters.
    // Does not add starting and ending quotes.
    // @param  source  String to escape.
    // @return         Escaped string where needed, else same string.
    std::string escape_string(const std::string& source)
    {
        std::string result = "";

        for(unsigned i = 0; i < source.size(); ++i)
            result += escape_char(source[i]);

        return result;
    }

    // Translates escaped characters.
    // Does not remove starting and ending quotes.
    // @param  source  String containing normal characters or escaped sequences.
    // @return         Unescaped string where needed, else same string.
    std::string unescape_string(const std::string& source)
    {
        std::string result = "";

        unsigned i = 0;
        while(i < source.size())
        {
            unsigned len = 0;
            result += unescape_char(source, i, &len);
            i += len;
        }

        return result;
    }


    // `BadCharacterEscape` constructor.
    // @param  source  Escaped source string.
    // @param  pos     Position of the bad escape in source.
    BadCharacterEscape::BadCharacterEscape(const std::string& source, unsigned pos) : m_source(source), m_pos(pos)
    {
        stream() << "Bad character escape";
    }

    // Get escaped source.
    const std::string& BadCharacterEscape::source() const
    {
        return m_source;
    }

    // Get escape position.
    unsigned BadCharacterEscape::pos() const
    {
        return m_pos;
    }

    // @}

    // Clear command line screen.
    void clear_screen()
    {
        // TODO: portabilize clear_screen.
        system("@CLS");
    }
}
