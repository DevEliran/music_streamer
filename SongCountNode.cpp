#include "SongCountNode.h"
#include <string>
#include <sstream>
SongCountNode::SongCountNode(int value):value(value), ptr(nullptr), next(nullptr),
                                        prev(nullptr){}
SongCountNode::~SongCountNode() {}

std::string SongCountNode::toString() {
    std::stringstream s;
    s << this->value;
    return s.str();
}

