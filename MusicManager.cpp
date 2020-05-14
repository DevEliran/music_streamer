#include "MusicManager.h"
#include "SongNode.h"
#include "AvlTree.h"
#include "DoublyLL.h"
#include "SongCountNode.h"


MusicManager::MusicManager():tree(nullptr),
                            countList(nullptr),
                             total_songs(0){
    tree = new(std::nothrow) AVLTree<ArtistNode>;
    countList = new(std::nothrow) DoublyLL<SongCountNode>;
}



StatusType MusicManager::AddDataCenter(int artistID, int numOfSongs){

    if (artistID <= 0 || numOfSongs <= 0){
        return INVALID_INPUT;
    }

    if (!tree->insert(artistID, numOfSongs)){
        return FAILURE;
    }
    ArtistNode* a = tree->searchNode(artistID, tree->root);
    countList->getHead()->ptr->insertSongTree(numOfSongs, artistID, a);
    total_songs += numOfSongs;

    return SUCCESS;
}


StatusType MusicManager::RemoveDataCenter(int artistID){

    if (artistID <= 0){
        return INVALID_INPUT;
    }
    ArtistNode* toDelete = tree->searchNode(artistID, this->tree->root);
    if (!toDelete){
        return FAILURE;
    }

    for(int i = 0; i < toDelete->numOfSongs; i++){
        delete toDelete->pointerArr[i];
        toDelete->pointerArr[i] = nullptr;

    }

    total_songs -= toDelete->numOfSongs;
    toDelete = nullptr;

    bool res = tree->deleteKey(artistID);
    if (!res){
        return FAILURE;
    }

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

    int numOfStreams = artist->songArr[songID];
    artist->songArr[songID] ++;

    SongCountNode* currNode = countList->searchNode(numOfStreams);
    SongCountNode* nextNode = countList->searchNode(numOfStreams + 1);

    if (!nextNode){
        countList->push(new SongCountNode(numOfStreams + 1));
        nextNode = countList->searchNode(numOfStreams + 1);
    }

    AVLTree<SongNode> *subTree = nextNode->ptr->searchNode(artistID, nextNode->ptr->root);
    AVLTree<SongNode> *prevSubTree = currNode->ptr->searchNode(artistID, currNode->ptr->root);

    if(!subTree){
        nextNode->ptr->insertSongTree(0, artistID, artist);
        subTree = nextNode->ptr->searchNode(artistID, nextNode->ptr->root);
    }

    subTree->insert(songID, artistID, true);
    prevSubTree->deleteKey(songID);

    if(prevSubTree) {
        if (prevSubTree->root == nullptr) {
            currNode->ptr->deleteKey(prevSubTree->key);
        }
    }

    if (currNode->ptr == nullptr){
        SongCountNode* prev = currNode->prev;
        SongCountNode* next = currNode->next;
        prev->next = next;
        next->prev = prev;
        delete currNode;
        currNode = nullptr;
    }

    return SUCCESS;
}


StatusType MusicManager::GetSongPopularity(int artistID, int songID, int* streams){

    if(artistID <= 0 || songID < 0 || !streams){
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

    if(numOfSongs <= 0 || !artists || !songs){
        return INVALID_INPUT;
    }

    if(total_songs < numOfSongs){
        return FAILURE;
    }


    for(int j = 0; j <numOfSongs; j++){
        songs[j] = -1;
        artists[j] = -1;
    }
    SongCountNode* tail = countList->getTail();

    //scan the avl tree of each node from tail to head until your reach songs_scanned == numOfSongs
    while(songs[numOfSongs-1] == -1 && tail != nullptr){
        tail->ptr->scanOuterTree(tail->ptr->minNode, artists, songs, numOfSongs, false);//was minNOde
        tail = tail->prev;
    }
    return SUCCESS;
}


//void MusicManager::Quit(ArtistNode* node){
//    if(node == nullptr){
//        return;
//    }
//
//    Quit(node->left);
//    Quit(node->right);
//    delete node;
//}

MusicManager::~MusicManager() {
    delete tree;
    tree = nullptr;
    delete countList;
    countList = nullptr;
}