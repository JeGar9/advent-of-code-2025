#include "Day2Solution.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <queue>

using namespace std;

namespace Day2 {

    class TrieNode {
        TrieNode* children[11] = { nullptr };
    public:
        TrieNode() = default;
        ~TrieNode() {
            for (const auto & i : children) {
                delete i;
            }
        }
        void insert(unsigned long word) {
            if (word == 0) {
                children[10] = new TrieNode();
            } else {
                const unsigned int index = word % 10;
                children[index] = new TrieNode();
                children[index]->insert(word/10);
            }
        }
    };

    class Trie {
        TrieNode * root;
    public:
        Trie(): root(nullptr) {}
        ~Trie() {
            delete root;
        }
        void insert(unsigned long word) {
            if (root == nullptr) {
                root = new TrieNode();
            }
            root->insert(word);
        }
    };

    class IdRange {
    public:
        unsigned long start;
        unsigned long end;
    };

    vector<IdRange> splitIdRanges(const string& line) {
        vector<IdRange> idRanges;
        stringstream ss(line);
        vector<string> v;
        string s;
        while (getline(ss, s, ',')) {
            auto pos = s.find('-');
            string s1 = s.substr(0, pos);
            string s2 = s.substr(pos + 1);
            idRanges.push_back(IdRange{stoull(s1), stoull(s2)});
        }
        return idRanges;
    }

    vector<unsigned char> split(unsigned long i) {
        vector<unsigned char> v;
        do {
          v.push_back(i % 10);
        } while (i /= 10);
        std::reverse(v.begin(), v.end());
        return v;
    }

    unsigned long getRepeatedElementsInRange(unsigned long num) {
        string snum = to_string(num);
        size_t len = snum.length();
        if (len % 2 == 0) {
            size_t len2 = len / 2;
            string left = snum.substr(0, len2);
            string right = snum.substr(len2);
            if (left == right) {
                return num;
            }
        }
        return 0;
    }

    string solve1(const vector<string>& input) {
        unsigned long counter = 0;
        for (auto& line: input) {
            vector<IdRange> idRanges = splitIdRanges(line);
            for (IdRange& idRange : idRanges) {
                for (unsigned long i = idRange.start; i <= idRange.end; i++) {
                    counter += getRepeatedElementsInRange(i);
                }
            }
        }
        return to_string(counter);
    }

    string solve2(const vector<string>& input) {
        return "0";
    }
}
