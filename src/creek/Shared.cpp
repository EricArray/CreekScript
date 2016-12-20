#include <creek/Shared.hpp>


namespace creek
{
    Shared::Shared(const SharedPointer<Shared>& sp) : m_wp(sp)
    {

    }
}
