#ifndef MUSIC_STREAMER_ARTISTNODE_H
#define MUSIC_STREAMER_ARTISTNODE_H

class ArtistNode{
public:
    ArtistNode(int id, int numOfSongs);

    int ArtistCompare(ArtistNode a, ArtistNode b);

    ~ArtistNode();

    int getArtistID();

    int getSongArrByIndex(int i);

    int* getPointerArrByIndex(int i);

private:
    int songArr[];
    int *pointerArr[];
    int artistID;
    int numOfSongs;
};

#endif //MUSIC_STREAMER_ARTISTNODE_H
