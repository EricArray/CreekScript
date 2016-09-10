#include <creek/Interpreter.hpp>

#include <fstream>
#include <iostream>
#include <string>

#include <creek/Expression.hpp>
#include <creek/Expression_Arithmetic.hpp>
#include <creek/Expression_BasicDataTypes.hpp>
#include <creek/Expression_Bitwise.hpp>
#include <creek/Expression_Boolean.hpp>
#include <creek/Expression_ControlFlow.hpp>
#include <creek/Expression_Debug.hpp>
#include <creek/Expression_General.hpp>
#include <creek/Expression_Variable.hpp>
#include <creek/utility.hpp>


namespace creek
{
    // find correct std::stoi function
    template<class T> T stoi(const std::string& source, std::size_t* pos, int base);

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

    // find correct std::stof function
    template<class T> T stof(const std::string& source, std::size_t* pos);

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



    // Token type names.
    const std::map<InterpreterTokenType, std::string> InterpreterToken::type_names
    {
        { InterpreterTokenType::unknown,        "unknown" },                    //< Unexpected character.

        { InterpreterTokenType::space,          "space" },                      //< Blank space (space, new line, etc.).
        { InterpreterTokenType::commentary,     "commentary" },                 //< Commentary (sigle-line or multi-line).

        { InterpreterTokenType::null,           "null literal" },               //< Null literal.
        { InterpreterTokenType::boolean,        "boolean literal" },            //< Boolean literal.
        { InterpreterTokenType::integer,        "integer literal" },            //< Integer number literal.
        { InterpreterTokenType::floatnum,       "floating-point literal" },     //< Floating-point number literal.
        { InterpreterTokenType::character,      "character literal" },          //< Character literal.
        { InterpreterTokenType::string,         "string literal" },             //< String literal.

        { InterpreterTokenType::identifier,     "identifier" },                 //< Variable name.

        { InterpreterTokenType::assign,         "equal sign" },                 //< Equal sign (=).
        { InterpreterTokenType::dot,            "dot" },                        //< Dota (.).
        { InterpreterTokenType::colon,          "colon" },                      //< Colon (:).
        { InterpreterTokenType::double_colon,   "double colon" },               //< Double colon (::).
        { InterpreterTokenType::comma,          "comma" },                      //< Comma (,).
        { InterpreterTokenType::semicolon,      "semicolon" },                  //< Semicolon (;).
        { InterpreterTokenType::dollar,         "dollar" },                     //< Dollar sign ($).
        { InterpreterTokenType::then,           "then" },                       ///< Then arrow (=>).
        { InterpreterTokenType::operation_sign, "operation sign" },             //< Arithmetic/bitwise/boolean operation sign (eg.: +, -, &, and).

        { InterpreterTokenType::open_round,     "open parentheses" },           //< Open round brackets or parentheses (().
        { InterpreterTokenType::close_round,    "close parentheses" },          //< Close round brackets or parentheses ()).
        { InterpreterTokenType::open_square,    "open square brackets" },       //< Open square brackets or crotchets ([).
        { InterpreterTokenType::close_square,   "close square brackets" },      //< Close square brackets or crotchets (]).
        { InterpreterTokenType::open_brace,     "open brace" },                 //< Open curly brackets or braces ({).
        { InterpreterTokenType::close_brace,    "close brace" },                //< Close curly brackets or braces (}).

        { InterpreterTokenType::keyword,        "keyword" },                    //< Identifier used as a keyword.
    };

    // `InterpreterToken` constructor.
    // @param  type    Token type.
    // @param  text    Token text.
    // @param  line    Line where token was extracted.
    // @param  column  Column where token was extracted.
    InterpreterToken::InterpreterToken(InterpreterTokenType type, const std::string& text, int line, int column) :
        m_type(type),
        m_text(text),
        m_line(line),
        m_column(column)
    {

    }

    // `InterpreterToken` copy constructor.
    InterpreterToken::InterpreterToken(const InterpreterToken& other) :
        m_type(other.m_type),
        m_text(other.m_text),
        m_line(other.m_line),
        m_column(other.m_column)
    {

    }

    // `InterpreterToken` move constructor.
    InterpreterToken::InterpreterToken(InterpreterToken&& other) :
        m_type(other.m_type),
        m_text(other.m_text),
        m_line(other.m_line),
        m_column(other.m_column)
    {

    }

