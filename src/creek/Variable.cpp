#include <creek/Variable.hpp>

#include <creek/Data.hpp>


namespace creek
{
    Data* Variable::data()
    {
        return m_data.get();
    }

    void Variable::data(Data* new_data)
    {
        m_data.reset(new_data);
    }
}