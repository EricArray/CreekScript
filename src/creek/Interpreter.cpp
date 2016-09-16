#include <creek/Interpreter.hpp>

#include <fstream>
#include <iostream>
#include <string>

#include <creek/Exception.hpp>
#include <creek/Expression.hpp>
#include <creek/Expression_Arithmetic.hpp>
#include <creek/Expression_DataTypes.hpp>
#include <creek/Expression_Bitwise.hpp>
#include <creek/Expression_Boolean.hpp>
#include <creek/Expression_Comparison.hpp>
#include <creek/Expression_ControlFlow.hpp>
#include <creek/Expression_Debug.hpp>
#include <creek/Expression_General.hpp>
#include <creek/Expression_Variable.hpp>
#include <creek/utility.hpp>


namespace creek
{
    // `InterpreterOperator` constructor.
    // @param  string      Operator string.
    // @param  precedence  Operator precedence (the more, the faster).
    InterpreterOperator::InterpreterOperator(const std::string& string, int precedence) :
        m_string(string),
        m_precedence(precedence)
    {

    }

    // Get string.
    const std::string& InterpreterOperator::string() const
    {
        return m_string;
    }

    // Get precedence.
    int InterpreterOperator::precedence() const
    {
        return m_precedence;
    }

    // Sort by string.
    bool InterpreterOperator::operator < (const InterpreterOperator& other) const
    {
        return m_string < other.m_string;
    }



    // Operators.
    const std::set<InterpreterOperator> Interpreter::operators =
    {
        InterpreterOperator("**", 12),

        InterpreterOperator("*", 11),
        InterpreterOperator("/", 11),
        InterpreterOperator("%", 11),

        InterpreterOperator("+", 10),
        InterpreterOperator("-", 10),

        InterpreterOperator("<<", 9),
        InterpreterOperator(">>", 9),

        InterpreterOperator("<=>", 8),

        InterpreterOperator("<", 7),
        InterpreterOperator("<=", 7),
        InterpreterOperator(">", 7),
        InterpreterOperator(">=", 7),

        InterpreterOperator("==", 6),
        InterpreterOperator("!=", 6),

        InterpreterOperator("&", 5),

        InterpreterOperator("^", 4),

        InterpreterOperator("|", 3),

        InterpreterOperator("&&", 2),

        InterpreterOperator("||", 1),
    };

