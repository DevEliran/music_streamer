#include "ArtistNode.h"

ArtistNode::ArtistNode(int id, int numOfSongs):key(id), numOfSongs(numOfSongs),
                                                left(nullptr), right(nullptr),
                                                parent(nullptr), balance(0){
    songArr = new int[numOfSongs];
    pointerArr = new SongNode*[numOfSongs];
    for(int i =0; i < numOfSongs; i++){
        songArr[i] = 0;
        pointerArr[i] = nullptr;
    }
}

int ArtistNode::ArtistCompare(ArtistNode a, ArtistNode b){
    if (a.key == b.key){
        return 0;
    }
    else if (a.key > b.key){
        return 1;
    }
    return -1;
}

ArtistNode::~ArtistNode(){
    delete[] songArr;
    songArr = nullptr;
    delete[] pointerArr;
    pointerArr = nullptr;
}

int ArtistNode::getArtistID(){
    return key;
}

int ArtistNode::getSongArrByIndex(int i){
    return songArr[i];
}

SongNode* ArtistNode::getPointerArrByIndex(int i){
    return pointerArr[i];
}

ArtistNode::ArtistNode(const ArtistNode& a):key(a.key), numOfSongs(a.numOfSongs),
    left(a.left), right(a.right), parent(a.parent), balance(a.balance){
    songArr = new int[numOfSongs];
    pointerArr = new SongNode*[numOfSongs];
    for (int i = 0; i<numOfSongs;i++){
        songArr[i] = a.songArr[i];
        pointerArr[i] = a.pointerArr[i];
    }
}

ArtistNode::ArtistNode(int id, int numOfSongs, ArtistNode* p) :key(id),
                                        numOfSongs(numOfSongs), left(nullptr),
                                    right(nullptr), parent(p), balance(0){
    songArr = new int[numOfSongs];
    pointerArr = new SongNode*[numOfSongs];
    for (int i = 0; i<numOfSongs;i++){
        songArr[i] = 0;
        pointerArr[i] = nullptr;
    }
}
