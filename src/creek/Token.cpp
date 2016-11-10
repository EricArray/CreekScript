#include <creek/Token.hpp>


namespace creek
{
    // Token type names.
    const std::map<TokenType, std::string> Token::type_names
    {
        { TokenType::unknown,        "unknown" },                    //< Unexpected character.
        { TokenType::eof,            "EOF" },                        //< End of file.
        { TokenType::space,          "space" },                      //< Blank space (space, new line, etc.).
        { TokenType::commentary,     "commentary" },                 //< Commentary (sigle-line or multi-line).

        { TokenType::void_l,         "void literal" },               //< Void literal.
        { TokenType::null,           "null literal" },               //< Null literal.
        { TokenType::boolean,        "boolean literal" },            //< Boolean literal.
        { TokenType::integer,        "integer literal" },            //< Integer number literal.
        { TokenType::floatnum,       "floating-point literal" },     //< Floating-point number literal.
        { TokenType::character,      "character literal" },          //< Character literal.
        { TokenType::string,         "string literal" },             //< String literal.

        { TokenType::identifier,     "identifier" },                 //< Variable name.

        { TokenType::assign,         "equal sign" },                 //< Equal sign (=).
        { TokenType::dot,            "dot" },                        //< Dot (.).
        { TokenType::ellipsis_2,     "two dots ellipsis" },          //< Two dots ellipsis (..).
        { TokenType::ellipsis_3,     "three dots ellipsis" },        //< Three dots ellipsis (...).
        { TokenType::colon,          "colon" },                      //< Colon (:).
        { TokenType::double_colon,   "double colon" },               //< Double colon (::).
        { TokenType::comma,          "comma" },                      //< Comma (,).
        { TokenType::semicolon,      "semicolon" },                  //< Semicolon (;).
        { TokenType::dollar,         "dollar" },                     //< Dollar sign ($).
        { TokenType::arrow,          "->" },                         ///< Return arrow (->).
        { TokenType::then,           "=>" },                         //< Then arrow (=>).
        { TokenType::operation_sign, "operation sign" },             //< Arithmetic/bitwise/boolean operation sign (eg.: +, -, &, and).

        { TokenType::open_round,     "open parentheses" },           //< Open round brackets or parentheses (().
        { TokenType::close_round,    "close parentheses" },          //< Close round brackets or parentheses ()).
        { TokenType::open_square,    "open square brackets" },       //< Open square brackets or crotchets ([).
        { TokenType::close_square,   "close square brackets" },      //< Close square brackets or crotchets (]).
        { TokenType::open_brace,     "open brace" },                 //< Open curly brackets or braces ({).
        { TokenType::close_brace,    "close brace" },                //< Close curly brackets or braces (}).

        { TokenType::keyword,        "keyword" },                    //< Identifier used as a keyword.
    };

    // `Token` constructor.
    // @param  type    Token type.
    // @param  text    Token text.
    // @param  line    Line where token was extracted.
    // @param  column  Column where token was extracted.
    Token::Token(TokenType type, const std::string& text, int line, int column) :
        m_type(type),
        m_text(text),
        m_line(line),
        m_column(column)
    {

    }

    // `Token` copy constructor.
    Token::Token(const Token& other) :
        m_type(other.m_type),
        m_text(other.m_text),
        m_line(other.m_line),
        m_column(other.m_column)
    {

    }

    // `Token` move constructor.
    Token::Token(Token&& other) :
        m_type(other.m_type),
        m_text(other.m_text),
        m_line(other.m_line),
        m_column(other.m_column)
    {

    }

    // Get type.
    TokenType Token::type() const
    {
        return m_type;
    }

    // Get text.
    const std::string& Token::text() const
    {
        return m_text;
    }

    // Get line.
    int Token::line() const
    {
        return m_line;
    }

    // Get column.
    int Token::column() const
    {
        return m_column;
    }


    // @name   Text translation
    // @{

    // Get the identifier this token represents.
    std::string Token::identifier() const
    {
        return m_text;
    }

    // Get the boolean this token represents.
    bool Token::boolean() const
    {
        if(text() == "true")
            return true;
        else
            return false;
    }

    // Get the character this token represents.
    char Token::character() const
    {
        return unescape_char(text(), 1);
    }

    // Get the string this token represents.
    std::string Token::string() const
    {
        return unescape_string(text().substr(1, text().size() - 2));
    }

    // @}



    // `SyntaxError` constructor.
    // @param  line    Line in source code where the exception happened.
    // @param  column  Line in source code where the exception happened.
    LexicError::LexicError(int line, int column) : m_line(line), m_column(column)
    {
        stream() << "Lexic error: ";
    }

    /// Get line.
    int LexicError::line() const
    {
        return m_line;
    }

    /// Get column.
    int LexicError::column() const
    {
        return m_column;
    }

    // `BadNumberFormat` constructor.
    // @param  token   Source code token where the exception happened.
    BadNumberFormat::BadNumberFormat(int line, int column) : LexicError(line, column)
    {
        stream() << "Bad number format";
    }
}
