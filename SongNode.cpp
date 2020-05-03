#include "SongNode.h"

SongNode::SongNode(int key) :key(key), song_ptr(nullptr), left(nullptr),
                            right(nullptr), parent(nullptr), balance(0){};

void SongNode::UpdatePtr(int *ptr){
    song_ptr = ptr;
}

SongNode::~SongNode() {
    delete song_ptr;
}

SongNode::SongNode(const SongNode &t, SongNode *p):key(t.key), song_ptr(t.song_ptr),
                                            left(t.left), right(t.right),
                                            parent(p), balance(t.balance){}

