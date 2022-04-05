/**
 ** \file misc/singleton.hh
 ** \brief Generic singleton
 */

#pragma once

namespace misc
{
    template <typename T> class Singleton
    {
    public:
        Singleton(const Singleton<T>&) = delete;
        Singleton(Singleton<T>&&) = delete;
        Singleton& operator=(const Singleton<T>&) = delete;
        Singleton& operator=(const Singleton<T>&&) = delete;

        static const T& instance()
        {
            //return std::unique_ptr<T>(new T());
            static T instance;
            return instance;
        }

    protected:
        Singleton() = default;
    };
} // namespace misc
