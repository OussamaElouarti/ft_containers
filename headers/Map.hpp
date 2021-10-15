#pragma once

#include <exception>
#include <cstring>
#include <memory>
#include "AVL.hpp"

namespace ft
{
    template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
    class Map 
    {
        public :
            typedef Key                                         key_type;
            typedef T                                           mapped_type;
            typedef ft::pair<const key_type, mapped_type>       value_type;
            typedef Compare                                     key_compare;
            typedef class value_compare : std::binary_function<value_type,value_type,bool>
            {   
                friend class Map;
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
            typedef ft::map_iterator<const value_type, ft::AVLNODE<const value_type> , key_compare, tree>    const_iterator;
            typedef ft::reverse_iterator<iterator>              reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;
            typedef std::ptrdiff_t                              difference_type;
            typedef size_t                                      size_type;
        public :

            // constructors
            explicit Map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _cmp(comp)
            {}
            template <class InputIterator>
            Map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _cmp(comp)
            {
                for (;first != last; first++)
                    _avl.insert(*first);
            }
            Map (const Map& x) : _avl(x._avl), _alloc(x._alloc), _cmp(x._cmp)
            {
                
            }

            // destructor
            ~Map() {}

            // operator =
            Map& operator= (const Map& x)
            {
                _alloc = x._alloc;
                _cmp = x._cmp;
                _avl = x._avl;
                return (*this);
            }

            // iterators methods
            iterator begin() { return(_avl.begin()); }
            const_iterator begin() const { return(_avl.begin()); }
            reverse_iterator rbegin() { return(_avl.rbegin()); }
            const_reverse_iterator rbegin() const { return(_avl.rbegin()); }
            iterator end() { return(_avl.end()); }
            const_iterator end() const { return(_avl.end()); }
            reverse_iterator rend() { return (_avl.rend()); }
            const_reverse_iterator rend() const { return (_avl.rend()); }

            // capacity
            bool empty() {return (_avl.empty());}
            size_type size() const { return (_avl.size());}
            size_type max_size() const { return (_avl.get_alloc()); }

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
                iterator first = iterator(_avl.find(x.first), nullptr);
                ft::pair<iterator, bool> ret = ft::make_pair(first, sec);
                return (ret);
            }
            iterator insert(iterator position, const value_type& x)
            {
                (void)position;
                _avl.insert(x);
                return (iterator(_avl.find(x.first), nullptr));
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
            void swap(Map& x)
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
                return (iterator(_avl.find(x), nullptr));
            }
            const_iterator find(const key_type& x) const
            {
                return (iterator(_avl.find(x), _avl));
            }

            size_type count(const key_type& x) const
            {
                return (_avl.contains(x));
            }

            iterator lower_bound(const key_type& x)
            {
                return (iterator(_avl.bound(x, "lower"), nullptr));
            }
            const_iterator lower_bound(const key_type& x) const
            {
                return (iterator(_avl.bound(x, "lower"), nullptr));
            }

            iterator upper_bound(const key_type& x)
            {
                return (iterator(_avl.bound(x, "upper"), nullptr));
            }
            const_iterator upper_bound(const key_type& x) const
            {
                return (iterator(_avl.bound(x, "upper"), nullptr));
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

            allocator_type get_allocator() const { return (_avl.get_allocator()); }
            
        // private variables
        private :
            tree                                    _avl;
            allocator_type                          _alloc;
            key_compare                             _cmp;
    };
    template <class Key, class T, class Compare, class Alloc>
    bool operator== ( const Map<Key,T,Compare,Alloc>& lhs, const Map<Key,T,Compare,Alloc>& rhs )
    {
        // if (lhs.size() == rhs.size())
        // {
        //     lhs::iterator it = lhs.begin();
        //     rhs::iterator it1 = rhs.begin();
        //     for (; it != lhs.end(); it++)
        //     {
        //         (it->first != it1->first)
        //             return false;
        //         it1++;
        //     }
        //     return true;
        // }
        return (false);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator!= ( const Map<Key,T,Compare,Alloc>& lhs, const Map<Key,T,Compare,Alloc>& rhs );
    // {
    //     return (!(lhs == rhs));
    // }

    template <class Key, class T, class Compare, class Alloc>
    bool operator<  ( const Map<Key,T,Compare,Alloc>& lhs, const Map<Key,T,Compare,Alloc>& rhs );

    template <class Key, class T, class Compare, class Alloc>
    bool operator<= ( const Map<Key,T,Compare,Alloc>& lhs, const Map<Key,T,Compare,Alloc>& rhs );

    template <class Key, class T, class Compare, class Alloc>
    bool operator>  ( const Map<Key,T,Compare,Alloc>& lhs,  const Map<Key,T,Compare,Alloc>& rhs );

    template <class Key, class T, class Compare, class Alloc>
    bool operator>= ( const Map<Key,T,Compare,Alloc>& lhs,  const Map<Key,T,Compare,Alloc>& rhs );
    
    template <class Key, class T, class Compare, class Alloc>
    void swap (Map<Key,T,Compare,Alloc>& x, Map<Key,T,Compare,Alloc>& y)
    {
        x.swap(y);
    }
}