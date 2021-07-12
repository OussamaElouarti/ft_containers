#pragma once

#include <iostream>
#include  <exception>
#include <cstring>
#include <memory>
#include "deque.hpp"
#include "Vetor.hpp"
#include "type_traits.hpp"

namespace ft
{
    template<class T, class Container = deque<T> >
    class stack
    {
        public :
            typedef T value_type;
            typedef Container container_type;
            typedef size_t size_type ;
        public :
            explicit stack(const container_type& ctnr = container_type());
            ~stack();
    };
}