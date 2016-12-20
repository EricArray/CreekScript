#pragma once

#include <memory>
#include <type_traits>

#include <creek/api_mode.hpp>
#include <creek/Exception.hpp>


namespace creek
{
    class Shared;
    template<class T> class SharedPointer;
    template<class T> class WeakPointer;


    /// @brief  Pointer with shared ownage that can be explicitly deleted.
    template<class T = Shared> class CREEK_API SharedPointer
    {
    public:
        // static_assert(std::is_base_of<Shared, T>::value, "T must be derived from Shared");

        SharedPointer();
        SharedPointer(const std::shared_ptr< std::unique_ptr<Shared> >& ptr);

        SharedPointer(std::nullptr_t);
        SharedPointer(const SharedPointer<T>& other);
        SharedPointer(SharedPointer<T>&& other);
        template<class U> SharedPointer(const SharedPointer<U>& other);
        template<class U> SharedPointer(SharedPointer<U>&& other);

        SharedPointer<T>& operator = (std::nullptr_t);
        SharedPointer<T>& operator = (const SharedPointer<T>& other);
        SharedPointer<T>& operator = (SharedPointer<T>&& other);
        template<class U> SharedPointer<T>& operator = (const SharedPointer<U>& other);
        template<class U> SharedPointer<T>& operator = (SharedPointer<U>&& other);

        void copy(const SharedPointer<T>& other);
        template<class U> void copy(const SharedPointer<U>& other);

        void swap(SharedPointer<T>&& other);
        template<class U> void swap(SharedPointer<U>&& other);

        /// @brief  Make a `SharedPointer`.
        /// @param  args... Arguments for T constructor.
        template<class... Args> static SharedPointer<T> make(Args... args);

        /// @brief  Create an object.
        /// @param  args... Arguments for T constructor.
        template<class... Args> void emplace(Args... args);

        const std::shared_ptr< std::unique_ptr<Shared> >& ptr() const;
        std::shared_ptr< std::unique_ptr<Shared> >& ptr();

        /// @brief  Get pointed object.
        T* get() const;

        /// @brief  Get pointed object.
        T& operator * () const;

        /// @brief  Access pointed object.
        T* operator -> () const;

        /// @brief  Check if has object.
        operator bool () const;

        /// @brief  Delete the pointed object.
        void destroy();

    private:
        std::shared_ptr< std::unique_ptr<Shared> > m_ptr;
    };


    /// @brief  Pointer without ownage, created from a `SharedPointer``.
    template<class T = Shared> class CREEK_API WeakPointer
    {
    public:
        // static_assert(std::is_base_of<Shared, T>::value, "T must be derived from Shared");

        WeakPointer();
        WeakPointer(const std::weak_ptr< std::unique_ptr<Shared> >& ptr);
        WeakPointer(const std::shared_ptr< std::unique_ptr<Shared> >& ptr);
        WeakPointer(const SharedPointer<T>& shared);
        template<class U> WeakPointer(const SharedPointer<U>& shared);

        WeakPointer(std::nullptr_t);
        WeakPointer(const WeakPointer<T>& other);
        WeakPointer(WeakPointer<T>&& other);
        template<class U> WeakPointer(const WeakPointer<U>& other);
        template<class U> WeakPointer(WeakPointer<U>&& other);

        WeakPointer<T>& operator = (std::nullptr_t);
        WeakPointer<T>& operator = (const WeakPointer<T>& other);
        WeakPointer<T>& operator = (WeakPointer<T>&& other);
        template<class U> WeakPointer<T>& operator = (const WeakPointer<U>& other);
        template<class U> WeakPointer<T>& operator = (WeakPointer<U>&& other);

        const std::weak_ptr< std::unique_ptr<Shared> >& ptr() const;
        std::weak_ptr< std::unique_ptr<Shared> >& ptr();

        SharedPointer<T> lock() const;

    private:
        std::weak_ptr< std::unique_ptr<Shared> > m_ptr;
    };


    /// @brief  Base for objects than can be used by `SharedPointer`.
    /// Has a weak pointer to itself.
    /// @sa SharedPointer
    class CREEK_API Shared
    {
    public:
        /// @brief  `Shared` constructor.
        /// @param  sp  SharedPointer where this object will be stored.
        Shared(const SharedPointer<Shared>& sp);

        Shared() = delete;
        shared(const Shared& other) = delete;
        operator = (const Shared& other) = delete;

        virtual ~Shared() = default;

        // void weak_ptr(const WeakPointer<Shared>& ptr);

        /// @brief  Get a weak pointer of self.
        template<class T = Shared> WeakPointer<T> weak_ptr() const;

        /// @brief  Get a strong pointer of self.
        template<class T = Shared> SharedPointer<T> shared_ptr() const;

    private:
        WeakPointer<Shared> m_wp;
    };
}


// template implementation
namespace creek
{
    // SharedPointer
    template<class T> SharedPointer<T>::SharedPointer()
    {

    }

