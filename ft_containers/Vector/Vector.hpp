#pragma once

#include <iostream>
#include "VectorIterator.hpp"

template<typename T>
class Vector
{
    public :
        typedef T ValueType;
        typedef VectorIterator<Vector<T> > Iterator;
    public :
        Vector() : m_data(nullptr), m_size(0), m_capacity(0)
        {
            alloc(2);
        }
        Vector(unsigned int n, T value)
        {
            alloc(n);
            for (unsigned int i = 0; i < n; i++)
                push_back(value);
        }
        ~Vector()
        {
            clear();
            // delete [] m_data;
        }
        const    T& operator[](size_t index) const
        {
            if (index >= m_size)
                std::cout << "index greater than size" << std::endl;
            return (m_data[index]);
        }
        T& operator[](size_t index)
        {
            if (index >= m_size)
                std::cout << "index greater than size" << std::endl;
            return (m_data[index]);
        }
        void    push_back(const T& value)
        {
            if (m_size > m_capacity)
                alloc(m_capacity + 2);
            m_data[m_size] = value;
            m_size++;
        }
        size_t  size() {return (m_size);}
        T& emplace_back(const T& value)
        {
            if (m_size >= m_capacity)
                alloc(m_capacity + 2);
            m_data[m_size] = std::move(value);
            return (m_data[m_size++]);
        }
        void    pop_back()
        {
            if (m_size > 0)
            {    
                m_size--;
                m_data[m_size].~T();
            }
        }
        void    clear()
        {
            for(int i = 0; i < m_size; i++)
                m_data[i].~T();
            m_size = 0;
        }
        Iterator begin() {return (Iterator(m_data));}
        Iterator end() {return (Iterator(m_data + m_size));}

    private :
        void    alloc(size_t newCapacity)
        {
            T* newBlock = (T*)::operator new(newCapacity * sizeof(T));
            if (newCapacity < m_size)
                m_size  = newCapacity;
            for (size_t i = 0; i < m_size; i++)
                newBlock[i] = std::move(m_data[i]);
            for(size_t i = 0; i < m_size; i++)
                m_data[i].~T();
        //    delete[] m_data;
            m_data = newBlock;
            m_capacity = newCapacity;
        }
        size_t  m_size;
        size_t  m_capacity;
        T*      m_data;
};