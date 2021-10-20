#pragma once
#include <typeinfo>

#include "tools.hpp"

namespace ft 
{
    template<typename Iterator>
    class reverse_iterator
    {
        public :
            typedef Iterator iterator_type;
            typedef typename ft::iterator_traits<Iterator>::value_type value_type;
            typedef typename ft::iterator_traits<Iterator>::pointer pointer;
            typedef typename ft::iterator_traits<Iterator>::reference reference;
            typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
            typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;

        public :
            reverse_iterator() : m_iter(iterator_type())
            {}
            explicit reverse_iterator (iterator_type const &it)
            {
                iterator_type tmp = it;
                m_iter = --tmp;
            }
            reverse_iterator (reverse_iterator const& rev_it) : m_iter(rev_it.m_iter)
            {}
            template<typename iter>
            reverse_iterator(const reverse_iterator<iter> & it) : m_iter(--it.base()) {}
            iterator_type base() const
            {
                iterator_type tmp = m_iter;
                return ++tmp;
            }
            reference operator*() const
            {
                iterator_type tmp = m_iter;
                return (*(tmp));
            }
            reverse_iterator operator+ (difference_type n) const
            {
                return (reverse_iterator(m_iter - (n - 1)));
            }
            reverse_iterator& operator++()
            {
                --m_iter;
                return (*this);
            }
            reverse_iterator  operator++(int)
            {
                reverse_iterator tmp = *this;
                ++(*this);
                return (tmp);
            }
            reverse_iterator& operator+= (difference_type n)
            {
                m_iter -= n;
                return (*this);
            }
            reverse_iterator operator- (difference_type n) const
            {
                return (reverse_iterator(m_iter + (n + 1)));
            }
            reverse_iterator& operator--()
            {
                ++m_iter;
                return (*this);
            }
            reverse_iterator operator--(int) 
            {
                reverse_iterator temp = *this;
                --(*this);
                return temp;
            }
            reverse_iterator& operator-= (difference_type n)
            {
                m_iter += n;
                return (*this);
            }
            pointer operator->() const 
            {
                return &(operator*());
            }
            reference operator[] (difference_type n) const
            {
                return (m_iter[-n]);
            }
            private :
                iterator_type m_iter;
    };
    template <class Iterator>
    bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() == rhs.base());
    }
    template <class Iterator>
    bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() != rhs.base());
    }
    template <class Iterator>
    bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() > rhs.base());
    }
    template <class Iterator>
    bool operator<=  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() >= rhs.base());
    }
    template <class Iterator>
    bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() < rhs.base());
    }
    template <class Iterator>
    bool operator>=  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() <= rhs.base());
    }
    template <class Iterator>
    reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
    {
        return (rev_it + n);
    }
    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (rhs.base() - lhs.base());
    }
}