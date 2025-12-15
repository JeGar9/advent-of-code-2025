//
// Created by Jesu on 13/12/2025.
//

#ifndef ADVENTOFCODE_2025_POINT_H
#define ADVENTOFCODE_2025_POINT_H

#include <functional>

class Pair {
public:
    static constexpr int DEFAULT = -1;
    int first;
    int second;

    Pair() : Pair(DEFAULT, DEFAULT) {}
    Pair(const int first, const int second) : first(first), second(second) {}

    bool operator==(const Pair& other) const {
        return first == other.first && second == other.second;
    }
};


template <>
struct std::hash<Pair> {
    size_t operator()(const Pair& p) const noexcept {
        return hash<int>{}(p.first) ^ (hash<int>()(p.second) << 1);
    }
};

#endif //ADVENTOFCODE_2025_POINT_H