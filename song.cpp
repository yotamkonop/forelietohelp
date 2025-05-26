#include "song.h"


Song::Song(int id, int plays): id(id), plays(plays), playlistNum(0){}

Song::Song(const Song& song) = default;

int Song::getPlays() const {
    return plays;
}

int Song::getID() const {
    return id;
}

int Song::getPlaylistNum() const {
    return playlistNum;
}

Song& Song::operator=(const Song& song) {
    this->plays = song.getPlays();
    this->id = song.getID();
    this->playlistNum = song.getPlaylistNum();
    return *this;
}

bool Song::operator==(const Song &song) const{
    if(this->id == song.getID() && this->plays == song.getPlays() &&
        this->playlistNum == song.getPlaylistNum()) {
        return true;
    }
    return false;
}

void Song::setPlaylistNum(int playlistNum) {
    this->playlistNum = playlistNum;
}

bool Song::operator!=(const Song &song) const {
    return (!(*this == song));
}

Song::Song(): id(0), plays(0), playlistNum(0){}
