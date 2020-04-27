#ifndef MUSIC_STREAMER_AVLTREE_H
#define MUSIC_STREAMER_AVLTREE_H

/* AVL node*/
template <class T>
class AVL_node{
public:
    int key;
    T data;
    int balance;
    AVL_node *left, *right, *parent;

    AVL_node(T t, AVL_node *p):key((ArtistNode*)t->artist_id), data(t), balance(0),
                                         parent(p), left(NULL),right(NULL){}
    ~AVL_node(){
        delete  left
        delete right
    }
};


/*AVL Tree*/
template <class T>
class AVLTree{
public:
    AVLTree(void);
    ~AVLTree(void);
    bool insert(T t);
    void deleteKey(const T t);
    void printBalance()

private:
    AVL_node<T> *root;

    AVL_node<T>* rotate_LL (AVL_node<T> * a);
    AVL_node<T>* rotate_RR (AVL_node<T> * a);
    AVL_node<T>* rotate_LR (AVL_node<T> * n);
    AVL_node<T>* rotate_RL (AVL_node<T> * n);
    void rebalance(AVL_node<T> *n);
    int height(AVL_node<T> *n);
    void setBalance(AVL_node<T> *n);
    void clearNode(AVL_node<T> *n);
};

template <class T>
void AVLtree<T>::rebalance(AVLnode<T> *n) {
    setBalance(n);

    if (n->balance == -2) {
        if (height(n->left->left) >= height(n->left->right))
            n = rotate_RR(n);
        else
            n = LR(n);
    }
    else if (n->balance == 2) {
        if (height(n->right->right) >= height(n->right->left))
            n = rotate_LL(n);
        else
            n = RL(n);
    }

    if (n->parent != NULL) {
        rebalance(n->parent);
    }
    else {
        root = n;
    }
}


template <class T>
AVLnode<T>* AVLtree<T>::rotate_LL(AVLnode<T> *a) {
    AVLnode<T> *b = a->right;
    b->parent = a->parent;
    a->right = b->left;

    if (a->right != NULL)
        a->right->parent = a;

    b->left = a;
    a->parent = b;

    if (b->parent != NULL) {
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
AVLnode<T>* AVLtree<T>::rotate_RR(AVLnode<T> *a) {
    AVLnode<T> *b = a->left;
    b->parent = a->parent;
    a->left = b->right;

    if (a->left != NULL)
        a->left->parent = a;

    b->right = a;
    a->parent = b;

    if (b->parent != NULL) {
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
AVLnode<T>* AVLtree<T>::rotate_LR(AVLnode<T> *n) {
    n->left = rotateLeft(n->left);
    return rotateRight(n);
}


template <class T>
AVLnode<T>* AVLtree<T>::rotate_RL(AVLnode<T> *n) {
    n->right = rotateRight(n->right);
    return rotateLeft(n);
}


template <class T>
int AVLtree<T>::height(AVLnode<T> *n) {
    if (n == NULL)
        return -1;
    return 1 + std::max(height(n->left), height(n->right));
}


template <class T>
void AVLtree<T>::setBalance(AVLnode<T> *n) {
    n->balance = height(n->right) - height(n->left);
}


template <class T>
AVLtree<T>::AVLTree(void) : root(NULL) {}


template <class T>
AVLtree<T>::~AVLTree(void) {
    delete root;
}


template <class T>
bool AVLtree<T>::insert(T key) {
    if (root == NULL) {
        root = new AVLnode<T>(key, NULL);
    }
    else {
        AVLnode<T>
                *n = root,
                *parent;

        while (true) {
            if (n->key == key)
                return false;

            parent = n;

            bool goLeft = n->key > key;
            n = goLeft ? n->left : n->right;

            if (n == NULL) {
                if (goLeft) {
                    parent->left = new AVLnode<T>(key, parent);
                }
                else {
                    parent->right = new AVLnode<T>(key, parent);
                }

                rebalance(parent);
                break;
            }
        }
    }

    return true;
}


template <class T>
void AVLtree<T>::deleteKey(const T delKey) {
    if (root == NULL)
        return;

    AVLnode<T>
            *n       = root,
            *parent  = root,
            *delNode = NULL,
            *child   = root;

    while (child != NULL) {
        parent = n;
        n = child;
        child = delKey >= n->key ? n->right : n->left;
        if (delKey == n->key)
            delNode = n;
    }

    if (delNode != NULL) {
        delNode->key = n->key;

        child = n->left != NULL ? n->left : n->right;

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
    }
}
#endif //MUSIC_STREAMER_AVLTREE_H
