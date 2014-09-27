#include <iostream>
#include <cstdlib>
#include <limits.h>

#include "Prims.h"

using namespace std;

extern int number_of_nodes;

int Prims::getEdgeBetween(int i, int j) {
    return graph[i*number_of_nodes + j];
}

int Prims::minIndexNotInSet(const vector <int> key) {
    int min = INT_MAX, min_index;
    for (int i = 0; i < number_of_nodes; i++) {
        if (mst_set.find(i) == mst_set.end() && key[i] < min) {
            min = key[i];
            min_index = i;
        }

    }
    return min_index;
}

void Prims::printMst() { 
    for (int i = 0; i < number_of_nodes; i++) {
        if (mst[i] != -1) 
            cout << i<< " --- " << mst[i] << " " << getEdgeBetween(mst[i], i)<< endl; 
    }

}

void Prims::findMst() {
    // Key vector to manage the validity of various vertices.
    vector <int> key(number_of_nodes);
    mst.resize(number_of_nodes);

    for (int i = 0; i < number_of_nodes; i++) { 
        key[i] = INT_MAX;
        mst[i] = -1;
    }

    // Include 1st node;
    key[0] = 0;
    
    // Include one vertex in every iteration.
    for (int i = 0; i < number_of_nodes; i++) {
        int min_index = minIndexNotInSet(key);

        mst_set.insert(min_index);
        for (int i = 0; i < number_of_nodes; i++) {
            if (getEdgeBetween(min_index, i) && mst_set.find(i) == mst_set.end() 
                    && getEdgeBetween(min_index, i) <= key[i]) {
                mst[i] = min_index; 
                key[i] = getEdgeBetween(min_index, i);
            }
        }
    }
}
