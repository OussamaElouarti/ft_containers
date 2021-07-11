#pragma once

#include <iostream>
#include  <exception>
#include <cstring>
#include <cstdlib>
#include <memory>
#include "ReverseIterator.hpp"
#include "type_traits.hpp"

template<typename T>
class Vectoriterator
{
    public :
        typedef T value_type;
        typedef value_type* PointerType;
        typedef const value_type * const_PointerType;
        typedef value_type& ReferenceType;
        typedef const value_type & const_ReferenceType;
        
    public :
        Vectoriterator(PointerType ptr) :m_ptr(ptr)
        {}
        Vectoriterator(const Vectoriterator& other) :m_ptr(other.m_ptr)
        {}
        Vectoriterator() :m_ptr(nullptr)
        {}
        Vectoriterator& operator=(const Vectoriterator& x)
        {
            this->m_ptr = x.m_ptr;
            return (*this);
        }
        Vectoriterator& operator++()
        {
            m_ptr++;
            return (*this);
        }
        operator Vectoriterator<const value_type>() const
        {
            return Vectoriterator<const value_type>(m_ptr);
        }
        Vectoriterator operator++(int)
        {
            Vectoriterator iterator = *this;
            ++(*this);
            return (iterator);
        }
        Vectoriterator& operator--()
        {
            m_ptr--;
            return (*this);
        }
        Vectoriterator operator--(int)
        {
            Vectoriterator iterator = *this;
            --(*this);
            return (iterator);
        }
        ReferenceType operator[](int index)
        {
            return (*(m_ptr + index));
        }
        const_ReferenceType operator[](int index) const
        {
            return (*(m_ptr + index));
        }
        PointerType operator->()
        {
            return (m_ptr);
        }
        const_PointerType operator->() const
        {
            return (m_ptr);
        }
        ReferenceType operator*()
        {
            return *(m_ptr);
        }
        const_ReferenceType operator*() const
        {
            return *(m_ptr);
        }
        bool operator==(const Vectoriterator& other) const
        {
            return (m_ptr == other.m_ptr);
        }
        bool operator!=(const Vectoriterator& other) const
        {
            return !(*this == other);
        }
        Vectoriterator operator-(int value)
        {
            m_ptr -= value;
            return (*this);
        }
        Vectoriterator operator+(int value)
        {
            m_ptr += value;
            return (*this);
        }
    protected :
        value_type * m_ptr;
};

template<typename T, class Alloc = std::allocator<T> >
class Vector
{
    public :
        typedef T value_type;
        typedef T& reference;
        typedef const T& const_reference;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef Vectoriterator<T> iterator;
        typedef Vectoriterator<const T> const_iterator;
        typedef Reverse_iterator<iterator> reverse_iterator;
        typedef Reverse_iterator<const_iterator> const_reverse_iterator;
        typedef Alloc allocator_type;


    public :
        Vector(const allocator_type& alloc = allocator_type()) : m_data(nullptr), m_size(0), m_capacity(0)
        {}
        Vector(Vector<T> & obj) : m_data(nullptr), m_size(0), m_capacity(0)
        {
            *this = obj;
        }
        Vector(unsigned long long n, T value, const allocator_type& alloc = allocator_type()) : m_data(nullptr), m_size(0), m_capacity(0)
        {
            m_data = m_alloc.allocate(n);
            m_alloc.construct(m_data);
            for (unsigned long long i = 0; i < n; i++)
            {
                m_size = i;
                m_data[i] = std::move(value);
            }
            m_size++;
            m_capacity = n;
        }
        template< typename Y>
        Vector(Y first, Y last, const allocator_type& alloc = allocator_type(), typename enable_if<!is_integral<Y>::value,Y >::type = Y()) : m_data(nullptr), m_size(0), m_capacity(0)
        {
            size_t i = 0;
            for (Y it = first; it != last; it++)
                i++;
            m_data = m_alloc.allocate(i + 1);
            m_alloc.construct(m_data);
            for(size_t j = 0; i > j; j++)
            {
                m_size++;
                m_data[j] = *first;
                first++;
            }
            m_capacity = i;
        }
        ~Vector()
        {
            m_alloc.deallocate(m_data, m_capacity);
            m_alloc.destroy(m_data);
        }
        Vector& operator=(const Vector& x)
        {
            m_alloc.deallocate(m_data, m_capacity);
            m_data = m_alloc.allocate(x.m_capacity);
            for (size_t i = 0; i < x.m_size; i++)
                m_data[i] = std::move(x.m_data[i]);
            m_size = x.m_size;
            m_capacity = x.m_capacity;
            return (*this);
        }

