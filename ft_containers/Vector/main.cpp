#include "Vector.hpp"
#include  <vector>
#include <iostream>
#include <array>
int main()
{
    Vector<int> vectorr(10, 100);
    Vector<int> vec(2,3);
    // std::cout << vectorr.max_size() << std::endl;
    // vectorr.assign(10,100);
    // std::cout << vectorr.size() << std::endl;
    // std::cout << vectorr.capacity() << std::endl;
    // vectorr.push_back(3);
    // vectorr.push_back(3);
    // vectorr.resize(5,8);
    // vectorr.push_back(15);
    // std::cout <<vectorr.size() << std::endl;
    // std::cout <<vectorr.capacity() << std::endl;
    // vectorr.clear();
    // std::cout << vectorr.empty() << std::endl;
    // try
    // {
    //     vectorr.at(1000) = 5;
    // }
    // catch (std::exception &e)
    // {
    //     std::cout << e.what() << std::endl;
    // }
    // std::cout << vectorr[1000] << std::endl;
    // std::cout << vectorr.front() - vectorr.back() << std::endl;
    // Vector<int>::Iterator it = vectorr.end();
    // Vector<int>::Iterator ite = vectorr.begin();
    // ite++;
    // vectorr.insert(ite, 5);
    // ite++;
    // it--;
    // Vector<int>::Iterator ite = vectorr.end();
    // Vector<int> vcopy(5, 3);
    // Vector<int>::Iterator pos = vcopy.begin();
    // pos++;
    // pos++;
    // pos++;
    // vcopy.insert(pos, it, ite);
    // vectorr.erase(ite, it);
    // std::cout << vectorr.size() << "ite" << std::endl;
    for (Vector<int>::Iterator it = vectorr.begin(); it != vectorr.end(); it++)
        std::cout << *it << std::endl;
    // vectorr.reserve(15);
    // std::cout << vectorr.size() << std::endl;
    // std::cout << vectorr.back() << std::endl;
    vectorr.swap(vec);
    std::cout << "vectorr" << std::endl;
    for (Vector<int>::Iterator it = vectorr.begin(); it != vectorr.end(); it++)
        std::cout << *it << std::endl;
    std::cout << "vec" << std::endl;
    for (Vector<int>::Iterator it = vec.begin(); it != vec.end(); it++)
        std::cout << *it << std::endl;
    // std::cout << vcopy.size() << std::endl;
    // std::cout << vcopy.capacity() << std::endl;
    // Vector<int>::Iterator it = vcopy.begin();
    // vcopy.insert(++it,3, 5);
    // for (Vector<int>::Iterator it = vcopy.begin(); it != vcopy.end(); it++)
    //     std::cout << *it << std::endl;
    // std::cout << vcopy.size() << std::endl;
    // std::cout << vcopy.capacity() << std::endl;
    // vectorr.pop_back();
    // vectorr.pop_back();
    // vectorr.pop_back();
    
    
    // Vector<int> V(it, ite);
    // for (Vector<int>::Iterator it = V.begin(); it != V.end(); it++)
    //     std::cout << *it << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::vector<int> vector(10, 100);
    std::vector<int> ve(2, 3);
    vector.swap(ve);
    for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); it++)
        std::cout << *it << std::endl;
    for (std::vector<int>::iterator it = ve.begin(); it != ve.end(); it++)
        std::cout << *it << std::endl;
    // std::cout << vector.max_size() << std::endl;
    // std::cout << vector.size() << std::endl;
    // std::cout << vector.capacity() << std::endl;
    // vector.push_back(3);
    // vector.push_back(3);
    // std::vector<int>::iterator it1 = vector.end();
    // std::vector<int>::iterator ite1 = vector.begin();
    // ite1++;
    // vector.insert(ite1, 5);
    // ite1++;
    // vector.erase(ite1, it1);
    // std::cout << vector.size() << "ite" << std::endl;
    // for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); it++)
    //     std::cout << *it << std::endl;
    // vector.reserve(15);
    // std::cout << vector.size() << std::endl;
    while (1);
    return (0);
}