    // Get type.
    InterpreterTokenType InterpreterToken::type() const
    {
        return m_type;
    }

    // Get text.
    const std::string& InterpreterToken::text() const
    {
        return m_text;
    }

    // Get line.
    int InterpreterToken::line() const
    {
        return m_line;
    }

    // Get column.
    int InterpreterToken::column() const
    {
        return m_column;
    }


    // @name   Text translation
    // @{

    // Get the identifier this token represents.
    std::string InterpreterToken::identifier() const
    {
        return m_text;
    }

    // Get the boolean this token represents.
    bool InterpreterToken::boolean() const
    {
        if(text() == "true")
            return true;
        else
            return false;
    }

    // Get the integer this token represents.
    int InterpreterToken::integer() const
    {
        std::size_t pos = 0;
        int result = 0;

        try
        {
            if(text()[0] == '0' && (text()[1] == 'b' || text()[1] == 'B'))
            {
                result = stoi<int>(text(), &pos, 2);
            }
            else if(text()[0] == '0' && (text()[1] == 'x' || text()[1] == 'X'))
            {
                result = stoi<int>(text(), &pos, 16);
            }
            else
            {
                result = stoi<int>(text(), &pos, 10);
            }
        }
        catch(const std::invalid_argument& e)
        {
            throw BadNumberFormat(*this);
        }
        catch(const std::out_of_range& e)
        {
            throw BadNumberFormat(*this);
        }

        if(pos != text().size())
        {
            throw BadNumberFormat(*this);
        }

        return result;
    }

    // Get the floating-point number this token represents.
    float InterpreterToken::floatnum() const
    {
        std::size_t pos = 0;
        float result = 0;

        try
        {
            result = stof<float>(text(), &pos);
        }
        catch (const std::invalid_argument& e)
        {
            throw BadNumberFormat(*this);
        }
        catch (const std::out_of_range& e)
        {
            throw BadNumberFormat(*this);
        }

        if(pos != text().size())
        {
            throw BadNumberFormat(*this);
        }

        return result;
    }

    // Get the character this token represents.
    char InterpreterToken::character() const
    {
        return unescape_char(text(), 1);
    }

    // Get the string this token represents.
    std::string InterpreterToken::string() const
    {
        return unescape_string(text().substr(1, text().size() - 2));
    }

    // @}




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
        InterpreterOperator("**", 11),

        InterpreterOperator("*", 10),
        InterpreterOperator("/", 10),
        InterpreterOperator("%", 10),

        InterpreterOperator("+", 9),
        InterpreterOperator("-", 9),

