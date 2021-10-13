#pragma once

#include  <exception>
#include <cstring>
#include <memory>
#include "ReverseIterator.hpp"
#include "tools.hpp"
#include "AVL.hpp"

namespace ft
{
    template < class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
    class map 
    {
        public :
            typedef Key                                         key_type;
            typedef T                                           mapped_type;
            typedef ft::pair<const key_type, mapped_type>       value_type;
            typedef Compare                                     key_compare;
            typedef class value_compare : std::binary_function<value_type,value_type,bool>
            {   
                friend class map;
                protected:
                    Compare comp;
                    value_compare (Compare c) : comp(c) {}
                public:
                    typedef bool result_type;
                    typedef value_type first_argument_type;
                    typedef value_type second_argument_type;
                    bool operator() (const value_type& x, const value_type& y) const
                    {
                        return comp(x.first, y.first);
                    }
            }    value_compare;
            typedef Alloc                                       allocator_type;
            typedef typename allocator_type::reference          reference;
            typedef typename allocator_type::const_reference    const_reference;
            typedef typename allocator_type::pointer            pointer;
            typedef typename allocator_type::const_pointer      const_pointer;
            typedef ft::AVL<value_type, key_compare, allocator_type>    tree;
            typedef ft::map_iterator<value_type, ft::AVLNODE<value_type> , key_compare, tree>          iterator;
            typedef ft::map_iterator<const value_type, ft::AVLNODE<value_type> , key_compare, tree>    const_iterator;
            typedef ft::reverse_iterator<iterator>              reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;
            typedef std::ptrdiff_t                              difference_type;
            typedef size_t                                      size_type;
        public :

            // constructors
            explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _cmp(comp), _alloc(alloc)
            {}
            template <class InputIterator>
            map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _cmp(comp)
            {
                for (;first != last; first++)
                    _avl.insert(*first);
            }
            map (const map& x) :_alloc(x._alloc), _cmp(x._cmp), _avl(x._avl)
            {}

            // destructor
            ~map() {}

            // operator =
            map& operator= (const map& x)
            {
                _alloc = x._alloc;
                _cmp = x._cmp;
                _avl = x._avl;
                return (*this);
            }

            // iterators methods
            iterator begin() { return(_avl.begin()); }
            const_iterator begin() const { return(_avl.begin()); }
            reverse_iterator rbegin();
            const_reverse_iterator rbegin() const;
            iterator end() { return(_avl.end()); }
            const_iterator end() const { return(_avl.begin()); }
            reverse_iterator rend();
            const_reverse_iterator rend() const;

            // capacity
            bool empty() {return (_avl.empty());}
            size_type size() const { return (_avl.size());}
            size_type max_size() const { return (_alloc.max_size()); }
            
            // observers
            key_compare key_comp() const { return (_cmp); }
            value_compare value_comp() const { return (value_compare(_cmp));}

            // elements access
            mapped_type& operator[] (const key_type& k);

             // modifiers
            bool insert(const value_type& x)
            {
                return(_avl.insert(x));
            }
            iterator insert(iterator position, const value_type& x);
            template <class InputIterator>
            void insert (InputIterator first, InputIterator last);

            void erase(iterator position);
            size_type erase(const key_type& x);
            void erase(iterator first, iterator last);

            void clear() { _avl.clear();}
            
            iterator find(const key_type& x);
            const_iterator find(const key_type& x) const;

            size_type count(const key_type& x) const;

            iterator lower_bound(const key_type& x);
            const_iterator lower_bound(const key_type& x) const;

            iterator upper_bound(const key_type& x);
            const_iterator upper_bound(const key_type& x) const;
            
            ft::pair<iterator,iterator> equal_range(const key_type& x);
            ft::pair<const_iterator,const_iterator> equal_range(const key_type& x) const;
        private :
            allocator_type                          _alloc;
            key_compare                             _cmp;
            tree                                    _avl;
    };
}