#pragma once

# include "tools.hpp"

namespace ft {
    template <class T, class Node, class Compare, class tree>
    class map_iterator : ft::iterator<std::bidirectional_iterator_tag, Node>
    {
        public :
            typedef typename iterator<std::bidirectional_iterator_tag, Node>::iterator_category         iterator_category;
            typedef typename iterator<std::bidirectional_iterator_tag, Node>::value_type                value_type;
            typedef typename iterator<std::bidirectional_iterator_tag, Node>::difference_type           difference_type;
            typedef typename iterator<std::bidirectional_iterator_tag, Node>::pointer                   pointer;
            typedef typename iterator<std::bidirectional_iterator_tag, Node>::reference                 reference;
            typedef Node*                                                                               node_pointer;
        public :
            map_iterator() : _ptr(nullptr) {}
            inline map_iterator(node_pointer node, tree &tr) : _ptr(node), _avl(tr) {}
            map_iterator(const map_iterator &other) : _ptr(other._ptr) {}
            virtual ~map_iterator() {}
            pointer base() const { return (_ptr);}
            operator map_iterator<const value_type, Node, Compare, tree>() const
            {
                return map_iterator<const value_type, Node, Compare, tree>(_ptr);
            }
            T *operator->()
            {
                return (_ptr->data);
            }
            T operator*()
            {
                return (*(_ptr->data));
            }
        private :
            node_pointer _ptr;
            tree         _avl;
            Compare      _cmp;
    };
}