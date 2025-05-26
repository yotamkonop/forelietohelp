#pragma once
#include "node.h"
#include "song.h"
#include <memory>


//
// Created by Yotam Konopnicki on 14/05/2025.
//
using namespace std;


class Playlist {
    int id;
    int songNum;
    Node<shared_ptr<Song>>* idRoot;
    Node<shared_ptr<Song>>* playedRoot;

public:
    Playlist();

    explicit Playlist(int id);

    Playlist(const Playlist& playlist);

    Playlist& operator=(const Playlist& playlist);

    int getID() const;

    void setID(int id);

    int getSongNum() const;

    Node<shared_ptr<Song>>*& getIDTree();

    Node<shared_ptr<Song>>*& getPlayedTree();

    bool operator==(const Playlist& playlist) const;

    ~Playlist();

    void setSongNum(int songNum);

    void setIdTree(Node<shared_ptr<Song>>* idTree);

    void setPlayedTree(Node<shared_ptr<Song>>* playedTree);
};