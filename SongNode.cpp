#include "SongNode.h"

SongNode::SongNode(int key, int artistID) :key(key), song_ptr(nullptr), left(nullptr),
                            right(nullptr), parent(nullptr), balance(0),
                            artistID(artistID){};

void SongNode::UpdatePtr(int *ptr){
    song_ptr = ptr;
}


SongNode::SongNode(int key, int artistID, SongNode *p):key(key), song_ptr(
        nullptr), left (nullptr), right(nullptr), parent(p), balance(0),
        artistID(artistID){}


SongNode::~SongNode() {
    delete song_ptr;
//    delete left;
//    delete right;
//    delete parent;
}

SongNode::SongNode(const SongNode &t, SongNode *p):key(t.key), song_ptr(t.song_ptr),
                                            left(t.left), right(t.right),
                                            parent(p), balance(t.balance),
                                            artistID(t.artistID){}

