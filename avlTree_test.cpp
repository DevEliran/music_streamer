#include <iostream>
#include "AvlTree.h"
#include "ArtistNode.h"
#include "DoublyLL.h"
#include "SongCountNode.h"
#include <cassert>

int main() {
    AVLTree<ArtistNode> *Tree = new AVLTree<ArtistNode>;
    assert(Tree->insert(14, 2) == true);
    assert(Tree->insert(1122,3) == true);
    assert(Tree->insert(502, 0) == true);
    assert(Tree->insert(501, 100) == true);
    assert(Tree->numOfNodes == 4);
    Tree->deleteKey(14);
    assert(Tree->numOfNodes == 3);
    assert(Tree->insert(502, 4) == false);
    assert(Tree->searchNode(502, Tree->root) != nullptr);
    Tree->deleteKey(1122);
    assert(Tree->numOfNodes == 2);
    Tree->deleteKey(502);
    assert(Tree->numOfNodes == 1);
    Tree->deleteKey(501);
    assert(Tree->numOfNodes == 0);
    Tree->printInorder(Tree->root);
    assert(!Tree->root);

    for(int i = 1; i<200; i++){
        assert(Tree->insert(i, 5) == true);
    }
    std::cout<<"Inorder....\n"<<std::endl;
    Tree->printInorder(Tree->root);
    std::cout<<"\n\nPostOrder....\n"<<std::endl;
    Tree->printPostorder(Tree->root);
    std::cout<< "\n\nDeleting the whole tree........\n\n"<<std::endl;
    if(Tree->root->balance > -2 || Tree->root->balance < 2){
        std::cout<<"Balanced"<<std::endl;
    }
    delete Tree;
    Tree->root = nullptr;
    Tree = nullptr;

    std::cout<<"Success"<<std::endl;



//
//    DoublyLL<SongCountNode>* list =  new DoublyLL<SongCountNode>;
//    SongCountNode *d1 = new SongCountNode(0);
//    SongCountNode *e = new SongCountNode(1);
//    SongCountNode *f = new SongCountNode(2);
//    SongCountNode *h = new SongCountNode(-1);
//
//    list->push(h);
//    list->push(e);
//    list->push(f);
//    list->printList();
    return 0;
}