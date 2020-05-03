#include "library1.h"
#include "MusicManager.h"

void *Init() {
    MusicManager *DS = new MusicManager();
    return (void *)DS;
}

StatusType AddArtist(void *DS, int artistID, int numOfSongs) {
    return ((MusicManager *)DS)-> AddDataCenter(artistID, numOfSongs);
}

StatusType RemoveArtist(void* DS, int artistID){
    return ((MusicManager *)DS)->RemoveDataCenter(artistID);
}

StatusType AddToSongCount(void *DS, int artistID, int songID){
    return ((MusicManager *)DS)->IncrementSong(artistID, songID);
}

StatusType NumberOfStreams(void *DS, int artistID, int songID, int *streams){
    return ((MusicManager *)DS)->GetSongPopularity(artistID, songID, streams);
}

StatusType GetRecommendedSongs(void *DS, int numOfSongs, int *artists, int *songs){
    return ((MusicManager *)DS)->GetBestSongs(numOfSongs, artists, songs);
}

void Quit(void **DS){
    ((MusicManager*)DS)->Quit();
    delete static_cast<MusicManager*>(*DS);
    *DS = nullptr;
}
