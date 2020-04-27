#include "ArtistNode.h"

ArtistNode::ArtistNode(int id, int numOfSongs):artistID(id), numOfSongs(numOfSongs){
    songArr = malloc(*songArr);
    pointerArr = malloc(*pointerArr);
    for(int i =0; i < numOfSongs; i++){
        songArr[i] = 0;
        pointerArr[i] = NULL;
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

int* ArtistNode::getPointerArrByIndex(int i){
    return pointerArr[i];
}