        InterpreterOperator("<<", 8),
        InterpreterOperator(">>", 8),

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
    const std::map<InterpreterTokenType, std::regex> Interpreter::token_regexes
    {
        { InterpreterTokenType::space,          std::regex(R"__(^(\s+))__") },

        { InterpreterTokenType::commentary,     std::regex(R"__(^(//[^\n]*))__") },

        // { InterpreterTokenType::boolean,        std::regex(R"(true|false)") },
        // { InterpreterTokenType::integer,        std::regex(R"__(^(0[bB][01]+|0[xX][0-9a-fA-F]+|[0-9]+))__") },
        { InterpreterTokenType::integer,        std::regex(R"__(^([0-9]+))__") },
        { InterpreterTokenType::floatnum,       std::regex(R"__(^((0[xX][0-9a-fA-F]+\.[0-9a-fA-F]+)|([0-9]+\.[0-9]+)))__") },
        { InterpreterTokenType::character,      std::regex(R"__(^('([^'\\]|\\.)'))__") },
        { InterpreterTokenType::string,         std::regex(R"__(^("([^"\\]|\\.)*"))__") },

        { InterpreterTokenType::identifier,     std::regex(R"__(^([_a-zA-Z][_a-zA-Z0-9]*))__") },
        { InterpreterTokenType::assign,         std::regex(R"__(^(=))__") },
        { InterpreterTokenType::dot,            std::regex(R"__(^(\.))__") },
        { InterpreterTokenType::colon,          std::regex(R"__(^(:))__") },
        { InterpreterTokenType::double_colon,   std::regex(R"__(^(::))__") },
        { InterpreterTokenType::comma,          std::regex(R"__(^(,))__") },
        { InterpreterTokenType::semicolon,      std::regex(R"__(^(;))__") },
        { InterpreterTokenType::dollar,         std::regex(R"__(^(\$))__") },
        { InterpreterTokenType::then,           std::regex(R"__(^(=>))__") },

        { InterpreterTokenType::operation_sign, std::regex(R"__(^(\+|\-|/|%|\^|~|!|(\*\*?)|(&&?)|(\|\|?)|(<[<=]?)|(>[>=]?)|(!=)))__") },

        { InterpreterTokenType::open_round,     std::regex(R"__(^(\())__") },
        { InterpreterTokenType::close_round,    std::regex(R"__(^(\)))__") },
        { InterpreterTokenType::open_square,    std::regex(R"__(^(\[))__") },
        { InterpreterTokenType::close_square,   std::regex(R"__(^(\]))__") },
        { InterpreterTokenType::open_brace,     std::regex(R"__(^(\{))__") },
        { InterpreterTokenType::close_brace,    std::regex(R"__(^(\}))__") },
    };

    // Keywords.
    const std::map<std::string, InterpreterTokenType> Interpreter::keywords
    {
        { "do",         InterpreterTokenType::keyword },
        { "if",         InterpreterTokenType::keyword },
        { "else",       InterpreterTokenType::keyword },
        { "loop",       InterpreterTokenType::keyword },
        { "while",      InterpreterTokenType::keyword },
        { "for",        InterpreterTokenType::keyword },
        { "in",         InterpreterTokenType::keyword },
        { "switch",     InterpreterTokenType::keyword },
        { "case",       InterpreterTokenType::keyword },
        { "default",    InterpreterTokenType::keyword },
        { "break",      InterpreterTokenType::keyword },

        { "var",        InterpreterTokenType::keyword },
        { "delete",     InterpreterTokenType::keyword },
        { "class",      InterpreterTokenType::keyword },
        { "function",   InterpreterTokenType::keyword },
        { "return",     InterpreterTokenType::keyword },

        { "null",       InterpreterTokenType::null },
        { "false",      InterpreterTokenType::boolean },
        { "true",       InterpreterTokenType::boolean },

        { "and",        InterpreterTokenType::operation_sign },
        { "or",         InterpreterTokenType::operation_sign },
        { "not",        InterpreterTokenType::operation_sign },
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
            std::string type_name = InterpreterToken::type_names.at(token.type());
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


    std::vector<InterpreterToken> Interpreter::scan(const std::string& code)
    {
        std::vector<InterpreterToken> tokens;

        // test every regex until source is deplected or an error occurs
        unsigned current_line = 1;
        unsigned current_column = 1;
        auto iter = code.cbegin();
        while (iter < code.cend())
        {
            std::vector<InterpreterTokenType> matching_types;

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
                InterpreterTokenType type = InterpreterTokenType::unknown;
                std::string text = std::string(iter, iter+1);
                InterpreterToken token(type, text, current_line, current_column);

                throw UnexpectedCharacter(token);
            }
            else
            {
                InterpreterTokenType type = matching_types.front();
                std::string text = std::string(iter, iter+largest);

                // keyword replacement
                if (keywords.count(text))
                {
                    type = keywords.at(text);
                }

                InterpreterToken token(type, text, current_line, current_column);

                // ambiguous token
                if (matching_types.size() > 1)
                {
                    throw AmbiguousToken(token, matching_types);
                }

                // meaningful token
                if (matching_types.front() != InterpreterTokenType::space &&
                    matching_types.front() != InterpreterTokenType::commentary) // one match
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

        return tokens;
    }


    std::vector<Expression*> Interpreter::parse(const std::vector<InterpreterToken>& tokens)
    {
        std::vector<Expression*> expressions;

        // parse each token
        auto iter = tokens.cbegin();
        while (iter < tokens.cend())
        {
            // statement body
            if (auto e = parse_statement(tokens, iter))
            {
                expressions.push_back(e);
            }

            // optional semicolon at the end
            if (iter < tokens.cend())
            {
                if (iter->type() == InterpreterTokenType::semicolon)
                {
                    iter += 1;
                }
                else
                {
                    throw UnexpectedToken(*iter, {InterpreterTokenType::semicolon});
                }
            }
        }

        return expressions;
    }


    void Interpreter::check_not_eof(const std::vector<InterpreterToken>& tokens, std::vector<InterpreterToken>::const_iterator& iter)
    {
        if (iter >= tokens.cend())
        {
            if (iter - 1 < tokens.cend())
            {
                throw UnexpectedEof(iter[-1]);
            }
            else
            {
                throw UnexpectedEof(InterpreterToken(InterpreterTokenType::unknown, "", 1, 1));
            }
        }
    }


    void Interpreter::check_token_type(const std::vector<InterpreterToken>& tokens, std::vector<InterpreterToken>::const_iterator& iter,
                                       const std::set<InterpreterTokenType>& accepted)
    {
        // check not EOF
        check_not_eof(tokens, iter);

        // check type
        if (accepted.count(iter->type()) == 0)
        {
            throw UnexpectedToken(*iter, accepted);
        }
    }


    Expression* Interpreter::parse_statement(const std::vector<InterpreterToken>& tokens, std::vector<InterpreterToken>::const_iterator& iter)
    {
        check_not_eof(tokens, iter);
        switch (iter->type())
        {
            case InterpreterTokenType::unknown:            //< Unexpected character.
            {
                throw UnexpectedCharacter(*iter);
            }

            case InterpreterTokenType::space:              //< Blank space (space, new line, etc.).
            case InterpreterTokenType::commentary:         //< Commentary (sigle-line or multi-line).
            {
                iter += 1;
                return nullptr;
            }

            case InterpreterTokenType::null:               //< Null literal.
            case InterpreterTokenType::boolean:            //< Boolean literal.
            case InterpreterTokenType::integer:            //< Integer number literal.
            case InterpreterTokenType::floatnum:           //< Floating-point number literal.
            case InterpreterTokenType::character:          //< Character literal.
            case InterpreterTokenType::string:             //< String literal.
            case InterpreterTokenType::identifier:         //< Variable name.
            case InterpreterTokenType::dollar:             //< Dollar sign ($).
            case InterpreterTokenType::operation_sign:     //< Arithmetic/bitwise/boolean operation sign (eg.: +, -, &, and).
            case InterpreterTokenType::open_round:         //< Open round brackets or parentheses (().
            case InterpreterTokenType::close_round:        //< Close round brackets or parentheses ()).
            case InterpreterTokenType::keyword:            //< Identifier used as a keyword.
            {
                return parse_operation(tokens, iter);
            }

            case InterpreterTokenType::open_square:        //< Open square brackets or crotchets ([).
            case InterpreterTokenType::close_square:       //< Close square brackets or crotchets (]).
            case InterpreterTokenType::open_brace:         //< Open curly brackets or braces ({).
            case InterpreterTokenType::close_brace:        //< Close curly brackets or braces (}).
            case InterpreterTokenType::assign:             //< Equal sign (=).
            case InterpreterTokenType::dot:                //< Dota (.).
            case InterpreterTokenType::colon:              //< Colon (:).
            case InterpreterTokenType::double_colon:       //< Double colon (::).
            case InterpreterTokenType::comma:              //< Comma (,).
            case InterpreterTokenType::then:               //< Then arrow (=>).
            {
                throw UnexpectedCharacter(*iter);
            }

            case InterpreterTokenType::semicolon:          //< Semicolon (;).
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
//        else if (operator_string == "<")    return new ExprLt(lhs, rhs);
//        else if (operator_string == "<=")   return new ExprLe(lhs, rhs);
//        else if (operator_string == ">")    return new ExprGt(lhs, rhs);
//        else if (operator_string == ">=")   return new ExprGe(lhs, rhs);
//        else if (operator_string == "==")   return new ExprEq(lhs, rhs);
//        else if (operator_string == "!=")   return new ExprNe(lhs, rhs);
        else if (operator_string == "&")    return new ExprBitAnd(lhs, rhs);
        else if (operator_string == "^")    return new ExprBitXor(lhs, rhs);
        else if (operator_string == "|")    return new ExprBitOr(lhs, rhs);
        else if (operator_string == "&&")   return new ExprBoolAnd(lhs, rhs);
        else if (operator_string == "||")   return new ExprBoolOr(lhs, rhs);
        else throw Undefined(std::string("Binary operator ") + operator_string);
    }

    Expression* Interpreter::parse_operation(const std::vector<InterpreterToken>& tokens, std::vector<InterpreterToken>::const_iterator& iter)
    {
        // a parameter followed by any number of operation signs and other parameter.

        std::vector<Expression*> param_stack;
        std::vector<InterpreterOperator> operator_stack;

        param_stack.push_back(parse_parameter(tokens, iter));

        while (iter < tokens.cend() &&
               iter->type() == InterpreterTokenType::operation_sign)
        {
            // operator
            auto o = std::find_if(operators.begin(), operators.end(), [iter](const InterpreterOperator& o){ return o.string() == iter->text(); });
            if (o == operators.cend())
            {
                throw UnexpectedToken(*iter, {InterpreterTokenType::operation_sign});
            }

            while (operator_stack.size() > 1 &&
                   operator_stack.back().precedence() >= o->precedence())
            {
                auto rhs = param_stack.back();
                param_stack.pop_back();

                auto lhs = param_stack.back();
                param_stack.pop_back();

                param_stack.push_back(token_to_operartion(operator_stack.back(), lhs, rhs));
                operator_stack.pop_back();
            }
            operator_stack.push_back(*o);
            iter += 1;

            // rhs parameter
            param_stack.push_back(parse_parameter(tokens, iter));
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


    Expression* Interpreter::parse_parameter(const std::vector<InterpreterToken>& tokens, std::vector<InterpreterToken>::const_iterator& iter)
    {
        Expression* e = nullptr;

        check_not_eof(tokens, iter);
        switch (iter->type())
        {
            case InterpreterTokenType::null:               //< Null literal.
            {
                throw Undefined("null literal");
            }

            case InterpreterTokenType::boolean:            //< Boolean literal.
            {
                Boolean::Value value = iter->boolean();
                iter += 1;
                e = new ExprBoolean(value);
                break;
            }

            case InterpreterTokenType::integer:            //< Integer number literal.
            {
                Number::Value value = iter->integer();
                iter += 1;
                e = new ExprNumber(value);
                break;
            }

            case InterpreterTokenType::floatnum:           //< Floating-point number literal.
            {
                Number::Value value = iter->floatnum();
                iter += 1;
                e = new ExprNumber(value);
                break;
            }

            case InterpreterTokenType::character:          //< Character literal.
            {
                String::Value value = std::string(1, iter->character());
                iter += 1;
                e = new ExprString(value);
                break;
            }

            case InterpreterTokenType::string:             //< String literal.
            {
                String::Value value = iter->string();
                iter += 1;
                e = new ExprString(value);
                break;
            }

            case InterpreterTokenType::identifier:         //< Variable name.
            {
                VarName var_name = VarName::from_name(iter->identifier());
                iter += 1;

                if (iter < tokens.cend() && iter->type() == InterpreterTokenType::assign)
                {
                    iter += 1;

                    Expression* value = parse_operation(tokens, iter);

                    e = new ExprStoreVar(var_name, value);
                }
                else
                {
                    e = new ExprLoadVar(var_name);
                }
                break;
            }

            case InterpreterTokenType::dollar:             //< Dollar sign ($).
            {
                iter += 1;

                check_token_type(tokens, iter, {InterpreterTokenType::identifier});
                VarName var_name = VarName::from_name(iter->identifier());
                iter += 1;

                e = new ExprIdentifier(var_name);
                break;
            }

            case InterpreterTokenType::operation_sign:     //< Arithmetic/bitwise/boolean operation sign (eg.: +, -, &, and).
            {
                // unary operations
                if (iter->text() == "+")
                {
                    iter += 1;
                    e = parse_parameter(tokens, iter);
                }
                else if (iter->text() == "-")
                {
                    iter += 1;
                    e = new ExprUnm(parse_parameter(tokens, iter));
                }
                else if (iter->text() == "~")
                {
                    iter += 1;
                    e = new ExprBitNot(parse_parameter(tokens, iter));
                }
                else if (iter->text() == "!")
                {
                    iter += 1;
                    e = new ExprBoolNot(parse_parameter(tokens, iter));
                }
                else
                {
                    throw UnexpectedToken(*iter, {InterpreterTokenType::operation_sign});
                }
                break;
            }

            case InterpreterTokenType::keyword:            //< Identifier used as a keyword.
            {
                if (iter->text() == "if")               e = parse_if_block(tokens, iter);
                else if (iter->text() == "do")          e = parse_do_block(tokens, iter);
                else if (iter->text() == "while")       e = parse_while_block(tokens, iter);
                else if (iter->text() == "for")         e = parse_for_block(tokens, iter);
                else if (iter->text() == "switch")      e = parse_switch_block(tokens, iter);
                else if (iter->text() == "var")         e = parse_local_var(tokens, iter);
                else if (iter->text() == "function")    e = parse_lambda(tokens, iter);
                else throw UnexpectedToken(*iter, {InterpreterTokenType::keyword});
                break;
            }

            case InterpreterTokenType::open_round:
            {
                iter += 1;

                e = parse_operation(tokens, iter);

                check_token_type(tokens, iter, {InterpreterTokenType::close_round});
                iter += 1;

                break;
            }

            // TODO: add literal vector and map here:
            // case InterpreterTokenType::open_square:        //< Open square brackets or crotchets ([).
            // case InterpreterTokenType::close_square:       //< Close square brackets or crotchets (]).
            // case InterpreterTokenType::open_brace:         //< Open curly brackets or braces ({).
            // case InterpreterTokenType::close_brace:        //< Close curly brackets or braces (}).

            default:
            {
                throw UnexpectedCharacter(*iter);
            }
        }


        // check suffixes
        bool done = false;
        while (iter < tokens.cend() && !done)
        {
            switch (iter->type())
            {
                case InterpreterTokenType::double_colon:        //< Double colon (::).
                {
                    iter += 1;

                    check_token_type(tokens, iter, {InterpreterTokenType::identifier});
                    Expression* index = new ExprIdentifier(VarName::from_name(iter->identifier()));

                    if (iter < tokens.cend() && iter->type() == InterpreterTokenType::assign)
                    {
                        iter += 1;

                        Expression* value = parse_operation(tokens, iter);

                        e = new ExprIndexSet(e, index, value);
                    }
                    else
                    {
                        e = new ExprIndexGet(e, index);
                    }

                    break;
                }

                case InterpreterTokenType::open_round:          //< Open round brackets or parentheses (().
                {
                    iter += 1;

                    std::vector<Expression*> args;
                    // TODO: function call arguments

                    check_token_type(tokens, iter, {InterpreterTokenType::close_round});
                    iter += 1;

                    e = new ExprCall(e, args);

                    break;
                }

                case InterpreterTokenType::open_square:        //< Open square brackets or crotchets ([).
                {
                    iter += 1;

                    Expression* index = parse_operation(tokens, iter);

                    check_token_type(tokens, iter, {InterpreterTokenType::close_square});
                    iter += 1;

                    if (iter < tokens.cend() && iter->type() == InterpreterTokenType::assign)
                    {
                        iter += 1;

                        Expression* value = parse_operation(tokens, iter);

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


Expression* Interpreter::parse_block_body(const std::vector<InterpreterToken>& tokens, std::vector<InterpreterToken>::const_iterator& iter)
{
    if (iter->type() == InterpreterTokenType::then)
    {
        iter += 1;
        return parse_operation(tokens, iter);
    }
    else if (iter->type() == InterpreterTokenType::open_brace)
    {
        iter += 1;

        std::vector<Expression*> expressions;
        while (iter < tokens.cend() &&
               iter->type() != InterpreterTokenType::close_brace)
        {
            // statement body
            if (auto e = parse_statement(tokens, iter)) // may return null if commentary, etc.
            {
                expressions.push_back(e);
            }

            // optional semicolon at the end
            if (iter < tokens.cend() &&
                iter->type() != InterpreterTokenType::close_brace)
            {
                if (iter->type() == InterpreterTokenType::semicolon)
                {
                    iter += 1;
                }
                else
                {
                    throw UnexpectedToken(*iter, {InterpreterTokenType::semicolon});
                }
            }
        }

        check_token_type(tokens, iter, {InterpreterTokenType::close_brace});
        iter += 1;

        return new ExprBlock(expressions);
    }
    else
    {
        throw UnexpectedToken(*iter, {InterpreterTokenType::then, InterpreterTokenType::open_brace});
    }
}

Expression* Interpreter::parse_do_block(const std::vector<InterpreterToken>& tokens, std::vector<InterpreterToken>::const_iterator& iter)
{
    iter += 1;
    return parse_block_body(tokens, iter);
}

Expression* Interpreter::parse_if_block(const std::vector<InterpreterToken>& tokens, std::vector<InterpreterToken>::const_iterator& iter)
{
    iter += 1;

    auto condition = parse_operation(tokens, iter);
    auto true_block = parse_block_body(tokens, iter);
    Expression* false_block = nullptr;

    if (iter < tokens.cend())
    {
        if (iter->type() == InterpreterTokenType::keyword &&
            iter->text() == "else")
        {
            iter += 1;

            if (iter < tokens.cend())
            {
                if (iter->type() == InterpreterTokenType::keyword &&
                    iter->text() == "if")
                {
                    false_block = parse_if_block(tokens, iter);
                }
                else
                {
                    false_block = parse_block_body(tokens, iter);
                }
            }
            else
            {
                throw UnexpectedEof(iter[-1]);
            }
        }
    }

    return new ExprIf(condition, true_block, false_block);
}

Expression* Interpreter::parse_loop_block(const std::vector<InterpreterToken>& tokens, std::vector<InterpreterToken>::const_iterator& iter)
{
    iter += 1;
    return new ExprLoop(parse_block_body(tokens, iter));
}

Expression* Interpreter::parse_while_block(const std::vector<InterpreterToken>& tokens, std::vector<InterpreterToken>::const_iterator& iter)
{
    iter += 1;

    auto condition = parse_operation(tokens, iter);
    auto body = parse_block_body(tokens, iter);

    return new ExprWhile(condition, body);
}

Expression* Interpreter::parse_for_block(const std::vector<InterpreterToken>& tokens, std::vector<InterpreterToken>::const_iterator& iter)
{
    throw Unimplemented("for blocks");
}

Expression* Interpreter::parse_switch_block(const std::vector<InterpreterToken>& tokens, std::vector<InterpreterToken>::const_iterator& iter)
{
    throw Unimplemented("switch blocks");
}

Expression* Interpreter::parse_local_var(const std::vector<InterpreterToken>& tokens, std::vector<InterpreterToken>::const_iterator& iter)
{
    iter += 1;

    auto var_name = VarName::from_name(iter->identifier());
    iter += 1;

    check_token_type(tokens, iter, {InterpreterTokenType::assign});
    iter += 1;

    auto value = parse_operation(tokens, iter);

    return new ExprLocalVar(var_name, value);
}

Expression* Interpreter::parse_lambda(const std::vector<InterpreterToken>& tokens, std::vector<InterpreterToken>::const_iterator& iter)
{
    throw Unimplemented("switch blocks");
}



    // `SyntaxError` constructor.
    // @param  token   Source code token where the exception happened.
    SyntaxError::SyntaxError(const InterpreterToken& token) : m_token(token)
    {
        stream() << "Syntax error: ";
    }

    // Get the token that raised the exception.
    const InterpreterToken& SyntaxError::token() const
    {
        return m_token;
    }

    // `BadNumberFormat` constructor.
    // @param  token   Source code token where the exception happened.
    BadNumberFormat::BadNumberFormat(const InterpreterToken& token) : SyntaxError(token)
    {
        stream() << "Bad number format";
    }

    // `AmbiguousToken` constructor.
    // @param  token   Source code token where the exception happened.
    // @param  types   List of types that the token matched.
    AmbiguousToken::AmbiguousToken(const InterpreterToken& token, const std::vector<InterpreterTokenType>& types) :
        SyntaxError(token),
        m_types(types)
    {
        stream() << "Ambiguous token could be ";
        int i = 0;
        for (auto& type : types)
        {
            if (i > 0) stream() << ", ";
            stream() << InterpreterToken::type_names.at(type);
            i += 1;
        }
    }

    // Get types.
    const std::vector<InterpreterTokenType>& AmbiguousToken::types() const
    {
        return m_types;
    }

    // `UnexpectedCharacter` constructor.
    // @param  token   Source code token where the exception happened.
    UnexpectedCharacter::UnexpectedCharacter(const InterpreterToken& token) : SyntaxError(token)
    {
        stream() << "Unexpected character found `" << token.text() << "`";
    }

    /// `UnexpectedToken` constructor.
    /// @param  token       Source code token where the exception happened.
    /// @param  accepted    Set of token types that could be accepted.
    UnexpectedToken::UnexpectedToken(const InterpreterToken& token, const std::set<InterpreterTokenType>& accepted) :
        SyntaxError(token),
        m_accepted(accepted)
    {
        stream() << "Unexpected token `" << token.text() << "`; expected ";
        int i = 0;
        for (auto& type : accepted)
        {
            if (i > 0)
            {
                stream() << ", ";
            }
            stream() << InterpreterToken::type_names.at(type);
            i += 1;
        }
    }

    // `UnexpectedEof` constructor.
    // @param  token   Source code token where the exception happened.
    UnexpectedEof::UnexpectedEof(const InterpreterToken& token) : SyntaxError(token)
    {
        stream() << "Unexpected EOF";
    }
}
