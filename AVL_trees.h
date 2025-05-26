#pragma once

#include "node.h"
#include <iostream>
#include "RealValueFunctions.h"
#include <memory>

using namespace std;

template <typename T>
void LL(Node<T>*& d) {

    if (d == nullptr || d->left == nullptr) {
        return;
    }

    Node<T>* b = d->left;
    Node <T>* c = b->right;
    b->right = d;
    d->left = c;
    d->updateHeight();
    b->updateHeight();
    d = b;
}

template <typename T>
void RR(Node<T>*& b) {
    if (b == nullptr || b->right == nullptr) {
        return;
    }

    Node<T>* d = b->right;
    Node<T>* c = d->left;

    d->left = b;
    b->right = c;

    b->updateHeight();
    d->updateHeight();

    b = d;
}

template <typename T>
void LRRotate(Node<T>* &f) {
    RR(f->left);
    LL(f);
}
template <typename T>
void RLRotate(Node<T>* &f) {
    LL(f->right);
    RR(f);
}

template <typename T>
void balanceAVL(Node<T>*& root) {
    if(root == nullptr) {
        return;
    }

    if (root->getBalanceFactor() > 1) {
        if (root->left->getBalanceFactor() < 0) {
            LRRotate(root);
        }
        else {
            LL(root);
        }
    }
    else if (root->getBalanceFactor() < -1) {
        if (root->right->getBalanceFactor() > 0) {
            RLRotate(root);
        }
        else {
            RR(root);
        }
    }
    root->updateHeight();
}

template <typename T, typename Func>
bool insertNodeIntoAVL(Node<T>*& root, Node<T>* &value_to_insert, Func RealValue) {
    if (root==nullptr) {
        root = value_to_insert;
        return true;
    }
    bool returnValue;
    comp status = RealValue(value_to_insert, root);
    if (status == comp::BIGGER) {
        returnValue = insertNodeIntoAVL(root->right, value_to_insert, RealValue);
    }
    else {
        returnValue = insertNodeIntoAVL(root->left, value_to_insert, RealValue);
    }
    if(root->getBalanceFactor() >= 2 || root->getBalanceFactor() <= -2) {
        balanceAVL(root);
    }
    return returnValue;
}

template <typename T, typename Func>
Node <T>* findNodeAVL(Node<T>*& root, T &value_to_find, Func RealValue) {
    if (root==nullptr) {
         throw std::runtime_error("No Such Node");
    }
    Node<T> node = Node<T>(value_to_find);
    const comp status = RealValue(&node, root);
    if (status == comp::EQUAL) {
        return root;
    }
    if (status == comp::BIGGER) {
        return findNodeAVL(root->right, value_to_find, RealValue);
    }

    return findNodeAVL(root->left, value_to_find, RealValue);
}

template <typename T, typename Func>
bool deleteRootAVL(Node<T>*& root, Func RealValue) {
    if (root==nullptr) {
        throw std::runtime_error("No Such Node");
    }
    if (root->left==nullptr && root->right==nullptr) {
        delete root;
        root = nullptr;

    }
    else if (root->right==nullptr) {
        Node<T>* temp = root->left;
        root->left = nullptr;
        delete root;
        root = temp;
    }
    else if (root->left==nullptr) {
        Node<T>* temp = root->right;
        root->right = nullptr;
        delete root;
        root = temp;
    }
    else {
        Node<T>* maxNode = findMax(root->left);
        root->val = maxNode->val;
        deleteNodeAVL(root->left, maxNode, RealValue);
    }
    return true;
}

template <typename T, typename Func>
bool deleteNodeAVL(Node<T>*& root, Node<T>*& value_to_delete, Func RealValue) {
    bool returnValue;
    if (root==nullptr) {
        throw std::runtime_error("No Such Node");
    }
    comp status = RealValue(value_to_delete, root);
    if (status == comp::EQUAL) {
        return deleteRootAVL(root, RealValue);
    }
    if (status == comp::BIGGER) {
        returnValue = deleteNodeAVL(root->right, value_to_delete, RealValue);
    }
    else {
        returnValue = deleteNodeAVL(root->left, value_to_delete, RealValue);
    }
    root->updateHeight();
    if(root != nullptr) {
        if(root->getBalanceFactor() >= 2 || root->getBalanceFactor() <= -2) {
            balanceAVL(root);
        }
    }
    return returnValue;
}

template <typename T>
Node <T>* findMax(Node<T>* root) {
    if (root->right==nullptr) {
        return root;
    }
    return findMax(root->right);
}


