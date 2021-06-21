#include "Vector.hpp"
#include  <vector>
#include <iostream>
int main()
{
    Vector<int> vectorr(10, 100);
    std::cout << vectorr.max_size() << std::endl;
    // vectorr.assign(10,100);
    std::cout << vectorr.size() << std::endl;
    std::cout << vectorr.capacity() << std::endl;
    vectorr.push_back(15);
    // vectorr.clear();
    std::cout << vectorr.empty() << std::endl;
    try
    {
        vectorr.at(1000) = 5;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << vectorr[1000] << std::endl;
    std::cout << vectorr.front() - vectorr.back() << std::endl;
    Vector<int> vcopy;
    vcopy = vectorr;
    for (Vector<int>::Iterator it = vcopy.begin(); it != vcopy.end(); it++)
        std::cout << *it << std::endl;
    std::cout << vcopy.size() << std::endl;
    std::cout << vcopy.capacity() << std::endl;
    Vector<int>::Iterator it = vcopy.begin();
    vcopy.insert(it,3, 5);
    for (Vector<int>::Iterator it = vcopy.begin(); it != vcopy.end(); it++)
        std::cout << *it << std::endl;
    std::cout << vcopy.size() << std::endl;
    std::cout << vcopy.capacity() << std::endl;
    std::cout << "-----------------------------" << std::endl;

    std::vector<int> vector(10, 100);
    std::cout << vector.max_size() << std::endl;
    // vector.assign(10,100);
    std::cout << vector.size() << std::endl;
    std::cout << vector.capacity() << std::endl;
    vector.push_back(15);
    // vector.clear();
    std::cout << vector.empty() << std::endl;
    try 
    {
        vector.at(1000) = 5;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << vector[1000] << std::endl;
    std::cout << vector.front() - vector.back() << std::endl;
    std::vector<int> vcopy1;
    vcopy1 = vector;
    for (std::vector<int>::iterator it = vcopy1.begin(); it != vcopy1.end(); it++)
        std::cout << *it << std::endl;
    std::cout << vcopy1.size() << std::endl;
    std::cout << vcopy1.capacity() << std::endl;
    std::vector<int>::iterator it1 = vcopy1.begin();
    vcopy1.insert(it1, 3, 5);
    for (std::vector<int>::iterator it = vcopy1.begin(); it != vcopy1.end(); it++)
        std::cout << *it << std::endl;
    std::cout << vcopy1.size() << std::endl;
    std::cout << vcopy1.capacity() << std::endl;
}