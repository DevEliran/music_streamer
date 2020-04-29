#include "ArtistNode.h"

ArtistNode::ArtistNode(int id, int numOfSongs):artistID(id), numOfSongs(numOfSongs),
                                                left(nullptr), right(nullptr),
                                                parent(nullptr), balance(0){
    songArr = new int[numOfSongs];
    pointerArr = new int[numOfSongs];
    for(int i =0; i < numOfSongs; i++){
        songArr[i] = 0;
        pointerArr[i] = 0;
    }
}

int ArtistNode::ArtistCompare(ArtistNode a, ArtistNode b){
    if (a.artistID == b.artistID){
        return 0;
    }
    else if (a.artistID > b.artistID){
        return 1;
    }
    return -1;
}

ArtistNode::~ArtistNode(){
    delete [] songArr;
    delete [] pointerArr;
}

int ArtistNode::getArtistID(){
    return artistID;
}

int ArtistNode::getSongArrByIndex(int i){
    return songArr[i];
}

int ArtistNode::getPointerArrByIndex(int i){
    return pointerArr[i];
}

ArtistNode::ArtistNode(const ArtistNode& a):artistID(a.artistID),numOfSongs(a.numOfSongs),
    left(a.left), right(a.right), parent(a.parent), balance(a.balance){
    songArr = new int[numOfSongs];
    pointerArr = new int[numOfSongs];
    for (int i = 0; i<numOfSongs;i++){
        songArr[i] = a.songArr[i];
        pointerArr[i] = a.pointerArr[i];
    }
}

ArtistNode::ArtistNode(const ArtistNode& t, ArtistNode* p) :artistID(t.artistID),
                                    numOfSongs(t.numOfSongs), balance(t.balance),
                                   parent(p), left(NULL),right(NULL){
    songArr = new int[numOfSongs];
    pointerArr = new int[numOfSongs];
    for (int i = 0; i<numOfSongs;i++){
        songArr[i] = t.songArr[i];
        pointerArr[i] = t.pointerArr[i];
    }
}
