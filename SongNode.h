#ifndef MUSIC_STREAMER_SONGNODE_H
#define MUSIC_STREAMER_SONGNODE_H

class SongNode{
public:
    int key;
    int* song_ptr;
    SongNode *left, *right, *parent;
    int balance;
    int artistID;

    SongNode() = default;
    SongNode(int key, int artistID);
    SongNode(const SongNode& t, SongNode* p);
    void UpdatePtr(int *ptr);
    ~SongNode();
};
#endif //MUSIC_STREAMER_SONGNODE_H
