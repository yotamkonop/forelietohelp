//
// Created by Yotam Konopnicki on 14/05/2025.
//
#pragma once
class Song{

    int id;
    int plays;
    int playlistNum;
public:
    Song(int id, int plays);

    Song();

    Song(const Song& song);

    int getPlays() const;

    int getID() const;

    int getPlaylistNum() const;

    Song& operator=(const Song& song);

    bool operator==(const Song& song) const;

    bool operator!=(const Song& song) const;

    void setPlaylistNum(int playlistNum);


};