    template<class T> SharedPointer<T>::SharedPointer(const std::shared_ptr< std::unique_ptr<Shared> >& ptr) :
        m_ptr(ptr)
    {

    }

    template<class T> SharedPointer<T>::SharedPointer(std::nullptr_t)
    {

    }

    template<class T> SharedPointer<T>::SharedPointer(const SharedPointer<T>& other) : m_ptr(other.m_ptr)
    {
    }

    template<class T> template<class U> SharedPointer<T>::SharedPointer(const SharedPointer<U>& other) : m_ptr(other.ptr())
    {
        static_assert(std::is_base_of<U, T>::value || std::is_base_of<T, U>::value, "T must be base of U or U base of T");
        // if (dynamic_cast<T*>(other.get()))
        // {
        //     m_ptr = other.ptr();
        // }
    }

    template<class T> SharedPointer<T>::SharedPointer(SharedPointer<T>&& other) : m_ptr(std::move(other.m_ptr))
    {
    }

    template<class T> template<class U> SharedPointer<T>::SharedPointer(SharedPointer<U>&& other) : m_ptr(std::move(other.ptr()))
    {
        static_assert(std::is_base_of<U, T>::value || std::is_base_of<T, U>::value, "T must be base of U or U base of T");
        // if (dynamic_cast<T*>(other.get()))
        // {
        //     m_ptr.swap(other.ptr());
        // }
    }

    template<class T> SharedPointer<T>& SharedPointer<T>::operator = (std::nullptr_t)
    {
        m_ptr.reset();
        return *this;
    }

    template<class T> SharedPointer<T>& SharedPointer<T>::operator = (const SharedPointer<T>& other)
    {
        m_ptr = other.ptr();
        return *this;
    }

    template<class T> template<class U> SharedPointer<T>& SharedPointer<T>::operator = (const SharedPointer<U>& other)
    {
        static_assert(std::is_base_of<U, T>::value || std::is_base_of<T, U>::value, "T must be base of U or U base of T");
        // if (dynamic_cast<T*>(other.get()))
        // {
            m_ptr = other.ptr();
        // }
        return *this;
    }

    template<class T> SharedPointer<T>& SharedPointer<T>::operator = (SharedPointer<T>&& other)
    {
        m_ptr = std::move(other.ptr());
        return *this;
    }

    template<class T> template<class U> SharedPointer<T>& SharedPointer<T>::operator = (SharedPointer<U>&& other)
    {
        static_assert(std::is_base_of<U, T>::value || std::is_base_of<T, U>::value, "T must be base of U or U base of T");
        // if (dynamic_cast<T*>(other.get()))
        // {
            m_ptr = std::move(other.ptr());
        // }
        return *this;
    }

    template<class T> void SharedPointer<T>::copy(const SharedPointer<T>& other)
    {
        m_ptr = other.m_ptr;
    }
    
    template<class T> template<class U> void SharedPointer<T>::copy(const SharedPointer<U>& other)
    {
        static_assert(std::is_base_of<U, T>::value || std::is_base_of<T, U>::value, "T or U must be base of the other");
        m_ptr = other.ptr();
    }

    template<class T> void SharedPointer<T>::swap(SharedPointer<T>&& other)
    {
        m_ptr.swap(other.m_ptr);
    }

    template<class T> template<class U> void SharedPointer<T>::swap(SharedPointer<U>&& other)
    {
        static_assert(std::is_base_of<U, T>::value || std::is_base_of<T, U>::value, "T or U must be base of the other");
        m_ptr.swap(other.ptr());
    }

    template<class T> const std::shared_ptr< std::unique_ptr<Shared> >& SharedPointer<T>::ptr() const
    {
        return m_ptr;
    }

    template<class T> std::shared_ptr< std::unique_ptr<Shared> >& SharedPointer<T>::ptr()
    {
        return m_ptr;
    }

    /// @brief  Get pointed object.
    template<class T> T* SharedPointer<T>::get() const
    {
        auto u = m_ptr.get();
        return u ? dynamic_cast<T*>(u->get()) : nullptr;
    }

    /// @brief  Get pointed object.
    template<class T> T& SharedPointer<T>::operator * () const
    {
        auto p = get();
        if (!p) throw Exception("Accessing null SharedPointer");
        return *p;
    }

    /// @brief  Access pointed object.
    template<class T> T* SharedPointer<T>::operator -> () const
    {
        auto p = get();
        if (!p) throw Exception("Accessing null SharedPointer");
        return p;
    }

    /// @brief  Check if has object.
    template<class T> SharedPointer<T>::operator bool () const
    {
        return m_ptr && *m_ptr;
    }

    /// @brief  Delete the pointed object.
    template<class T> void SharedPointer<T>::destroy()
    {
        if (auto u = m_ptr.get())
        {
            u->reset();
        }
    }

