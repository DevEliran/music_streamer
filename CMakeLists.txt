cmake_minimum_required(VERSION 3.15)
project(music_streamer)

set(CMAKE_CXX_STANDARD 11)

add_executable(music_streamer
                main.cpp
        DoublyLL.h
        SongCountNode.h
        AvlTree.h
        ArtistNode.h
        SongCountNode.cpp
        ArtistNode.cpp
        library1.h
        library1.cpp
        MusicManager.cpp
        MusicManager.h
#                avlTree_test.cpp
        )
