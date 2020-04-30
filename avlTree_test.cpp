#include <iostream>
#include "AvlTree.h"
#include "ArtistNode.h"
#include "DoublyLL.h"
#include "SongCountNode.h"

int main() {
    ArtistNode *a = new ArtistNode(14, 2);
    ArtistNode *b = new ArtistNode(1122, 3);
    ArtistNode *c = new ArtistNode(502, 0);
    ArtistNode *d = new ArtistNode(501, 100);

    AVLTree<ArtistNode> *Tree = new AVLTree<ArtistNode>();
    Tree->insert(*a);
    Tree->insert(*b);
    Tree->insert(*c);
    Tree->insert(*d);
    Tree->printInorder(Tree->root);

    DoublyLL<SongCountNode>* list =  new DoublyLL<SongCountNode>;
    SongCountNode *d1 = new SongCountNode(0);
    SongCountNode *e = new SongCountNode(1);
    SongCountNode *f = new SongCountNode(2);
    SongCountNode *h = new SongCountNode(-1);

    list->push(h);
    list->push(e);
    list->push(f);
    list->printList();
    return 0;
}