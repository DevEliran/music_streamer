#ifndef MUSIC_STREAMER_AVLTREE_H
#define MUSIC_STREAMER_AVLTREE_H

#include <iostream>
#include "ArtistNode.h"

/*AVL Tree*/
template <class T>
class AVLTree{
public:
    T *root;

    AVLTree(void);
    ~AVLTree(void);
    bool insert(T t);
    void deleteKey(const T t);
    void printBalance();
    void printInorder(T* t);

private:
    T* rotate_LL (T * a);
    T* rotate_RR (T * a);
    T* rotate_LR (T * n);
    T* rotate_RL (T * n);
    void rebalance(T *n);
    int height(T *n);
    void setBalance(T *n);
    void clearNode(T *n);
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


template <class T>
AVLTree<T>::AVLTree(void) : root(nullptr) {}


template <class T>
AVLTree<T>::~AVLTree(void) {
    delete root;
}


template <class T>
bool AVLTree<T>::insert(T t) {
    if (root == nullptr) {
        root = new T(t);
    }
    else {
        T
                *n = root,
                *parent;

        while (true) {
            if (n->artistID == t.artistID)
                return false;

            parent = n;

            bool goLeft = n->artistID > t.artistID;
            n = goLeft ? n->left : n->right;

            if (n == nullptr) {
                if (goLeft) {
                    parent->left = new T(t, parent);
                }
                else {
                    parent->right = new T(t, parent);
                }

                rebalance(parent);
                break;
            }
        }
    }

    return true;
}


template <class T>
void AVLTree<T>::deleteKey(const T delKey) {
    if (root == nullptr)
        return;

    T
            *n       = root,
            *parent  = root,
            *delNode = nullptr,
            *child   = root;

    while (child != nullptr) {
        parent = n;
        n = child;
        child = delKey >= n->artistID ? n->right : n->left;
        if (delKey == n->artistID)
            delNode = n;
    }

    if (delNode != nullptr) {
        delNode->artistID = n->artistID;

        child = n->left != nullptr ? n->left : n->right;

        if (root->artistID == delKey) {
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
    }
}

template <class T>
void AVLTree<T>::printInorder(T* t)
{
    if (t == nullptr)
        return;
    printInorder(t->left);
    std::cout << t->artistID << " ";
    printInorder(t->right);
}
#endif //MUSIC_STREAMER_AVLTREE_H
