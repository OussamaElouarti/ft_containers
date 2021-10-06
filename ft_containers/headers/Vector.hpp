#pragma once

#include <cstring>
#include <memory>
#include <stdexcept>
#include "ReverseIterator.hpp"
#include "tools.hpp"
namespace ft
{
    template <class T>
    class random_access_iterator : ft::iterator<std::random_access_iterator_tag, T>
    {
        public :
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category     iterator_category;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type            value_type;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type       difference_type;
            typedef T*                                                                          pointer;
            typedef T&                                                                          reference;
            
        public :
            random_access_iterator(pointer ptr) :m_ptr(ptr)
            {}
            random_access_iterator(const random_access_iterator& other) :m_ptr(other.m_ptr)
            {}
            random_access_iterator() :m_ptr(nullptr)
            {}
            virtual ~random_access_iterator() {}
            pointer base() const
            {
                return (m_ptr);
            }
            random_access_iterator& operator=(const random_access_iterator& x)
            {
                this->m_ptr = x.m_ptr;
                return (*this);
            }
            random_access_iterator& operator++()
            {
                m_ptr++;
                return (*this);
            }
            operator random_access_iterator<const value_type>() const
            {
                return random_access_iterator<const value_type>(m_ptr);
            }
            random_access_iterator operator++(int)
            {
                random_access_iterator tmp(*this);
                operator++();
                return (tmp);
            }
            random_access_iterator& operator--()
            {
                m_ptr--;
                return (*this);
            }
            random_access_iterator operator--(int)
            {
                random_access_iterator tmp(*this);
                operator--();
                return (tmp);
            }
            reference operator[](difference_type n)
            {
                return (*(operator+(n)));
            }
            pointer operator->()
            {
                return (m_ptr);
            }
            reference operator*()
            {
                return *(m_ptr);
            }
            random_access_iterator operator-(difference_type n) const 
            {
                return (m_ptr - n);
            }
            random_access_iterator operator+(difference_type n) const
            {
                return (m_ptr + n);
            }
            random_access_iterator& operator+=(difference_type n)
            {
                m_ptr += n;
                return (*this);
            }
            random_access_iterator& operator-=(difference_type n)
            {
                m_ptr -= n;
                return (*this);
            }
        protected :
            pointer m_ptr;
    };
    template <class T>
    bool operator== (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
    {
        return (lhs.base() == rhs.base());
    }
    template <class T>
    bool operator!= (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
    {
        return (lhs.base() != rhs.base());
    }
    template <class T>
    bool operator<  (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
    {
        return (lhs.base() < rhs.base());
    }
    template <class T>
    bool operator<=  (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
    {
        return (lhs.base() <= rhs.base());
    }
    template <class T>
    bool operator>  (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
    {
        return (lhs.base() > rhs.base());
    }
    template <class T>
    bool operator>=  (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
    {
        return (lhs.base() >= rhs.base());
    }
    template <class T>
    random_access_iterator<T> operator+ (typename random_access_iterator<T>::difference_type n, const random_access_iterator<T>& rand)
    {
        return (rand + n);
    }
    template <class T>
    typename random_access_iterator<T>::difference_type operator- (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
    {
        return (lhs.base() - rhs.base());
    }

    template<class T, class Alloc = std::allocator<T>  >
    class vector
    {
        public :
            typedef T value_type;
            typedef Alloc allocator_type;
            typedef typename allocator_type::reference reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::const_pointer const_pointer;
            typedef ft::random_access_iterator<value_type> iterator;
            typedef ft::random_access_iterator<const value_type> const_iterator;
            typedef ft::reverse_iterator<iterator> reverse_iterator;
            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
            typedef size_t size_type;
            typedef std::ptrdiff_t difference_type;

        public :
            explicit vector (const allocator_type& alloc = allocator_type()) : m_alloc(alloc),m_data(nullptr), m_size(0), m_capacity(0)
            {}
            vector(const vector& x) : m_data(nullptr), m_size(0), m_capacity(0)
            {
                *this = x;
            }
            explicit vector(size_type n, const value_type& value = value_type(), const allocator_type& alloc = allocator_type()) : m_alloc(alloc),m_data(nullptr), m_size(0), m_capacity(0)
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
            vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename enable_if<!is_integral<InputIterator>::value,InputIterator >::type = InputIterator()) : m_alloc(alloc),m_data(nullptr), m_size(0), m_capacity(0)
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
                if (m_size == 0)
                    reserve(1);
                else if (m_capacity == m_size)
                    reserve(m_capacity * 2);
                m_data[m_size] = val;
                m_size++;
            }
            size_type  size() const {return (m_size);}
            void    pop_back() { m_size--;}
            void    clear() {m_size = 0;}
            iterator begin() {return (iterator(m_data));}
            allocator_type get_allocator() const { return (m_alloc); }
            iterator end()  {return (iterator(m_data + m_size));}
            const_iterator begin() const {return (iterator(m_data));}
            const_iterator end()  const {return (iterator(m_data + m_size));}
            const_reverse_iterator rbegin() const {return (reverse_iterator(iterator(m_data + m_size)));}
            const_reverse_iterator rend()  const {return (reverse_iterator(iterator(m_data)));}
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
                if (n > m_size)
                    throw std::out_of_range("Out of Range error");
                return (m_data[n]);
            }
            const_reference  at(size_type n) const
            {
                if (n > m_size)
                    throw std::out_of_range("Out of Range error");
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
            void assign (InputIterator first, InputIterator last,  typename enable_if<!is_integral<InputIterator>::value,InputIterator >::type = InputIterator())
            {
                size_t i = 0;
                for(InputIterator it = first; it != last; it++)
                    i++;
                reserve(i);
                i = 0;
                m_size = 0;
                while (first != last)
                {
                    m_data[i] = *first;
                    first++;
                    m_size++;
                    i++;
                }
            }
            iterator insert(iterator position, const value_type& val)
            {
                difference_type d = std::distance(begin(), position);
                if (m_size == 0)
                    reserve(1);
                else if (m_size + 1 > m_capacity)
                    reserve(m_size + 1);
                for (size_type i = d + 1; i <= m_size; i++)
                    std::swap(m_data[d], m_data[i]);
                m_alloc.construct(&m_data[d], val);
                m_size++;
                return (begin() + d);
            }
            void    insert(iterator position, size_type n, const value_type& val)
            {
                vector tmp(*this);
                if ((m_size + n) > m_capacity)
                    reserve(m_size + n);
                iterator it = position;
                while (n) 
                {
                    *(position) = val;
                    n--;
                    position++;
                    m_size++;
                }
                while (it != tmp.end()) {
                    m_data[m_size] = *it;
                    ++it;
                }
            }
            template<class InputIterator>
            void    insert(iterator position, InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value,InputIterator >::type = InputIterator())
            {
                vector tmp(position, end());
                int i = 0;
                for (iterator it = end(); it != position; it--)
                    i++;
                if (m_capacity < m_size + i)
                {
                    if (m_capacity * 2 < m_capacity + i)
                        reserve(m_size + i);
                    else
                        reserve(m_capacity * 2);
                }
                m_size -= i;
                while (first != last) {
                    push_back(*first);
                    ++first;
                }
                iterator it = tmp.begin();
                while (it != tmp.end()) {
                    push_back(*it);
                    ++it;
                }
            }
            void    resize(size_type n, value_type val = value_type())
            {
                if (n > m_size)
                {
                    if (n > m_capacity)
                    {
                        reserve(n);
                        for (; m_size < n ; m_size++)
                            m_data[m_size] = val;
                    }
                    else
                    {
                        for (; m_size < n ; m_size++)
                            m_data[m_size] = val;
                    }
                }   
                else
                {
                    for (size_t i = m_size; i > n; i--)
                        m_data[m_size--].~value_type();
                }
            }
            void    reserve(size_type n)
            {
                if (n <= m_capacity)
				    return ;
                else if (n < m_capacity * 2)
                    n = m_capacity * 2;
                value_type *tmp = m_alloc.allocate(n);
                for (size_type i = 0; i < m_size; i++) 
                    tmp[i] = m_data[i];
                m_alloc.deallocate(m_data, m_capacity);
                m_data = tmp;
                m_capacity = n;
            }
            iterator    erase(iterator position)
            {
                iterator pos(position);
                while (position != end() - 1)
                {
                    *position = *(position + 1);
                    position++;
                }
                m_size--;
                return (pos);
            }
            iterator    erase(iterator first, iterator last)
            {
                iterator pos(first);
                int i = 0;
                while (last != end())
                {
                    *first = *last;
                    first++;
                    last++;
                }
                for (;first != last;first++)
                    i++;
                m_size -= i;
                return (pos);
            }
            void    swap(vector& x)
            {
                T			*tmp_data;
				size_type	tmp_size;

				tmp_data = x.m_data;
				x.m_data = this->m_data;
				this->m_data = tmp_data;
				tmp_size = x.m_size;
				x.m_size = this->m_size;
				this->m_size = tmp_size;
				tmp_size = x.m_capacity;
				x.m_capacity = this->m_capacity;
				this->m_capacity = tmp_size;
            }
        private :
            void    m_push_back(const value_type& val)
            {
                m_data[m_size] = val;
                m_size++;
            }
            Alloc   m_alloc;
            value_type*      m_data;
            size_t  m_size;
            size_t  m_capacity;  
    };
    template<class T, class Alloc>
    bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        if (lhs.size() != rhs.size())
            return (lhs.size() == rhs.size());
        return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }
    template<class T, class Alloc>
    bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (!(lhs == rhs));
    }
    template<class T, class Alloc>
    bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }
    template<class T, class Alloc>
    bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (!ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
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