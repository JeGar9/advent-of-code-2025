//
// Created by Jesu on 08/12/2025.
//

#include "ULongTrie.h"

class ULongTrieNode {
    ULongTrieNode* children[11] = { nullptr };
public:
    ULongTrieNode() = default;
    ~ULongTrieNode();
    void insert(unsigned long word);
};


ULongTrieNode::~ULongTrieNode() {
    for (const auto & i : children) {
        delete i;
    }
}

void ULongTrieNode::insert(unsigned long word) {
    if (word == 0) {
        children[10] = new ULongTrieNode();
    } else {
        const unsigned int index = word % 10;
        children[index] = new ULongTrieNode();
        children[index]->insert(word/10);
    }
}

ULongTrie::ULongTrie(): root(nullptr) {}

ULongTrie::~ULongTrie() {
    delete root;
}

void ULongTrie::insert(unsigned long word) {
    if (root == nullptr) {
        root = new ULongTrieNode();
    }
    root->insert(word);
}
