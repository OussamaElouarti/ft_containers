#pragma once

#include "Vector.hpp"

namespace ft
{
    template<class T, class Container = vector<T> >
    class Stack
    {
        public :
            typedef T value_type;
            typedef Container container_type;
            typedef size_t size_type ;
        public :
            explicit Stack(const container_type& ctnr = container_type()) : _c(ctnr) {}
            ~Stack() {}
            bool empty() const {return(_c.empty());}
            size_type size() const { return (_c.size());}
            value_type& top() {return (_c.back());}
            const value_type& top() const {return (_c.back());}
            void push (const value_type& val) { _c.push_back(val);}
            void pop () { _c.pop_back();}
            template<class U, class Container1>
            friend bool operator== (const Stack<U,Container1>& lhs, const Stack<U,Container1>& rhs);
            template<class U, class Container1>
            friend bool operator!= (const Stack<U,Container1>& lhs, const Stack<U,Container1>& rhs);
            template<class U, class Container1>
            friend bool operator<  (const Stack<U,Container1>& lhs, const Stack<U,Container1>& rhs);
            template<class U, class Container1>
            friend bool operator<= (const Stack<U,Container1>& lhs, const Stack<U,Container1>& rhs);
            template<class U, class Container1>
            friend bool operator>  (const Stack<U,Container1>& lhs, const Stack<U,Container1>& rhs);
            template<class U, class Container1>
            friend bool operator>= (const Stack<U,Container1>& lhs, const Stack<U,Container1>& rhs);
        protected :
            container_type _c;
    };
    template<class T, class Container>
    bool operator== (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
    {
        return (lhs._c == rhs._c);
    }
    template <class T, class Container>
    bool operator!= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
    {
        return (lhs._c != rhs._c);
    }
    template <class T, class Container>
    bool operator<  (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
    {
        return (lhs._c < rhs._c);
    }
    template <class T, class Container>
    bool operator<= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
    {
        return (lhs._c <= rhs._c);
    }
    template <class T, class Container>
    bool operator>  (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
    {
        return (lhs._c > rhs._c);
    }
    template <class T, class Container>
    bool operator>= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
    {
        return (lhs._c >= rhs._c);
    }
}