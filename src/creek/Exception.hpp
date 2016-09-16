#pragma once

#include <sstream>
#include <string>

#include <creek/api_mode.hpp>

namespace creek
{
    /// Base class for exceptions.
    /// Can be constructed by passing a error message to the constructor or
    /// by appending text to the string stream using `stream` method.
    class CREEK_API Exception
    {
    public:
        /// `Exception` constructor.
        Exception();

        /// `Exception` copy constructor.
        Exception(const Exception& other);

        /// `Exception` move constructor.
        Exception(Exception&& other);

        /// `Exception` constructor.
        /// @param  message     Description of the error.
        Exception(const std::string& message);

        virtual ~Exception() = default;

        /// Get exception message.
        std::string message() const;

    protected:
        /// Get the string stream to append messages.
        std::stringstream& stream();

    private:
        std::stringstream m_stream;
    };


    /// Undefined operation.
    class CREEK_API Undefined : public Exception
    {
    public:
        /// `Undefined` constructor.
        /// @param  what    What is undefined?
        Undefined(const std::string& what);
    };


    /// Not yet implemented operation/feature.
    class CREEK_API Unimplemented : public Exception
    {
    public:
        /// `Unimplemented` constructor.
        /// @param  what    What is Unimplemented?
        Unimplemented(const std::string& what);
    };
}
