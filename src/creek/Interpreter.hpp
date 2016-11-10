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
        /// @brief  `InterpreterOperator` constructor..
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
        static const std::map<std::string, std::pair<std::string, TokenType> > keywords;


        /// @brief  `Interpreter` constructor..
        Interpreter();

        /// Interpret a source file.
        /// @param  path    Path to the source file.
        Expression* load_file(const std::string& path);

        /// Interpret a source code.
        /// @param  code    Source code.
        Expression* load_code(const std::string& code);


    private:
        struct ParseIterator
        {
            const Token* operator -> () const
            {
                return &*iter;
            }

            const Token& operator * () const
            {
                return *iter;
            }

            ParseIterator operator + (int delta)
            {
                return { iter + delta, false };
            }

            ParseIterator& operator += (int delta)
            {
                iter += delta;
                return *this;
            }

            std::vector<Token>::const_iterator iter;
            bool need_semicolon;
        };


        std::string load(const std::string& path);
        std::vector<Token> scan(const std::string& code);
        std::vector<Expression*> parse(const std::vector<Token>& tokens);

        Expression* parse_statement(ParseIterator& iter);
        Expression* parse_operation(ParseIterator& iter);
        Expression* parse_parameter(ParseIterator& iter);

        Expression* parse_block_body(ParseIterator& iter);
        Expression* parse_do_block(ParseIterator& iter);
        Expression* parse_if_block(ParseIterator& iter);
        Expression* parse_loop_block(ParseIterator& iter);
        Expression* parse_while_block(ParseIterator& iter);
        Expression* parse_for_block(ParseIterator& iter);
        Expression* parse_switch_block(ParseIterator& iter);
        Expression* parse_try_block(ParseIterator& iter);

        Expression* parse_var(ParseIterator& iter);
        Expression* parse_function(ParseIterator& iter);
        Expression* parse_class(ParseIterator& iter);

        static bool is_operation(ParseIterator& iter);

        void check_not_eof(ParseIterator& iter);
        void check_token_type(ParseIterator& iter, const std::set<TokenType>& accepted);
    };


    /// Exception raised during interpretion time.
    class CREEK_API SyntaxError : public Exception
    {
    public:
        /// @brief  `SyntaxError` constructor..
        /// @param  token   Source code token where the exception happened.
        SyntaxError(const Token& token);

        /// @brief  `SyntaxError` constructor..
        /// @param  token   Source code token where the exception happened.
        /// @param  message Description of the error.
        SyntaxError(const Token& token, const std::string& message);

        /// Get the token that raised the exception.
        const Token& token() const;

    private:
        Token m_token;
    };


    /// A token has ambiguous meaning.
    class CREEK_API AmbiguousToken : public SyntaxError
    {
    public:
        /// @brief  `AmbiguousToken` constructor..
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
        /// @brief  `UnexpectedCharacter` constructor..
        /// @param  token   Source code token where the exception happened.
        UnexpectedCharacter(const Token& token);
    };


    /// Unexpected token.
    class CREEK_API UnexpectedToken : public SyntaxError
    {
    public:
        /// @brief  `UnexpectedToken` constructor..
        /// @param  token       Source code token where the exception happened.
        UnexpectedToken(const Token& token);

        /// @brief  `UnexpectedToken` constructor..
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
        /// @brief  `UnexpectedEof` constructor..
        /// @param  token   Source code token where the exception happened.
        UnexpectedEof(const Token& token);
    };
}
