#pragma once

#include <string>

#include <creek/api_mode.hpp>


#define CREEK_LINKED_MAJOR  0
#define CREEK_LINKED_MINOR  1
#define CREEK_LINKED_PATCH  2


namespace creek
{
    /// @brief  Script version.
    class CREEK_API Version
    {
    public:
        /// @brief  Get version when it was linked.
        static Version linked();

        /// @brief  Get version of the loaded dynamic library.
        static Version loaded();


        /// @brief  `Version` constructor.
        Version(int major, int minor, int patch) :
            m_major(major),
            m_minor(minor),
            m_patch(patch)
        {

        }

        Version(const Version& other) :
            m_major(other.m_major),
            m_minor(other.m_minor),
            m_patch(other.m_patch)
        {

        }


        /// @brief  Get major version.
        int major() const;

        /// @brief  Get minor version.
        int minor() const;

        /// @brief  Get patch version.
        int patch() const;

        /// @brief  Get version as string in format "<major>.<minor>.<patch>".
        /// @param  base    Number base (dec, hex, bin).
        std::string str(int base = 10) const;


    private:
        int m_major;
        int m_minor;
        int m_patch;
    };


    /// @brief  Get version when it was linked.
    Version Version::linked()
    {
        return Version(CREEK_LINKED_MAJOR, CREEK_LINKED_MINOR, CREEK_LINKED_PATCH);
    }
}
