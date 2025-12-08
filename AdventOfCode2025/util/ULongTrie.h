//
// Created by Jesu on 08/12/2025.
//

#ifndef ADVENTOFCODE_2025_TRIE_H
#define ADVENTOFCODE_2025_TRIE_H

class ULongTrieNode;

class ULongTrie {
    ULongTrieNode * root;
public:
    ULongTrie();
    ~ULongTrie();
    void insert(unsigned long word);
};

#endif //ADVENTOFCODE_2025_TRIE_H