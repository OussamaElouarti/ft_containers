#pragma once

#include <iostream>
#include "VectorIterator.hpp"
#include  <exception>

template<typename T>
class Vector
{
    public :
        typedef T ValueType;
        typedef VectorIterator<Vector<T> > Iterator;
    public :
        Vector() : m_data(nullptr), m_size(0), m_capacity(0)
        {
            alloc(2, 0);
        }
        Vector(unsigned long long n, T value) : m_data(nullptr), m_size(0), m_capacity(0)
        {
            if (n > 4611686018427387903)
                throw OutOfRange();
            else if (n == 4611686018427387903)
                throw BadAlloc();
            alloc(n, 0);
            for (unsigned int i = 0; i < n; i++)
            {
                m_size = i;
                m_data[i] = value;
            }
            m_size++;
        }
        Vector(Iterator first, Iterator last) : m_data(nullptr), m_size(0), m_capacity(0)
        {
            size_t i = 0;
            for (Iterator it = first; it != last; it++)
                i++;
            alloc(i, 0);
            for(size_t j = 0; i > j; j++)
            {
                m_size++;
                m_data[j] = *first;
                first++;
            }
        }
        ~Vector()
        {
            clear();
            if (m_data)
            {
                delete[] m_data;
                m_data = nullptr;
            }
        }
        Vector& operator=(const Vector& x)
        {
            for(size_t i = 0; i < m_size; i++)
                m_data[i].~T();
            alloc(x.m_size, 0);
            for (size_t i = 0; i < x.m_size; i++)
                m_data[i] = x.m_data[i];
            m_size = x.m_size;
            return (*this);
        }
        const    T& operator[](size_t index) const
        {
            // if (index >= m_size)
            //     std::cout << "index greater than size" << std::endl;
            return (m_data[index]);
        }
        T& operator[](size_t index)
        {
            // if (index >= m_size)
            //     std::cout << "index greater than size" << std::endl;
            return (m_data[index]);
        }
        void    push_back(const T& value)
        {
            if (m_size > m_capacity)
                alloc(m_capacity, 0);
            m_data[m_size] = value;
            m_size++;
        }
        size_t  size() {return (m_size);}
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
            for(size_t i = 0; i < m_size; i++)
                m_data[i].~T();
            m_size = 0;
        }
        Iterator begin() {return (Iterator(m_data));}
        Iterator rbegin() {return (Iterator(m_data));}
        Iterator end() {return (Iterator(m_data + m_size));}
        Iterator rend() {return (Iterator(m_data + m_size));}
        size_t  capacity(){ return(m_capacity);}
        size_t  max_size(){ return (4611686018427387903);}
        bool    empty()
        {
            if (m_size == 0)
                return (1);
            return (0);
        }
        T&  at(unsigned int n)
        {
            if (n >= m_size)
                throw OutOfRange();
            return (m_data[n]);
        }
        T&  front() {return(m_data[0]);}
        T&  back() {return(m_data[m_size - 1]);}
        void    assign(size_t n, const T& value)
        {
            alloc(n, 1);
            for (unsigned int i = 0; i < n; i++)
                m_data[i] = value;;
        }
        Iterator insert(Iterator position, const T& value)
        {
            int i = 0;
            int j;
            for(Iterator it = begin(); it != position; it++)
                i++;
            i++;
            for (j = m_size; j >= i; j--)
                m_data[j] = m_data[j - 1];
            m_data[j] = value;
            m_size++;
            m_capacity *= 2;
            return (position);
        }
        void    insert(Iterator position, size_t n, const T& value)
        {
            int i = 0;
            int j;
            size_t k;
            T* newBlock = (T*)::operator new(m_size * sizeof(T));
            for (size_t i = 0; i < m_size; i++)
                newBlock[i] = std::move(m_data[i]);
            for(Iterator it = begin(); it != position; it++)
                i++;
            alloc(m_capacity * 2, 0);
            for (j = 0; j < i; j++)
                m_data[j] = newBlock[j];
            int l = j;
             for (k = 0; k < n; k++)
            {
                m_data[j] = value;
                j++;
                m_size++;
            }
            while (newBlock[l] && m_data[j])
            {
                m_data[j] = newBlock[l++];
                j++;
            }
            delete [] newBlock;
        }
        void    insert(Iterator position, Iterator first, Iterator last)
        {
            size_t n = 0;
            int i = 0;
            int j;
            size_t k;
            for (Iterator it = first; it != last; it++)
                n++;
            T* newBlock = (T*)::operator new(m_size * sizeof(T));
            for (size_t i = 0; i < m_size; i++)
                newBlock[i] = std::move(m_data[i]);
            for(Iterator it = begin(); it != position; it++)
                i++;
            alloc(m_capacity + n, 0);
            for (j = 0; j < i; j++)
                m_data[j] = newBlock[j];
            int l = j;
             for (k = 0; k < n; k++)
            {
                m_data[j] = *first;
                j++;
                first++;
                m_size++;
            }
            while (newBlock[l] && m_data[j - 1])
            {
                m_data[j] = newBlock[l++];
                j++;
            }
            delete [] newBlock;
        }
        void    resize(size_t n, T value)
        {
            if (n > 4611686018427387903)
                throw OutOfRange();
            else if (n == 4611686018427387903)
                throw BadAlloc();
            if (n > m_capacity)
            {
                alloc(n, 0);
                for (int i = m_size; m_size < n; m_size++)
                    m_data[m_size] = value;
            }
            else
            {
                for (int i = m_size; i > n; i--)
                    m_data[m_size--].~T();
            }
        }
        void    reserve(size_t n)
        {
            if (n > 4611686018427387903)
                throw OutOfRange();
            else if (n == 4611686018427387903)
                throw BadAlloc();
            if (n > m_capacity)
                alloc(n, 0);
    
        }
        class OutOfRange : public std::exception
		{
			public :
				OutOfRange() throw(){}
				virtual ~OutOfRange() throw(){}
				virtual const char* what() const throw() {return ("vector");}
		};
        class BadAlloc : public std::exception
		{
			public :
				BadAlloc() throw(){}
				virtual ~BadAlloc() throw(){}
				virtual const char* what() const throw() {return ("bad::alloc");}
		};
    private :
        void    alloc(size_t newCapacity, int n)
        {
            T* newBlock = (T*)::operator new(newCapacity * sizeof(T));
            if (newCapacity < m_size)
                m_size  = newCapacity;
            for (size_t i = 0; i < m_size; i++)
                newBlock[i] = std::move(m_data[i]);
            for (size_t i = 0; i < m_size; i++)
                m_data[i].~T();
            if (m_data)
            {
                delete[] m_data;
                m_data = nullptr;
            }
            m_data = newBlock;
            if (!n)
                m_capacity = newCapacity;
        }
        T*      m_data;
        size_t  m_size;
        size_t  m_capacity;  
};