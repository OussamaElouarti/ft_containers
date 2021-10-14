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
            mapped_type& operator[] (const key_type& k)
            {
                return (_avl.find(k)->data->second);
            }

            // modifiers
            //insert
            ft::pair<iterator, bool> insert(const value_type& x)
            {
                bool sec = _avl.insert(x);
                iterator first = iterator(_avl.find(x.first), _avl);
                ft::pair<iterator, bool> ret = ft::make_pair(first, sec);
                return (ret);
            }
            iterator insert(iterator position, const value_type& x)
            {
                (void)position;
                _avl.insert(x);
                return (iterator(_avl.find(x.first), _avl));
            }
            template <class InputIterator>
            void insert (InputIterator first, InputIterator last)
            {
                for (; first != last; first++)
                    _avl.insert(*first);
                return ;
            }
            // erase 
            void erase(iterator position)
            {
                _avl.remove(position->first);
                return ;
            }
            size_type erase(const key_type& x)
            {
                return (_avl.remove(x));
            }
            void erase(iterator first, iterator last)
            {
                for (; first != last; first++)
                    _avl.remove(first->first);
                return ;
            }

            // swap
            void swap(map& x)
            {
                key_compare     tmp_cmp;
                tree            tmp_avl;

                tmp_cmp = x._cmp;
                x._cmp = _cmp;
                _cmp = tmp_cmp;

                tmp_avl = x._avl;
                x._avl = _avl;
                _avl = tmp_avl;

                return ;
            }

            //clear
            void clear() { _avl.clear();}
            
            // operations
            iterator find(const key_type& x)
            {
                return (iterator(_avl.find(x), _avl));
            }
            const_iterator find(const key_type& x) const
            {
                return (iterator(_avl.find(x), _avl));
            }

            size_type count(const key_type& x) const
            {
                return (_avl.countains(x));
            }

            iterator lower_bound(const key_type& x)
            {
                return (iterator(_avl.bound(x, "lower"), _avl));
            }
            const_iterator lower_bound(const key_type& x) const
            {
                return (iterator(_avl.bound(x, "lower"), _avl));
            }

            iterator upper_bound(const key_type& x)
            {
                return (iterator(_avl.bound(x, "upper"), _avl));
            }
            const_iterator upper_bound(const key_type& x) const
            {
                return (iterator(_avl.bound(x, "upper"), _avl));
            }
            
            ft::pair<iterator,iterator> equal_range(const key_type& x)
            {
                ft::pair<iterator,iterator> ret =  ft::make_pair(lower_bound(x), upper_bound(x));
                return (ret);
            }
            ft::pair<const_iterator,const_iterator> equal_range(const key_type& x) const
            {
                ft::pair<const_iterator,const_iterator> ret =  ft::make_pair(lower_bound(x), upper_bound(x));
                return (ret);
            }
            
        // private variables
            tree                                    _avl;
        private :
            allocator_type                          _alloc;
            key_compare                             _cmp;
    };
    template <class Key, class T, class Compare, class Alloc>
    bool operator== ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );

    template <class Key, class T, class Compare, class Alloc>
    bool operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );

    template <class Key, class T, class Compare, class Alloc>
    bool operator<  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );

    template <class Key, class T, class Compare, class Alloc>
    bool operator<= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );

    template <class Key, class T, class Compare, class Alloc>
    bool operator>  ( const map<Key,T,Compare,Alloc>& lhs,  const map<Key,T,Compare,Alloc>& rhs );

    template <class Key, class T, class Compare, class Alloc>
    bool operator>= ( const map<Key,T,Compare,Alloc>& lhs,  const map<Key,T,Compare,Alloc>& rhs );
    
    template <class Key, class T, class Compare, class Alloc>
    void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
    {
        x.swap(y);
    }
}