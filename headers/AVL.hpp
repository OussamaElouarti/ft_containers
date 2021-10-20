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
        typedef T value_type;
        typedef ft::AVLNODE<const T> const_node;
        typedef Alloc pair_alloc;
        typedef typename Alloc::template rebind<ft::AVLNODE<T> >::other node_alloc;
        typedef ft::map_iterator<T, ft::AVLNODE<T>, Compare, AVL> iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::map_iterator<const T, const ft::AVLNODE<T>, Compare, AVL> const_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef typename value_type::first_type          key;
        typedef typename value_type::second_type          value;

    public:
        AVL() : _root(nullptr), _size(0) {}
        AVL(const AVL &x) : _root(nullptr) {
            *this = assign(x);
        }
        ~AVL() {
            // deleteTree();
        }
        
        AVL&    assign (AVL const& x)
        {
            deleteTree();
            p_alloc = x.p_alloc;
            n_alloc = x.n_alloc;
            _comp = x._comp;
            for (const_iterator it = x.begin(); it != x.end(); it++)
                insert(*it);
            _size = x._size;
            return *this;
        }

        // return the size of the tree
        int size() const { return (_size); }

        // checking if th tree is empty or not
        bool empty()
        {
            if (_size == 0)
                return true;
            return false;
        }
        void deleteTree()
        {
            _root = _deleteTree(_root);
            _size = 0;
        }
        ft::AVLNODE<T> * _deleteTree(ft::AVLNODE<T> * node)
        {
            if (node != nullptr)
            {
                _deleteTree(node->left);
                _deleteTree(node->right);
                deleteNode(node);
            }
            return nullptr;
        }
        void deleteNode(ft::AVLNODE<T> * node)
        {
            p_alloc.destroy(node->data);
            p_alloc.deallocate(node->data, 1);
            node->data = NULL;
            n_alloc.deallocate(node, 1);
            node = NULL;
        }
        // clearing the tree
        void clear() { _size = 0; }

        // end and begin
        iterator begin() {
            ft::AVLNODE<T> *first = find(findMin(_root).first);
            return (iterator(first, this));
        }
        iterator end() {
            return (iterator(NULL, this)); 
            }
        const_iterator begin() const { 
            ft::AVLNODE<T> *first = find(findMin(_root).first);
            return (iterator(first, this));
        }
        const_iterator end() const { 
            return (iterator(NULL, this)); 
        }

        // rend and rbegin
        reverse_iterator rbegin() { return reverse_iterator(end()); }
        reverse_iterator rend() { return (reverse_iterator(begin())); }
        const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
        const_reverse_iterator rend() const { return (const_reverse_iterator(begin())); }

        // create a new node
        ft::AVLNODE<T>* newNode(T obj)
        {
            ft::AVLNODE<T>* node = n_alloc.allocate(1);
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
        bool contains(key k) const { return (contains(_root, k)); }

        // insert/add value , value != null, 0(log(n))
        bool insert(T value)
        {
            if (!contains(_root, value.first))
            {
                _root = insert(_root, value);
                _root->parent = nullptr;
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
                // _root->parent = nullptr;
                _size--;
                return true;
            }
            return false;
        }

        // find value, value != null, 0(log(n))
        ft::AVLNODE<T>* find(key val)
        {
            if (contains(_root, val))
                return (find(_root, val));
            return nullptr;
        }
        ft::AVLNODE<T>* find(key val) const
        {
            if (contains(_root, val))
                return (find(_root, val));
            return nullptr;
        }

        iterator bound(key val, std::string s)
        {
            ft::AVLNODE<T>* con = nullptr;
            if (s == "lower")
            {
                lower_bound(_root, val, &con);
                if (!con)
                    return(iterator(nullptr, this));
                else
                    return iterator(con, this);
            }
            else
            {
                upper_bound(_root, val, &con);
                if (!con)
                    return(iterator(nullptr, this));
                else
                    return iterator(con, this);
            }
            return iterator(nullptr, this);
        }
        
        const_iterator bound(key val, std::string s) const
        {
            ft::AVLNODE<T>* con = nullptr;
            if (s == "lower")
            {
                lower_bound(_root, val, &con);
                if (!con)
                    return(const_iterator(nullptr, this));
                else
                    return const_iterator(con, this);
            }
            else
            {
                upper_bound(_root, val, &con);
                if (!con)
                    return(const_iterator(nullptr, this));
                else
                    return const_iterator(con, this);
            }
            return iterator(nullptr, this);
        }

        // allocator methods
        size_t get_alloc() const { return (n_alloc.max_size()); }
        node_alloc get_allocator() const { return (n_alloc); }
        ft::AVLNODE<T>* getRoot( void ) const { return (_root); }
        // methods to help find min and max value
        ft::AVLNODE<T>* findm(ft::AVLNODE<T>* node) 
        {
            while (node->left != nullptr)
                node = node->left;
            return (node);
        }
        ft::AVLNODE<T>* findM(ft::AVLNODE<T>* node) 
        {
            while (node->right != nullptr)
                node = node->right;
            return (node);
        }
        ft::AVLNODE<T>* findm(ft::AVLNODE<T>* node) const
        {
            while (node->left != nullptr)
                node = node->left;
            return (node);
        }
        ft::AVLNODE<T>* findM(ft::AVLNODE<T>* node) const
        {
            while (node->right != nullptr)
                node = node->right;
            return (node);
        }

    private:
        //height overload
        int height(ft::AVLNODE<T>* node)
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
        bool contains(ft::AVLNODE<T>* node, key k) const
        {
            if (node == nullptr)
                return false;
            bool cmp = _comp(node->data->first, k);
            bool cmp1 = _comp(k, node->data->first);
            if (!cmp1 && !cmp)
                return true;
            if (!cmp)
                return (contains(node->left, k));
            if (cmp)
                return (contains(node->right, k));
            return true;
        }

        //insert overload
        ft::AVLNODE<T>* insert(ft::AVLNODE<T>* node, T val)
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
        void update(ft::AVLNODE<T>* node)
        {
            int leftNodeHeight = (node->left == nullptr) ? -1 : node->left->height;
            int rightNodeHeight = (node->right == nullptr) ? -1 : node->right->height;
            node->height = 1 + std::max(leftNodeHeight, rightNodeHeight);
            node->bf = rightNodeHeight - leftNodeHeight;
        }

        // balance the tree after insertion or deletion
        ft::AVLNODE<T>* balance(ft::AVLNODE<T>* node)
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
        ft::AVLNODE<T>* leftleftCase(ft::AVLNODE<T>* node) { return rightRotation(node); }
        ft::AVLNODE<T>* leftrightCase(ft::AVLNODE<T>* node)
        {
            node->left = leftRotation(node->left);
            return leftleftCase(node);
        }
        ft::AVLNODE<T>* rightrightCase(ft::AVLNODE<T>* node) { return leftRotation(node); }
        ft::AVLNODE<T>* rightleftCase(ft::AVLNODE<T>* node)
        {
            node->right = rightRotation(node->right);
            return rightrightCase(node);
        }

        // rotations
        ft::AVLNODE<T>* leftRotation(ft::AVLNODE<T>* node)
        {
            ft::AVLNODE<T>* tmp = node->right;
            node->right = tmp->left;
            tmp->left = node;
            _resetParent(node, tmp);
            update(node);
            update(tmp);
            return tmp;
        }
        ft::AVLNODE<T>* rightRotation(ft::AVLNODE<T>* node)
        {
            ft::AVLNODE<T>* tmp = node->left;
            node->left = tmp->right;
            tmp->right = node;
            _resetParent(node, tmp);
            update(node);
            update(tmp);
            return tmp;
        }


        void _resetParent(ft::AVLNODE<T>* oldRoot, ft::AVLNODE<T>* newRoot) const
        {
            if (!oldRoot->parent)
            {
                newRoot->parent = NULL;
                if (oldRoot->left)
                    oldRoot->left->parent = oldRoot;
                if (oldRoot->right)
                    oldRoot->right->parent = oldRoot;
                oldRoot->parent = newRoot;
                return;
            }
            newRoot->parent = oldRoot->parent;
            oldRoot->parent = newRoot;
            if (oldRoot->left)
                oldRoot->left->parent = oldRoot;
            if (oldRoot->right)
                oldRoot->right->parent = oldRoot;
        }

        // remove overload
        ft::AVLNODE<T>* remove(ft::AVLNODE<T>* node, key val)
        {
            if (node == nullptr)
                return nullptr;
            int cmp = _comp(val, node->data->first);
            bool cmp1 = _comp(node->data->first, val);
            if (!cmp && !cmp1)
            {
                if (node->left == nullptr)
                    return node->right;
                else if (node->right == nullptr)
                    return node->left;
                else
                {
                    if (height(node->left) > height(node->right))
                    {
                        T Svalue = findMax(node->left);
                        node->data = &Svalue;
                        node->left = remove(node->left, Svalue.first);
                    }
                    else
                    {
                        T Svalue = findMin(node->right);
                        node->data = &Svalue;
                        node->right = remove(node->right, Svalue.first);
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

        // overload for find
        ft::AVLNODE<T>* find(ft::AVLNODE<T>* node, key val)
        {
            if (node == nullptr)
                return nullptr;
            bool cmp = _comp(node->data->first, val);
            bool cmp1 = _comp(val, node->data->first);
            if (!cmp && !cmp1)
                return node;
            if (!cmp)
                return (find(node->left, val));
            else if (cmp)
                return (find(node->right, val));
            return node;
        }

        ft::AVLNODE<T>* find(ft::AVLNODE<T>* node, key val) const
        {
            if (node == nullptr)
                return nullptr;
            bool cmp = _comp(node->data->first, val);
            bool cmp1 = _comp(val, node->data->first);
            if (!cmp && !cmp1)
                return node;
            if (!cmp)
                return (find(node->left, val));
            else if (cmp)
                return (find(node->right, val));
            return node;
        }

        void lower_bound(ft::AVLNODE<T>* node, key val, ft::AVLNODE<T>** con) const
        {
            if (node == nullptr)
                return ;
            bool cmp = _comp(node->data->first, val);
            bool cmp1 = _comp(val, node->data->first);
            if (!cmp && !cmp1)
            {
                *con = node;
                return ;
            }
            if (!cmp)
                lower_bound(node->left, val, con);
            if (*con == nullptr && !cmp)
            {
                *con = node;
                return ;
            }
            if (cmp)
                lower_bound(node->right, val, con);
        }

        T findMin(ft::AVLNODE<T>* node) 
        {
            if (node == nullptr)
                return (ft::make_pair(key(), value()));
            while (node->left != nullptr)
                node = node->left;
            return (*(node->data));
        }
        T findMax(ft::AVLNODE<T>* node) 
        {
            if (node == nullptr)
                return (ft::make_pair(key(), value()));
            while (node->right != nullptr)
                node = node->right;
            return (*(node->data));
        }
        T findMin(ft::AVLNODE<T>* node) const
        {
            if (node == nullptr)
                return (ft::make_pair(key(), value()));
            while (node->left != nullptr)
                node = node->left;
            return (*(node->data));
        }
        T findMax(ft::AVLNODE<T>* node) const
        {
            if (node == nullptr)
                return (ft::make_pair(key(), value()));
            while (node->right != nullptr)
                node = node->right;
            return (*(node->data));
        }

        void upper_bound(ft::AVLNODE<T>* node, key val, ft::AVLNODE<T>** con) const
        {
            if (node == nullptr)
                return ;
            bool cmp =_comp(node->data->first, val);
            bool cmp1 = _comp(val, node->data->first);
            if (!cmp && !cmp1)
            {
                *con = node->right;
                return ;
            }
            if (!cmp)
                upper_bound(node->left, val, con);
            if (*con == nullptr && !cmp)
            {
                *con = node;
                return ;
            }
            if (cmp)
                upper_bound(node->right, val, con);
        }
    private:
        ft::AVLNODE<T>* _root;
        node_alloc n_alloc;
        pair_alloc p_alloc;
        int _size;
        Compare _comp;
    };
}