//This file is made for RealValue function used in AVL_trees

#include "RealValueFunctions.h"
#include <memory>

using namespace std;

comp songRealValueId(const shared_ptr<Song> &ptr1, const shared_ptr<Song> &ptr2) {
    assert(ptr1 != nullptr && ptr2 != nullptr);
    if(ptr1->getID() == ptr2->getID()) return comp::EQUAL;
    if(ptr1->getID() > ptr2->getID()) return comp::BIGGER;
    return comp::SMALLER;
}

comp songRealValuePlays(const shared_ptr<Song> &ptr1, const shared_ptr<Song> &ptr2) {
    assert(ptr1 != nullptr && ptr2 != nullptr);
    if(ptr1->getPlays() == ptr2->getPlays()) {
        if(ptr1->getID() == ptr2->getID()) return comp::EQUAL;
        if(ptr1->getID() > ptr2->getID()) return comp::BIGGER;
        return comp::SMALLER;
    }
    if(ptr1->getPlays() > ptr2->getPlays()) return comp::BIGGER;
    return comp::SMALLER;
}

comp songRealValuePlaysPtr(const Node<shared_ptr<Song>> *node, const Node<shared_ptr<Song>> *node2) {
    assert(node->val != nullptr && node2->val != nullptr);
    if(node->val->getPlays() == node2->val->getPlays()) {
        if(node->val->getID() == node2->val->getID()) return comp::EQUAL;
        if(node->val->getID() > node2->val->getID()) return comp::BIGGER;
        return comp::SMALLER;
    }
    if(node->val->getPlays() > node2->val->getPlays()) return comp::BIGGER;
    return comp::SMALLER;
}

comp songRealValueIdPtr(const Node<shared_ptr<Song>> *node, const Node<shared_ptr<Song>> *node2) {
    assert(node->val != nullptr && node2->val != nullptr);
    if(node->val->getID() == node2->val->getID()) return comp::EQUAL;
    if(node->val->getID() > node2->val->getID()) return comp::BIGGER;
    return comp::SMALLER;
}

comp playlistRealValueId(const Node<Playlist> *node, const Node<Playlist> *node2) {
    if(node->val.getID() == node2->val.getID()) return comp::EQUAL;
    if(node->val.getID() > node2->val.getID()) return comp::BIGGER;
    return comp::SMALLER;
}