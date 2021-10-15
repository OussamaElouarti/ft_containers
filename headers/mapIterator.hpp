#pragma once

# include "tools.hpp"

namespace ft {
    template <class T, class Node, class Compare, class tree>
    class map_iterator : ft::iterator<std::bidirectional_iterator_tag, T>
    {
        public :
            typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::iterator_category         iterator_category;
            typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::value_type                value_type;
            typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::difference_type           difference_type;
            typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::pointer                   pointer;
            typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::reference                 reference;
        public :
            map_iterator() : _ptr(nullptr) {}
            inline map_iterator(Node* node, Node* last) : _ptr(node), _last(last) {}
            map_iterator(const map_iterator &other) : _ptr(other._ptr), _last(other._last) {}
            virtual ~map_iterator() {}
            Node* base() const { return (_ptr); }
            map_iterator& operator= (const map_iterator &x)
            {
                _ptr = x._ptr;
                _last = x._last;
                return (*this);
            }
            operator map_iterator<const T, Node, Compare, tree>() const
            {
                return map_iterator<const T, Node, Compare, tree>(_ptr, NULL);
            }
            T* operator->() const
            {
                return (_ptr->data);
            }
            T& operator*() const
            {
                return (*_ptr->data);
            }
            map_iterator& operator++()
            {
                Node* p;
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
                return (*this);
            }
            map_iterator operator++(int)
            {
                map_iterator tmp(*this);
                operator++();
                return (tmp);
            }
            map_iterator& operator--()
            {
                Node* p;
                if (_ptr == nullptr)
                    _ptr = _last;
                else
                {
                    if (_ptr->left != nullptr)
                    {
                        _ptr = _ptr->left;
                        while (_ptr->right != nullptr)
                            _ptr= _ptr->right;
                    }
                    else
                    {
                        p = _ptr->parent;
                        while (p != nullptr && _ptr == p->left)
                        {
                            _ptr = p;
                            p = p->parent;
                        }
                        _ptr = p;
                    }
                }
                return (*this);
            }
            map_iterator operator--(int)
            {
                map_iterator tmp(*this);
                operator--();
                return (tmp);
            }
        private :
            Node* _ptr;
            Node*         _last;
            Compare      _cmp;
    };
    template <class T, class Node, class Compare, class tree>
    bool operator== (const map_iterator<T, Node, Compare, tree>& lhs, const map_iterator<T, Node, Compare, tree>& rhs)
    {
        return (lhs.base() == rhs.base());
    }
    template <class T, class Node, class Compare, class tree>
    bool operator!= (const map_iterator<T, Node, Compare, tree>& lhs, const map_iterator<T, Node, Compare, tree>& rhs)
    {
        return (lhs.base() != rhs.base());
    }
}