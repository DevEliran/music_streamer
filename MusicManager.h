#ifndef MUSIC_STREAMER_MUSICMANAGER_H
#define MUSIC_STREAMER_MUSICMANAGER_H
class MusicManager(){
public:
    MusicManager();
    AddDataCenter(int artistID, int numOfSongs);
    RemoveDataCenter(int artistId);
    IncrementSong(int artistID, int songID);
    GetSongPopularity(int artistID, int songID, int* streams);
    GetBestSongs(int numOfSongs, int* artists, int* songs);
}
#endif //MUSIC_STREAMER_MUSICMANAGER_H
