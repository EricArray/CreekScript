#include <creek/Exception.hpp>


namespace creek
{
    Exception::Exception()
    {

    }

    Exception::Exception(const Exception& other)
    {
        m_stream.str(other.m_stream.str());
    }

    Exception::Exception(Exception&& other)
    {
        m_stream.swap(other.m_stream);
    }

    Exception::Exception(const std::string& message)
    {
        m_stream.str(message);
    }

    // Get exception message.
    std::string Exception::message() const
    {
        return m_stream.str();
    }

    // Get the string stream to append messages.
    std::stringstream& Exception::stream()
    {
        return m_stream;
    }

    // `Undefined` constructor.
    // @param  what    What is undefined?
    Undefined::Undefined(const std::string& what)
    {
        stream() << "Undefined: " << what;
    }

    // `Unimplemented` constructor.
    // @param  what    What is Unimplemented?
    Unimplemented::Unimplemented(const std::string& what)
    {
        stream() << "Unimplemented: " << what;
    }
}
