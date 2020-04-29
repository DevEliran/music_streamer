#include <iostream>
#include "AvlTree.h"
#include "ArtistNode.cpp"

int main() {
//    std::cout << "Hello World!";
    ArtistNode *a = new ArtistNode(14, 2);
    ArtistNode *b = new ArtistNode(1122, 3);
    ArtistNode *c = new ArtistNode(502, 0);

    AVLTree<ArtistNode> *Tree = new AVLTree<ArtistNode>();
    Tree->insert(*a);
    Tree->insert(*b);
    Tree->insert(*c);
    Tree->printInorder(Tree->root);
    return 0;
}