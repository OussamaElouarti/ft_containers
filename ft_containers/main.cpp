#include "headers/Vector.hpp"
#include "headers/deque.hpp"
#include  <vector>
#include  <deque>
#include <iostream>
#include <array>
int main()
{
    ft::deque<int> lol;
    lol.push_back(1);
    lol.push_back(1);
    lol.push_back(1);
    lol.push_back(1);
    lol.push_front(5);
    lol.pop_front();
    for (ft::deque<int>::iterator it = lol.begin(); it != lol.end(); it++)
        std::cout << *it << std::endl;
    ft::vector<int> van(5,10);
    // std::ft::vector<int> bo(++van.begin(),--van.end());
    //  if (bo == van)
    //     std::cout << "kik" << std::endl;
    // else
    //     std::cout << "kok" << std::endl;
    // // constuct with n range && capacity && push && pop back
    // ft::vector<int> vectorr(10, 100);
    // std::cout << "vectorr ---" << std::endl;
    // vectorr.push_back(4);
    // vectorr.push_back(4);
    // vectorr.pop_back();
    // for (ft::vector<int>::iterator it = vectorr.begin(); it != vectorr.end(); it++)
    //     std::cout << *it << std::endl;
    // std::cout << vectorr.capacity() << std::endl;
    // // construct  with iterators
    // ft::vector<int>::iterator it = vectorr.begin();
    // it++;
    // it++;
    // it++;
    // ft::vector<int> vec(vectorr.begin(), it);
    // std::cout << "vec ---" << std::endl;
    // for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
    //     std::cout << *it << std::endl;
    // // copy construct
    // ft::vector<int> vecto(vec);
    // std::cout << "vecto ---" << std::endl;
    // for (ft::vector<int>::iterator it = vecto.begin(); it != vecto.end(); it++)
    //     std::cout << *it << std::endl;
    // // assign && reserve
    // std::cout << "vectorr assign" << std::endl;
    // vectorr.assign(4, 5);
    // vectorr.reserve(100);
    // for (ft::vector<int>::iterator it = vectorr.begin(); it != vectorr.end(); it++)
    //     std::cout << *it << std::endl;
    // std::cout << vectorr.capacity() << std::endl;
    // // swap && erase
    // std::cout << "erase" << std::endl;
    ft::vector<int> va;
    va.push_back(1);
    va.push_back(2);
    va.push_back(3);
    va.push_back(4);
    // ft::vector<int>::iterator to = va.erase(va.begin());
    // for (ft::vector<int>::iterator it = va.begin(); it != va.end(); it++)
    //     std::cout << *it << std::endl;
    // std::cout << *to << std::endl;
    // // erase range of its
    // std::cout << "range erase" << std::endl;
    // ft::vector<int>::iterator top = va.erase(va.begin(), va.end());
    // for (ft::vector<int>::iterator it = va.begin(); it != va.end(); it++)
    //     std::cout << *it << std::endl;
    //     std::cout << *to << std::endl;
    // resize
    // std::cout << "resize" << std::endl;
    // va.resize(6,10);
    // for (ft::vector<int>::iterator it = va.begin(); it != va.end(); it++)
    //     std::cout << *it << std::endl;
    // std::cout << va.size() << std::endl;
    // insert
    ft::vector<int>::iterator po = va.insert(++va.begin(), 3);
    // std::cout << "insert" << std::endl;
    va.insert(++va.begin(),17, 5);
    va.insert(++va.begin(),van.begin(), --van.end()); 
    std::cout << *va.erase(va.begin()) << "lol"<< std::endl;
    std::cout << *va.erase(++va.begin(),--va.end()) << "lol"<< std::endl;
    std::cout << "n" << std::endl;
     for (ft::vector<int>::iterator it = va.begin(); it != va.end(); it++)
        std::cout << *it << std::endl;
    std::cout << "n" << std::endl;
    std::cout << *po << std::endl;
    std::cout << va.capacity() << std::endl;
    // std::cout << &(*po) << " " << &(*(++va.begin())) << std::endl;
    // std::cout << *po << std::endl;
    // std::cout << *po << std::endl;
    // std::cout << "n" << std::endl;
    // std::cout << "n" << std::endl;
    // for (ft::vector<int>::iterator it = van.begin(); it != van.end(); it++)
    //     std::cout << *it << std::endl;
    // std::cout << va.capacity() << "   lol"<< std::endl;
    // std::cout << va.size() << "   lol"<< std::endl;
    // std::cout << *po << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::deque<int> lol1;
    lol1.push_back(1);
    lol1.push_back(1);
    lol1.push_back(1);
    lol1.push_back(1);
    lol1.push_front(5);
    lol1.pop_front();
    for (std::deque<int>::iterator it = lol1.begin(); it != lol1.end(); it++)
        std::cout << *it << std::endl;
    std::vector<int> vo(5, 10);
    // vo.push_back(4);
    // vo.push_back(4);
    // vo.pop_back();
    // vo.assign(4, 5);
    // vo.reserve(100);
    // for (std::vector<int>::iterator it = vo.begin(); it != vo.end(); it++)
    //     std::cout << *it << std::endl;
    // std::cout << vo.capacity() << std::endl;
    std::vector<int> vop;
    vop.push_back(1);
    vop.push_back(2);
    vop.push_back(3);
    vop.push_back(4);
    // vop.push_back(5);
    //  std::vector<int>::iterator too = vop.erase(vop.begin());
    // for (std::vector<int>::iterator it = vop.begin(); it != vop.end(); it++)
    //     std::cout << *it << std::endl;
    // std::vector<int>::iterator tat = vop.erase(vop.begin(), vop.end());
    // for (std::vector<int>::iterator it = vop.begin(); it != vop.end(); it++)
    //     std::cout << *it << std::endl;
        // std::cout << vop.capacity() << std::endl;
    std::vector<int>::iterator pol = vop.insert(++vop.begin(),3);
    vop.insert(++vop.begin(),17,5);
    vop.insert(++vop.begin(),vo.begin(),--vo.end());
    std::cout << *vop.erase(vop.begin()) << "lol "<< std::endl;
    std::cout << *vop.erase(++vop.begin(),--vop.end()) << "lol"<< std::endl;
    std::cout << "n" << std::endl;
    for (std::vector<int>::iterator it = vop.begin(); it != vop.end(); it++)
        std::cout << *it << std::endl;
    std::cout << "n" << std::endl;
    std::cout << *pol << std::endl;
    std::cout << vop.capacity() << std::endl;
    // while (1);
    return (0);
}