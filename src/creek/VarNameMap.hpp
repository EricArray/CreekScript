#pragma once

#include <map>

#include <creek/api_mode.hpp>
#include <creek/VarName.hpp>


namespace creek
{
    /// @brief  Dictionary of identifiers for a bytecode file.
    class CREEK_API VarNameMap
    {
    public:
        /// @brief  Get an ID from a name.
        /// The name is registered if it was not.
        VarName::Id id_from_name(const VarName::Name& name);

        /// @brief  Get a name from an ID.
        /// An exception is thrown if the ID was not registered.
        const VarName::Name& name_from_id(VarName::Id id) const;

        /// @brief  Get a global ID from a local ID.
        /// If the local ID is not yet registered as global, it will be
        /// registered.
        VarName::Id global_from_local(VarName::Id local_id) const;

        /// @brief  Register a new var name.
        void register_name(VarName::Id id, const VarName::Name& name);

        /// @brief  Get the map.
        const std::map<VarName::Name, VarName::Id>& map() const;

        /// @brief  Get the map.
        std::map<VarName::Name, VarName::Id>& map();

    private:
        std::map<VarName::Name, VarName::Id> m_id_from_name;
    };
}
