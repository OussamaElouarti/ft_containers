# include <vector>
# include <iostream>
# include <iterator>
# include <ctime>
# include <iomanip>
# include <unistd.h>
# include <signal.h>
# include <sys/time.h>
# include "./headers/Vector.hpp"

int main(){
    ft::vector<int> ve;
    for (int i = 0; i < 10; i++)
        ve.push_back(i);
    ft::vector<int>::reverse_iterator it = ve.rbegin();
    ft::vector<int>::reverse_iterator ite = ve.rend();
    std::cout <<it - ite << std::endl;

      std::vector<int> vev;
    for (int i = 0; i < 10; i++)
        ve.push_back(i);
    std::vector<int>::reverse_iterator vit = vev.rbegin();
    std::vector<int>::reverse_iterator vite = vev.rend();
    std::cout <<vit - vite << std::endl;
}