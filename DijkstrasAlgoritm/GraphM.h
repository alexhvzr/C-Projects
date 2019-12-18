//
// Created by Alex Hayden van Zuiden-Rylander on 2019-05-10.
//

#ifndef DIJKSTRASALGORITM_GRAPHM_H
#define DIJKSTRASALGORITM_GRAPHM_H

#include "nodedata.h"



struct TableType {
    bool visited;          // Whether node has been visited.
    int dist;              // Shortest distance from source known so far.
    int path;              // Previous node in path of min dist.
};



class GraphM {
    NodeData data[MAXNODES];              // Data array of for the nodes.
    int C[MAXNODES][MAXNODES];            // Cost values, the adjacency matrix.
    int size;                             // Number of nodes in the graph.
    TableType T[MAXNODES][MAXNODES];      // Table that stores visited, distance, path for each node.

    // Helper functions.
    void printData(int, int);
    void printPath(int, int);

public:
    // Constructor
    GraphM();

    // Functions
    void buildGraph(ifstream &inFile);
    void findShortestPath();
    bool insertEdge(int, int, int);
    bool removeEdge(int, int);
    void display(int, int);
    void displayAll();
};


#endif //DIJKSTRASALGORITM_GRAPHM_H
