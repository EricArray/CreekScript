#include <creek/VarName.hpp>

#include <creek/Exception.hpp>


namespace creek
{
    std::map<VarName::Name, VarName::Id> VarName::s_ids = { {"", 0} };

    std::vector<VarName::Name> VarName::s_names = {""};

    // @brief  `VarName` constructor.
    VarName::VarName() : m_id(0)
    {

    }

    VarName::VarName(Id id) : m_id(id)
    {

    }

    // @brief  `VarName` constructor.
    // @param  name    Name of the variable.
    VarName::VarName(const std::string& name) : VarName(VarName::from_name(name))
    {

    }

    // @brief  `VarName` constructor.
    // @param  name    Name of the variable.
    VarName::VarName(const char* name) : VarName(VarName::from_name(name))
    {

    }

    VarName::VarName(const VarName& other) : m_id(other.m_id)
    {

    }

    VarName::VarName(VarName&& other) : m_id(other.m_id)
    {

    }

    // Create a `VarName` from an id.
    // If the id is not register, throws an exception.
    VarName VarName::from_id(Id id)
    {
        if (id >= s_names.size())
        {
            throw Exception("VarName id not registered");
        }
        return VarName(id);
    }

    // @brief  Assignment.
    VarName& VarName::operator = (const VarName& other)
    {
        m_id = other.m_id;
    }


    // Create a `VarName` from a name.
    // If the name is not register, creates a new VarName.
    VarName VarName::from_name(const std::string& name)
    {
        auto it = s_ids.find(name);
        if (it == s_ids.end())
        {
            s_names.push_back(name);
            Id id = s_names.size() - 1;
            auto emplaceo = s_ids.emplace(name, id);
            it = emplaceo.first;
        }
        return VarName(it->second);
    }

    // Get the id.
    VarName::Id VarName::id() const
    {
        return m_id;
    }

    // Get the name.
    const VarName::Name& VarName::name() const
    {
        return s_names[m_id];
    }

    bool VarName::operator == (const VarName& other) const
    {
        return m_id == other.m_id;
    }

    bool VarName::operator != (const VarName& other) const
    {
        return m_id != other.m_id;
    }

    bool VarName::operator <  (const VarName& other) const
    {
        return m_id < other.m_id;
    }

    bool VarName::operator <= (const VarName& other) const
    {
        return m_id <= other.m_id;
    }

    bool VarName::operator >  (const VarName& other) const
    {
        return m_id > other.m_id;
    }

    bool VarName::operator >= (const VarName& other) const
    {
        return m_id >= other.m_id;
    }
}
