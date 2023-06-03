#include <iostream>
#include <memory>
#include <stdlib.h>
template<typename T>
struct AutoPtr4
{
    AutoPtr4(T* ptr = nullptr)
        : ptr(ptr)
    {
    }
    ~AutoPtr4()
    {
        if(this->ptr != nullptr)
        {
            delete this->ptr;
            this->ptr = nullptr;
        }
    }

    AutoPtr4(const AutoPtr4& ptr4) = delete; // disable copying

    AutoPtr4(AutoPtr4&& ptr4) noexcept // move constructor
        : ptr(ptr4)
    {
        ptr4.ptr = nullptr;
    }

    AutoPtr4& operator=(const AutoPtr4& ptr4) = delete; // disable copy assignment

    AutoPtr4& operator=(AutoPtr4&& ptr4) noexcept // move assignment
    {
        if(this == &ptr4)
        {
            return *this;
        }

        delete this->ptr;
        this->ptr = ptr4.ptr;
        ptr4.ptr = nullptr;
        return *this;
    }

    T& operator*() const
    {
        return *this->ptr;
    }

    T* operator->() const
    {
        return this->ptr;
    }

    bool isNull() const
    {
        return this->ptr == nullptr;
    }

private:
    T* ptr;
};