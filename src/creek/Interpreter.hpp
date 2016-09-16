#pragma once

#include <map>
#include <regex>
#include <set>
#include <string>

#include <creek/api_mode.hpp>
#include <creek/Exception.hpp>
#include <creek/Token.hpp>


namespace creek
{
    class Expression;


    /// Interpreter operator.
    class CREEK_API InterpreterOperator
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
    class CREEK_API Interpreter
    {
    public:
        /// Operators.
        static const std::set<InterpreterOperator> operators;

        /// Regular expressions for tokens.
        static const std::map<TokenType, std::regex> token_regexes;

        /// Keywords.
        static const std::map<std::string, TokenType> keywords;

        /// Textual token synonyms.
        static const std::map<std::string, std::string> synonyms;


        /// `Interpreter` constructor.
        Interpreter();

        /// Interpret a source file.
        /// @param  path    Path to the source file.
        Expression* load_file(const std::string& path);


    private:
        std::string load(const std::string& path);
        std::vector<Token> scan(const std::string& code);
        std::vector<Expression*> parse(const std::vector<Token>& tokens);

        Expression* parse_statement(std::vector<Token>::const_iterator& iter);
        Expression* parse_operation(std::vector<Token>::const_iterator& iter);
        Expression* parse_parameter(std::vector<Token>::const_iterator& iter);

        Expression* parse_block_body(std::vector<Token>::const_iterator& iter);
        Expression* parse_do_block(std::vector<Token>::const_iterator& iter);
        Expression* parse_if_block(std::vector<Token>::const_iterator& iter);
        Expression* parse_loop_block(std::vector<Token>::const_iterator& iter);
        Expression* parse_while_block(std::vector<Token>::const_iterator& iter);
        Expression* parse_for_block(std::vector<Token>::const_iterator& iter);
        Expression* parse_switch_block(std::vector<Token>::const_iterator& iter);
        Expression* parse_try_block(std::vector<Token>::const_iterator& iter);

        Expression* parse_local_var(std::vector<Token>::const_iterator& iter);
        Expression* parse_function(std::vector<Token>::const_iterator& iter);

        void check_not_eof(std::vector<Token>::const_iterator& iter);
        void check_token_type(std::vector<Token>::const_iterator& iter, const std::set<TokenType>& accepted);
    };


    /// Exception raised during interpretion time.
    class CREEK_API SyntaxError : public Exception
    {
    public:
        /// `SyntaxError` constructor.
        /// @param  token   Source code token where the exception happened.
        SyntaxError(const Token& token);

        /// Get the token that raised the exception.
        const Token& token() const;

    private:
        Token m_token;
    };


    /// A token has ambiguous meaning.
    class CREEK_API AmbiguousToken : public SyntaxError
    {
    public:
        /// `AmbiguousToken` constructor.
        /// @param  token   Source code token where the exception happened.
        /// @param  types   List of types that the token matched.
        AmbiguousToken(const Token& token, const std::vector<TokenType>& types);

        /// Get types.
        const std::vector<TokenType>& types() const;

    private:
        std::vector<TokenType> m_types;
    };


    /// Unexpected character.
    class CREEK_API UnexpectedCharacter : public SyntaxError
    {
    public:
        /// `UnexpectedCharacter` constructor.
        /// @param  token   Source code token where the exception happened.
        UnexpectedCharacter(const Token& token);
    };


    /// Unexpected token.
    class CREEK_API UnexpectedToken : public SyntaxError
    {
    public:
        /// `UnexpectedToken` constructor.
        /// @param  token       Source code token where the exception happened.
        UnexpectedToken(const Token& token);

        /// `UnexpectedToken` constructor.
        /// @param  token       Source code token where the exception happened.
        /// @param  accepted    Token types that could be accepted.
        UnexpectedToken(const Token& token, const std::set<TokenType>& accepted);

    private:
        std::set<TokenType> m_accepted;
    };


    /// Unexpected EOF.
    class CREEK_API UnexpectedEof : public SyntaxError
    {
    public:
        /// `UnexpectedEof` constructor.
        /// @param  token   Source code token where the exception happened.
        UnexpectedEof(const Token& token);
    };
}
