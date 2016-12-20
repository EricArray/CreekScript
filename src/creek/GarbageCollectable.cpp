#include <creek/GarbageCollectable.hpp>

#include <iostream> // TODO: remove

namespace creek
{
    // GarbageCollector::TraceMark GarbageCollector::current_trace_mark = 0;
    // GarbageCollector::List GarbageCollector::collection;

    GarbageCollector GarbageCollector::instance;

    GarbageCollector::GarbageCollector() :
        current_trace_mark(0)
    {

    }

    /// @brief  Register a GarbageCollectable so it can be collected.
    void GarbageCollector::add_to_collection(const WeakPointer<GarbageCollectable>& p)
    {
        instance.collection.emplace_back(p);
    }

    GarbageCollectable::GarbageCollectable(const SharedPointer<Shared>& sp) :
        Shared(sp),
        m_trace_mark(GarbageCollector::instance.current_trace_mark - 1)
    {
        GarbageCollector::add_to_collection(weak_ptr());
    }

    /// @brief  Delete objects not traced; increase collection counter for following trace.
    void GarbageCollector::collect_garbage()
    {
        auto& collection = instance.collection;
        auto& current_trace_mark = instance.current_trace_mark;

        std::cout << "collecting garbage: " << collection.size() << " objects\n";

        for(auto it = collection.begin(); it != collection.end(); )
        {
            // lock pointer
            if(auto l = it->lock())
            {
                if(l->m_trace_mark == current_trace_mark)
                {
                    ++it;
                }
                else
                {
                    l.destroy();
                    it = collection.erase(it);
                }
            }

            // erase if already deleted
            else
            {
                it = collection.erase(it);
            }
        }

        current_trace_mark += 1;

        std::cout << "collected garbage: " << collection.size() << " objects\n";
    }

    /// @brief  Mark this object to not be collected in this trace.
    /// Calls @c on_trace_garbage of this object
    void GarbageCollectable::garbage_trace()
    {
        auto& current_trace_mark = GarbageCollector::instance.current_trace_mark;
        if (m_trace_mark != current_trace_mark)
        {
            m_trace_mark = current_trace_mark;
            on_garbage_trace();
        }
    }
}
