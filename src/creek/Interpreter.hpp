#pragma once

#include <map>
#include <regex>
#include <set>
#include <string>

#include <creek/Exception.hpp>


namespace creek
{
    class Expression;


    /// Source code token type.
    enum class InterpreterTokenType
    {
        unknown,            ///< Unexpected character.

        space,              ///< Blank space (space, new line, etc.).
        commentary,         ///< Commentary (sigle-line or multi-line).

        null,               ///< Null literal.
        boolean,            ///< Boolean literal.
        integer,            ///< Integer number literal.
        floatnum,           ///< Floating-point number literal.
        character,          ///< Character literal.
        string,             ///< String literal.

        identifier,         ///< Variable name.

        assign,             ///< Equal sign (=).
        dot,                ///< Dota (.).
        colon,              ///< Colon (:).
        double_colon,       ///< Double colon (::).
        comma,              ///< Comma (,).
        semicolon,          ///< Semicolon (;).
        dollar,             ///< Dollar sign ($).
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
    class InterpreterToken
    {
    public:
        /// Token type names.
        static const std::map<InterpreterTokenType, std::string> type_names;

        /// `InterpreterToken` constructor.
        /// @param  type    Token type.
        /// @param  text    Token text.
        /// @param  line    Line where token was extracted.
        /// @param  column  Column where token was extracted.
        InterpreterToken(InterpreterTokenType type, const std::string& text, int line, int column);

        /// `InterpreterToken` copy constructor.
        InterpreterToken(const InterpreterToken& other);

        /// `InterpreterToken` move constructor.
        InterpreterToken(InterpreterToken&& other);

        /// Get type.
        InterpreterTokenType type() const;

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
        InterpreterTokenType m_type;
        std::string m_text;
        int m_line;
        int m_column;
    };


    /// Interpreter operator.
    class InterpreterOperator
    {
    public:
        /// `InterpreterOperator` constructor.
        /// @param  string      Operator string.
        /// @param  precedence  Operator precedence (the more, the faster).
        InterpreterOperator(const std::string& string, int precedence);

        /// Get string.
        const std::string& string() const;

        /// Get precedence.
        int precedence() const;

        /// Sort by string.
        bool operator < (const InterpreterOperator& other) const;

    private:
        std::string m_string;
        int m_precedence;
    };


    /// Source code interpreter.
    class Interpreter
    {
    public:
        /// Operators.
        static const std::set<InterpreterOperator> operators;

        /// Regular expressions for tokens.
        static const std::map<InterpreterTokenType, std::regex> token_regexes;

        /// Keywords.
        static const std::map<std::string, InterpreterTokenType> keywords;


        /// `Interpreter` constructor.
        Interpreter();

        /// Interpret a source file.
        /// @param  path    Path to the source file.
        Expression* load_file(const std::string& path);


    private:
        std::string load(const std::string& path);
        std::vector<InterpreterToken> scan(const std::string& code);
        std::vector<Expression*> parse(const std::vector<InterpreterToken>& tokens);

        Expression* parse_body(const std::vector<InterpreterToken>& tokens, std::vector<InterpreterToken>::const_iterator& iter);
        Expression* parse_statement(const std::vector<InterpreterToken>& tokens, std::vector<InterpreterToken>::const_iterator& iter);
        Expression* parse_operation(const std::vector<InterpreterToken>& tokens, std::vector<InterpreterToken>::const_iterator& iter);
        Expression* parse_parameter(const std::vector<InterpreterToken>& tokens, std::vector<InterpreterToken>::const_iterator& iter);

        Expression* parse_block_body(const std::vector<InterpreterToken>& tokens, std::vector<InterpreterToken>::const_iterator& iter);
        Expression* parse_do_block(const std::vector<InterpreterToken>& tokens, std::vector<InterpreterToken>::const_iterator& iter);
        Expression* parse_if_block(const std::vector<InterpreterToken>& tokens, std::vector<InterpreterToken>::const_iterator& iter);
        Expression* parse_loop_block(const std::vector<InterpreterToken>& tokens, std::vector<InterpreterToken>::const_iterator& iter);
        Expression* parse_while_block(const std::vector<InterpreterToken>& tokens, std::vector<InterpreterToken>::const_iterator& iter);
        Expression* parse_for_block(const std::vector<InterpreterToken>& tokens, std::vector<InterpreterToken>::const_iterator& iter);
        Expression* parse_switch_block(const std::vector<InterpreterToken>& tokens, std::vector<InterpreterToken>::const_iterator& iter);
        Expression* parse_local_var(const std::vector<InterpreterToken>& tokens, std::vector<InterpreterToken>::const_iterator& iter);
        Expression* parse_lambda(const std::vector<InterpreterToken>& tokens, std::vector<InterpreterToken>::const_iterator& iter);

        void check_not_eof(const std::vector<InterpreterToken>& tokens, std::vector<InterpreterToken>::const_iterator& iter);
        void check_token_type(const std::vector<InterpreterToken>& tokens, std::vector<InterpreterToken>::const_iterator& iter,
                              const std::set<InterpreterTokenType>& accepted);
    };


    /// Exception raised during interpretion time.
    class SyntaxError : public Exception
    {
    public:
        /// `SyntaxError` constructor.
        /// @param  token   Source code token where the exception happened.
        SyntaxError(const InterpreterToken& token);

        /// Get the token that raised the exception.
        const InterpreterToken& token() const;

    private:
        InterpreterToken m_token;
    };


    /// Bad number format in source code.
    class BadNumberFormat : public SyntaxError
    {
    public:
        /// `BadNumberFormat` constructor.
        /// @param  token   Source code token where the exception happened.
        BadNumberFormat(const InterpreterToken& token);
    };


    /// A token has ambiguous meaning.
    class AmbiguousToken : public SyntaxError
    {
    public:
        /// `AmbiguousToken` constructor.
        /// @param  token   Source code token where the exception happened.
        /// @param  types   List of types that the token matched.
        AmbiguousToken(const InterpreterToken& token, const std::vector<InterpreterTokenType>& types);

        /// Get types.
        const std::vector<InterpreterTokenType>& types() const;

    private:
        std::vector<InterpreterTokenType> m_types;
    };


    /// Unexpected character.
    class UnexpectedCharacter : public SyntaxError
    {
    public:
        /// `UnexpectedCharacter` constructor.
        /// @param  token   Source code token where the exception happened.
        UnexpectedCharacter(const InterpreterToken& token);
    };


    /// Unexpected token.
    class UnexpectedToken : public SyntaxError
    {
    public:
        /// `UnexpectedToken` constructor.
        /// @param  token       Source code token where the exception happened.
        /// @param  accepted    Token types that could be accepted.
        UnexpectedToken(const InterpreterToken& token, const std::set<InterpreterTokenType>& accepted);

    private:
        std::set<InterpreterTokenType> m_accepted;
    };


    /// Unexpected EOF.
    class UnexpectedEof : public SyntaxError
    {
    public:
        /// `UnexpectedEof` constructor.
        /// @param  token   Source code token where the exception happened.
        UnexpectedEof(const InterpreterToken& token);
    };
}
