#pragma once

#include "tools.hpp"
#include "mapIterator.hpp"
#include "ReverseIterator.hpp"

namespace ft
{
    template <class T, class Compare = std::less<typename T::first_type>, class Alloc = std::allocator<T> >
    class AVL
    {
    public:
        typedef T               value_type;
        typedef ft::AVLNODE<T>  node_type;
        typedef ft::AVLNODE<const T> const_node;
        typedef ft::AVLNODE<T> *node_pointer;
        typedef Alloc pair_alloc;
        typedef typename Alloc::template rebind<ft::AVLNODE<T> >::other node_alloc;
        typedef ft::map_iterator<value_type, node_type, Compare, AVL> iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::map_iterator<const value_type, const_node, Compare, AVL> const_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef typename value_type::first_type          key;
        typedef typename value_type::second_type          value;

    public:
        AVL() : _root(nullptr), _size(0) {}
        AVL(AVL &x) : _root(x._root), _size(x._size) {}
        ~AVL() {}
        
        AVL&    operator= (const AVL& x)
        {
            _root = x._root;
            _size = x._size;
        }

        // return the size of the tree
        int size() { return (_size); }

        // checking if th tree is empty or not
        bool empty()
        {
            if (_size == 0)
                return true;
            return false;
        }

        // clearing the tree
        void clear() { _size = 0; }

        // end and begin
        iterator begin() { return (iterator(find(findMin(_root).first), *this)); }
        iterator end() { return (iterator()); }
        const_iterator begin() const { return (iterator(find(findMin(_root).first), this)); }
        const_iterator end() const { return (nullptr, this); }

        // rend and rbegin
        reverse_iterator rbegin() { return (iterator(find(findMin(_root).first), this)); }
        reverse_iterator rend() { return (iterator(nullptr, this)); }
        const_reverse_iterator rbegin() const { return (iterator(find(findMin(_root)), this)); }
        const_reverse_iterator rend() const { return (nullptr, this); }

        // create a new node
        node_pointer newNode(value_type obj)
        {
            node_pointer node = n_alloc.allocate(1);
            n_alloc.construct(node);
            node->data = p_alloc.allocate(1);
            p_alloc.construct(node->data, obj);
            return (node);
        }

        // calculate the height of the node
        int height()
        {
            if (_root == nullptr)
                return (0);
            return (height(_root) - 1);
        }

        // checking if value already exist in the AVL tree
        bool contains(key k) { return (contains(_root, k)); }

        // insert/add value , value != null, 0(log(n))
        bool insert(value_type value)
        {
            if (!contains(_root, value.first))
            {
                _root = insert(_root, value);
                _size++;
                return true;
            }
            return false;
        }

        // remove value , value != null, 0(log(n))
        bool remove(key val)
        {
            if (contains(_root, val))
            {
                _root = remove(_root, val);
                _root->parent = nullptr;
                _size--;
                return true;
            }
            return false;
        }

        // find value, value != null, 0(log(n))
        node_pointer find(key val)
        {
            if (contains(_root, val))
                return (find(_root, val));
            return nullptr;
        }

        node_pointer bound(key val, std::string s)
        {
            if (s == "lower")
                return (lower_bound(_root, val));
            else
                return (upper_bound(_root, val));
            return nullptr;
        }
    private:
        //height overload
        int height(node_pointer node)
        {
            if (node == nullptr)
                return -1;
            int leftHeight = height(node->left) + 1;
            int rightHeight = height(node->right) + 1;
            if (leftHeight > rightHeight)
                return leftHeight;
            return rightHeight;
        }

        //contains overload
        bool contains(node_pointer node, key k)
        {
            if (node == nullptr)
                return false;
            bool cmp = _comp(node->data->first, k);
            if (k == (node->data->first))
                return true;
            if (!cmp)
                return (contains(node->left, k));
            if (cmp)
                return (contains(node->right, k));
            return true;
        }

        //insert overload
        node_pointer insert(node_pointer node, value_type val)
        {
            if (node == nullptr)
                return (newNode(val));
            bool cmp = _comp(val.first, node->data->first);
            if (cmp)
            {
                node->left = insert(node->left, val);
                node->left->parent = node;
            }
            else if (!cmp)
            {
                node->right = insert(node->right, val);
                node->right->parent = node;
            }
            update(node);
            return (balance(node));
        }

