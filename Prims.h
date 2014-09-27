#ifndef PRIMS_H
#define PRIME_H

#include <set>
#include <vector>

class Prims {
    private:
        // Set of indices.
        std::set<int> mst_set;

        // UNdirected graph.
        std::vector <int> graph;
        std::vector <int> mst;
        int minIndexNotInSet(const std::vector<int>);
        int getEdgeBetween(int i, int j);

    public:
        Prims(std::vector <int> g) {
            graph = g;
        }
        void findMst();
        void printMst();
};

#endif
