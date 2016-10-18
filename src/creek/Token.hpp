#pragma once

#include <string>
#include <map>

#include <creek/api_mode.hpp>
#include <creek/Exception.hpp>
#include <creek/utility.hpp>


namespace creek
{
    /// Source code token type.
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

        keyword,            ///< Identifier used as a keyword.
    };


    /// Source code token.
    class CREEK_API Token
    {
    public:
        /// Token type names.
        static const std::map<TokenType, std::string> type_names;

        /// `Token` constructor.
        /// @param  type    Token type.
        /// @param  text    Token text.
        /// @param  line    Line where token was extracted.
        /// @param  column  Column where token was extracted.
        Token(TokenType type, const std::string& text, int line, int column);

        /// `Token` copy constructor.
        Token(const Token& other);

        /// `Token` move constructor.
        Token(Token&& other);

        /// Get type.
        TokenType type() const;

        /// Get text.
        const std::string& text() const;

        /// Get line.
        int line() const;

        /// Get column.
        int column() const;


        /// @name   Text translation
        /// @{

        /// Get the identifier this token represents.
        std::string identifier() const;

        /// Get the boolean this token represents.
        bool boolean() const;

        /// Get the integer this token represents.
        int integer() const;

        /// Get the floating-point number this token represents.
        float floatnum() const;

        /// Get the character this token represents.
        char character() const;

        /// Get the string this token represents.
        std::string string() const;

        /// @}


    private:
        TokenType m_type;
        std::string m_text;
        int m_line;
        int m_column;
    };


    /// Lexic error raised when scanning code.
    class CREEK_API LexicError : public Exception
    {
    public:
        /// `LexicError` constructor.
        /// @param  line    Line in source code where the exception happened.
        /// @param  column  Line in source code where the exception happened.
        LexicError(int line, int column);

        /// Get line.
        int line() const;

        /// Get column.
        int column() const;

    private:
        int m_line;
        int m_column;
    };


    /// Bad number format in source code.
    class CREEK_API BadNumberFormat : public LexicError
    {
    public:
        /// `BadNumberFormat` constructor.
        /// @param  line    Line in source code where the exception happened.
        /// @param  column  Line in source code where the exception happened.
        BadNumberFormat(int line, int column);
    };
}