        // update the node after insertion or deletion
        void update(node_pointer node)
        {
            int leftNodeHeight = (node->left == nullptr) ? -1 : node->left->height;
            int rightNodeHeight = (node->right == nullptr) ? -1 : node->right->height;
            node->height = 1 + std::max(leftNodeHeight, rightNodeHeight);
            node->bf = rightNodeHeight - leftNodeHeight;
        }

        // balance the tree after insertion or deletion
        node_pointer balance(node_pointer node)
        {
            if (node->bf == -2)
            {
                if (node->left->bf <= 0)
                    return leftleftCase(node);
                else
                    return leftrightCase(node);
            }
            else if (node->bf == 2)
            {
                if (node->right->bf >= 0)
                    return rightrightCase(node);
                else
                    return rightleftCase(node);
            }
            return node;
        }

        // cases
        node_pointer leftleftCase(node_pointer node) { return rightRotation(node); }
        node_pointer leftrightCase(node_pointer node)
        {
            node->left = leftRotation(node->left);
            return leftleftCase(node);
        }
        node_pointer rightrightCase(node_pointer node) { return leftRotation(node); }
        node_pointer rightleftCase(node_pointer node)
        {
            node->right = rightRotation(node->right);
            return rightrightCase(node);
        }

        // rotations
        node_pointer leftRotation(node_pointer node)
        {
            node_pointer tmp = node->right;
            node->right = tmp->left;
            tmp->left = node;
            update(node);
            update(tmp);
            return tmp;
        }
        node_pointer rightRotation(node_pointer node)
        {
            node_pointer tmp = node->left;
            node->left = tmp->right;
            tmp->right = node;
            update(node);
            update(tmp);
            return tmp;
        }

        // remove overload
        node_pointer remove(node_pointer node, value_type val)
        {
            if (node == nullptr)
                return nullptr;
            int cmp = _comp(val.first, *(node->data->first));
            if (val.first == *(node->data->first))
            {
                if (node->left == nullptr)
                    return node->right;
                else if (node->right == nullptr)
                    return node->left;
                else
                {
                    if (height(node->left) > height(node->right))
                    {
                        value_type Svalue = findMax(node->left);
                        *(node->data) = Svalue;
                        node->left = remove(node->left, Svalue);
                    }
                    else
                    {
                        value_type Svalue = findMin(node->right);
                        *(node->data) = Svalue;
                        node->right = remove(node->right, Svalue);
                    }
                }
            }
            else if (cmp)
                node->left = remove(node->left, val);
            else if (!cmp)
                node->right = remove(node->right, val);
            update(node);
            return (balance(node));
        }
        // methods to help find min and max value
        value_type findMin(node_pointer node)
        {
            while (node->left != nullptr)
                node = node->left;
            return (*(node->data));
        }
        value_type findMax(node_pointer node)
        {
            while (node->right != nullptr)
                node = node->right;
            return (*(node->data));
        }

        // overload for find
        node_pointer find(node_pointer node, key val)
        {
            if (node == nullptr)
                return nullptr;
            bool cmp = _comp(node->data->first, val);
            if (val == node->data->first)
                return node;
            if (!cmp)
                return (find(node->left, val));
            else if (cmp)
                return (find(node->right, val));
            return node;
        }

        node_pointer lower_bound(node_pointer node, key val)
        {
            if (node == nullptr)
                return nullptr;
            bool cmp = _comp(node->data->first, val);
            if (val == node->data->first)
                return node;
            if (!cmp)
            {
                if (node->left == nullptr)
                    return node->parent;
                else
                    return (lower_bound(node->left, val));
            }
            else if (cmp)
            {
                if (node->right == nullptr || node->right->data->first > val)
                    return nullptr;
                else
                    return (lower_bound(node->right, val));
            }
            return nullptr;
        }

        node_pointer upper_bound(node_pointer node, key val)
        {
            if (node == nullptr)
                return nullptr;
            bool cmp = _comp(node->data->first, val);
            if (val == node->data->first)
                return node->parent;
            if (!cmp)
            {
                if (node->left == nullptr)
                    return node;
                else
                    return (upper_bound(node->left, val));
            }
            else if (cmp)
            {
                if (node->right == nullptr || node->right->data->first > val)
                    return node->right;
                else
                    return (upper_bound(node->right, val));
            }
            return nullptr;
        }

    public:
        node_pointer _root;

    private:
        int _size;
        node_alloc n_alloc;
        pair_alloc p_alloc;
        Compare _comp;
    };
}