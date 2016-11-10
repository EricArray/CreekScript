#include <creek/Map.hpp>

#include <sstream>

#include <creek/Expression_DataTypes.hpp>
#include <creek/GlobalScope.hpp>


namespace creek
{
    // @brief  `Map` constructor.
    // @param  value   Map value.
    Map::Map(const Value& value) : m_value(value)
    {

    }

    /// @brief  Get shared value.
    const Map::Value& Map::value() const
    {
        return m_value;
    }

    Data* Map::copy() const
    {
        return new Map(m_value);
    }

    std::string Map::class_name() const
    {
        return "Map";
    }

    std::string Map::debug_text() const
    {
        // return "{" + each key&item debug text + "}"
        std::stringstream stream;
        stream << "{";
        bool i = 0;
        for (auto& pair : *m_value)
        {
            if (i > 0)
            {
                stream << ", ";
            }
            stream << pair.first->debug_text();
            stream << ": ";
            stream << pair.second->debug_text();
            i += 1;
        }
        stream << "}";
        return stream.str();
    }

    Expression* Map::to_expression() const
    {
        std::vector<ExprMap::Pair> pairs;
        for (auto& v : *m_value)
        {
            pairs.emplace_back(v.first->to_expression(), v.second->to_expression());
        }
        return new ExprMap(pairs);
    }


    bool Map::bool_value() const
    {
        return true;
    }

    // // Get the vector value of this data.
    // std::vector<Variable>& Map::vector_value() const
    // {
    //     return *m_value;
    // }



    Data* Map::index(Data* key)
    {
        auto iter = m_value->find(Key(key->copy()));
        if (iter == m_value->end())
        {
            auto key_text = key->debug_text();
            throw Exception(std::string("Key not found: ") + key_text);
        }
        return iter->second->copy();
    }

    Data* Map::index(Data* key, Data* new_value)
    {
        (*m_value)[Key(key->copy())] = Variable(new_value->copy());
        return new_value;
    }

    Data* Map::attr(VarName key)
    {
        Variable i = new Identifier(key);
        return index(*i);
    }

    Data* Map::attr(VarName key, Data* new_value)
    {
        Variable i = new Identifier(key);
        return index(*i, new_value);
    }


    // int Map::cmp(Data* other)
    // {
    //     if (Map* other_as_map = dynamic_cast<Map*>(other))
    //     {

    //     }
    //     else
    //     {
    //         return Data::cmp(other);
    //     }
    // }

    Data* Map::get_class() const
    {
        return GlobalScope::class_Map->copy();
    }
}
