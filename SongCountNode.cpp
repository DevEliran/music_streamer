#include "SongCountNode.h"
#include <string>
#include <sstream>
SongCountNode::SongCountNode(int value):value(value), ptr(new AVLTree<AVLTree<SongNode>>), next(nullptr),
                                        prev(nullptr){}
SongCountNode::~SongCountNode() {
    delete ptr;
    ptr = nullptr;
}

std::string SongCountNode::toString() {
    std::stringstream s;
    s << this->value;
    return s.str();
}

