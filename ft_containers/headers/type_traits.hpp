#pragma once

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

template <class InputIterator1, class InputIterator2>
bool equal( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
{
  while (first1!=last1 || *first2) 
  {
    if (!(*first1 == *first2))
        return false;
    ++first1; 
    ++first2;
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
template<class T1, class T2>
{ return !(lhs<rhs); }
pair<T1, T2> make_pair(T1 x, T2 y)
{
  return (pair<T1, T2>(x, y));
}