Node<shared_ptr<Song>>* findClosestBiggerSong(Node<shared_ptr<Song>>* root, int value_to_find_bigger_of, Node<shared_ptr<Song>>* curr_best_approx) {
    if(curr_best_approx == nullptr) {
        return nullptr;
    }
    if(root == nullptr) {
        return curr_best_approx;
    }
    if(root->val->getPlays() >= value_to_find_bigger_of) {
        return findClosestBiggerSong(root->left, value_to_find_bigger_of, root);
    }
    if(curr_best_approx->val->getPlays() >= value_to_find_bigger_of) {
        return findClosestBiggerSong(root->right, value_to_find_bigger_of, curr_best_approx);
    }
    return findClosestBiggerSong(root->right, value_to_find_bigger_of, root);
}

template <typename T>
int lengthAVL(Node<T>* root) {
    if (root==nullptr) {
        return 0;
    }
    return 1 + lengthAVL(root->right) + lengthAVL(root->left);
}



template <typename T>
struct ListNode {
    shared_ptr<Song> treeNode;
    ListNode* next;

    ListNode(shared_ptr<Song> &n) : treeNode(n), next(nullptr) {}
};

void inorderToList(Node<shared_ptr<Song>>* root, ListNode<shared_ptr<Song>>*& head, ListNode<shared_ptr<Song>>*& tail) {
    if (!root) return;

    if(root->val->getID() == 717117) {
        cout << root->val.use_count() << endl;
    }
    inorderToList(root->left, head, tail);

    ListNode<shared_ptr<Song>>* newNode = new ListNode<shared_ptr<Song>>(root->val);
    if (!head) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }

    inorderToList(root->right, head, tail);
}

template <typename Func>
ListNode<shared_ptr<Song>>* mergeLists(ListNode<shared_ptr<Song>>* l1, ListNode<shared_ptr<Song>>* l2, Func func) {
    shared_ptr<Song> dummy_shared = nullptr;
    ListNode<shared_ptr<Song>> dummy(dummy_shared);
    ListNode<shared_ptr<Song>>* tail = &dummy;
    comp compare;

    while (l1 && l2) {
        compare = func(l1->treeNode, l2->treeNode);

        if(l1->treeNode->getID() == 717117) {
            cout << l1->treeNode.use_count() << endl;
        }

        if (compare == comp::SMALLER ) {
            tail->next = new ListNode<shared_ptr<Song>>(l1->treeNode);
            l1 = l1->next;
        } else if(compare == comp::BIGGER) {
            tail->next = new ListNode<shared_ptr<Song>>(l2->treeNode);
            l2 = l2->next;
        } else {
            tail->next = new ListNode<shared_ptr<Song>>(l2->treeNode);
            l1->treeNode->setPlaylistNum(l1->treeNode->getPlaylistNum() - 1);
            l2 = l2->next;
            l1 = l1->next;

        }
        tail = tail->next;
    }

    while (l1) {
        if(l1->treeNode->getID() == 717117) {
            cout << l1->treeNode.use_count() << endl;
        }
        tail->next = new ListNode<shared_ptr<Song>>(l1->treeNode);
        l1 = l1->next;
        tail = tail->next;
    }
    while (l2) {
        tail->next = new ListNode<shared_ptr<Song>>(l2->treeNode);
        l2 = l2->next;
        tail = tail->next;
    }

    return dummy.next;
}

template <typename T>
int countListLength(ListNode<T>* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}


Node<shared_ptr<Song>>* buildAVLFromList(ListNode<shared_ptr<Song>>*& listHead, int n) {
    if (n <= 0 || !listHead) return nullptr;

    if(listHead->treeNode->getID() == 717117) {
        cout << listHead->treeNode.use_count() << endl;
    }
    Node<shared_ptr<Song>>* left = buildAVLFromList(listHead, n / 2);

    Node<shared_ptr<Song>>* root = new Node<shared_ptr<Song>>(listHead->treeNode);  // copy the shared_ptr
    root->left = left;

    listHead = listHead->next;

    root->right = buildAVLFromList(listHead, n - n / 2 - 1);
    root->updateHeight();

    return root;
}

void deleteLinked(ListNode<shared_ptr<Song>> *head) {
    if(head == nullptr) return;
    if(head->treeNode->getID() == 717117) {
        cout << head->treeNode.use_count() << endl;
    }
    deleteLinked(head->next);
    delete head;
}

