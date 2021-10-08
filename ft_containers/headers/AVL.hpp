#pragma once

#include "tools.hpp"

template <class T, class Compare = ft::less<T>, class Alloc = std::allocator<T> >
class AVL
{

public:
    typedef T value_type;
    typedef ft::AVLNODE<T> node_type;
    typedef ft::AVLNODE<T> *node_pointer;
    typedef Alloc pair_alloc;
    typedef typename Alloc::template rebind<ft::AVLNODE<T> >::other node_alloc;

public:
    AVL() : _root(nullptr), _size(0) {}
    ~AVL() {}
    int size() { return (_size); }
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
    bool contains(value_type val) { return (contains(_root, val)); }

    // insert/add value , value != null, 0(log(n))
    bool insert(value_type value)
    {
        if (!value)
            return false;
        if (!contains(_root, value))
        {
            _root = insert(_root, value);
            _size++;
            return true;
        }
        return false;
    }

    // remove value , value != null, 0(log(n))
    bool remove(value_type val)
    {
        if (!val)
            return false;
        if (contains(_root, val))
        {
            _root = remove(_root, val);
            _size--;
            return true;
        }
        return false;
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
    bool contains(node_pointer node, value_type val)
    {
        if (node == nullptr)
            return false;
        bool cmp = _comp(*(node->data), val);
        if (!cmp)
            return (contains(node->left, val));
        if (cmp)
            return (contains(node->right, val));
        return true;
    }

    //insert overload
    node_pointer insert(node_pointer node, value_type val)
    {
        if (node == nullptr)
            return (newNode(val));
        bool cmp = _comp(val, *(node->data));
        if (cmp)
            node->left = insert(node->left, val);
        else if (!cmp)
            node->right = insert(node->right, val);
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
        int cmp = _cmp(val, node->data);
        if (cmp < 0)
            node->left = remove(node->left, val);
        else if (cmp > 0)
            node->right = remove(node->right, val);
        else
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
                    node->value = Svalue;
                    node->left = remove(node->left, Svalue);
                }
                else
                {
                    value_type Svalue = findMin(node->right);
                    node->value = Svalue;
                    node->right = remove(node->right, Svalue);
                }
            }
        }
        update(node);
        return (balance(node));
    }
    // methods to help find min and max value
    value_type findMin(node_type node)
    {
        while (node->left != nullptr)
            node = node->left;
        return node->data;
    }
    value_type findMax(node_type node)
    {
        while (node->right != nullptr)
            node = node->right;
        return node->data;
    }

public:
    node_pointer _root;

private:
    int _size;
    node_alloc n_alloc;
    pair_alloc p_alloc;
    Compare _comp;
};