#ifndef MUSIC_STREAMER_AVLTREE_H
#define MUSIC_STREAMER_AVLTREE_H

#include <iostream>
#include "SongNode.h"
#include "ArtistNode.h"
/*AVL Tree*/
template <class T>
class AVLTree{
public:
    T *root;
    int key;
    AVLTree *left, *right, *parent;
    int balance;
    T *minNode;
    int numOfNodes;

    AVLTree(void);
    AVLTree(int key);
    AVLTree(const AVLTree<T>& t, AVLTree<T>* p);
    ~AVLTree(void);
    bool insert(int key, int numOfSongs);
    bool insertSongTree(int numOfSongs, int artistID, ArtistNode* a);
    bool deleteKey(int t);
    void printInorder(T* t);
    T* searchNode(int value, T* t);
    void scanInorder(SongNode* t, int* artists, int* songs, int iter, bool wentRight);
    void scanOuterTree(AVLTree<SongNode> *t, int* artists, int *songs, int numOfSongs, bool wentRight);
    void deleteTree(ArtistNode* node);
    void deleteTree(AVLTree<SongNode> *node);
    void deleteTree(SongNode *node);
    void printPostorder(T* t);
    SongNode* insert(int key, int numOfSongs, bool flag);
    T* searchNode(int value, T* t, bool flag);

private:
    T* rotate_LL (T * a);
    T* rotate_RR (T * a);
    T* rotate_LR (T * n);
    T* rotate_RL (T * n);
    void rebalance(T *n);
    int height(T *n);
    void setBalance(T *n);
    void clearNode(T *n);
    void rebalance(T *n, bool flag);
};

template <class T>
void AVLTree<T>::rebalance(T *n) {
    setBalance(n);

    if (n->balance == -2) {
        if (height(n->left->left) >= height(n->left->right))
            n = rotate_RR(n);
        else
            n = rotate_LR(n);
    }
    else if (n->balance == 2) {
        if (height(n->right->right) >= height(n->right->left))
            n = rotate_LL(n);
        else
            n = rotate_RL(n);
    }

    if (n->parent != nullptr) {
        rebalance(n->parent);
    }
    else {
        root = n;
    }
}

template <class T>
void AVLTree<T>::rebalance(T *n, bool flag) {
    setBalance(n);

    if (n->balance == -2) {
        if (height(n->left->left) >= height(n->left->right))
            n = rotate_RR(n);
        else
            n = rotate_LR(n);
    }
    else if (n->balance == 2) {
        if (height(n->right->right) >= height(n->right->left))
            n = rotate_LL(n);
        else
            n = rotate_RL(n);
    }

    if (n->parent != nullptr) {
        rebalance(n->parent);
    }
    else {
        root->root = n;
    }
}


template <class T>
T* AVLTree<T>::rotate_LL(T *a) {
    T *b = a->right;
    b->parent = a->parent;
    a->right = b->left;

    if (a->right != nullptr)
        a->right->parent = a;

    b->left = a;
    a->parent = b;

    if (b->parent != nullptr) {
        if (b->parent->right == a) {
            b->parent->right = b;
        }
        else {
            b->parent->left = b;
        }
    }

    setBalance(a);
    setBalance(b);
    return b;
}


template <class T>
T* AVLTree<T>::rotate_RR(T *a) {
    T *b = a->left;
    b->parent = a->parent;
    a->left = b->right;

    if (a->left != nullptr)
        a->left->parent = a;

    b->right = a;
    a->parent = b;

    if (b->parent != nullptr) {
        if (b->parent->right == a) {
            b->parent->right = b;
        }
        else {
            b->parent->left = b;
        }
    }

    setBalance(a);
    setBalance(b);
    return b;
}


template <class T>
T* AVLTree<T>::rotate_LR(T *n) {
    n->left = rotate_LL(n->left);
    return rotate_RR(n);
}


template <class T>
T* AVLTree<T>::rotate_RL(T *n) {
    n->right = rotate_RR(n->right);
    return rotate_LL(n);
}


template <class T>
int AVLTree<T>::height(T *n) {
    if (n == nullptr)
        return -1;
    return 1 + std::max(height(n->left), height(n->right));
}


