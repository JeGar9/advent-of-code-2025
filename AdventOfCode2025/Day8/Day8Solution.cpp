#include "Day8Solution.h"

#include <iostream>
#include <ostream>
#include <cmath>
#include <deque>
#include <queue>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <utility>

#include "Pair.h"

using namespace std;

namespace Day8 {
    class Box {
    public:
        int x;
        int y;
        int z;

        Box() : Box(0, 0, 0) {}
        Box(const Box& box) = default;
        Box(Box&& box) = default;
        Box(int x, int y, int z) : x(x), y(y), z(z) {}
        Box& operator=(const Box&) = default;  // copy assignment
        Box& operator=(Box&&) noexcept = default; // move assignment

        bool operator==(const Box& b) const {
            return x == b.x && y == b.y && z == b.z;
        }

        bool operator!=(const Box& b) const {
            return x != b.x || y != b.y || z != b.z;
        }

        int& operator[](int axis) {
            switch (axis) {
                case 0: return x;
                case 1: return y;
                case 2: return z;
                default: throw out_of_range("Invalid Axis");
            }
        }

        const int& operator[](int axis) const {
            switch (axis) {
                case 0: return x;
                case 1: return y;
                case 2: return z;
                default: throw out_of_range("Invalid Axis");
            }
        }

    };

    std::ostream& operator<<(std::ostream& os, const Box& b) {
        return os << "(" << b.x << "," << b.y << "," << b.z << ")";
    }

    double distanceSquared(const Box& a, const Box& b) {
        return pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2);
    }

    double distance(const Box& a, const Box& b) {
        return sqrt(distanceSquared(a, b));
    }
}

template <>
struct std::hash<Day8::Box> {
    size_t operator()(const Day8::Box& b) const noexcept {
        const size_t h1 = std::hash<int>{}(b.x);
        const size_t h2 = std::hash<int>{}(b.y);
        const size_t h3 = std::hash<int>{}(b.z);
        return h1 ^ (h2 << 1) ^ (h3 << 2) ;
    }
};

namespace Day8 {

    class KNode;

    struct Candidate {
        const Box& point;
        double dist;

        Candidate(const Box& point, double dist) : point(point), dist(dist) {
        }

        bool operator<(const Candidate& other) const {
            return dist > other.dist;
        }
    };

    struct NearestNode {
        const KNode* node = nullptr;
        double dist = numeric_limits<double>::infinity();

        bool operator<(const Candidate& other) const {
            return dist < other.dist;
        }
    };

    struct ByDistance {
        bool operator()(const NearestNode& a, const NearestNode& b) const {
            return a.dist < b.dist;
        }
    };

    using MaxHeap = priority_queue<NearestNode, vector<NearestNode>, ByDistance>;

    class KNode {
    public:
        Box data;
        int axis;
        KNode* left;
        KNode* right;

        KNode(const Box & data, int axis) : data(data), axis(axis), left(nullptr), right(nullptr) {}
        ~KNode() {
            delete left;
            delete right;
        }

        [[nodiscard]] int coord() const {
            return coord(data);
        }

        [[nodiscard]] int coord(const Box& box) const {
            return box[axis];
        }

        void kNearest(const Box& query, size_t k, MaxHeap& best) const {

            if (this->data != query) {
                double dist = distanceSquared(this->data, query);
                if (best.size() >= k && dist < best.top().dist) {
                    best.pop();
                }
                best.push(NearestNode{this, dist});
            }
            double diff = this->coord(query) - this->coord();
            const KNode* near = diff < 0? left : right;
            const KNode* far = diff < 0? right: left;

            if (near) {
                near->kNearest(query, k, best);
            }
            if (far && (best.size() < k || diff * diff < best.top().dist)) {
                far->kNearest(query, k, best);
            }
        }
    };

    class KTree {
    public:
        KNode* root;
        KTree(std::vector<Box>& boxes) {
            root = buildTree(boxes.begin(), boxes.end(), 0);
        }
        ~KTree() {
            delete root;
        }

        vector<Candidate> kNearest(const Box& box, size_t k) const {

            MaxHeap nearestNodes;
            if (root != nullptr) {
                root->kNearest(box, k, nearestNodes);
            }
            vector<Candidate> ret;
            for (int i = 0; i < k && !nearestNodes.empty(); ++i) {
                auto node = nearestNodes.top();
                ret.emplace_back(node.node->data, node.dist);
                nearestNodes.pop();
            }
            return ret;
        }

    private:
        static KNode* buildTree(std::vector<Box>::iterator begin, std::vector<Box>::iterator end, int axis) {
            if (begin == end) {
                return nullptr;
            }
            auto mid = (end - begin) / 2;
            auto midITer = begin + mid;
            nth_element(begin, midITer, end, [axis](const Box& a, const Box& b) {
                        return a[axis] < b[axis];
                });
            auto* node = new KNode(*midITer, axis);
            node->left = buildTree(begin, midITer, (axis + 1) % 3);
            node->right = buildTree(midITer + 1, end, (axis + 1) % 3);
            return node;
        }
    };

