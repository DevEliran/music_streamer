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
    }

    total_songs -= toDelete->numOfSongs;

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

    //Find the proper node in the list of avltree and move it to the next node of the list
//    SongNode* song = artist->pointerArr[songID];
    SongCountNode* currNode = countList->searchNode(numOfStreams);
    SongCountNode* nextNode = countList->searchNode(numOfStreams + 1);

    if (!nextNode){
        countList->push(new SongCountNode(numOfStreams + 1));
        nextNode = countList->searchNode(numOfStreams + 1);
    }

    AVLTree<SongNode> *subTree = nextNode->ptr->searchNode(artistID, nextNode->ptr->root);
    AVLTree<SongNode> *prevSubTree = currNode->ptr->searchNode(artistID, currNode->ptr->root);

    if(!subTree){
        nextNode->ptr->insertSongTree(1, artistID, artist);
        subTree = nextNode->ptr->searchNode(artistID, nextNode->ptr->root);
    }

    subTree->insert(songID, artistID, true);
    prevSubTree->deleteKey(songID);
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
    while(songs_scanned < numOfSongs && tail != nullptr){
//        tail->ptr->root->scanInorder(tail->ptr->minNode->minNode, artists, songs, 0);
        tail->ptr->scanOuterTree(tail->ptr, artists, songs);
        songs_scanned +=tail->ptr->numOfNodes;
        tail = tail->prev;
    }
    return SUCCESS;
}


void MusicManager::Quit(ArtistNode* node){
    if(node == nullptr){
        return;
    }

    Quit(node->left);
    Quit(node->right);
    delete node;
}

MusicManager::~MusicManager() {
    delete tree;
    delete countList;
}