#pragma once


template<typename iterator>
class Reverse_iterator : public iterator
{
    public :
        typedef typename iterator::value_type value_type;
        typedef value_type* PointerType;
        typedef const value_type * const_PointerType;
        typedef value_type& ReferenceType;
        typedef const value_type & const_ReferenceType;
    public :
        Reverse_iterator(iterator it) : iterator(it)
        {}
        Reverse_iterator(const Reverse_iterator& other) :iterator(other)
        {}
        Reverse_iterator() : iterator()
        {}
        Reverse_iterator& operator=(const Reverse_iterator& x)
        {
            this->m_ptr = x.m_ptr;
            return (*this);
        }
        // Reverse_iterator& operator++()
        // {
        //     m_ptr++;
        //     return (*this);
        // }
        // operator Reverse_iterator<const value_type>() const
        // {
        //     return Reverse_iterator<const value_type>(iterator);
        // }
        // Reverse_iterator operator++(int)
        // {
        //     Reverse_iterator iterator = *this;
        //     ++(*this);
        //     return (iterator);
        // }
        // Reverse_iterator& operator--()
        // {
        //     m_ptr--;
        //     return (*this);
        // }
        // Reverse_iterator operator--(int)
        // {
        //     Reverse_iterator iterator = *this;
        //     --(*this);
        //     return (iterator);
        // }
        // ReferenceType operator[](int index)
        // {
        //     return (*(m_ptr + index));
        // }
        // const_ReferenceType operator[](int index) const
        // {
        //     return (*(m_ptr + index));
        // }
        // PointerType operator->()
        // {
        //     return (m_ptr);
        // }
        // const_PointerType operator->() const
        // {
        //     return (m_ptr);
        // }
        // ReferenceType operator*()
        // {
        //     return *(m_ptr);
        // }
        // const_ReferenceType operator*() const
        // {
        //     return *(m_ptr);
        // }
        // bool operator==(const Reverse_iterator& other) const
        // {
        //     return (m_ptr == other.m_ptr);
        // }
        // bool operator!=(const Reverse_iterator& other) const
        // {
        //     return !(*this == other);
        // }
        // Reverse_iterator operator-(int value)
        // {
        //     m_ptr -= value;
        //     return (*this);
        // }
        // Reverse_iterator operator+(int value)
        // {
        //     m_ptr += value;
        //     return (*this);
        // }
};
