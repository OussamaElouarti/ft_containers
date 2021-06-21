#pragma once

#include <iostream>
#include "Vector.hpp"

template<typename Vector>
class VectorIterator
{
    public :
        typedef typename Vector::ValueType ValueType;
        typedef ValueType* PointerType;
        typedef ValueType& ReferenceType;
    public :
        VectorIterator(PointerType ptr) :m_ptr(ptr)
        {}
        VectorIterator& operator++()
        {
            m_ptr++;
            return (*this);
        }
        VectorIterator operator++(int)
        {
            VectorIterator iterator = *this;
            ++(*this);
            return (iterator);
        }
        VectorIterator& operator--()
        {
            m_ptr--;
            return (*this);
        }
        VectorIterator operator--(int)
        {
            VectorIterator iterator = *this;
            --(*this);
            return (iterator);
        }
        ReferenceType operator[](int index)
        {
            return (*(m_ptr + index));
        }
        PointerType operator->()
        {
            return (m_ptr);
        }
        ReferenceType operator*()
        {
            return *(m_ptr);
        }
        bool operator==(const VectorIterator& other) const
        {
            return (m_ptr == other.m_ptr);
        }
        bool operator!=(const VectorIterator& other) const
        {
            return !(*this == other);
        }
    private :
        PointerType m_ptr;
};