    // Regular expressions for tokens.
    const std::map<TokenType, std::regex> Interpreter::token_regexes
    {
        { TokenType::space,          std::regex(R"__(^(\s+))__") },

        { TokenType::commentary,     std::regex(R"__(^(//[^\n]*))__") },

        // { TokenType::boolean,        std::regex(R"(true|false)") },
        // { TokenType::integer,        std::regex(R"__(^(0[bB][01]+|0[xX][0-9a-fA-F]+|[0-9]+))__") },
        { TokenType::integer,        std::regex(R"__(^([0-9]+))__") },
        { TokenType::floatnum,       std::regex(R"__(^((0[xX][0-9a-fA-F]+\.[0-9a-fA-F]+)|([0-9]+\.[0-9]+)))__") },
        { TokenType::character,      std::regex(R"__(^('([^'\\]|\\.)'))__") },
        { TokenType::string,         std::regex(R"__(^("([^"\\]|\\.)*"))__") },

        { TokenType::identifier,     std::regex(R"__(^([_a-zA-Z][_a-zA-Z0-9]*))__") },
        { TokenType::assign,         std::regex(R"__(^(=))__") },
        { TokenType::dot,            std::regex(R"__(^(\.))__") },
        { TokenType::ellipsis_2,     std::regex(R"__(^(\.\.))__") },
        { TokenType::ellipsis_3,     std::regex(R"__(^(\.\.\.))__") },
        { TokenType::colon,          std::regex(R"__(^(:))__") },
        { TokenType::double_colon,   std::regex(R"__(^(::))__") },
        { TokenType::comma,          std::regex(R"__(^(,))__") },
        { TokenType::semicolon,      std::regex(R"__(^(;))__") },
        { TokenType::dollar,         std::regex(R"__(^(\$))__") },
        { TokenType::then,           std::regex(R"__(^(=>))__") },

        // { TokenType::operation_sign, std::regex(R"__(^(\+|\-|/|%|\^|~|!|(\*\*?)|(&&?)|(\|\|?)|(<[<=]?)|(>[>=]?)|(!=)))__") },
        { TokenType::operation_sign, std::regex(R"__(^(\+|\-|/|%|~|!|\*\*?|&&?|\|\|?|\^\^?|<(=>?)?|>=?|==|!=))__") },

        { TokenType::open_round,     std::regex(R"__(^(\())__") },
        { TokenType::close_round,    std::regex(R"__(^(\)))__") },
        { TokenType::open_square,    std::regex(R"__(^(\[))__") },
        { TokenType::close_square,   std::regex(R"__(^(\]))__") },
        { TokenType::open_brace,     std::regex(R"__(^(\{))__") },
        { TokenType::close_brace,    std::regex(R"__(^(\}))__") },
    };

    // Keywords.
    const std::map<std::string, TokenType> Interpreter::keywords
    {
        { "do",         TokenType::keyword },
        { "if",         TokenType::keyword },
        { "else",       TokenType::keyword },
        { "loop",       TokenType::keyword },
        { "while",      TokenType::keyword },
        { "for",        TokenType::keyword },
        { "in",         TokenType::keyword },
        { "switch",     TokenType::keyword },
        { "case",       TokenType::keyword },
        { "default",    TokenType::keyword },
        { "break",      TokenType::keyword },

        { "var",        TokenType::keyword },
        { "delete",     TokenType::keyword },
        { "class",      TokenType::keyword },
        { "func",       TokenType::keyword },
        { "return",     TokenType::keyword },
        { "throw",      TokenType::keyword },

        { "null",       TokenType::null },
        { "false",      TokenType::boolean },
        { "true",       TokenType::boolean },
    };


    // Textual token synonyms.
    const std::map<std::string, std::string> Interpreter::synonyms
    {
        { "and",        "&&" },
        { "or",         "||" },
        { "xor",        "^^" },
        { "not",        "!" },
    };


    // `Interpreter` constructor.
    Interpreter::Interpreter()
    {

    }

    // Interpret a source file.
    // @param  path    Path to the source file.
    Expression* Interpreter::load_file(const std::string& path)
    {
        auto code = load(path);
        auto tokens = scan(code);

        std::cout << "Scanned tokens\n";
        for (auto& token : tokens) {
            std::string type_name = Token::type_names.at(token.type());
            type_name.resize(23, ' ');
            std::cout << path << ":" << token.line() << ":" << token.column() << "\t" << type_name << "\t" << token.text() << std::endl;
        }

        auto expressions = parse(tokens);

        return new ExprBlock(expressions);
    }

    std::string Interpreter::load(const std::string& path)
    {
        // open file
        std::ifstream file(path, std::ios::binary);

        if (file.fail())
        {
            throw Exception("Can't open source file");
        }

        // get length of file
        file.seekg(0, file.end);
        unsigned length = file.tellg();
        file.seekg(0, file.beg);

        // read whole file
        std::string code;
        code.resize(length, '\0');
        char& begin = *code.begin();

        file.read(&begin, length);
        if(file.fail())
        {
            file.close();
            throw Exception("Can't read source file");
        }

        // close file
        file.close();

        return code;
    }


    std::vector<Token> Interpreter::scan(const std::string& code)
    {
        std::vector<Token> tokens;

        // test every regex until source is deplected or an error occurs
        unsigned current_line = 1;
        unsigned current_column = 1;
        auto iter = code.cbegin();
        while (iter < code.cend())
        {
            std::vector<TokenType> matching_types;

            // matchs regexes
            unsigned largest = 0;
            for (auto& regex : token_regexes)
            {
                std::smatch match;
                if (std::regex_search(iter, code.cend(), match, regex.second))
                {
                    // reset when longer
                    if (largest < match.length())
                    {
                        largest = match.length();
                        matching_types.clear();
                        matching_types.push_back(regex.first);
                    }
                    // push when same length
                    else if (largest == match.length())
                    {
                        matching_types.push_back(regex.first);
                    }
                }
            }

            // check results
            if (matching_types.size() == 0) // no match
            {
                TokenType type = TokenType::unknown;
                std::string text = std::string(iter, iter+1);
                Token token(type, text, current_line, current_column);

                throw UnexpectedCharacter(token);
            }
            else
            {
                TokenType type = matching_types.front();
                std::string text = std::string(iter, iter+largest);

                // keyword replacement
                if (keywords.count(text))
                {
                    type = keywords.at(text);
                }

                Token token(type, text, current_line, current_column);

                // ambiguous token
                if (matching_types.size() > 1)
                {
                    throw AmbiguousToken(token, matching_types);
                }

                // meaningful token
                if (matching_types.front() != TokenType::space &&
                    matching_types.front() != TokenType::commentary) // one match
                {
                    tokens.push_back(token);
                }
            }

            // update line & column
            for(unsigned i = 0; i < largest; ++i)
            {
                char c = iter[i];
                if(c == '\n')
                {
                    current_line += 1;
                    current_column = 1;
                }
                else if(c >= ' ')
                {
                    current_column += 1;
                }
            }

            // update iterator
            iter += largest;
        }

        // add EOF token
        tokens.push_back(Token(TokenType::eof, "", current_line, current_column));

        return tokens;
    }


    std::vector<Expression*> Interpreter::parse(const std::vector<Token>& tokens)
    {
        std::vector<Expression*> expressions;

        // parse each token
        auto iter = tokens.cbegin();
        while (iter->type() != TokenType::eof)
        {
            // statement body
            if (auto e = parse_statement(iter))
            {
                expressions.push_back(e);
            }

            // optional semicolon at the end
            if (iter->type() != TokenType::eof)
            {
                if (iter->type() == TokenType::semicolon)
                {
                    iter += 1;
                }
                else
                {
                    throw UnexpectedToken(*iter, {TokenType::semicolon});
                }
            }
        }

        return expressions;
    }


    void Interpreter::check_not_eof(std::vector<Token>::const_iterator& iter)
    {
        if (iter->type() == TokenType::eof)
        {
            throw UnexpectedEof(*iter);
        }
    }


    void Interpreter::check_token_type(std::vector<Token>::const_iterator& iter,
                                       const std::set<TokenType>& accepted)
    {
        // check not EOF
        check_not_eof(iter);

        // check type
        if (accepted.count(iter->type()) == 0)
        {
            throw UnexpectedToken(*iter, accepted);
        }
    }


    Expression* Interpreter::parse_statement(std::vector<Token>::const_iterator& iter)
    {
        check_not_eof(iter);
        switch (iter->type())
        {
            case TokenType::unknown:            //< Unexpected character.
            {
                throw UnexpectedCharacter(*iter);
            }

            case TokenType::space:              //< Blank space (space, new line, etc.).
            case TokenType::commentary:         //< Commentary (sigle-line or multi-line).
            {
                iter += 1;
                return nullptr;
            }

            case TokenType::null:               //< Null literal.
            case TokenType::boolean:            //< Boolean literal.
            case TokenType::integer:            //< Integer number literal.
            case TokenType::floatnum:           //< Floating-point number literal.
            case TokenType::character:          //< Character literal.
            case TokenType::string:             //< String literal.
            case TokenType::identifier:         //< Variable name.
            case TokenType::dollar:             //< Dollar sign ($).
            case TokenType::operation_sign:     //< Arithmetic/bitwise/boolean operation sign (eg.: +, -, &, and).
            case TokenType::open_round:         //< Open round brackets or parentheses (().
            case TokenType::close_round:        //< Close round brackets or parentheses ()).
            case TokenType::keyword:            //< Identifier used as a keyword.
            {
                return parse_operation(iter);
            }

            case TokenType::open_square:        //< Open square brackets or crotchets ([).
            case TokenType::close_square:       //< Close square brackets or crotchets (]).
            case TokenType::open_brace:         //< Open curly brackets or braces ({).
            case TokenType::close_brace:        //< Close curly brackets or braces (}).
            case TokenType::assign:             //< Equal sign (=).
            case TokenType::dot:                //< Dot (.).
            case TokenType::ellipsis_2:         //< Two dots ellipsis (..).
            case TokenType::ellipsis_3:         //< Three dots ellipsis (...).
            case TokenType::colon:              //< Colon (:).
            case TokenType::double_colon:       //< Double colon (::).
            case TokenType::comma:              //< Comma (,).
            case TokenType::then:               //< Then arrow (=>).
            {
                throw UnexpectedCharacter(*iter);
            }

            case TokenType::semicolon:          //< Semicolon (;).
            {
                iter += 1;
                return nullptr;
            }

            default:
            {
                throw UnexpectedCharacter(*iter);
            }
        }
    }


    Expression* token_to_operartion(const InterpreterOperator& token, Expression* lhs, Expression* rhs)
    {
        std::string operator_string = token.string();

        if (operator_string == "**")        return new ExprExp(lhs, rhs);
        else if (operator_string == "*")    return new ExprMul(lhs, rhs);
        else if (operator_string == "/")    return new ExprDiv(lhs, rhs);
        else if (operator_string == "%")    return new ExprMod(lhs, rhs);
        else if (operator_string == "+")    return new ExprAdd(lhs, rhs);
        else if (operator_string == "-")    return new ExprSub(lhs, rhs);

        else if (operator_string == "<<")   return new ExprBitLeftShift(lhs, rhs);
        else if (operator_string == ">>")   return new ExprBitRightShift(lhs, rhs);

        else if (operator_string == "<=>")  return new ExprCmp(lhs, rhs);
        else if (operator_string == "<")    return new ExprLT(lhs, rhs);
        else if (operator_string == "<=")   return new ExprLE(lhs, rhs);
        else if (operator_string == ">")    return new ExprGT(lhs, rhs);
        else if (operator_string == ">=")   return new ExprGE(lhs, rhs);
        else if (operator_string == "==")   return new ExprEQ(lhs, rhs);
        else if (operator_string == "!=")   return new ExprNE(lhs, rhs);

        else if (operator_string == "&")    return new ExprBitAnd(lhs, rhs);
        else if (operator_string == "^")    return new ExprBitXor(lhs, rhs);
        else if (operator_string == "|")    return new ExprBitOr(lhs, rhs);

        else if (operator_string == "&&")   return new ExprBoolAnd(lhs, rhs);
        else if (operator_string == "||")   return new ExprBoolOr(lhs, rhs);
        else throw Undefined(std::string("Binary operator ") + operator_string);
    }

    Expression* Interpreter::parse_operation(std::vector<Token>::const_iterator& iter)
    {
        // a parameter followed by any number of operation signs and other parameter.

        std::vector<Expression*> param_stack;
        std::vector<InterpreterOperator> operator_stack;

        param_stack.push_back(parse_parameter(iter));

        while (iter->type() == TokenType::operation_sign)
        {
            // operator
            auto o = std::find_if(operators.begin(), operators.end(), [iter](const InterpreterOperator& o){ return o.string() == iter->text(); });
            if (o == operators.cend())
            {
                throw UnexpectedToken(*iter, {TokenType::operation_sign});
            }

            // pop operators with higher precedence
            while (!operator_stack.empty() &&
                   operator_stack.back().precedence() >= o->precedence())
            {
                auto rhs = param_stack.back();
                param_stack.pop_back();

                auto lhs = param_stack.back();
                param_stack.pop_back();

                param_stack.push_back(token_to_operartion(operator_stack.back(), lhs, rhs));
                operator_stack.pop_back();
            }

            // push
            operator_stack.push_back(*o);
            iter += 1;

            // rhs parameter
            param_stack.push_back(parse_parameter(iter));
        }

        // pop remaining operators
        while (!operator_stack.empty())
        {
            auto rhs = param_stack.back();
            param_stack.pop_back();

            auto lhs = param_stack.back();
            param_stack.pop_back();

            param_stack.push_back(token_to_operartion(operator_stack.back(), lhs, rhs));
            operator_stack.pop_back();
        }

        return param_stack.back();
    }


    Expression* Interpreter::parse_parameter(std::vector<Token>::const_iterator& iter)
    {
        Expression* e = nullptr;

        check_not_eof(iter);
        switch (iter->type())
        {
            case TokenType::null:               //< Null literal.
            {
                throw Unimplemented("null literal");
            }

            case TokenType::boolean:            //< Boolean literal.
            {
                Boolean::Value value = iter->boolean();
                iter += 1;
                e = new ExprBoolean(value);
                break;
            }

            case TokenType::integer:            //< Integer number literal.
            {
                Number::Value value = iter->integer();
                iter += 1;
                e = new ExprNumber(value);
                break;
            }

            case TokenType::floatnum:           //< Floating-point number literal.
            {
                Number::Value value = iter->floatnum();
                iter += 1;
                e = new ExprNumber(value);
                break;
            }

            case TokenType::character:          //< Character literal.
            {
                String::Value value = std::string(1, iter->character());
                iter += 1;
                e = new ExprString(value);
                break;
            }

            case TokenType::string:             //< String literal.
            {
                String::Value value = iter->string();
                iter += 1;
                e = new ExprString(value);
                break;
            }

            case TokenType::identifier:         //< Variable name.
            {
                VarName var_name = VarName::from_name(iter->identifier());
                iter += 1;

                if (iter->type() == TokenType::assign)
                {
                    iter += 1;

                    Expression* value = parse_operation(iter);

                    e = new ExprStoreVar(var_name, value);
                }
                else
                {
                    e = new ExprLoadVar(var_name);
                }
                break;
            }

            case TokenType::dollar:             //< Dollar sign ($).
            {
                iter += 1;

                check_token_type(iter, {TokenType::identifier});
                VarName var_name = VarName::from_name(iter->identifier());
                iter += 1;

                e = new ExprIdentifier(var_name);
                break;
            }

            case TokenType::operation_sign:     //< Arithmetic/bitwise/boolean operation sign (eg.: +, -, &, and).
            {
                // unary operations
                if (iter->text() == "+")
                {
                    iter += 1;
                    e = parse_parameter(iter);
                }
                else if (iter->text() == "-")
                {
                    iter += 1;
                    e = new ExprUnm(parse_parameter(iter));
                }
                else if (iter->text() == "~")
                {
                    iter += 1;
                    e = new ExprBitNot(parse_parameter(iter));
                }
                else if (iter->text() == "!")
                {
                    iter += 1;
                    e = new ExprBoolNot(parse_parameter(iter));
                }
                else
                {
                    throw UnexpectedToken(*iter, {TokenType::operation_sign});
                }
                break;
            }

            case TokenType::keyword:            //< Identifier used as a keyword.
            {
                if (iter->text() == "if")               e = parse_if_block(iter);
                else if (iter->text() == "do")          e = parse_do_block(iter);
                else if (iter->text() == "while")       e = parse_while_block(iter);
                else if (iter->text() == "for")         e = parse_for_block(iter);
                else if (iter->text() == "switch")      e = parse_switch_block(iter);
                else if (iter->text() == "try")         e = parse_try_block(iter);
                else if (iter->text() == "var")         e = parse_local_var(iter);
                else if (iter->text() == "func")        e = parse_function(iter);
                else if (iter->text() == "return")
                {
                    iter += 1;
                    e = new ExprReturn(parse_operation(iter));
                }
                else if (iter->text() == "throw")
                {
                    iter += 1;
                    e = new ExprThrow(parse_operation(iter));
                }
                else throw UnexpectedToken(*iter);
                break;
            }

            case TokenType::open_round:
            {
                iter += 1;

                e = parse_operation(iter);

                check_token_type(iter, {TokenType::close_round});
                iter += 1;

                break;
            }

            // TODO: add literal vector and map here:
            // case TokenType::open_square:        //< Open square brackets or crotchets ([).
            // case TokenType::close_square:       //< Close square brackets or crotchets (]).
            // case TokenType::open_brace:         //< Open curly brackets or braces ({).
            // case TokenType::close_brace:        //< Close curly brackets or braces (}).

            default:
            {
                throw UnexpectedCharacter(*iter);
            }
        }


        // check suffixes
        bool done = false;
        while (!done)
        {
            switch (iter->type())
            {
                case TokenType::double_colon:        //< Double colon (::).
                {
                    iter += 1;

                    check_token_type(iter, {TokenType::identifier});
                    Expression* index = new ExprIdentifier(VarName::from_name(iter->identifier()));

                    if (iter->type() == TokenType::assign)
                    {
                        iter += 1;

                        Expression* value = parse_operation(iter);

                        e = new ExprIndexSet(e, index, value);
                    }
                    else
                    {
                        e = new ExprIndexGet(e, index);
                    }

                    break;
                }

                case TokenType::open_round:          //< Open round brackets or parentheses (().
                {
                    iter += 1;

                    std::vector<Expression*> args;
                    Expression* vararg = nullptr;

                    check_not_eof(iter);
                    while (iter->type() != TokenType::close_round && !vararg)
                    {
                        // value
                        auto arg = parse_operation(iter);

                        // variadic
                        if (iter->type() == TokenType::ellipsis_3)
                        {
                            vararg = arg;
                            iter += 1;
                        }
                        else
                        {
                            args.push_back(arg);
                        }

                        // optional comma
                        if (iter->type() != TokenType::close_round)
                        {
                            if (iter->type() == TokenType::comma)
                            {
                                iter += 1;
                            }
                            else
                            {
                                throw UnexpectedToken(*iter);
                            }
                        }
                    }

                    check_token_type(iter, {TokenType::close_round});
                    iter += 1;

                    if (vararg)
                    {
                        e = new ExprVariadicCall(e, args, vararg);
                    }
                    else
                    {
                        e = new ExprCall(e, args);
                    }

                    break;
                }

                case TokenType::open_square:        //< Open square brackets or crotchets ([).
                {
                    iter += 1;

                    Expression* index = parse_operation(iter);

                    check_token_type(iter, {TokenType::close_square});
                    iter += 1;

                    if (iter->type() == TokenType::assign)
                    {
                        iter += 1;

                        Expression* value = parse_operation(iter);

                        e = new ExprIndexSet(e, index, value);
                    }
                    else
                    {
                        e = new ExprIndexGet(e, index);
                    }

                    break;
                }

                default:
                {
                    done = true;
                    break;
                }
            }
        }

        return e;
    }


    Expression* Interpreter::parse_block_body(std::vector<Token>::const_iterator& iter)
    {
        check_not_eof(iter);
        // TODO: token then
        // if (iter->type() == TokenType::then)
        // {
        //     iter += 1;
        //     return new ExprBlock({parse_operation(iter)});
        // }
        // else
        if (iter->type() == TokenType::open_brace)
        {
            iter += 1;

            std::vector<Expression*> expressions;
            while (iter->type() != TokenType::close_brace)
            {
                // statement body
                if (auto e = parse_statement(iter)) // may return null if commentary, etc.
                {
                    expressions.push_back(e);
                }

                // optional semicolon at the end
                if (iter->type() != TokenType::close_brace)
                {
                    if (iter->type() == TokenType::semicolon)
                    {
                        iter += 1;
                    }
                    else
                    {
                        throw UnexpectedToken(*iter, {TokenType::semicolon});
                    }
                }
            }

            check_token_type(iter, {TokenType::close_brace});
            iter += 1;

            return new ExprBlock(expressions);
        }
        else
        {
            throw UnexpectedToken(*iter, {TokenType::then, TokenType::open_brace});
        }
    }

    Expression* Interpreter::parse_do_block(std::vector<Token>::const_iterator& iter)
    {
        iter += 1;
        return parse_block_body(iter);
    }

    Expression* Interpreter::parse_if_block(std::vector<Token>::const_iterator& iter)
    {
        iter += 1;

        auto condition = parse_operation(iter);
        auto true_block = parse_block_body(iter);
        Expression* false_block = nullptr;

        if (iter->type() == TokenType::keyword &&
            iter->text() == "else")
        {
            iter += 1;

            if (iter->type() == TokenType::keyword &&
                iter->text() == "if")
            {
                false_block = parse_if_block(iter);
            }
            else
            {
                false_block = parse_block_body(iter);
            }
        }

        return new ExprIf(condition, true_block, false_block);
    }

    Expression* Interpreter::parse_loop_block(std::vector<Token>::const_iterator& iter)
    {
        iter += 1;
        return new ExprLoop(parse_block_body(iter));
    }

    Expression* Interpreter::parse_while_block(std::vector<Token>::const_iterator& iter)
    {
        iter += 1;

        auto condition = parse_operation(iter);
        auto body = parse_block_body(iter);

        return new ExprWhile(condition, body);
    }

    Expression* Interpreter::parse_for_block(std::vector<Token>::const_iterator& iter)
    {
        iter += 1;

        check_token_type(iter, {TokenType::identifier});
        auto var_name = VarName::from_name(iter->identifier());
        iter += 1;

        check_not_eof(iter);
        switch (iter->type())
        {
            case TokenType::assign:
            {
                iter += 1;

                auto initial_value = parse_operation(iter);

                check_token_type(iter, {TokenType::ellipsis_2});
                iter += 1;

                auto max_value = parse_operation(iter);

                Expression* step_value = nullptr;
                check_not_eof(iter);
                if (iter->type() == TokenType::comma)
                {
                    iter += 1;
                    step_value = parse_operation(iter);
                }
                else
                {
                    step_value = new ExprNumber(1);
                }

                auto body = parse_block_body(iter);

                return new ExprFor(var_name, initial_value, max_value, step_value, body);
            }

            case TokenType::keyword:
            {
                if (iter->text() == "in")
                {
                    iter += 1;

                    auto range = parse_operation(iter);
                    auto body = parse_block_body(iter);

                    return new ExprForIn(var_name, range, body);
                }
                else
                {
                    throw UnexpectedToken(*iter);
                }
                break;
            }

            default:
            {
                throw UnexpectedToken(*iter, {TokenType::assign, TokenType::keyword});
            }
        }

        throw Unimplemented("for blocks");
    }

    Expression* Interpreter::parse_switch_block(std::vector<Token>::const_iterator& iter)
    {
        throw Unimplemented("switch blocks");
    }

    Expression* Interpreter::parse_try_block(std::vector<Token>::const_iterator& iter)
    {
        iter += 1;

        auto try_body = parse_block_body(iter);

        check_token_type(iter, {TokenType::keyword});
        if (iter->text() != "catch")
        {
            throw UnexpectedToken(*iter);
        }
        iter += 1;

        auto catch_body = parse_block_body(iter);

        return new ExprTry(try_body, catch_body);
    }


    Expression* Interpreter::parse_local_var(std::vector<Token>::const_iterator& iter)
    {
        iter += 1;

        auto var_name = VarName::from_name(iter->identifier());
        iter += 1;

        check_token_type(iter, {TokenType::assign});
        iter += 1;

        auto value = parse_operation(iter);

        return new ExprLocalVar(var_name, value);
    }

    Expression* Interpreter::parse_function(std::vector<Token>::const_iterator& iter)
    {
        iter += 1;

        check_token_type(iter, {TokenType::open_round});
        iter += 1;

        bool is_variadic = false;

        // arg names
        std::vector<VarName> arg_names;
        while (iter->type() != TokenType::close_round && !is_variadic)
        {
            // name
            check_token_type(iter, {TokenType::identifier});
            arg_names.push_back(VarName::from_name(iter->identifier()));
            iter += 1;

            // variadic
            if (iter->type() == TokenType::ellipsis_3)
            {
                is_variadic = true;
                iter += 1;
            }

            // optional comma
            if (iter->type() != TokenType::close_round)
            {
                if (iter->type() == TokenType::comma)
                {
                    iter += 1;
                }
                else
                {
                    throw UnexpectedToken(*iter);
                }
            }
        }

        check_token_type(iter, {TokenType::close_round});
        iter += 1;

        // body
        Expression* body = parse_block_body(iter);

        return new ExprFunction(arg_names, is_variadic, body);
    }



    // `SyntaxError` constructor.
    // @param  token   Source code token where the exception happened.
    SyntaxError::SyntaxError(const Token& token) : m_token(token)
    {
        stream() << "Syntax error: ";
    }

    // Get the token that raised the exception.
    const Token& SyntaxError::token() const
    {
        return m_token;
    }

    // `AmbiguousToken` constructor.
    // @param  token   Source code token where the exception happened.
    // @param  types   List of types that the token matched.
    AmbiguousToken::AmbiguousToken(const Token& token, const std::vector<TokenType>& types) :
        SyntaxError(token),
        m_types(types)
    {
        stream() << "Ambiguous token could be ";
        int i = 0;
        for (auto& type : types)
        {
            if (i > 0) stream() << ", ";
            stream() << Token::type_names.at(type);
            i += 1;
        }
    }

    // Get types.
    const std::vector<TokenType>& AmbiguousToken::types() const
    {
        return m_types;
    }

    // `UnexpectedCharacter` constructor.
    // @param  token   Source code token where the exception happened.
    UnexpectedCharacter::UnexpectedCharacter(const Token& token) : SyntaxError(token)
    {
        stream() << "Unexpected character found `" << token.text() << "`";
    }

    // `UnexpectedToken` constructor.
    // @param  token       Source code token where the exception happened.
    UnexpectedToken::UnexpectedToken(const Token& token) : SyntaxError(token)
    {
        stream() << "Unexpected " << Token::type_names.at(token.type()) << " `" << token.text() << "`";
    }

    // `UnexpectedToken` constructor.
    // @param  token       Source code token where the exception happened.
    // @param  accepted    Set of token types that could be accepted.
    UnexpectedToken::UnexpectedToken(const Token& token, const std::set<TokenType>& accepted) :
        SyntaxError(token),
        m_accepted(accepted)
    {
        stream() << "Unexpected " << Token::type_names.at(token.type()) << " `" << token.text() << "`; expected ";
        int i = 0;
        for (auto& type : accepted)
        {
            if (i > 0)
            {
                stream() << "/";
            }
            stream() << Token::type_names.at(type);
            i += 1;
        }
    }

    // `UnexpectedEof` constructor.
    // @param  token   Source code token where the exception happened.
    UnexpectedEof::UnexpectedEof(const Token& token) : SyntaxError(token)
    {
        stream() << "Unexpected EOF";
    }
}
