#pragma once

#include <string>
#include <map>

#include <creek/api_mode.hpp>
#include <creek/Exception.hpp>
#include <creek/utility.hpp>


namespace creek
{
    /// @brief  Source code token type.
    enum class TokenType
    {
        unknown,            ///< Unexpected character.
        eof,                ///< End of file.
        space,              ///< Blank space (space, new line, etc.).
        commentary,         ///< Commentary (sigle-line or multi-line).

        void_l,             ///< Void literal.
        null,               ///< Null literal.
        boolean,            ///< Boolean literal.
        integer,            ///< Integer number literal.
        floatnum,           ///< Floating-point number literal.
        character,          ///< Character literal.
        string,             ///< String literal.

        identifier,         ///< Variable name.

        assign,             ///< Equal sign (=).
        dot,                ///< Dot (.).
        ellipsis_2,         ///< Two dots ellipsis (..).
        ellipsis_3,         ///< Three dots ellipsis (...).
        colon,              ///< Colon (:).
        double_colon,       ///< Double colon (::).
        comma,              ///< Comma (,).
        semicolon,          ///< Semicolon (;).
        at,                 ///< At sign (@).
        hash,               ///< Hash sign (#).
        dollar,             ///< Dollar sign ($).
        arrow,              ///< Return arrow (->).
        then,               ///< Then arrow (=>).
        operation_sign,     ///< Arithmetic/bitwise/boolean operation sign (eg.: +, -, &, and).

        open_round,         ///< Open round brackets or parentheses (().
        close_round,        ///< Close round brackets or parentheses ()).
        open_square,        ///< Open square brackets or crotchets ([).
        close_square,       ///< Close square brackets or crotchets (]).
        open_brace,         ///< Open curly brackets or braces ({).
        close_brace,        ///< Close curly brackets or braces (}).

        // keyword,            ///< Identifier used as a keyword.
    };


    /// @brief  Source code token.
    class CREEK_API Token
    {
    public:
        /// @brief  Token type names.
        static const std::map<TokenType, std::string> type_names;

        /// @brief  `Token` constructor..
        /// @param  type    Token type.
        /// @param  text    Token text.
        /// @param  line    Line where token was extracted.
        /// @param  column  Column where token was extracted.
        Token(TokenType type, const std::string& text, int line, int column);

        /// @brief  `Token` copy constructor.
        Token(const Token& other);

        /// @brief  `Token` move constructor.
        Token(Token&& other);

        /// @brief  Get type.
        TokenType type() const;

        /// @brief  Get text.
        const std::string& text() const;

        /// @brief  Get line.
        int line() const;

        /// @brief  Get column.
        int column() const;


        /// @name   Text translation
        /// @{

        /// @brief  Get the identifier this token represents.
        std::string identifier() const;

        /// @brief  Get the boolean this token represents.
        bool boolean() const;

        /// @brief  Get the integer this token represents.
        template<class T = int> T integer() const;

        /// @brief  Get the floating-point number this token represents.
        template<class T = float> T floatnum() const;

        /// @brief  Get the character this token represents.
        char character() const;

        /// @brief  Get the string this token represents.
        std::string string() const;

        /// @}


    private:
        TokenType m_type;
        std::string m_text;
        int m_line;
        int m_column;
    };


    /// @brief  Lexic error raised when scanning code.
    class CREEK_API LexicError : public Exception
    {
    public:
        /// @brief  `LexicError` constructor..
        /// @param  line    Line in source code where the exception happened.
        /// @param  column  Line in source code where the exception happened.
        LexicError(int line, int column);

        /// @brief  Get line.
        int line() const;

        /// @brief  Get column.
        int column() const;

    private:
        int m_line;
        int m_column;
    };


    /// @brief  Bad number format in source code.
    class CREEK_API BadNumberFormat : public LexicError
    {
    public:
        /// @brief  `BadNumberFormat` constructor..
        /// @param  line    Line in source code where the exception happened.
        /// @param  column  Line in source code where the exception happened.
        BadNumberFormat(int line, int column);
    };
}


// Template implementation
namespace creek
{
    // Get the integer this token represents.
    template<class T> T Token::integer() const
    {
        std::size_t pos = 0;
        T result = 0;

        std::string value;

        try
        {
            if(text()[0] == '0' && (text()[1] == 'b' || text()[1] == 'B'))
            {
                value = text().substr(2);
                result = stoi<T>(value, &pos, 2);
            }
            else if(text()[0] == '0' && (text()[1] == 'x' || text()[1] == 'X'))
            {
                value = text().substr(2);
                result = stoi<T>(value, &pos, 16);
            }
            else
            {
                value = text();
                result = stoi<T>(value, &pos, 10);
            }
        }
        catch(const std::invalid_argument& e)
        {
            throw BadNumberFormat(m_line, m_column);
        }
        catch(const std::out_of_range& e)
        {
            throw BadNumberFormat(m_line, m_column);
        }

        if(pos != value.size())
        {
            throw BadNumberFormat(m_line, m_column);
        }

        return result;
    }

    // Get the floating-point number this token represents.
    template<class T> T Token::floatnum() const
    {
        std::size_t pos = 0;
        T result = 0;

        try
        {
            result = stof<T>(text(), &pos);
        }
        catch (const std::invalid_argument& e)
        {
            throw BadNumberFormat(m_line, m_column);
        }
        catch (const std::out_of_range& e)
        {
            throw BadNumberFormat(m_line, m_column);
        }

        if(pos != text().size())
        {
            throw BadNumberFormat(m_line, m_column);
        }

        return result;
    }
}
