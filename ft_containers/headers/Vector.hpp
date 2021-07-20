#pragma once

#include <iostream>
#include  <exception>
#include <cstring>
#include <cstdlib>
#include <memory>
#include "ReverseIterator.hpp"
#include "type_traits.hpp"
namespace ft
{
    template<typename T>
    class vectoriterator
    {
        public :
            typedef T value_type;
            typedef value_type* PointerType;
            typedef const value_type * const_PointerType;
            typedef value_type& ReferenceType;
            typedef const value_type & const_ReferenceType;
            
        public :
            vectoriterator(PointerType ptr) :m_ptr(ptr)
            {}
            vectoriterator(const vectoriterator& other) :m_ptr(other.m_ptr)
            {}
            vectoriterator() :m_ptr(nullptr)
            {}
            vectoriterator& operator=(const vectoriterator& x)
            {
                this->m_ptr = x.m_ptr;
                return (*this);
            }
            vectoriterator& operator++()
            {
                m_ptr++;
                return (*this);
            }
            operator vectoriterator<const value_type>() const
            {
                return vectoriterator<const value_type>(m_ptr);
            }
            vectoriterator operator++(int)
            {
                vectoriterator iterator = *this;
                ++(*this);
                return (iterator);
            }
            vectoriterator& operator--()
            {
                m_ptr--;
                return (*this);
            }
            vectoriterator operator--(int)
            {
                vectoriterator iterator = *this;
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
            bool operator==(const vectoriterator& other) const
            {
                return (m_ptr == other.m_ptr);
            }
            bool operator!=(const vectoriterator& other) const
            {
                return !(*this == other);
            }
            vectoriterator operator-(int value)
            {
                m_ptr -= value;
                return (*this);
            }
            vectoriterator operator+(int value)
            {
                m_ptr += value;
                return (*this);
            }
        protected :
            value_type * m_ptr;
    };

    template<class T, class Alloc = std::allocator<T> >
    class vector
    {
        public :
            typedef T value_type;
            typedef value_type& reference;
            typedef const value_type& const_reference;
            typedef value_type* pointer;
            typedef const value_type* const_pointer;
            typedef vectoriterator<value_type> iterator;
            typedef vectoriterator<const value_type> const_iterator;
            typedef Reverse_iterator<iterator> reverse_iterator;
            typedef Reverse_iterator<const_iterator> const_reverse_iterator;
            typedef Alloc allocator_type;
            typedef size_t size_type;
            typedef std::ptrdiff_t difference_type;

