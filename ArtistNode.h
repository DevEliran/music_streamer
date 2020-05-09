#ifndef MUSIC_STREAMER_ARTISTNODE_H
#define MUSIC_STREAMER_ARTISTNODE_H

#include "SongNode.h"

class ArtistNode{
public:
//    int artistID;
    int key;
    int numOfSongs;
    ArtistNode *left, *right, *parent;
    int balance;
    int* songArr;
    SongNode** pointerArr;

    ArtistNode(int id, int numOfSongs);

    ArtistNode(int id, int numOfSongs, ArtistNode* p);

    ArtistNode(const ArtistNode& a);

    int ArtistCompare(ArtistNode a, ArtistNode b);

    ~ArtistNode();

    int getArtistID();

    int getSongArrByIndex(int i);

    SongNode* getPointerArrByIndex(int i);
};

#endif //MUSIC_STREAMER_ARTISTNODE_H