template<typename Func>
Node<std::shared_ptr<Song>>* mergeAVL(
    Node<std::shared_ptr<Song>>* root1,
    Node<std::shared_ptr<Song>>* root2,
    Func func
) {
    ListNode<std::shared_ptr<Song>> *head1 = nullptr, *tail1 = nullptr;
    ListNode<std::shared_ptr<Song>> *head2 = nullptr, *tail2 = nullptr;

    inorderToList(root1, head1, tail1);
    inorderToList(root2, head2, tail2);

    ListNode<std::shared_ptr<Song>>* mergedList = mergeLists(head1, head2, func);

    int len = countListLength(mergedList);

    deleteLinked(head1);
    deleteLinked(head2);

    Node<shared_ptr<Song>> *root = buildAVLFromList(mergedList, len);


    deleteLinked(mergedList);
    return root;
}



/*template <typename T>
void AVLToList(Node<T>* root, Node<T>*& rootUnion, int &counter) {
    if (root == nullptr) {
        return;
    }
    AVLToList(root->left, rootUnion, counter);
    rootUnion[counter] = Node<T>(root->val);
    rootUnion[counter].left = nullptr;
    rootUnion[counter].right = nullptr;
    counter++;
    AVLToList(root->right, rootUnion, counter);
}

template<typename Func>
int mergeAVLsToList(Node<shared_ptr<Song>>* root1, Node<shared_ptr<Song>>* root2, Node<shared_ptr<Song>>*& rootUnion, Func RealValue) {
    if(root1 == nullptr && root2 == nullptr) {
        return 0;
    }
    if(root1 == nullptr) {
        int counter = 0;
        int len = lengthAVL(root2);
        rootUnion = new Node<shared_ptr<Song>>[len];
        AVLToList(root2, rootUnion, counter);
        return len;
    }
    if(root2 == nullptr) {
        int counter = 0;
        int len = lengthAVL(root1);
        rootUnion = new Node<shared_ptr<Song>>[len];
        AVLToList(root1, rootUnion, counter);
        return len;
    }
    int len1 = lengthAVL(root1);
    int len2 = lengthAVL(root2);
    int len = len1 + len2;

    Node<shared_ptr<Song>>* rootUnion1 = new Node<shared_ptr<Song>>[len1];
    Node<shared_ptr<Song>>* rootUnion2 = new Node<shared_ptr<Song>>[len2];
    rootUnion = new Node<shared_ptr<Song>>[len];
    int counter = 0;
    AVLToList(root1, rootUnion1, counter);
    counter = 0;
    AVLToList(root2, rootUnion2, counter);
    int i1 = 0;
    int i2 = 0;
    int i = 0;
    comp status;
    while (i < len) {
        if(i1 == len1) {
            while (i2 < len2) {
                rootUnion[i] = Node<shared_ptr<Song>>(rootUnion2[i2].val);
                i++;
                i2++;
            }

            return i;
        }
        if(i2 == len2) {
            while (i1 < len1) {
                rootUnion[i] = Node<shared_ptr<Song>>(rootUnion1[i1].val);

                i++;
                i1++;
            }

            return i;
        }
        status = RealValue(&(rootUnion1[i1]), &(rootUnion2[i2]));
        if(status == comp::EQUAL) {
            rootUnion[i] = Node<shared_ptr<Song>>(rootUnion1[i1].val);
            rootUnion[i].val->setPlaylistNum(rootUnion[i].val->getPlaylistNum() - 1);
            i++;
            i1++;
            i2++;
            continue;
        }
        if(status == comp::BIGGER) {
            rootUnion[i] = Node<shared_ptr<Song>>(rootUnion2[i2].val);
            i++;
            i2++;
            continue;
        }
        else {
            rootUnion[i] = Node<shared_ptr<Song>>(rootUnion1[i1].val);

            i++;
            i1++;
        }
    }

    return len;
}

template <typename T>
Node<T>* buildAVLFromList(Node<T>* nodes, int start, int end) {
    if (start>end) {
        return nullptr;
    }
    int mid = (start+end)/2;
    Node<T>* node = new Node<T>(nodes[mid].val);
    node->left = buildAVLFromList(nodes, start, mid-1);
    node->right = buildAVLFromList(nodes, mid+1, end);
    node->updateHeight();
    return node;
}

template<typename Func>
Node<shared_ptr<Song>> *mergeTrees(Node<shared_ptr<Song>> *root1, Node<shared_ptr<Song>> *root2, Func RealValue) {

    Node<shared_ptr<Song>> *Union = nullptr;
    int len = mergeAVLsToList(root1, root2, Union, RealValue);
    Node<shared_ptr<Song>>* newRoot = buildAVLFromList(Union, 0, len - 1);
    delete[] Union;
    return newRoot;
}*/