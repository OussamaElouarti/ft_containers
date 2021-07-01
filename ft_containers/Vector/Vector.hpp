#pragma once

#include <iostream>
#include  <exception>
#include <cstring>
#include <memory>

template<typename Vector>
class Vectoriterator
{
    public :
        typedef typename Vector::value_type value_type;
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
        operator Vectoriterator<Vector const>() const
        {
            return Vectoriterator<Vector const>(m_ptr);
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
        PointerType m_ptr;
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
        typedef Vectoriterator<Vector<T> > iterator;
        typedef Vectoriterator<Vector<const T> > const_iterator;
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
            if (n > 4611686018427387903)
                throw OutOfRange();
            else if (n == 4611686018427387903)
                throw BadAlloc();
            m_data = m_alloc.allocate(n);
            m_alloc.construct(m_data);
            for (unsigned int i = 0; i < n; i++)
            {
                m_size = i;
                m_data[i] = std::move(value);
            }
            m_size++;
            m_capacity = n;
        }
        Vector(iterator first, iterator last, const allocator_type& alloc = allocator_type()) : m_data(nullptr), m_size(0), m_capacity(0)
        {
            size_t i = 0;
            for (iterator it = first; it != last; it++)
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
        iterator end() {return (iterator(m_data + m_size));}
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
            int i = 0;
            int j;
            for(iterator it = begin(); it != position; it++)
                i++;
            i++;
            m_data = m_alloc.allocate(m_capacity);
            m_alloc.construct(m_data);
            for (j = m_size; j >= i; j--)
                m_data[j] = m_data[j - 1];
            m_data[j] = std::move(value);
            m_size++;
            return (position);
        }
        // void    insert(iterator position, size_t n, const T& value)
        // {
        //     int i = 0;
        //     int j;
        //     size_t k;
        //     T* newBlock = (T*)::operator new(m_size * sizeof(T));
        //     for (size_t i = 0; i < m_size; i++)
        //         newBlock[i] = std::move(m_data[i]);
        //     for(iterator it = begin(); it != position; it++)
        //         i++;
        //     m_data = m_alloc.allocate(m_capacity * 2);
        //     m_alloc.construct(m_data);
        //     for (j = 0; j < i; j++)
        //         m_data[j] = std::move(newBlock[j]);
        //     int l = j;
        //      for (k = 0; k < n; k++)
        //     {
        //         m_data[j] = std::move(value);
        //         j++;
        //         m_size++;
        //     }
        //     while (newBlock[l] && m_data[j])
        //     {
        //         m_data[j] = std::move(newBlock[l++]);
        //         j++;
        //     }
        //     delete [] newBlock;
        // }
        // void    insert(iterator position, iterator first, iterator last)
        // {
        //     size_t n = 0;
        //     int i = 0;
        //     int j;
        //     size_t k;
        //     size_t size = m_size;
        //     for (iterator it = first; it != last; it++)
        //         n++;
        //     T* newBlock = (T*)::operator new(m_size * sizeof(T));
        //     for (size_t i = 0; i < m_size; i++)
        //         newBlock[i] = std::move(m_data[i]);
        //     for(iterator it = begin(); it != position; it++)
        //         i++;
        //     m_data = m_alloc.allocate(m_capacity + n);
        //     m_alloc.construct(m_data);
        //     for (j = 0; j < i; j++)
        //         m_data[j] = std::move(newBlock[j]);
        //     int l = j;
        //      for (k = 0; k < n; k++)
        //     {
        //         m_data[j] = std::move(*first);
        //         j++;
        //         first++;
        //         m_size++;
        //     }
        //     for (int b = l; b < size; b++)
        //     {
        //         if (j < m_size + n)
        //             m_data[j++] = std::move(newBlock[b]);   
        //     }
        //     delete [] newBlock;
        // }
        // void    resize(size_t n, T value)
        // {
        //     if (n > 4611686018427387903)
        //         throw OutOfRange();
        //     else if (n == 4611686018427387903)
        //         throw BadAlloc();
        //     if (n > m_capacity)
        //     {
        //         m_data = m_alloc.allocate(n);
        //         m_alloc.construct(m_data);
        //         for (int i = m_size; m_size < n; m_size++)
        //             m_data[m_size] = std::move(value);
        //     }
        //     else
        //     {
        //         for (int i = m_size; i > n; i--)
        //             m_data[m_size--].~T();
        //     }
        // }
        void    reserve(size_t n)
        {
            if (n > m_alloc.max_size())
                throw OutOfRange();
            else if (n == m_alloc.max_size())
                throw BadAlloc();
            if (n > m_capacity)
            {
                T* block = new T[m_size];
                for (size_t i = 0; i < m_size; i++)
                    block[i] = std::move(m_data[i]);
                m_alloc.deallocate(m_data, m_capacity);
                m_data = m_alloc.allocate(n);
                m_alloc.construct(m_data);
                for (size_t i = 0; i < m_size; i++)
                    m_data[i] = std::move(block[i]);
                m_capacity = n;
                delete [] block;
            }
        }
        iterator    erase(iterator position)
        {
            int n = 0;
            iterator it;
            for (it = begin(); it != position; it++)
                n++;
            m_size--;
            for(size_t i = n; i < m_size; i++)
                m_data[i] = std::move(m_data[i + 1]);
            return (it);
        }
        // iterator    erase(iterator first, iterator last)
        // {
        //     size_t n = 0;
        //     size_t i = 0;
        //     iterator it;
        //     for (it = begin(); it != first; it++)
        //         n++;
        //     for (iterator it = first; first != last; first++)
        //         i++;
        //     i--;
        //     for (int k = n; k < i + n; k++)
        //     {
        //         m_data[k].~T();
        //         m_data[k] = std::move(m_data[k + i]);
        //         m_size--;
        //     }
        //     return (it);
        // }
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
        Alloc m_alloc;
        T*      m_data;
        size_t  m_size;
        size_t  m_capacity;  
};
template<typename T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs)
{
    for (size_t i = 0; i < lhs.size(); i++)
    {
        if (lhs[i] == rhs[i])
            continue ;
        else 
            return (false);
    }
    return (true);
}
template<typename T>
bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs)
{
    if (lhs == rhs)
        return (false);
    return (true);
}
template<typename T>
bool operator<(const Vector<T>& lhs, const Vector<T>& rhs)
{
    for (size_t i = 0; i < lhs.size(); i++)
    {
        if (lhs[i] > rhs[i]) 
            return (false);
        else if (lhs[i] < rhs[i])
            return (true);
    }
    return (false);
}
template<typename T>
bool operator>(const Vector<T>& lhs, const Vector<T>& rhs)
{
    if (lhs < rhs || lhs == rhs)
        return (false);
    else if (lhs != rhs)
        return (true);
    return (false);
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
    if (lhs  > rhs || lhs == rhs)
        return (true);
    return (false);
}