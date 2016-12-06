#include <creek/VarNameMap.hpp>

#include <creek/Exception.hpp>


namespace creek
{
    /// @brief  Get an ID from a name.
    VarName::Id VarNameMap::id_from_name(const VarName::Name& name)
    {
        auto iter = m_id_from_name.find(name);
        if (iter == m_id_from_name.end())
        {
            VarName::Id new_id(m_id_from_name.size());
            register_name(new_id, name);
            return new_id;
        }
        else
        {
            return iter->second;
        }
    }

    /// @brief  Get a name from an ID.
    const VarName::Name& VarNameMap::name_from_id(VarName::Id id) const
    {
        auto iter = m_name_from_id.find(id);
        if (iter == m_name_from_id.end())
        {
            throw Exception("VarName ID not found");
        }
        return iter->second;
    }

    /// @brief  Get a global ID from a local ID.
    /// If the local ID is not yet registered as global, it will be
    /// registered.
    VarName::Id VarNameMap::global_from_local(VarName::Id local_id) const
    {
        auto& name = name_from_id(local_id);
        auto global_var_name = VarName::from_name(name);
        return global_var_name.id();
    }

    /// @brief  Register a new var name.
    void VarNameMap::register_name(VarName::Id id, const VarName::Name& name)
    {
        if (m_id_from_name.emplace(name, id).second == false)
        {
            throw Exception("Var name already exists");
        }
        if (m_name_from_id.emplace(id, name).second == false)
        {
            throw Exception("Var name already exists");
        }
    }

    /// @brief  Get the map.
    const std::map<VarName::Name, VarName::Id>& VarNameMap::map() const
    {
        return m_id_from_name;
    }

    /// @brief  Get the map.
    std::map<VarName::Name, VarName::Id>& VarNameMap::map()
    {
        return m_id_from_name;
    }
}