        const_reference operator[](size_t index) const
        {
            return (m_data[index]);
        }
        reference operator[](size_t index)
        {
            return (m_data[index]);
        }
        void    push_back(const T& value)
        {
            if (m_capacity == 0)
                reserve(2);
            else if (m_size + 1 > m_capacity)
                reserve(m_capacity * 2);
            m_data[m_size] = value;
            m_size++;
        }
        size_t  size() const {return (m_size);}
        void    pop_back() { m_size--;}
        void    clear(){m_size = 0;}
        iterator begin() {return (iterator(m_data));}
        iterator end()  {return (iterator(m_data + m_size));}
        const_iterator begin() const {return (iterator(m_data));}
        const_iterator end()  const {return (iterator(m_data + m_size));}
        const_reverse_iterator rbegin() const {return (reverse_iterator(end()));}
        const_reverse_iterator rend()  const {return (reverse_iterator(begin()));}
        reverse_iterator rbegin() {return (reverse_iterator(end()));}
        reverse_iterator rend() {return (reverse_iterator(begin()));}
        size_t  capacity(){ return(m_capacity);}
        size_t  max_size(){ return (m_alloc.max_size());}
        bool    empty()
        {
            if (m_size == 0)
                return (1);
            return (0);
        }
        reference  at(size_t n)
        {
            if (n >= m_size)
                throw OutOfRange();
            return (m_data[n]);
        }
        const_reference  at(size_t n) const
        {
            if (n >= m_size)
                throw OutOfRange();
            return (m_data[n]);
        }
        reference  front() {return(m_data[0]);}
        const_reference  front() const {return(m_data[0]);}
        reference  back() {return(m_data[m_size - 1]);}
        const_reference  back() const{return(m_data[m_size - 1]);}
        void    assign(size_t n, const value_type& value)
        {
            if (m_size < n)
            {
                m_alloc.deallocate(m_data, m_capacity);
                m_data = m_alloc.allocate(n, m_data);
                for (size_t i = 0; i < n; i++)
                m_data[i] = std::move(value);
            }
            for (size_t i = 0; i < n; i++)
                m_data[i] = value;
            m_size = n;
        }
        iterator insert(iterator position, const T& value)
        {
            T* block = m_data;
            int i = 0;
            int j = 0;
            for (iterator it = begin(); it != position; it++)
                i++;
            if (m_capacity < m_size + 1)
                reserve(m_capacity * 2);
            for (j = m_size - 1; j >= i; j--)
                m_data[j + 1] = block[j];
            m_data[j + 1] = value;
            for (int k = j; k >= 0 ; k--)
                m_data[k] = block[k];
            iterator ite = &m_data[j+1];
            m_size++;
            return (ite);
        }
        void    insert(iterator position, size_t n, const T& value)
        {
            T* block = m_data;
            int i = 0;
            int j = 0;
            for (iterator it = begin(); it != position; it++)
                i++;
            if (m_capacity < m_size + n)
            {
                if (m_capacity * 2 < m_capacity + n)
                    reserve(m_size + n);
                else
                    reserve(m_capacity * 2);
            }
            for (j = m_size - 1; j >= i; j--)
                m_data[j + n] = block[j];
            for (int k = 0; k < n; n--)
            {
                m_data[j + n] = value;
                m_size++;
            }
            for (int k = j; k >= 0 ; k--)
                m_data[k] = block[k];
        }
        template<typename Y>
        void    insert(iterator position, Y first, Y last, typename enable_if<!is_integral<Y>::value,Y >::type = Y())
        {
            T* block;
            if (m_data != nullptr)
                block = m_data;
            int i = 0;
            int j = 0;
            int n = 0;
            for (iterator it = begin(); it != position; it++)
                i++;
            for (Y it = first; it != last; it++)
                n++;
            if (m_capacity < m_size + n)
            {
                if (m_capacity * 2 < m_size + n)
                    reserve(m_capacity * 2);
                else
                    reserve(m_size + n);
            }
            for (j = m_size; j >= i; j--)
                m_data[j + n] = block[j];
            for (int i = 0; i < n; n--)
            {
                m_data[j + n] = *first;
                first++;
                m_size++;
            }
            for (int k = j; k >= 0 ; k--)
                m_data[k] = block[k];
        }
        void    resize(size_t n, T value)
        {
            if (n > m_size)
                *this = Vector(n, value);
            else
            {
                for (int i = m_size; i > n; i--)
                    m_data[m_size--].~T();
            }
        }
        void    reserve(size_t n)
        {
            if (m_size > 0)
            {
                m_alloc.deallocate(m_data, m_capacity);
                m_data = nullptr;
                m_data = m_alloc.allocate(n);
            }
            else if (m_size == 0)
            {
                m_data = m_alloc.allocate(n);
                m_alloc.construct(m_data);
            }
            m_capacity = n;
        }
        iterator    erase(iterator position)
        {
            T* block = m_data;
            int i = 0;
            for (iterator it = begin(); it != position; it++)
                i++;
            for (int k = i; k < m_size ; k++)
                m_data[k] = block[k + 1];
            m_size--;
            return (position);
        }
        iterator    erase(iterator first, iterator last)
        {
            T* block = m_data;
            int i = 0;
            int n = 0;
            for (iterator it = begin(); it != position; it++)
                i++;
            
        }
        void    swap(Vector<T>& x)
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
        
        Alloc   m_alloc;
        T*      m_data;
        size_t  m_size;
        size_t  m_capacity;  
};
template<typename T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs)
{
   return (equal(lhs.begin(), lhs.end(), rhs.begin()));
}
template<typename T>
bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs)
{
    return (!(lhs == rhs));
}
template<typename T>
bool operator<(const Vector<T>& lhs, const Vector<T>& rhs)
{
    return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}
template<typename T>
bool operator>(const Vector<T>& lhs, const Vector<T>& rhs)
{
   return (!lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}
template<typename T>
bool operator<=(const Vector<T>& lhs, const Vector<T>& rhs)
{
    if (lhs  < rhs || lhs == rhs)
        return (true);
    return (false);
}
template<typename T>
bool operator>=(const Vector<T>& lhs, const Vector<T>& rhs)
{
    if (lhs > rhs || lhs == rhs)
        return (true);
    return (false);
}