template <class T>
void AVLTree<T>::setBalance(T *n) {
    n->balance = height(n->right) - height(n->left);
}
;

template <class T>
AVLTree<T>::AVLTree(void) : root(nullptr), key(0),
                left(nullptr), right(nullptr), parent(nullptr),
                balance(0), minNode(nullptr), numOfNodes(0){}

template <class T>
AVLTree<T>::AVLTree(int key) : root(nullptr), key(key),
                            left(nullptr), right(nullptr), parent(nullptr),
                            balance(0), minNode(nullptr), numOfNodes(0){}
template <class T>
AVLTree<T>::AVLTree(const AVLTree<T> &t, AVLTree<T> *p):root(t.root),
                        key(t.key), left(t.left),
                        right(t.right), parent(p),
                        balance(t.balance), minNode(t.minNode),
                        numOfNodes(t.numOfNodes){}

template <class T>
AVLTree<T>::~AVLTree(void) {
    deleteTree(root);
    this->root = nullptr;
    this->minNode = nullptr;
}


template <class T>
void AVLTree<T>::deleteTree(ArtistNode *node) {
    if (node == nullptr){
        return;
    }

    deleteTree(node->left);
    deleteTree(node->right);
    numOfNodes--;
    delete node;
    node = nullptr;
}


template <class T>
void AVLTree<T>::deleteTree(AVLTree<SongNode> *node) {
    if (node == nullptr){
        return;
    }

    deleteTree(node->left);
    deleteTree(node->right);
    numOfNodes--;
    delete node;
    node = nullptr;
}

template <class T>
void AVLTree<T>::deleteTree(SongNode *node) {
    return;
}


template <class T>
bool AVLTree<T>::insert(int key, int numOfSongs) {
    if (root == nullptr) {
        root = new T(key, numOfSongs, nullptr);
        minNode = root;
        numOfNodes++;
        return true;
    }
    else {
        T
                *n = root,
                *parent;

        while (true) {
            if (n->key == key)
                return false;

            parent = n;

            bool goLeft = n->key > key;
            n = goLeft ? n->left : n->right;

            if (n == nullptr) {
                if (goLeft) {
                    parent->left = new T(key, numOfSongs, parent);
                    minNode = parent->left;
                    numOfNodes++;
                    rebalance(parent);
                    return true;
                }
                else {
                    parent->right = new T(key, numOfSongs, parent);
                    numOfNodes++;
                    rebalance(parent);
                    return true;
                }
            }
        }
    }
}


template <class T>
bool AVLTree<T>::deleteKey(int delKey) {
    if(!this){
        return false;
    }
    if (root == nullptr)
        return false;

    T
            *n       = root,
            *parent  = root,
            *delNode = nullptr,
            *child   = root;

    while (child != nullptr) {
        parent = n;
        n = child;
        if(n && child) {
            if (delKey >= n->key){
                child = n->right;
            }
            else{
                child = n->left;
            }
//            child = delKey >= n->key ? n->right : n->left;
            if (delKey == n->key)
                delNode = n;
        }
    }
    if (delNode == minNode && delNode){
        minNode = delNode->parent;
    }
    if (delNode != nullptr) {
        delNode->key = n->key;

        child = n->left != nullptr ? n->left : n->right;

        if (root->key == delKey) {
            root = child;
        }
        else {
            if (parent->left == n) {
                parent->left = child;
            }
            else {
                parent->right = child;
            }

            rebalance(parent);
        }
        this->numOfNodes--;
        return true;
    }
    return false;
}

template <class T>
void AVLTree<T>::printInorder(T* t)
{
    if (t == nullptr)
        return;
    printInorder(t->left);
    std::cout << t->key << " ";
    printInorder(t->right);
}

template <class T>
void AVLTree<T>::printPostorder(T* t)
{
    if (t == nullptr)
        return;
    printInorder(t->left);
    printInorder(t->right);
    std::cout << t->key << " ";
}