    /// @brief  Make a `SharedPointer`.
    /// @param  args... Arguments for T constructor.
    template<class T> template<class... Args> SharedPointer<T> SharedPointer<T>::make(Args... args)
    {
        SharedPointer<T> p;
        p.emplace(args...);
        return p;
    }

    /// @brief  Create an object.
    template<class T> template<class... Args> void SharedPointer<T>::emplace(Args... args)
    {
        std::unique_ptr<Shared>* u = new std::unique_ptr<Shared>(nullptr);
        m_ptr.reset(u);

        Shared* o = new T(*this, args...);
        u->reset(o);
    }


    // WeakPointer
    template<class T> WeakPointer<T>::WeakPointer()
    {

    }

    template<class T> WeakPointer<T>::WeakPointer(const std::weak_ptr< std::unique_ptr<Shared> >& ptr) :
        m_ptr(ptr)
    {

    }

    template<class T> WeakPointer<T>::WeakPointer(const std::shared_ptr< std::unique_ptr<Shared> >& ptr) :
        m_ptr(ptr)
    {

    }

    template<class T> WeakPointer<T>::WeakPointer(const SharedPointer<T>& shared) : m_ptr(shared.ptr())
    {
    }

    template<class T> template<class U> WeakPointer<T>::WeakPointer(const SharedPointer<U>& shared) : m_ptr(shared.ptr())
    {
        static_assert(std::is_base_of<U, T>::value || std::is_base_of<T, U>::value, "T must be base of U or U base of T");
        // if (dynamic_cast<T*>(shared.get()))
        // {
        //     m_ptr = shared.ptr();
        // }
    }

    template<class T> WeakPointer<T>::WeakPointer(std::nullptr_t)
    {

    }

    template<class T> WeakPointer<T>::WeakPointer(const WeakPointer<T>& other) : m_ptr(other.m_ptr)
    {
    }

    template<class T> template<class U> WeakPointer<T>::WeakPointer(const WeakPointer<U>& other) : m_ptr(other.ptr())
    {
        static_assert(std::is_base_of<U, T>::value || std::is_base_of<T, U>::value, "T must be base of U or U base of T");
        // if (dynamic_cast<T*>(other.get()))
        // {
        //     m_ptr = other.ptr();
        // }
    }

    template<class T> WeakPointer<T>::WeakPointer(WeakPointer<T>&& other) : m_ptr(std::move(other.m_ptr))
    {
    }

    template<class T> template<class U> WeakPointer<T>::WeakPointer(WeakPointer<U>&& other) : m_ptr(std::move(other.ptr()))
    {
        static_assert(std::is_base_of<U, T>::value || std::is_base_of<T, U>::value, "T must be base of U or U base of T");
        // if (auto l = other.lock())
        // {
        //     if (dynamic_cast<T*>(l.get()))
        //     {
        //         m_ptr = std::move(other.ptr());
        //     }
        // }
    }

    template<class T> WeakPointer<T>& WeakPointer<T>::operator = (std::nullptr_t)
    {
        m_ptr.reset();
        return *this;
    }

    template<class T> WeakPointer<T>& WeakPointer<T>::operator = (const WeakPointer<T>& other)
    {
        m_ptr = other.m_ptr;
        return *this;
    }

    template<class T> template<class U> WeakPointer<T>& WeakPointer<T>::operator = (const WeakPointer<U>& other)
    {
        static_assert(std::is_base_of<U, T>::value || std::is_base_of<T, U>::value, "T must be base of U or U base of T");
        // if (dynamic_cast<T*>(other.get()))
        // {
            m_ptr = other.ptr();
        // }
        return *this;
    }

    template<class T> WeakPointer<T>& WeakPointer<T>::operator = (WeakPointer<T>&& other)
    {
        m_ptr = std::move(other.m_ptr);
        return *this;
    }

    template<class T> template<class U> WeakPointer<T>& WeakPointer<T>::operator = (WeakPointer<U>&& other)
    {
        static_assert(std::is_base_of<U, T>::value || std::is_base_of<T, U>::value, "T must be base of U or U base of T");
        // if (dynamic_cast<T*>(other.get()))
        // {
            m_ptr = std::move(other.ptr());
        // }
        return *this;
    }

    template<class T> const std::weak_ptr< std::unique_ptr<Shared> >& WeakPointer<T>::ptr() const
    {
        return m_ptr;
    }

    template<class T> std::weak_ptr< std::unique_ptr<Shared> >& WeakPointer<T>::ptr()
    {
        return m_ptr;
    }

    template<class T> SharedPointer<T> WeakPointer<T>::lock() const
    {
        return SharedPointer<T>(m_ptr.lock());
    }


    // Shared
    template<class T> WeakPointer<T> Shared::weak_ptr() const
    {
        return WeakPointer<T>(m_wp);
    }

    template<class T> SharedPointer<T> Shared::shared_ptr() const
    {
        return SharedPointer<T>(m_wp.lock());
    }
}
