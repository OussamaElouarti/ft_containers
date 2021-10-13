# include "./headers/tools.hpp"
# include "./headers/AVL.hpp"
# include "./headers/Map.hpp"

int main()
{
    ft::map<int, int> mapox;
    ft::pair<int, int> par = ft::make_pair(10, 5);
    mapox.insert(par);

    // ft::AVL<ft::pair<int, int> >  tree;
    // tree.insert(par);
    ft::map<int, int> ::iterator it = mapox.begin();
    std::cout << it->first << " " << it->second << std::endl;

}
    