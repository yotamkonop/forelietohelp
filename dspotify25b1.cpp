// You can edit anything you want in this file.
// However you need to implement all public DSpotify function, as provided below as a template

#include "dspotify25b1.h"
#include "RealValueFunctions.h"
#include "AVL_trees.h"
#include <memory>


DSpotify::DSpotify():   playlistRoot(nullptr) , songRoot(nullptr){}

DSpotify::~DSpotify(){
    delete playlistRoot;
    delete songRoot;
}

StatusType DSpotify::add_playlist(int playlistId){
    if(playlistId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        Playlist play = Playlist(playlistId);
        findNodeAVL(playlistRoot, play, playlistRealValueId);
        return StatusType::FAILURE;
    } catch (...) {
        try {
            Playlist playlist(playlistId);
            Node<Playlist> *node = new Node<Playlist>(playlist);
            insertNodeIntoAVL(playlistRoot, node, playlistRealValueId);
            return  StatusType::SUCCESS;
        } catch (...) {
            return StatusType::ALLOCATION_ERROR;
        }
    }
}

StatusType DSpotify::delete_playlist(int playlistId){
    if (playlistId<=0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        Playlist play(playlistId);
        Node<Playlist> *playlist= findNodeAVL(playlistRoot, play, playlistRealValueId);
        if(playlist->val.getSongNum() == 0) {
            deletePlaylist(playlistRoot, playlist);
            return StatusType::SUCCESS;
        }
        else {
            return StatusType::FAILURE;
        }
    } catch (...) {
        return StatusType::FAILURE;
    }
}

StatusType DSpotify::add_song(int songId, int plays){
    if(songId <=0 || plays < 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        shared_ptr<Song> ptrS = std::make_shared<Song>(songId, plays);
        findNodeAVL(songRoot, ptrS, songRealValueIdPtr);
    /*    try {
            shared_ptr<Song> ptrcheck = std::make_shared<Song>(139620, 0);
            Node<shared_ptr<Song>> *chechPtr = findNodeAVL(songRoot, ptrcheck, songRealValueIdPtr);
            cout << "the counter of 139620 is: " << chechPtr->val.use_count() << endl;
        } catch (...){}*/
        return StatusType::FAILURE;
    } catch (...) {
        try {
            shared_ptr<Song> ptrS = std::make_shared<Song>(songId, plays);
            Node<shared_ptr<Song>> *node = new Node<shared_ptr<Song>>(ptrS);
            insertNodeIntoAVL(songRoot, node, songRealValueIdPtr);
//            cout << "add Song: should be 2 " << node->val.use_count() << endl;

            //check
/*            try {
                shared_ptr<Song> ptrcheck = std::make_shared<Song>(717117, 0);
                Node<shared_ptr<Song>> *chechPtr = findNodeAVL(songRoot, ptrcheck, songRealValueIdPtr);
                cout << "the counter of 717117 is: " << chechPtr->val.use_count() << endl;
            } catch (...){}*/

            /*try {
                shared_ptr<Song> ptrcheck = std::make_shared<Song>(139620, 0);
                Node<shared_ptr<Song>> *chechPtr = findNodeAVL(songRoot, ptrcheck, songRealValueIdPtr);
                cout << "the counter of 139620 is: " << chechPtr->val.use_count() << endl;
            } catch (...){}*/
            return StatusType::SUCCESS;
        } catch (...) {
            return StatusType::ALLOCATION_ERROR;
        }
    }
}

