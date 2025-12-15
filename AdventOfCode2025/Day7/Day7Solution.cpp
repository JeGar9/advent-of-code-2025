#include "Day7Solution.h"

#include <algorithm>
#include <unordered_set>
#include <iostream>
#include <ostream>
#include <unordered_map>
#include <utility>

#include "Pair.h"
#include <iostream>

using namespace std;

namespace Day7 {

    std::string solve1(const std::vector<std::string>& input) {
        unordered_set<int> set1;
        unordered_set<int> set2;
        unordered_set<int>* previousSet = &set1;
        unordered_set<int>* currentSet = &set2;
        int splitCount = 0;
        for (int i = 0; i < input.size(); i++) {
            previousSet->clear();
            swap(currentSet, previousSet);
            const string & line = input[i];
            for (int j = 0; j < input.size(); j++) {
                char c = line[j];
                switch (c) {
                    case 'S':
                        currentSet->emplace(j);
                        break;
                    case '^': {
                        auto it = previousSet->find(j);
                        if (it != previousSet->end()) {
                            currentSet->emplace(j - 1);
                            currentSet->emplace(j + 1);
                            splitCount++;
                        }
                    }
                        break;
                    default: {
                        auto it = previousSet->find(j);
                        if (it != previousSet->end()) {
                            currentSet->emplace(j);
                        }
                    }
                        break;
                }
            }
        }
        return to_string(splitCount);
    }

    class Graph {
    public:
        unordered_multimap<Pair, Pair> nodes;
        Pair root;
        size_t depth;

        Graph() : depth(0) {}
        unordered_multimap<Pair, Pair>::iterator emplace(int ki, int kj, int vi, int vj) {
            return nodes.emplace(Pair(ki, kj), Pair(vi, vj));
        }

    };

    Graph calculateGraph(const vector<string>& input) {
        unordered_set<int> set1;
        unordered_set<int> set2;
        unordered_set<int>* previousSet = &set1;
        unordered_set<int>* currentSet = &set2;
        Graph graph;
        graph.depth = input.size();
        for (int i = 0; i < input.size(); i++) {
            const string & line = input[i];
            previousSet->clear();
            swap(currentSet, previousSet);
            for (int j = 0; j < line.size(); j++) {
                char c = line[j];
                switch (c) {
                    case 'S':
                        currentSet->emplace(j);
                        graph.root = Pair(i, j);
                        break;
                    case '^': {
                        if (auto it = previousSet->find(j); it != previousSet->end()) {
                            currentSet->emplace(j - 1);
                            currentSet->emplace(j + 1);
                            graph.emplace(i - 1, j, i, j - 1);
                            graph.emplace(i - 1, j, i, j + 1);
                        }
                    }
                        break;
                    default: {
                        if (auto it = previousSet->find(j); it != previousSet->end()) {
                            currentSet->emplace(j);
                            graph.emplace(i - 1, j, i, j);
                        }
                    }
                        break;
                }
            }
        }
        return graph;
    }

    void calculatePathsForDepth(const Graph & graph, unordered_map<Pair, long long> & numPathsToElement) {
        unordered_map<Pair, long long> newPathsToElement;
        for (const auto & root : numPathsToElement) {
            for (auto [it, end] = graph.nodes.equal_range(root.first); it != end; ++it) {
                const Pair & nextRoot = it->second;
                newPathsToElement[nextRoot] += root.second;
            }
        }
        numPathsToElement = newPathsToElement;
    }

    void printGraph(const Graph & graph, size_t maxRows, size_t maxCols) {
        unordered_set<Pair> elements;
        for (const auto & pair : graph.nodes) {
            unordered_multimap<Pair, Pair>::size_type num = graph.nodes.count(pair.first);
            if (num > 1) {
                elements.emplace(pair.first.first + 1, pair.first.second);
            }
        }
        for (int i = 0; i < maxRows; i++) {
            for (int j = 0; j < maxCols; j++) {
                if (graph.root == Pair(i, j)) {
                    cout << "S";
                } else if (elements.find(Pair(i, j)) != elements.end()) {
                    cout << "^";
                } else {
                    cout << ".";
                }
            }
            cout << endl;
        }
    }

    std::string solve2(const vector<string>& input) {
        Graph graph = calculateGraph(input);
        //printGraph(graph, input.size(), input[0].size());
        unordered_map<Pair, long long> numPathsToElement = { {graph.root, 1LL} };
        for (int i = 1; i < graph.depth; i++) {
            calculatePathsForDepth(graph, numPathsToElement);
        }
        long long numPaths = 0;
        for (const auto & rootPair : numPathsToElement) {
            numPaths += rootPair.second;
        }
        return to_string(numPaths);
    }
}