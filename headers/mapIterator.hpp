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
            map_iterator() : _ptr(), _tree() , _cmp(){}
            map_iterator(Node* node, const tree *tre) : _ptr(node), _tree(tre) {}
            map_iterator(map_iterator const&other) { *this = other; }
            virtual ~map_iterator() {}
            Node* base() const { return (_ptr); }
            map_iterator& operator= (map_iterator const& x)
            {
                _ptr = x._ptr;
                _tree = x._tree;
                _cmp = x._cmp;
                return (*this);
            }
            operator map_iterator<const T, const Node, Compare, tree>() const
            {
                return map_iterator<const T, const Node, Compare, tree>(_ptr, _tree);
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
                if (_ptr == nullptr)
                    return (*this = map_iterator(_tree->findm(_tree->getRoot()), _tree));
                if (_ptr == _tree->findM(_tree->getRoot()))
                    return (*this = map_iterator(nullptr, _tree));
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
                ++(*this);
                return (tmp);
            }
            map_iterator& operator--()
            {
                Node* p;
                if (_ptr == nullptr)
                    _ptr = _tree->findM(_tree->getRoot());
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
            friend bool	operator==(map_iterator const& lhs, map_iterator const& rhs) { return (lhs._ptr == rhs._ptr); }
            friend bool	operator!=(map_iterator const& lhs, map_iterator const& rhs) { return (lhs._ptr != rhs._ptr); }
        private :
            Node* _ptr;
            tree  const       *_tree;
            Compare      _cmp;
    };
}