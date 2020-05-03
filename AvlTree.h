#ifndef MUSIC_STREAMER_AVLTREE_H
#define MUSIC_STREAMER_AVLTREE_H

#include <iostream>

/*AVL Tree*/
template <class T>
class AVLTree{
public:
    T *root;
    int key;
    AVLTree *left, *right, *parent;
    int balance;

    AVLTree(void);
    AVLTree(const AVLTree<T>& t, AVLTree<T>* p);
    ~AVLTree(void);
    bool insert(T *t);
    bool deleteKey(const T t);
    void printBalance();
    void printInorder(T* t);
    T* searchNode(int value, T* t);

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
;

template <class T>
AVLTree<T>::AVLTree(void) : root(nullptr), key(0),
                left(nullptr), right(nullptr), parent(nullptr),
                balance(0){}


template <class T>
AVLTree<T>::AVLTree(const AVLTree<T> &t, AVLTree<T> *p):root(t.root),
                        key(t.key), left(t.left),
                        right(t.right), parent(p),
                        balance(t.balance){}

template <class T>
AVLTree<T>::~AVLTree(void) {
    delete root;
}


template <class T>
bool AVLTree<T>::insert(T *t) {
    if (root == nullptr) {
        root = new T(*t);
    }
    else {
        T
                *n = root,
                *parent;

        while (true) {
            if (n->key == t->key)
                return false;

            parent = n;

            bool goLeft = n->key > t->key;
            n = goLeft ? n->left : n->right;

            if (n == nullptr) {
                if (goLeft) {
                    parent->left = new T(*t, parent);
                }
                else {
                    parent->right = new T(*t, parent);
                }

                rebalance(parent);
                break;
            }
        }
    }

    return true;
}


template <class T>
bool AVLTree<T>::deleteKey(const T delKey) {
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
        child = delKey.key >= n->key ? n->right : n->left;
        if (delKey.key == n->key)
            delNode = n;
    }

    if (delNode != nullptr) {
        delNode->key = n->key;

        child = n->left != nullptr ? n->left : n->right;

        if (root->key == delKey.key) {
            root = child;
            return true;
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
#endif //MUSIC_STREAMER_AVLTREE_H
