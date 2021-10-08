# include "./headers/tools.hpp"
# include "./headers/AVL.hpp"

int main()
{
    AVL<int> tree;
    tree.insert(10);
    tree.insert(15);
    tree.insert(12);
    ft::AVLNODE<int> *node = tree._root;
    std::cout << *(node->data) << " root" << std::endl;
    std::cout << *(node->left->data)<< " left" << std::endl;
    std::cout << *(node->right->data)<< " right" << std::endl;
    // std::cout << *(node->right->right->data)<< " right right" << std::endl;
    // std::cout << *(node->left->left->data)<< " left left" << std::endl;
    // std::cout << *(node->left->right->data)<< " left right" << std::endl;
}