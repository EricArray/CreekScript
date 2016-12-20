#pragma once

#include <list>

#include <creek/api_mode.hpp>
#include <creek/Shared.hpp>


namespace creek
{
    class GarbageCollectable;

    class CREEK_API GarbageCollector
    {
    public:
        using TraceMark = uint8_t;
        using List = std::list<WeakPointer<GarbageCollectable>>;

        /// @brief  Delete objects not traced; increase collection counter for following trace.
        static void collect_garbage();

        static GarbageCollector instance;

        TraceMark current_trace_mark;
        List collection;


    protected:
        friend class GarbageCollectable;
        
        /// @brief  Register a GarbageCollectable so it can be collected.
        static void add_to_collection(const WeakPointer<GarbageCollectable>& p);

    private:

        GarbageCollector();
    };


    /// @brief  Garbage collectable base class.
    class CREEK_API GarbageCollectable : public Shared
    {
    public:
        GarbageCollectable(const SharedPointer<Shared>& sp);

        /// @brief  Mark this object to not be collected in this trace.
        /// Calls @c on_trace_garbage of this object
        void garbage_trace();


        GarbageCollector::TraceMark m_trace_mark;
    private:
        /// @brief  Called when tracing this object.
        /// Override to spread the trace to child objects by calling @c garbage_trace on them.
        virtual void on_garbage_trace() = 0;

    };
}
