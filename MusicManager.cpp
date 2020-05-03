#include "MusicManager.h"

MusicManager::MusicManager():tree(new(std::nothrow) AVLTree<ArtistNode>),
                            countList(new(std::nothrow) DoublyLL<SongCountNode>){}


StatusType MusicManager::AddDataCenter(int artistID, int numOfSongs){

    if (artistID <= 0 || numOfSongs <= 0){
        return INVALID_INPUT;
    }

    ArtistNode *artist = new(std::nothrow) ArtistNode(artistID, numOfSongs);
    if (!artist){
        return ALLOCATION_ERROR;
    }

    bool res = tree->insert(artist);
    if (res == false){
        return FAILURE;
    }

    SongCountNode* head = countList->getHead();

    head->ptr = new(std::nothrow) AVLTree<AVLTree<int>>;
    if (!head->ptr){
        return ALLOCATION_ERROR;
    }

    AVLTree<int> *songsTree = new(std::nothrow) AVLTree<int>;
    if(!songsTree){
        return ALLOCATION_ERROR;
    }

    for (int i = 0; i < numOfSongs; i++){
        songsTree->insert(&i);
    }

    head->ptr->insert(songsTree);
    total_songs += numOfSongs;
    return SUCCESS;
}


StatusType MusicManager::RemoveDataCenter(int artistID){

    if (artistID <= 0){
        return INVALID_INPUT;
    }

    ArtistNode* toDelete = new(std::nothrow) ArtistNode(artistID, 1);
    if (!toDelete){
        return ALLOCATION_ERROR;
    }

    bool res = tree->deleteKey(*toDelete);
    if (!res){
        return FAILURE;
    }

    //remove from countList as well, implement a pointer from the array in AVLTree to the proper node in the avltree inside the list.
    total_songs -= toDelete->numOfSongs;
    return SUCCESS;
}


StatusType MusicManager::IncrementSong(int artistID, int songID){

    if(artistID <= 0 || songID < 0){
        return INVALID_INPUT;
    }

    ArtistNode* artist = tree->searchNode(artistID, tree->root);
    if (artist == nullptr){
        return FAILURE;
    }

    if(artist->numOfSongs <= songID){
        return INVALID_INPUT;
    }

    artist->songArr[songID] ++;

    //Find the proper node in the list of avltree and move it to the next node of the list
    return SUCCESS;
}


StatusType MusicManager::GetSongPopularity(int artistID, int songID, int* streams){

    if(artistID <= 0 || songID < 0){
        return INVALID_INPUT;
    }

    ArtistNode* artist = tree->searchNode(artistID, tree->root);
    if(artist == nullptr){
        return FAILURE;
    }

    if(artist->numOfSongs <= songID){
        return INVALID_INPUT;
    }

    *streams =  artist->songArr[songID];

    return SUCCESS;
}


StatusType MusicManager::GetBestSongs(int numOfSongs, int* artists, int* songs){

    if(numOfSongs <= 0){
        return INVALID_INPUT;
    }

    if(total_songs < numOfSongs){
        return FAILURE;
    }

    int songs_scanned = 0;

    SongCountNode* tail = countList->getTail();

    //scan the avl tree of each node from tail to head until your reach songs_scanned == numOfSongs
    return SUCCESS;
}


void MusicManager::Quit(){
    delete tree;
    delete countList;
}
