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
            map_iterator& operator= (const map_iterator &x)
            {
                _ptr = x._ptr;
                _avl = x._avl;
                return (*this);
            }
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
            map_iterator& operator++()
            {
                node_pointer p;
                if (_ptr == nullptr)
                {
                    _ptr = _avl._root;
                    if (_ptr == nullptr)
                        std::cout << "empty tree!" << std::endl;
                    while (_ptr->left != nullptr)
                        _ptr = _ptr->left;
                }
                else
                {
                    if (_ptr->right != nullptr)
                    {
                        _ptr = _ptr->right;
                        while (_ptr->left != nullptr)
                            _ptr= _ptr->left;
                    }
                    else
                    {
                        p = _ptr->parent;
                        while (p != nullptr && _ptr == p->right)
                        {
                            _ptr = p;
                            p = p->parent;
                        }
                        _ptr = p;
                    }
                }
                return (*this);
            }
            map_iterator operator++(int)
            {
                map_iterator tmp(*this);
                operator++();
                return (tmp);
            }
        private :
            node_pointer _ptr;
            tree         _avl;
            Compare      _cmp;
    };
    template <class T, class Node, class Compare, class tree>
    bool operator!= (const map_iterator<T, Node, Compare, tree>& lhs, const map_iterator<T, Node, Compare, tree>& rhs)
    {
        return (lhs.base() != rhs.base());
    }
}