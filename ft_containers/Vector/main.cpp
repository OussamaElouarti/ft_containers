#include "Vector.hpp"

int main()
{
    //vector.jtmhobi(100%);
    Vector<int> vectorr(5, 100);
    vectorr.push_back(5);
    // vector.emplace_back(2);
    // vector.emplace_back(2);
    // vector.emplace_back(2);
    // vector.emplace_back(2);
    // vector.emplace_back(2);
    // vector.pop_back();
    // vector.clear();
    for (Vector<int>::Iterator it = vectorr.begin(); it != vectorr.end(); it++)
        std::cout << *it << std::endl;
    return (0);
}