        public :
            explicit vector (const allocator_type& alloc = allocator_type()) : m_data(nullptr), m_size(0), m_capacity(0)
            {}
            vector(const vector& x) : m_data(nullptr), m_size(0), m_capacity(0)
            {
                *this = x;
            }
            explicit vector(size_type n, const value_type& value = value_type(), const allocator_type& alloc = allocator_type()) : m_data(nullptr), m_size(0), m_capacity(0)
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
            template<class InputIterator>
            vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename enable_if<!is_integral<InputIterator>::value,InputIterator >::type = InputIterator()) : m_data(nullptr), m_size(0), m_capacity(0)
            {
                size_t i = 0;
                for (InputIterator it = first; it != last; it++)
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
            ~vector()
            {
                m_alloc.deallocate(m_data, m_capacity);
                m_alloc.destroy(m_data);
            }
            vector& operator=(const vector& x)
            {
                m_alloc.deallocate(m_data, m_capacity);
                m_data = m_alloc.allocate(x.m_capacity);
                for (size_t i = 0; i < x.m_size; i++)
                    m_data[i] = std::move(x.m_data[i]);
                m_size = x.m_size;
                m_capacity = x.m_capacity;
                return (*this);
            }

            const_reference operator[](size_type n) const
            {
                return (m_data[n]);
            }
            reference operator[](size_type n)
            {
                return (m_data[n]);
            }
            void    push_back(const value_type& val)
            {
                if (m_capacity == 0)
                    reserve(2);
                else if (m_size + 1 > m_capacity)
                    reserve(m_capacity * 2);
                m_data[m_size] = val;
                m_size++;
            }
            size_type  size() const {return (m_size);}
            void    pop_back() { m_size--;}
            void    clear() {m_size = 0;}
            iterator begin() {return (iterator(m_data));}
            iterator end()  {return (iterator(m_data + m_size));}
            const_iterator begin() const {return (iterator(m_data));}
            const_iterator end()  const {return (iterator(m_data + m_size));}
            const_reverse_iterator rbegin() const {return (reverse_iterator(end()));}
            const_reverse_iterator rend()  const {return (reverse_iterator(begin()));}
            reverse_iterator rbegin() {return (reverse_iterator(end()));}
            reverse_iterator rend() {return (reverse_iterator(begin()));}
            size_type  capacity() const { return(m_capacity);}
            size_type  max_size() const { return (m_alloc.max_size());}
            bool    empty() const
            {
                if (m_size == 0)
                    return (1);
                return (0);
            }
            reference  at(size_type n)
            {
                if (n >= m_size)
                    throw OutOfRange();
                return (m_data[n]);
            }
            const_reference  at(size_type n) const
            {
                if (n >= m_size)
                    throw OutOfRange();
                return (m_data[n]);
            }
            reference  front() {return(m_data[0]);}
            const_reference  front() const {return(m_data[0]);}
            reference  back() {return(m_data[m_size - 1]);}
            const_reference  back() const {return(m_data[m_size - 1]);}
            void    assign(size_type n, const value_type& val)
            {
                if (m_capacity < n)
                    reserve(n);
                for (size_t i = 0; i < n; i++)
                    m_data[i] = val;
                m_size = n;
            }
            template<class InputIterator>
            void assign (InputIterator first, InputIterator last)
            {
                int n = 0;
                for (InputIterator it = first; it != last; it++)
                    n++;
                if (m_capacity < n)
                    reserve(n);
                for (int i = 0; i < n; i++)
                {
                    m_data[i] = *first;
                    first++;
                }
                m_size = n;
            }
            iterator insert(iterator position, const value_type& val)
            {
                value_type* block = m_data;
                int i = 0;
                int j = 0;
                for (iterator it = begin(); it != position; it++)
                    i++;
                if (m_capacity < m_size + 1)
                    reserve(m_capacity * 2);
                for (j = m_size - 1; j >= i; j--)
                    m_data[j + 1] = block[j];
                m_data[j + 1] = val;
                for (int k = j; k >= 0 ; k--)
                    m_data[k] = block[k];
                iterator ite = &m_data[j+1];
                m_size++;
                return (ite);
            }
            void    insert(iterator position, size_type n, const value_type& val)
            {
                value_type* block = m_data;
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
                    m_data[j + n] = val;
                    m_size++;
                }
                for (int k = j; k >= 0 ; k--)
                    m_data[k] = block[k];
            }
            template<class InputIterator>
            void    insert(iterator position, InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value,InputIterator >::type = InputIterator())
            {
                value_type* block;
                if (m_data != nullptr)
                    block = m_data;
                int i = 0;
                int j = 0;
                int n = 0;
                for (iterator it = begin(); it != position; it++)
                    i++;
                for (InputIterator it = first; it != last; it++)
                    n++;
                if (m_capacity < m_size + n)
                {
                    if (m_capacity * 2 < m_size + n)
                        reserve(m_size + n);
                    else
                        reserve(m_capacity * 2);
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
            void    resize(size_type n, value_type val = value_type())
            {
                if (n > m_size)
                    *this = vector(n, val);
                else
                {
                    for (int i = m_size; i > n; i--)
                        m_data[m_size--].~value_type();
                }
            }
            void    reserve(size_type n)
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
                value_type* block = m_data;
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
                value_type* block = m_data;
                unsigned int i = 0;
                unsigned int n = 0;
                for (iterator it = begin(); it != first; it++)
                    i++;
                for (iterator it = first; it != last; it++)
                    n++;
                for (unsigned int k = i; k <= n; k++)
                {
                    m_size--;
                    m_data[k] = block[k + n];
                }
                return (first);
            }
            void    swap(vector& x)
            {
                vector *tmp = new vector(*this);
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
            value_type*      m_data;
            size_t  m_size;
            size_t  m_capacity;  
    };
    template<class T, class Alloc>
    bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
    return (equal(lhs.begin(), lhs.end(), rhs.begin()));
    }
    template<class T, class Alloc>
    bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (!(lhs == rhs));
    }
    template<class T, class Alloc>
    bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }
    template<class T, class Alloc>
    bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
    return (!lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }
    template<class T, class Alloc>
    bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        if (lhs  < rhs || lhs == rhs)
            return (true);
        return (false);
    }
    template<class T, class Alloc>
    bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        if (lhs > rhs || lhs == rhs)
            return (true);
        return (false);
    }
    template<class T, class Alloc>
    void    swap(vector<T, Alloc>& x, vector<T, Alloc>& y) { x.swap(y);}
}