#include <memory>


namespace creek
{
    class Data;


    /// Stores a data of any type.
    class Variable
    {
    public:
        /// Get the stored data.
        Data* data();

        /// Set the stored data.
        void data(Data* new_data);


    private:
        std::unique_ptr<Data> m_data = nullptr;
    }
}