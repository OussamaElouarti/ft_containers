#pragma once

#include  <exception>
#include <cstring>
#include <memory>
#include "ReverseIterator.hpp"
#include "tools.hpp"
#include "BST.hpp"

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
            typedef Alloc                                       allocator_type;
            typedef typename allocator_type::reference          reference;
            typedef typename allocator_type::const_reference    const_reference;
            typedef typename allocator_type::pointer            pointer;
            typedef typename allocator_type::const_pointer      const_pointer;
            typedef ft::bidirectional_iterator<value_type>          iterator;
            typedef ft::bidirectional_iterator<const value_type>    const_iterator;
            typedef ft::reverse_iterator<iterator>              reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;
            typedef std::ptrdiff_t                              difference_type;
            typedef size_t                                      size_type;
        public :
            explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _cmp(nullptr), _bst(nullptr), _alloc(alloc)
            {}
            template <class InputIterator>
            map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _cmp(comp), _bst() 
            {}
            map (const map& x) :_alloc(x._alloc), _cmp(x._cmp), _bst(x._bst)
            {}
            key_compare key_comp() const;
            value_compare value_comp() const;
            iterator begin();
            const_iterator begin();
            reverse_iterator rbegin();
            const_reverse_iterator rbegin();
            iterator end();
            const_iterator end();
            reverse_iterator rend();
            const_reverse_iterator rend();
            bool empty();
            size_type size() const;
            size_type max_size() const;
            mapped_type& operator[] (const key_type& k);
            ft::pair<iterator,bool> insert(const value_type& x);
            iterator insert(iterator position, const value_type& x);
            template <class InputIterator>
            void insert (InputIterator first, InputIterator last);
            void erase(iterator position);
            size_type erase(const key_type& x);
            void erase(iterator first, iterator last);
            void clear();
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
            allocator_type                  _alloc;
            key_compare                     _cmp;
            BST<value_type, key_compare>    _bst;
    };
}