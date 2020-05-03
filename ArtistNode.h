#ifndef MUSIC_STREAMER_ARTISTNODE_H
#define MUSIC_STREAMER_ARTISTNODE_H

class ArtistNode{
public:
    int artistID;
    int key;
    int numOfSongs;
    ArtistNode *left, *right, *parent;
    int balance;
    int* songArr;
    int* pointerArr;

    ArtistNode(int id, int numOfSongs);

    ArtistNode(const ArtistNode& t, ArtistNode* p);

    ArtistNode(const ArtistNode& a);

    int ArtistCompare(ArtistNode a, ArtistNode b);

    ~ArtistNode();

    int getArtistID();

    int getSongArrByIndex(int i);

    int getPointerArrByIndex(int i);
};

#endif //MUSIC_STREAMER_ARTISTNODE_H