    vector<Box> linesToBoxes(const vector<string>& input, int& numElements) {
        vector<Box> boxes;
        int a, b, c;
        bool isFirst = true;
        for (const auto& line : input) {
            stringstream iss(line);
            if (isFirst) {
                iss >> numElements;
                isFirst = false;
            } else{
                char comma;
                iss >> a >> comma >> b >> comma >> c;
                boxes.push_back({a, b, c});
            }
        }
        return boxes;
    }

    class Graph {
        unordered_map<Box, unordered_set<Box>> data;
        unordered_map<Box,Box> parent;
        unordered_map<Box, int> rank;
        int counter = 1;
    public:
        Graph() = default;
        Graph(Graph & other) noexcept = default;
        Graph(const Graph & other) noexcept = default;
        Graph(Graph && other) noexcept : data(std::move(other.data)){}

        Graph& operator=(const Graph& other) noexcept = default;

        class iterator {
            using MapIt = unordered_map<Box, unordered_set<Box>>::iterator;
            MapIt _it;
        public:
            using iterator_category = forward_iterator_tag;
            using value_type = Box;
            using reference = const Box&;
            using pointer = const Box*;

            iterator() = default;
            iterator(const MapIt it) : _it(it) {}
            iterator& operator++() { ++_it; return *this;}
            iterator operator++(int) { iterator tmp = *this; ++_it; return tmp;}
            value_type operator*() const { return _it->first;}
            value_type operator->() const { return _it->first;}
            bool operator==(const iterator& other) const { return _it == other._it; }
            bool operator!=(const iterator& other) const { return _it != other._it; }
        };

        void insert(const Box& node) {
            auto _ = data[node];
            parent.emplace(node, node);
            rank.emplace(node, 0);
        }

        bool insert(const Box& from, const Box& to) {
            insert(from);
            insert(to);
            data[from].insert(to);
            data[to].insert(from);
            return join(from, to);
        }

        bool join(const Box& a, const Box& b) {
            Box ra = find(a);
            Box rb = find(b);

            if (ra == rb)
                return false;

            if (rank[ra] < rank[rb]) {
                parent[ra] = rb;
            } else if (rank[ra] > rank[rb]) {
                parent[rb] = ra;
            } else {
                parent[rb] = ra;
                rank[ra]++;
            }
            return true;
        }

        Box find(const Box& x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }

        void removeNodes(iterator it, iterator end) {
            while (it != end) {
                removeNode(*it);
                ++it;
            }
        }
        void removeNode(const Box& from) {
            if (const auto it = data.find(from); it != data.end()) {
                const auto set = it->second;
                for (auto& other: set) {
                    auto auxSet = data[other];
                    auxSet.erase(from);
                }
                data.erase(from);
            }
        }

        iterator beginNode() {
            return iterator{ data.begin() };
        }
        iterator endNode() {
            return { data.end() };
        }
        size_t countNodes() const {
            return data.size();
        }
        bool nodeInGraph(const Box& node) const {
            return data.find(node) != data.end();
        }

        vector<Graph> getConnectedComponents() {
            unordered_map<Box, Graph> groupings;
            for (auto& entry : data) {
                Box root = find(entry.first);
                unordered_set<Box>& values = entry.second;
                Graph& gr = groupings[root];
                for (const Box& elem : values) {
                    gr.insert(entry.first, elem);
                }
            }
            vector<Graph> graphs;
            for (auto& entry : groupings) {
                graphs.push_back(entry.second);
            }
            return graphs;
        }
    };


    Graph toGraph(const vector<tuple<Box, Box, double>> &results, int n) {
        Graph values;
        for (int i = 0; i < n;) {
            auto& tmp = results[i];
            const Box& from = get<0>(tmp);
            const Box& to = get<1>(tmp);
            if (values.insert(from, to)) {
                ++i;
            }
        }
        return values;
    }

    std::string solve1(const std::vector<std::string>& input) {
        int nConnections;
        vector<Box> boxes = linesToBoxes(input, nConnections);
        KTree tree(boxes);
        vector<tuple<Box, Box, double>> results;

        for (const Box& box : boxes) {
            vector<Candidate> closest = tree.kNearest(box, 16);
            for (Candidate& candidate : closest) {
                results.emplace_back(box, candidate.point, candidate.dist);
            }
        }

        {
            sort(results.begin(), results.end(), [](auto& p1, auto& p2) {return get<2>(p1) < get<2>(p2);});
            auto it = unique(results.begin(), results.end(),
                [](auto& p1, auto& p2) {
                    return (get<0>(p1) == get<0>(p2) && get<1>(p1) == get<1>(p2) && get<2>(p1) == get<2>(p2))
                        || (get<1>(p1) == get<0>(p2) && get<0>(p1) == get<1>(p2) && get<2>(p1) == get<2>(p2)) ;
                });
            results.erase(it, results.end());
        }

        auto graph = toGraph(results, nConnections);

        auto connectedComponents = graph.getConnectedComponents();
        sort(connectedComponents.begin(), connectedComponents.end(), [](auto& p1, auto& p2) { return p1.countNodes() > p2.countNodes(); });
        connectedComponents.resize(3);
        return to_string(connectedComponents[0].countNodes() * connectedComponents[1].countNodes() * connectedComponents[2].countNodes());
    }

    std::string solve2(const vector<string>& input) {
        return "";
    }
}


