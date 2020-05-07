#ifndef MUSIC_STREAMER_MUSICMANAGER_H
#define MUSIC_STREAMER_MUSICMANAGER_H

#include "DoublyLL.h"
#include "ArtistNode.h"
#include "AvlTree.h"
#include "SongCountNode.h"
#include "library1.h"


class MusicManager{
public:
    MusicManager();
    StatusType AddDataCenter(int artistID, int numOfSongs);
    StatusType RemoveDataCenter(int artistId);
    StatusType IncrementSong(int artistID, int songID);
    StatusType GetSongPopularity(int artistID, int songID, int* streams);
    StatusType GetBestSongs(int numOfSongs, int* artists, int* songs);
    void Quit(ArtistNode* node);
    ~MusicManager();

    AVLTree<ArtistNode>* tree;
    DoublyLL<SongCountNode>* countList;
    int total_songs;
};
#endif //MUSIC_STREAMER_MUSICMANAGER_H
