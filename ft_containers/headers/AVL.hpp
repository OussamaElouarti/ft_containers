#pragma once

#include  "tools.hpp"

template < class T, class Compare, class Alloc >
class AVL
{
    
    public :
        typedef T                                                       alue_type;
        typedef AVLNode<T>                                              ode_type;
        typedef AVLNode*                                                ode_pointer;
        typedef                                                         Alloc pair_alloc;
        typedef typename std::allocator_traits<MyAllocator>::template  rebind_alloc<AVLNode<T>> node_alloc;
    public :
        AVL() : _root(nullptr), _size(0) {}
        node_type newNode(T obj) {
            node_type node;
            node = n_alloc.allocate(1);
            obj = p_alloc.allocate(1);
            p_alloc.construct(obj);
            return (node);
        }
        void addNode(T obj)
        {
            node_type node = newNode(obj);
            if (root == nullptr) {
                _root = node;
                _size++;
                return ;
            }
            add(root, node);
        }
        void add(node_type parent, node_type newNode)
        {
            if (_comp(parent.first(), newNode.first()))
            {
                if (parent.right == nullptr)
                {
                    parent.right = newNode;
                    newNode.parent = parent;
                    _size++;
                }
                else
                    add(parent.right, newNode);
            }
            else
            {
                if (parent.left == nullptre)
                {
                    parent.left = newNode;
                    newNode.parent = parent;
                    _size++;
                }
                else
                    add(parent.left, newNode);
            }
            checkBalance(newNode);
        }
        int height() {
            if (root == nullptr)
                return (0);
            return (height(root) - 1);
        }
        int height(node_type node) {
            if (node == nullptr)
                return 0;
            int leftHeight =  height(node.left) + 1;
            int rightHeight = height(node.right) + 1;
            if (leftHieght > rightHeight)
                return leftHeight;
            return rightHeight;
        }
        node_type rightRotate(node_type node)
        {
            node_type tmp = node.right;
            node.right = tmp.left;
            tmp.left = node;
            return tmp;
        }
        node_type leftRotate(node_type node)
        {
            node_type tmp = node.left;
            node.left = tmp.right;
            tmp.right = node;
            return tmp;
        }
        node_type rightleftRotate(node_type node)
        {
            node_type tmp = 
        }
        void rebalance(node_type node)
        {
            if (height(node.left) - height(node.right) > 1)
                if (height(node.left.left) > height(node.left.right))
                    node = rightRotate(node);
        }
        void checkBalance(node_type node)
        {
            if (height(node.left) - height(node.right) > 1 || height(node.left) - height(node.right) < -1)
                rebalance(node);
            if (node.parent == nullptr)
                return ;
            checkBalance(node.parent);    
        }
    private :
        node_pointer    _root;
        int             _size;
        node_alloc      n_alloc;
        pair_alloc      p_alloc;
        Compare         _comp;
};