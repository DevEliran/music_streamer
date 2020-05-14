#include "library1.h"
#include "MusicManager.h"

void *Init() {
    MusicManager *DS = new MusicManager();
    return (void *)DS;
}

StatusType AddArtist(void *DS, int artistID, int numOfSongs) {
    if(!DS){
        return INVALID_INPUT;
    }
    return ((MusicManager *)DS)-> AddDataCenter(artistID, numOfSongs);
}

StatusType RemoveArtist(void* DS, int artistID){
    if(!DS){
        return INVALID_INPUT;
    }
    return ((MusicManager *)DS)->RemoveDataCenter(artistID);
}

StatusType AddToSongCount(void *DS, int artistID, int songID){
    if(!DS){
        return INVALID_INPUT;
    }
    return ((MusicManager *)DS)->IncrementSong(artistID, songID);
}

StatusType NumberOfStreams(void *DS, int artistID, int songID, int *streams){
    if(!DS){
        return INVALID_INPUT;
    }
    return ((MusicManager *)DS)->GetSongPopularity(artistID, songID, streams);
}

StatusType GetRecommendedSongs(void *DS, int numOfSongs, int *artists, int *songs){
    if(!DS){
        return INVALID_INPUT;
    }
    return ((MusicManager *)DS)->GetBestSongs(numOfSongs, artists, songs);
}

void Quit(void **DS){
//    ((MusicManager*)DS)->Quit();
    delete static_cast<MusicManager*>(*DS);
    *DS = nullptr;
}
