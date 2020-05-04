#include "MusicManager.h"
#include "SongNode.h"
#include "AvlTree.h"
#include "DoublyLL.h"
#include "SongCountNode.h"


MusicManager::MusicManager():tree(new(std::nothrow) AVLTree<ArtistNode>),
                            countList(new(std::nothrow) DoublyLL<SongCountNode>),
                             total_songs(0){}



StatusType MusicManager::AddDataCenter(int artistID, int numOfSongs){

    if (artistID <= 0 || numOfSongs <= 0){
        return INVALID_INPUT;
    }

    ArtistNode *artist = new(std::nothrow) ArtistNode(artistID, numOfSongs);
    if (!artist){
        return ALLOCATION_ERROR;
    }

    ArtistNode* res = tree->insert(artist);
    if (!res){
        return FAILURE;
    }

    SongCountNode* head = countList->getHead();

    head->ptr = new(std::nothrow) AVLTree<AVLTree<SongNode>>;
    if (!head->ptr){
        return ALLOCATION_ERROR;
    }

    AVLTree<SongNode> *songsTree = new(std::nothrow) AVLTree<SongNode>;
    if(!songsTree){
        return ALLOCATION_ERROR;
    }

    for (int i = 0; i < numOfSongs; i++){
        SongNode* n = new(std::nothrow) SongNode(i);
        if (!n){
            return ALLOCATION_ERROR;
        }
        songsTree->insert(n);
        res->pointerArr[i] = n;
    }

    head->ptr->insert(songsTree);
    total_songs += numOfSongs;
    return SUCCESS;
}


StatusType MusicManager::RemoveDataCenter(int artistID){

    if (artistID <= 0){
        return INVALID_INPUT;
    }
    ArtistNode* toDelete = tree->searchNode(artistID, this->tree->root);
    if (!toDelete){
        return ALLOCATION_ERROR;
    }
    for (int i = 0; i<toDelete->numOfSongs; i++){
        delete toDelete->pointerArr[i];
    }
    bool res = tree->deleteKey(*toDelete);
    if (!res){
        return FAILURE;
    }

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
    tree = nullptr;
    countList = nullptr;
}