template <class T>
void AVLTree<T>::scanOuterTree(AVLTree<SongNode> *t, int* artists, int *songs, int numOfSongs, bool wentRight){
    if (t == nullptr || artists[numOfSongs - 1] != -1){
        return;
    }

    scanInorder(t->minNode, artists, songs, numOfSongs, false);//should be minNOde
    if(!wentRight) {
        scanOuterTree(t->parent, artists, songs, numOfSongs, false);
    }
    scanOuterTree(t->right, artists, songs, numOfSongs, true);
}

template <class T>
void AVLTree<T>::scanInorder(SongNode* t, int* artists, int* songs, int numOfSongs, bool wentRight)
{
    if(t == nullptr || artists[numOfSongs - 1] != -1){
        return;
    }
    int free_index = -1;
    for(int i = 0; i < numOfSongs; i++){
        if (artists[i] == -1){
            free_index = i;
            break;
        }
    }
    if(free_index != -1) {
        artists[free_index] = t->artistID;
        songs[free_index] = t->key;
    }

    if(!wentRight) {
        scanInorder(t->parent, artists, songs, numOfSongs, false);
    }
    scanInorder(t->right, artists, songs, numOfSongs, true);

}

template <class T>
T* AVLTree<T>::searchNode(int value, T* t){
    if(t == nullptr || t->key == value){
        return t;
    }
    if (value < t->key){
        return searchNode(value, t->left);
    }
    if (value > t->key){
        return searchNode(value, t->right);
    }
    return nullptr;
}


template <class T>
T* AVLTree<T>::searchNode(int value, T* t, bool flag){
    if(t == nullptr || t->artistID == value){
        return t;
    }
    if (value < t->artistID){
        return searchNode(value, t->left);
    }
    if (value > t->artistID){
        return searchNode(value, t->right);
    }
    return nullptr;
}


template <class T>
bool AVLTree<T>::insertSongTree(int numOfSongs, int artistID, ArtistNode* a) {
    if(!a){
        return false;
    }
    if (root == nullptr) {
        root = new T;
        minNode = root;
        root->key = artistID;
        for(int i = 0; i < numOfSongs; i++){
            //songID (i) is the key.
            a->pointerArr[i] = root->insert(i, artistID, true);
        }
        return true;
    }
    else {
        T
                *n = root,
                *parent;

        while (true) {
//            if (n->key == key)
//                return false;

            parent = n;

            bool goLeft = n->key > artistID;
            n = goLeft ? n->left : n->right;

            if (n == nullptr) {
                if (goLeft) {
                    parent->left = new T;
                    parent->left->key = artistID;
                    for(int i = 0; i < numOfSongs; i++){
                        a->pointerArr[i] = parent->left->insert(i, artistID, true);
                    }
                    minNode = parent->left;
                    numOfNodes++;
                    parent->left->parent = parent;
                    rebalance(parent);
                    return true;
                }
                else {
                    parent->right = new T;
                    parent->right->key = artistID;
                    for(int i = 0; i < numOfSongs; i++){
                        a->pointerArr[i] = parent->right->insert(i, artistID, true);
                    }
                    numOfNodes++;
                    parent->right->parent = parent;
                    rebalance(parent);
                    return true;
                }
            }
        }
    }
}


template <class T>
SongNode* AVLTree<T>::insert(int key, int numOfSongs, bool flag) {
    if (root == nullptr) {
        root = new T(key, numOfSongs, nullptr);
        minNode = root;
        numOfNodes++;
        return root;
    }
    else {
        T
                *n = root,
                *parent;

        while (true) {
            if (n->key == key)
                return nullptr;

            parent = n;

            bool goLeft = n->key > key;
            n = goLeft ? n->left : n->right;

            if (n == nullptr) {
                if (goLeft) {
                    parent->left = new T(key, numOfSongs, parent);
                    minNode = parent->left;
                    numOfNodes++;
                    rebalance(parent);
                    return parent->left;
                }
                else {
                    parent->right = new T(key, numOfSongs, parent);
                    numOfNodes++;
                    rebalance(parent);
                    return parent->right;
                }
            }
        }
    }
}
#endif //MUSIC_STREAMER_AVLTREE_H