StatusType DSpotify::add_to_playlist(int playlistId, int songId){

    //check
/*    try {
        shared_ptr<Song> ptrcheck = std::make_shared<Song>(717117, 0);
        Node<shared_ptr<Song>> *chechPtr = findNodeAVL(songRoot, ptrcheck, songRealValueIdPtr);
        cout << "the counter of 717117 is: " << chechPtr->val.use_count() << endl;
    } catch (...){}*/

    if(playlistId <= 0 || songId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    Node<shared_ptr<Song>> *nodeToId = nullptr;
    Node<shared_ptr<Song>> *nodeToPlays = nullptr;
    try {

        Playlist playlist(playlistId);
        shared_ptr<Song> ptrS = std::make_shared<Song>(songId, 0);
        Node<shared_ptr<Song>> *songNode = findNodeAVL(songRoot, ptrS, songRealValueIdPtr);
        Node<Playlist> *playlistNode = findNodeAVL(playlistRoot, playlist, playlistRealValueId);
    //    cout << "add to playlist start: should be equal (songs in playlist): " << playlistNode->val.getSongNum() << "   " << lengthAVL(playlistNode->val.getIDTree()) << endl;
     //   cout << "add to playlist start: should be equal (songs in playlist): " << playlistNode->val.getSongNum() << "   " << lengthAVL(playlistNode->val.getPlayedTree()) << endl;

        try {
            nodeToId= new Node<shared_ptr<Song>>(songNode->val);
            nodeToPlays= new Node<shared_ptr<Song>>(songNode->val);
       //     cout << "add to playlist: should be (playlists for this song): " << nodeToId->val->getPlaylistNum() << "  " << (nodeToId->val.use_count() - 3) / 2 << endl;
            try {
 /*               if (playlistNode->val.getIDTree() == nullptr) {
                    cout << "here" << endl;
                }
                else if(playlistNode->val.getIDTree()->val == nullptr){
                    cout << "here 2" << endl;
                }
                else {
                    cout << playlistNode->val.getIDTree()->val.use_count() << endl;
                    try {
                        cout << "here 3" << endl;
                        findNodeAVL(songRoot, playlistNode->val.getIDTree()->val, songRealValueIdPtr);
                        cout << "exists" << endl;
                    } catch (...) {
                        cout << "dont exist" << endl;
                    }
                }*/
               /* if(songId == 757410) {
                    cout << "here" << endl;
                    cout << playlistNode->val.getIDTree()->val->getID() << endl;
                    cout << "here 2" << endl;
                    cout << playlistNode->val.getPlayedTree()->val->getID() << endl;
                    cout << "here 3" << endl;
                }*/
                Node<shared_ptr<Song>> *check = findNodeAVL(playlistNode->val.getIDTree(), nodeToId->val, songRealValueIdPtr);
                delete nodeToId;
                delete nodeToPlays;
 //               cout << "add to playlist: fail :" << check->val.use_count() << endl;
                return StatusType::FAILURE;
            } catch (...) {
               /* if(songId == 757410) {
                    cout << "here" << endl;
                    cout << playlistNode->val.getIDTree()->val->getID() << endl;
                    cout << playlistNode->val.getPlayedTree()->val->getID() << endl;
                }*/
                insertNodeIntoAVL(playlistNode->val.getIDTree(), nodeToId, songRealValueIdPtr);
                insertNodeIntoAVL(playlistNode->val.getPlayedTree(), nodeToPlays, songRealValuePlaysPtr);
                nodeToId->val->setPlaylistNum(nodeToId->val->getPlaylistNum() + 1);
                playlistNode->val.setSongNum(playlistNode->val.getSongNum() + 1);

          /*      if(nodeToId->val->getID() == 139620) {
                    cout << nodeToId->val.use_count() << endl;
                }*/
      //          cout << "add to playlist end: should be equal (songs in playlist): " << playlistNode->val.getSongNum() << "   " << lengthAVL(playlistNode->val.getIDTree()) << endl;
                return StatusType::SUCCESS;
            }
        } catch (...) {
            delete nodeToId;
            delete nodeToPlays;
            return StatusType::ALLOCATION_ERROR;
        }
    } catch (...) {
        delete nodeToId;
        delete nodeToPlays;
        return StatusType::FAILURE;
    }
}

StatusType DSpotify::delete_song(int songId){
    if(songId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        shared_ptr<Song> ptrS = std::make_shared<Song>(songId, 0);
        Node<shared_ptr<Song>> *node = findNodeAVL(songRoot, ptrS, songRealValueIdPtr);
        if(node->val->getPlaylistNum() != 0) {
            return StatusType::FAILURE;
        }
        else if(node->val->getPlaylistNum() == 0) {
        //    cout << "delte song: should be 1 " << node->val.use_count() << endl;
            deleteNodeAVL(songRoot, node, songRealValueIdPtr);
            return StatusType::SUCCESS;
        }
        return StatusType::FAILURE;
    } catch (...) {
        return StatusType::FAILURE;
    }
}

StatusType DSpotify::remove_from_playlist(int playlistId, int songId){
    if(playlistId <= 0 || songId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        Playlist playlist(playlistId);
        shared_ptr<Song> ptrS = std::make_shared<Song>(songId, 0);
        Node<Playlist> *playlistNode = findNodeAVL(playlistRoot, playlist, playlistRealValueId);
        Node<shared_ptr<Song>> *songIdPtr = findNodeAVL(playlistNode->val.getIDTree(), ptrS, songRealValueIdPtr);
        Node<shared_ptr<Song>> *songPlaysPtr = findNodeAVL(playlistNode->val.getPlayedTree(),
            songIdPtr->val, songRealValuePlaysPtr);

        songIdPtr->val->setPlaylistNum(songIdPtr->val->getPlaylistNum() - 1);
       // cout << "remove from playlist: should be:" << songIdPtr->val->getPlaylistNum() << "  " << ((songIdPtr->val.use_count() - 3) / 2) << endl;

        deleteNodeAVL(playlistNode->val.getIDTree(), songIdPtr, songRealValueIdPtr);
        deleteNodeAVL(playlistNode->val.getPlayedTree(), songPlaysPtr, songRealValuePlaysPtr);

        playlistNode->val.setSongNum(playlistNode->val.getSongNum() - 1);

//        cout << "remove from playlist: should be equal (songs in playlist): " << playlistNode->val.getSongNum() << "   " << lengthAVL(playlistNode->val.getIDTree()) << endl;

        return StatusType::SUCCESS;
    } catch (...) {
        return StatusType::FAILURE;
    }
}

output_t<int> DSpotify::get_plays(int songId){
    if(songId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        shared_ptr<Song> ptrS = std::make_shared<Song>(songId, 0);
        Node<shared_ptr<Song>> *node = findNodeAVL(songRoot, ptrS, songRealValueIdPtr);
        return node->val->getPlays();
    } catch (...) {
        return StatusType::FAILURE;
    }
}

output_t<int> DSpotify::get_num_songs(int playlistId){
    if(playlistId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        Playlist playlist(playlistId);
        Node<Playlist> *node = findNodeAVL(playlistRoot, playlist, playlistRealValueId);
        return node->val.getSongNum();
    } catch (...) {
        return StatusType::FAILURE;
    }
}

output_t<int> DSpotify::get_by_plays(int playlistId, int plays){
    if(playlistId <= 0 || plays < 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        Playlist playlist = Playlist(playlistId);
        Node<Playlist> *playlistNode = findNodeAVL(playlistRoot, playlist, playlistRealValueId);
        Node<shared_ptr<Song>> nodeSong = std::make_shared<Song>(0, -1);
        Node<shared_ptr<Song>> *best = findClosestBiggerSong(playlistNode->val.getPlayedTree(), plays, &nodeSong);
        if(best == nullptr) {
            return StatusType::FAILURE;
        }
      //  cout << "getbyplays: should be:" << best->val->getPlaylistNum() << "  " << ((best->val.use_count() - 1) / 2) << endl;
        if(best->val->getPlays() < plays) {
            return StatusType::FAILURE;
        }
        return best->val->getID();
    } catch (...) {
        return StatusType::FAILURE;
    }
}

StatusType DSpotify::unite_playlists(int playlistId1, int playlistId2){

    //check
 /*   try {
        shared_ptr<Song> ptrcheck = std::make_shared<Song>(139620, 0);
        Node<shared_ptr<Song>> *chechPtr = findNodeAVL(songRoot, ptrcheck, songRealValueIdPtr);
        cout << "the counter of 139620 is: " << chechPtr->val.use_count() << endl;
    } catch (...){}*/

    if(playlistId1 <= 0 || playlistId2 <= 0 || playlistId1 == playlistId2) {
        return StatusType::INVALID_INPUT;
    }
    try {
        Playlist playlist1(playlistId1);
        Playlist playlist2(playlistId2);
        Node<Playlist> *playlist1Node = findNodeAVL(playlistRoot, playlist1, playlistRealValueId);
        Node<Playlist> *playlist2Node = findNodeAVL(playlistRoot, playlist2, playlistRealValueId);

        decreasePlaylistNum(playlist2Node->val.getIDTree());
        decreasePlaylistNum(playlist1Node->val.getIDTree());

        Node<shared_ptr<Song>> *newIdRoot = mergeAVL(playlist1Node->val.getIDTree(), playlist2Node->val.getIDTree(),
            songRealValueId);
        Node<shared_ptr<Song>> *newPlaysRoot = mergeAVL(playlist1Node->val.getPlayedTree(),
            playlist2Node->val.getPlayedTree(), songRealValuePlays);

        //check
/*        try {
            shared_ptr<Song> ptrcheck = std::make_shared<Song>(717117, 0);
            Node<shared_ptr<Song>> *chechPtr = findNodeAVL(songRoot, ptrcheck, songRealValueIdPtr);
            cout << "the counter of 717117 is: " << chechPtr->val.use_count() << endl;
        } catch (...){}*/

        //check
 /*       try {
                shared_ptr<Song> ptrcheck = std::make_shared<Song>(139620, 0);
                Node<shared_ptr<Song>> *chechPtr = findNodeAVL(songRoot, ptrcheck, songRealValueIdPtr);
                cout << "the counter of 139620 is: " << chechPtr->val.use_count() << endl;
            } catch (...){}*/



        delete playlist2Node->val.getIDTree();
        delete playlist2Node->val.getPlayedTree();
        playlist2Node->val.setIdTree(nullptr);
        playlist2Node->val.setPlayedTree(nullptr);



  //      cout << "check if its here before" << endl;
        deletePlaylist(playlistRoot, playlist2Node);
 //       cout << "check if its here after" << endl;



 //       cout << "check here" << endl;

        delete playlist1Node->val.getIDTree();
        delete playlist1Node->val.getPlayedTree();

        playlist1Node->val.setIdTree(newIdRoot);
        playlist1Node->val.setPlayedTree(newPlaysRoot);
        playlist1Node->val.setSongNum(lengthAVL(newIdRoot));

        increasePlaylistNum(playlist1Node->val.getIDTree());
        //check
 /*       try {
            shared_ptr<Song> ptrcheck = std::make_shared<Song>(139620, 0);
            Node<shared_ptr<Song>> *chechPtr = findNodeAVL(songRoot, ptrcheck, songRealValueIdPtr);
            cout << "the counter of 139620 is: " << chechPtr->val.use_count() << endl;
        } catch (...){}*/

        return StatusType::SUCCESS;
    } catch (...) {
        return StatusType::FAILURE;
    }
}
