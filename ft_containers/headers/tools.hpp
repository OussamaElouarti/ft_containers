#pragma once

#include <iostream>
#include <functional>
namespace ft 
{
  template <typename T> struct is_integral{static const bool value = false;};
  template <> struct is_integral<bool>{static const bool value = true;};
  template <> struct is_integral<char>{static const bool value = true;};
  template <> struct is_integral<char16_t>{static const bool value = true;};
  template <> struct is_integral<char32_t>{static const bool value = true;};
  template <> struct is_integral<wchar_t>{static const bool value = true;};
  template <> struct is_integral<signed char>{static const bool value = true;};
  template <> struct is_integral<short int>{static const bool value = true;};
  template <> struct is_integral<int>{static const bool value = true;};
  template <> struct is_integral<long int>{static const bool value = true;};
  template <> struct is_integral<long long int>{static const bool value = true;};
  template <> struct is_integral<unsigned char>{static const bool value = true;};
  template <> struct is_integral<unsigned short int>{static const bool value = true;};
  template <> struct is_integral<unsigned int>{static const bool value = true;};
  template <> struct is_integral<unsigned long int>{static const bool value = true;};
  template <> struct is_integral<unsigned long long int>{static const bool value = true;};

  template<bool B, class T = void>
  struct enable_if {};
  
  template<class T>
  struct enable_if<true, T> { typedef T type; };

  template<class InputIt1, class InputIt2>
  bool equal(InputIt1 first1, InputIt1 last1, 
            InputIt2 first2)
  {
      for (; first1 != last1; ++first1, ++first2) {
          if (!(*first1 == *first2)) {
              return false;
          }
      }
      return true;
  }

  template <class InputIterator1, class InputIterator2>
  bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
  {
    while (first1!=last1)
    {
      if (first2==last2 || *first2<*first1) return false;
      else if (*first1<*first2) return true;
      ++first1; ++first2;
    }
    return (first2!=last2);
  }
  template <class T1, class T2>
  struct pair
  {
    public:
      typedef T1 first_type;
      typedef T2 second_type;

      first_type first;
      second_type second;
      pair() : first() , second() {}
      template< class U, class V>
      pair(const pair<U,V>& pr) : first(pr.first), second(pr.second){}
      pair(const first_type& a, const second_type& b) : first(a), second(b) {}
      pair& operator= (const pair& pr)
      {
        if (this == pr)
          return (*this);
        this->first = pr.first;
        this->second = pr.second;
        return (*this);
      }
  };
  template <class T1, class T2>
  bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
  {
    return (lhs.first == rhs.first && lhs.second == rhs.second);
  }
  template <class T1, class T2>
  bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
  {
    return (!(lhs == rhs));
  }
  template <class T1, class T2>
  bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
  { return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }
  template <class T1, class T2>
  bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
  { return rhs<lhs; }
  template <class T1, class T2>
  bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
  { return !(rhs<lhs); }
  template <class T1, class T2>
  bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
  { return !(lhs<rhs); }
  template<class T1, class T2>
  pair<T1, T2> make_pair(T1 x, T2 y)
  {
    return (pair<T1, T2>(x, y));
  }

  template <class Iterator> 
  struct iterator_traits
  {
      typedef typename Iterator::difference_type       difference_type;
      typedef typename Iterator::value_type            value_type;
      typedef typename Iterator::pointer               pointer;
      typedef typename Iterator::reference             reference;
      typedef typename Iterator::iterator_category     iterator_category;
  };

  template <class T>
  struct iterator_traits<T*>
  {
      typedef ptrdiff_t                       difference_type;
      typedef T                               value_type;
      typedef T*                              pointer;
      typedef T&                              reference;
      typedef std::random_access_iterator_tag  iterator_category;
  };
    template <class T>
    class iterator_traits<const T*>
    {
        typedef ptrdiff_t                       difference_type;
        typedef T                               value_type;
        typedef const T*                        pointer;
        typedef const T&                        reference;
        typedef std::random_access_iterator_tag  iterator_category;
    };
  template<class InputIterator>
  typename iterator_traits<InputIterator>::difference_type distance (InputIterator first, InputIterator last)
  {
      typename iterator_traits<InputIterator>::difference_type rtn = 0;
      while (first != last)
      {
          first++;
          rtn++;
      }
      return (rtn);
  }

  template <class Category, class T, class Distance = ptrdiff_t,
  class Pointer = T*, class Reference = T&>
  class iterator
  {
      public:
          typedef T           value_type;
          typedef Distance    difference_type;
          typedef Pointer     pointer;
          typedef Reference   reference;
          typedef Category    iterator_category;
  };

  template <class T>
  class bidirectional_iterator : iterator<std::bidirectional_iterator_tag, T>
  {
      typedef typename iterator<std::bidirectional_iterator_tag, T>::iterator_category     iterator_category;
      typedef typename iterator<std::bidirectional_iterator_tag, T>::value_type            value_type;
      typedef typename iterator<std::bidirectional_iterator_tag, T>::difference_type       difference_type;
      typedef typename iterator<std::bidirectional_iterator_tag, T>::pointer               pointer;
      typedef typename iterator<std::bidirectional_iterator_tag, T>::reference             reference;
      
      private:
        pointer m_ptr;
  };

  template<typename T>
  struct BSTNode
  {
      typedef T       value_type;
      public :
        value_type    value;
        BSTNode       *left;
        BSTNode       *right;
        BSTNode       *parent;
        int           color;
      public :
          BSTNode() : value(), left(nullptr), right(nullptr), parent(nullptr)
          {}
          BSTNode(value_type val) : value(val), left(nullptr), right(nullptr), parent(nullptr)
          {}
          BSTNode(const BSTNode& nd) : value(nd.value), left(nd.left), right(nd.right), parent(nd.parent)
          {}
          virtual ~BSTNode();
          BSTNode& operator=(const BSTNode& nd)
          {
            value = nd.value;
            left = nd.left;
            right = nd.right;
            parent = nd.parent;
            return (*this);
          }
          bool  operator== (const BSTNode<T>& nd)
          {
              return (value == nd.value);
          }
          bool operator!=(const BSTNode<T>& nd)
          {
            return (!(value == nd.value));
          }
  };
  template <class T>
  struct less : std::binary_function<T,T,bool>
  {
    bool operator() (const T& x, const T& y) const
    {
      return (x < y);
    }
  };
}