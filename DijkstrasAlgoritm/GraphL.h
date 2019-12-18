//
// Created by Alex Hayden van Zuiden-Rylander on 2019-05-10.
//

#ifndef DIJKSTRASALGORITM_GRAPHL_H
#define DIJKSTRASALGORITM_GRAPHL_H

#include <iostream>
#include <fstream>
#include "nodedata.h"


class GraphL {
    // Whats declared in a class is inherently private unless stated public.

    // Structs.
    struct EdgeNode{
        int adjGraphNode;           // Subscript of the adjacent graph node.
        EdgeNode* nextEdge;         // Next node.
    };
    struct GraphNode{
        EdgeNode* edgeHead;        // Head of the list of edges.
        NodeData* data;            // Information about each node.
        bool visited;
    };

    int size;


    GraphNode graphNodeArray[MAXNODES];

    // Delete object.
    void emptyGraph();
    // Helper function.
    void depthFirstSearchHelper(int);
public:
    // Constructor and Destructor.
    GraphL();
    ~GraphL();
    // Public functions.
    void buildGraph(ifstream &inFile);
    void depthFirstSearch();
    void displayGraph();
};


#endif //DIJKSTRASALGORITM_GRAPHL_H
