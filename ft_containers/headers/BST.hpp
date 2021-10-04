#pragma once

#include  "tools.hpp"

template < class T, class Compare>
class BST_iterator : ft::iterator<bidirectional_iterator_tag, T>
{
    public :
        typedef typename T::value_type value_type;
        typedef typename iterator<bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
        typedef typename iterator<bidirectional_iterator_tag, value_type>::difference_type   difference_type;
        typedef typename iterator<bidirectional_iterator_tag, value_type>::pointer           pointer;
        typedef typename iterator<bidirectional_iterator_tag, value_type>::reference         reference;
    public :
        BST_iterator(const Compare& comp = Compare()) : _cmp(comp), _node(), l_node()
        {}
        BST_iterator(T* node, T* lastNode, const Compare& comp = Compare()) : _cmp(comp), _node(node), l_node(lastNode)
        {}
        BST_iterator(const BST_iterator& it) : _node(it._node), l_node(it.l_node), _cmp()
        {}
        virtual ~BST_iterator() { }
        BST_iterator& operator=(const BST_iterator& x)
        {
            _node = x._node;
            l_node = x.l_node;
            _cmp = x._cmp;
            return (*this);
        }
        bool operator==(const BST_iterator& x) const
        {
            return (_node == x._node);
        }
        bool operator!=(const BST_iterator& x) const
        {
            return (_node != x._node);
        }
        pointer operator->() const
        {
            return(&(_node->value));
        }
        reference operator*() const
        {
            return(_node->value);
        }
        BST_iterator operator++(void)
        {
            T* pos = _node;
            if (pos == l_node)
                _node = pos->right;
            else if (pos->right== l_node)
            {
                pos = pos->parent;
                while (pos != l_node && _cmp(pos->value.first, _node->value.first))
                    pos = pos->parent;
                _node = pos;
            }
            else
            {
                pos = _node->right;
                if (pos == l_node->parent && pos->right == l_node)
                    _node = pos;
                else
                    while (pos->left != l_node)
                        pos = pos->left;
                _node = pos;
            }
            return (*this);
        }
        BST_iterator operator--(void)
        {
            T* pos;
            if (_node->left != nullptr)
            {
                _node = _node->left;
                while (_node->right != nulllptr)
                    _node = pos->right;
            }
            else
            {
                pos = _node->parent;
                {
                    while (pos != nullptr && _node == pos->left)
                    {
                        _node = pos;
                        pos = pos->parent;
                    }
                    _node = pos;
                }
            }
        }
        BST_iterator operator++(int)
        {

        }
        BST_iterator operator--(int)
        {

        }
    private : 
        T* _node;
        T* l_node;
        Compare _cmp;
};

template < class T, class Compare = ft::less<T>, class Node = ft::BSTNode<T>, class Alloc = std::allocator<T>, class Node_alloc = std::allocator<Node> >
class BRT
{
    
    public :
        typedef T       value_type;
        typedef Node    node_type;
        typedef Node*   node_pointer;
        typedef Node_alloc node_alloc;
    public :
        BRT() {

        }
    private :
        
};