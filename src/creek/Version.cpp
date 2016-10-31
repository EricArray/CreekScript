#include <creek/Version.hpp>

#include <creek/utility.hpp>


namespace creek
{
//    /// @brief  Get version when it was linked.
//    static const Version& Version::linked();

    /// @brief  Get version of the loaded dynamic library.
    Version Version::loaded()
    {
        return linked();
    }


    /// @brief  Get major version.
    int Version::major() const
    {
        return m_major;
    }

    /// @brief  Get minor version.
    int Version::minor() const
    {
        return m_minor;
    }

    /// @brief  Get patch version.
    int Version::patch() const
    {
        return m_patch;
    }

    /// @brief  Get version as string in format "<major>.<minor>.<patch>".
    std::string Version::str(int base) const
    {
        return int_to_string(m_major, base) + "." +
               int_to_string(m_minor, base) + "." +
               int_to_string(m_patch, base);
    }
}
