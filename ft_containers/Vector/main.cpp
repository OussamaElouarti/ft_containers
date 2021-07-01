#include "Vector.hpp"
#include  <vector>
#include <iostream>
#include <array>
int main()
{
    // constuct with n range && capacity && push && pop back
    Vector<int> vectorr(10, 100);
    std::cout << "vectorr ---" << std::endl;
    vectorr.push_back(4);
    vectorr.push_back(4);
    vectorr.pop_back();
    for (Vector<int>::iterator it = vectorr.begin(); it != vectorr.end(); it++)
        std::cout << *it << std::endl;
    std::cout << vectorr.capacity() << std::endl;
    // construct  with iterators
    Vector<int>::iterator it = vectorr.begin();
    it++;
    it++;
    it++;
    Vector<int> vec(vectorr.begin(), it);
    std::cout << "vec ---" << std::endl;
    for (Vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
        std::cout << *it << std::endl;
    // copy construct
    Vector<int> vecto(vec);
    std::cout << "vecto ---" << std::endl;
    for (Vector<int>::iterator it = vecto.begin(); it != vecto.end(); it++)
        std::cout << *it << std::endl;
    // assign && reserve
    std::cout << "vectorr assign" << std::endl;
    vectorr.assign(4, 5);
    vectorr.reserve(100);
    for (Vector<int>::iterator it = vectorr.begin(); it != vectorr.end(); it++)
        std::cout << *it << std::endl;
    std::cout << vectorr.capacity() << std::endl;
    // swap && erase
    std::cout << "erase" << std::endl;
    Vector<int> va;
    va.push_back(1);
    va.push_back(2);
    va.push_back(3);
    Vector<int>::iterator to = va.erase(--va.end());
    // for (Vector<int>::iterator it = va.begin(); it != va.end(); it++)
        std::cout << *to << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::vector<int> vo(10, 100);
    vo.push_back(4);
    vo.push_back(4);
    vo.pop_back();
    vo.assign(4, 5);
    vo.reserve(100);
    for (std::vector<int>::iterator it = vo.begin(); it != vo.end(); it++)
        std::cout << *it << std::endl;
    std::cout << vo.capacity() << std::endl;
    std::vector<int> vop;
    vop.push_back(1);
    vop.push_back(2);
    vop.push_back(3);
    for (std::vector<int>::iterator it = vop.begin(); it != vop.end(); it++)
        std::cout << *it << std::endl;
    std::vector<int>::iterator ta = vop.erase(--vop.end());
    std::vector<int>::iterator pa = vop.begin() - ta;
    std::cout << *pa << std::endl;
    // std::cout << vop.size() << std::endl;
    while (1);
    return (0);
}