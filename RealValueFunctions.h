#pragma once

#include "node.h"
#include "playlist.h"
#include <memory>

using namespace std;
#ifndef REALVALUEFUNCTIONS_H
#define REALVALUEFUNCTIONS_H

#endif //REALVALUEFUNCTIONS_H

enum struct comp {

    BIGGER = 0,
    SMALLER = 1,
    EQUAL = 2

};

comp songRealValueId(const shared_ptr<Song> &ptr1, const shared_ptr<Song> &ptr2);
comp songRealValuePlays(const shared_ptr<Song> &ptr1, const shared_ptr<Song> &ptr2);
comp songRealValuePlaysPtr(const Node<shared_ptr<Song>> *node, const Node<shared_ptr<Song>> *node2);
comp songRealValueIdPtr(const Node<shared_ptr<Song>> *node, const Node<shared_ptr<Song>> *node2);
comp playlistRealValueId(const Node<Playlist> *node, const Node<Playlist> *node2);