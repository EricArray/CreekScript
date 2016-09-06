#pragma once

#include <sstream>
#include <string>


namespace creek
{
    /// Base class for exceptions.
    class Exception
    {
    public:
        Exception();
        Exception(const Exception& other);
        Exception(Exception&& other);
        virtual ~Exception() = default;

        /// Get exception message.
        std::string message() const;

    protected:
        /// Get the string stream to append messages.
        std::stringstream& stream();

    private:
        std::stringstream m_stream;
    };


    /// Undefined operation/feature.
    class Undefined : public Exception
    {
    public:
        /// `Undefined` constructor.
        /// @param  what    What is undefined?
        Undefined(const std::string& what);
    };
}
