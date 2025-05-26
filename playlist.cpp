#include "playlist.h"
#include <memory>

using namespace std;

Playlist::Playlist(): id(0), songNum(0), idRoot(nullptr), playedRoot(nullptr){}

Playlist::Playlist(int id): id(id), songNum(0) , idRoot(nullptr), playedRoot(nullptr){}

Playlist::Playlist(const Playlist &playlist) = default;

Playlist &Playlist::operator=(const Playlist &playlist) = default;

int Playlist::getID() const {
    return id;
}

void Playlist::setID(int id) {
    this->id = id;
}


int Playlist::getSongNum() const {
    return songNum;
}

Node<shared_ptr<Song>>*& Playlist::getIDTree() {
    return idRoot;
}

Node<shared_ptr<Song>>*& Playlist::getPlayedTree() {
    return playedRoot;
}

bool Playlist::operator==(const Playlist &playlist) const{
    if(id == playlist.getID()) {
        return true;
    }
    return false;
}

Playlist::~Playlist() {
    delete playedRoot;
    delete idRoot;
}

void Playlist::setSongNum(int songNum) {
    this->songNum = songNum;
}

void Playlist::setIdTree(Node<shared_ptr<Song>> *idTree) {
    this->idRoot = idTree;
}

void Playlist::setPlayedTree(Node<shared_ptr<Song>> *playedTree) {
    this->playedRoot = playedTree;
}



