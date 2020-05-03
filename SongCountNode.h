#ifndef MUSIC_STREAMER_SONGCOUNTNODE_H
#define MUSIC_STREAMER_SONGCOUNTNODE_H

#include "AvlTree.h"
#include "SongNode.h"
#include <string>
#include <sstream>

class SongCountNode{
public:
    int value;
    AVLTree<AVLTree<SongNode>> * ptr;
    SongCountNode *next, *prev;

    SongCountNode(int value);
    ~SongCountNode();
    std::string toString();
};
#endif //MUSIC_STREAMER_SONGCOUNTNODE_H
