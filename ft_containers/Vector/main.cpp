#include "Vector.hpp"
#include  <vector>
#include <iostream>
#include <array>
int main()
{
    Vector<int> vectorr(10, 100);
    std::cout << vectorr.max_size() << std::endl;
    // vectorr.assign(10,100);
    std::cout << vectorr.size() << std::endl;
    std::cout << vectorr.capacity() << std::endl;
    vectorr.resize(5,8);
    // vectorr.push_back(15);
    std::cout <<vectorr.size() << std::endl;
    std::cout <<vectorr.capacity() << std::endl;
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
    // Vector<int>::Iterator it = vectorr.begin();
    // Vector<int>::Iterator ite = vectorr.end();
    // Vector<int> vcopy(5, 3);
    // Vector<int>::Iterator pos = vcopy.begin();
    // pos++;
    // pos++;
    // pos++;
    // vcopy.insert(pos, it, ite);
    for (Vector<int>::Iterator it = vectorr.begin(); it != vectorr.end(); it++)
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
try
{
    std::vector<int> vector(4611686018427387900, 100);
}
catch(const std::exception& e)
{
    std::cerr << e.what() << '\n';
}

    // // std::vector<int> vector(, 100);
    // std::cout << vector.max_size() << std::endl;
    // // vector.assign(10,100);
    // std::cout << vector.size() << std::endl;
    // std::cout << vector.capacity() << std::endl;
    // vector.resize(5, 8);
    // // vector.push_back(15);
    // std::cout << vector.size() << std::endl;
    // std::cout << vector.capacity() << std::endl;
    // vector.clear();
    // std::cout << vector.empty() << std::endl;
    // try 
    // {
    //     vector.at(1000) = 5;
    // }
    // catch (std::exception &e)
    // {
    //     std::cout << e.what() << std::endl;
    // }
    // std::cout << vector[1000] << std::endl;
    // // std::cout << vector.front() - vector.back() << std::endl;
    // std::vector<int>::iterator it1 = vector.begin();
    // std::vector<int>::iterator ite1 = vector.end();
    // std::vector<int> vcopy1(5,3);
    // std::vector<int>::iterator pos2 = vcopy1.begin();
    // pos2++;
    // pos2++;
    // pos2++;
    // vcopy1.insert(pos2, it1, ite1);
    // vcopy1 = vector;
    // for (std::vector<int>::iterator it = vcopy1.begin(); it != vcopy1.end(); it++)
    //     std::cout << *it << std::endl;
    // // std::cout << vcopy1.size() << std::endl;
    // // std::cout << vcopy1.capacity() << std::endl;
    // // std::vector<int>::iterator it1 = vcopy1.begin();
    // // vcopy1.insert(++it1, 3, 5);
    // // for (std::vector<int>::iterator it = vcopy1.begin(); it != vcopy1.end(); it++)
    // //     std::cout << *it << std::endl;
    // // std::cout << vcopy1.size() << std::endl;
    // // std::cout << vcopy1.capacity() << std::endl;
    // vector.pop_back();
    // vector.pop_back();
    // vector.pop_back();
    // std::vector<int> V1(it1, ite1);
    // for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); it++)
    //     std::cout << *it << std::endl;
    // std::cout <<vcopy1.size() << std::endl;
    // std::cout <<vcopy1.capacity() << std::endl;
    return (0);
}