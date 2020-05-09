#ifndef MUSIC_STREAMER_DOUBLYLL_H
#define MUSIC_STREAMER_DOUBLYLL_H

#include "SongCountNode.h"

template <class T>
class DoublyLL{
private:
    T* head;
    T* tail;
    int list_size;
public:
    DoublyLL();
    T* getHead();
    T* getTail();
    int size(bool update=false);
    void addNodeAsTail(T* new_node);
    void addNodeAsHead(T* new_node);
    void push(T* new_node);
    T* pop();
    T* peek();
    void enqueue(T* new_node);
    T* dequeue();
    T* get(int index);
    void printList();
    void printListBackwards();
    ~DoublyLL(void);
    SongCountNode* searchNode(int value);
};

template <class T>
DoublyLL<T>::DoublyLL(void) {
    this->head = nullptr;
    this->tail = nullptr;
    SongCountNode* a = new SongCountNode(0);
    this->push(a);
    this->list_size = 1;
}

template <class T>
T* DoublyLL<T>::getHead() {
    return this->head;
}

template <class T>
T* DoublyLL<T>::getTail() {
    return this->tail;
}

template <class T>
int DoublyLL<T>::size(bool update) {
    if (!update) {
        return this->list_size;
    }
    int size = 0;
    T* temp = this->head;
    while (temp) {
        size++;
        temp = temp->next;
    }
    this->list_size = size;
    return this->list_size;
}

template <class T>
void DoublyLL<T>::addNodeAsTail(T* new_node) {
    new_node->next = NULL;
    new_node->prev = NULL;

    if (this->head == NULL) {
        this->head = new_node;
        this->tail = this->head;
        this->list_size = this->list_size + 1;
    } else {
        this->tail->next = new_node;
        new_node->prev = this->tail;
        this->tail = new_node;
        this->list_size = this->list_size + 1;
    }
}

template <class T>
void DoublyLL<T>::addNodeAsHead(T* new_node) {
    new_node->next = NULL;
    new_node->prev = NULL;

    if (this->head == NULL) {
        this->head = new_node;
        this->tail = this->head;
        this->list_size = this->list_size + 1;
    } else {
        this->head->prev = new_node;
        new_node->next = this->head;
        this->head = new_node;
        this->list_size = this->list_size + 1;
    }
}

template <class T>
void DoublyLL<T>::push(T* new_node) {
    this->addNodeAsTail(new_node);
}

template <class T>
T* DoublyLL<T>::pop() {
    T* temp = this->head;
    this->head = this->head->next;
    this->head->prev = NULL;
    this->list_size = this->list_size - 1;
    return temp;
}

template <class T>
T* DoublyLL<T>::peek() {
    return this->head;
}

template <class T>
void DoublyLL<T>::enqueue(T* new_node) {
    this->addNodeAsTail(new_node);
}

template <class T>
T* DoublyLL<T>::dequeue() {
    return this->pop();
}

template <class T>
T* DoublyLL<T>::get(int index) {
    if (index == 0) {
        return this->head;
    } else if (index == this->list_size - 1) {
        return this->tail;
    } else if (index < 0 || index >= this->list_size) {
        return NULL;
    }
    if (index < this->list_size / 2) {
        T* temp = this->head;
        int i = 0;
        while (temp) {
            if (i == index) { return temp; }
            i++;
            temp = temp->next;
        }
    } else {
        T* temp = this->tail;
        int i = this->list_size - 1;
        while (temp) {
            if (i == index) { return temp; }
            i--;
            temp = temp->prev;
        }
    }
    return NULL;
}

template <class T>
void DoublyLL<T>::printList() {
    std::cout << "HEAD: ";
    T* temp = this->head;
    while(temp) {
        std::cout << temp->toString() << " -> ";
        temp = temp->next;
    }
    std::cout << "\b\b\b\b :TAIL" << std::endl;
}

template <class T>
void DoublyLL<T>::printListBackwards() {
    std::cout << "TAIL: ";
    T* temp = this->tail;
    while(temp) {
        std::cout << temp->toString() << " -> ";
        temp = temp->prev;
    }
    std::cout << "\b\b\b\b :HEAD" << std::endl;
}

template <class T>
DoublyLL<T>::~DoublyLL() {
    while (this->head) {
        T* next = this->head->next;
        delete this->head;
        this->list_size = this->list_size - 1;
        this->head = next;
    }
}


template <class T>
SongCountNode* DoublyLL<T>::searchNode(int value){
    T* temp = this->head;
    while(temp){
        if (temp->value == value){
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}
#endif //MUSIC_STREAMER_DOUBLYLL_H
