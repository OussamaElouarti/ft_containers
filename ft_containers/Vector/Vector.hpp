#pragma once

#include <iostream>
#include <stdio.h>
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
            alloc(1, 0);
        }
        Vector(Vector<T> & obj) : m_data(nullptr), m_size(0), m_capacity(0)
        {
            *this = obj;
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
                m_data[i] = std::move(value);
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
                m_data[j] = std::move(*first);
                first++;
            }
        }
        ~Vector()
        {
            clear();
            if (m_data)
            {
                delete [] m_data;
                m_data = nullptr;
            }
        }
        Vector& operator=(const Vector& x)
        {
            T* newBlock = new T[x.m_size];
            for (size_t i = 0; i < x.m_size; i++)
                newBlock[i] = std::move(x.m_data[i]);
            if (m_data)
                delete [] m_data;
            m_data = newBlock;
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
            alloc(m_capacity + 1, 0);
            m_data[m_size] = std::move(value);
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
                m_data[i] = std::move(value);
        }
        Iterator insert(Iterator position, const T& value)
        {
            int i = 0;
            int j;
            for(Iterator it = begin(); it != position; it++)
                i++;
            i++;
            alloc(m_capacity * 2, 1);
            for (j = m_size; j >= i; j--)
                m_data[j] = m_data[j - 1];
            m_data[j] = std::move(value);
            m_size++;
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
                m_data[j] = std::move(newBlock[j]);
            int l = j;
             for (k = 0; k < n; k++)
            {
                m_data[j] = std::move(value);
                j++;
                m_size++;
            }
            while (newBlock[l] && m_data[j])
            {
                m_data[j] = std::move(newBlock[l++]);
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
            size_t size = m_size;
            for (Iterator it = first; it != last; it++)
                n++;
            T* newBlock = (T*)::operator new(m_size * sizeof(T));
            for (size_t i = 0; i < m_size; i++)
                newBlock[i] = std::move(m_data[i]);
            for(Iterator it = begin(); it != position; it++)
                i++;
            alloc(m_capacity + n, 0);
            for (j = 0; j < i; j++)
                m_data[j] = std::move(newBlock[j]);
            int l = j;
             for (k = 0; k < n; k++)
            {
                m_data[j] = std::move(*first);
                j++;
                first++;
                m_size++;
            }
            for (int b = l; b < size; b++)
            {
                if (j < m_size + n)
                    m_data[j++] = std::move(newBlock[b]);   
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
                    m_data[m_size] = std::move(value);
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
        Iterator    erase(Iterator position)
        {
            int n = 0;
            Iterator it;
            for (it = begin(); it != position; it++)
                n++;
            m_data[n].~T();
            m_size--;
            for(size_t i = n; i < m_size; i++)
                m_data[i] = std::move(m_data[i + 1]);
            return (it);
        }
        Iterator    erase(Iterator first, Iterator last)
        {
            size_t n = 0;
            size_t i = 0;
            Iterator it;
            for (it = begin(); it != first; it++)
                n++;
            for (Iterator it = first; first != last; first++)
                i++;
            for (int k = n; k < i + n; k++)
            {
                m_data[k].~T();
                m_data[k] = std::move(m_data[k + i]);
                m_size--;
            }
            return (it);
        }
        void    swap(Vector& x)
        {
            Vector<T> *tmp = new Vector(*this);
            *this = x;
            x = *tmp;
            delete tmp;
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