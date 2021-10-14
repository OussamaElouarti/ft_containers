# include "../headers/tools.hpp"
# include "../headers/AVL.hpp"
# include "../headers/Map.hpp"
# include <map>

int main()
{
    ft::map<int, int> mapox;
    ft::pair<int, int> par = ft::make_pair(10, 5);
    ft::pair<int, int> par1 = ft::make_pair(12, 3);
    ft::pair<int, int> par2 = ft::make_pair(15, 2);
    ft::pair<int, int> par3 = ft::make_pair(8, 1);
    ft::pair<int, int> par4 = ft::make_pair(20, 1);
    std::map<int, int> mapoxx;

     mapox.insert(par);
     mapox.insert(par1);
     mapox.insert(par2);
     mapox.insert(par3);
     mapox.insert(par4);

     mapoxx.insert(std::pair<int,int>(10,5));
     mapoxx.insert(std::pair<int,int>(12,3));
     mapoxx.insert(std::pair<int,int>(15,2));
     mapoxx.insert(std::pair<int,int>(8,1));
     mapoxx.insert(std::pair<int,int>(20,1));

    
    // ft::map<int, int>::iterator it = mapox.lower_bound(2);
    // std::map<int, int>::iterator it1 = mapoxx.lower_bound(2);
    ft::map<int, int>::iterator it = mapox.begin();
    std::map<int, int>::iterator it1 = mapoxx.begin();
    for (; it != mapox.end(); it++)
        std::cout << it->first << " " << it->second << std::endl;
    for (; it1 != mapoxx.end(); it1++)
        std::cout << it1->first << " " << it1->second << std::endl;
}
    