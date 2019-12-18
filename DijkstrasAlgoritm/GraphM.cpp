/*------------------------------- GraphM.cpp -------------------------------------------------------/
 * Author   : Alex van Zuiden-Rylander                                                              /
 * Class    : CSS 343 B Spring 2019 | Data Structures, Algorithms, Discrete Mathematics 2           /
 * Started  : May 7th, 2019                                                                         /
 * Modified : May 13th, 2019                                                                        /
 * -------------------------------------------------------------------------------------------------/
 * Purpose  : This class was written in to allow the user to create a graph and perform a depth     /
 *            first search through it.                                                              /
 * -------------------------------------------------------------------------------------------------/
 * Notes    : One can make a graph through an input file, the first number given is the number of   /
 *            nodes that are within the file and then the next X names are the names of the nodes.  /
 *            That is followed by the node value and which nodes it's pointing at in the graph.     /
 --------------------------------------------------------------------------------------------------*/

#include "GraphM.h"
#include <iomanip>
#include <climits>

/*---------------------------------- printData -----------------------------------------------------/
 *  Function to go through and recursively print the data from one node to the next.                /
 --------------------------------------------------------------------------------------------------*/
void GraphM::printData(int fromNode, int toNode) {
    if (T[fromNode][toNode].dist == INT_MAX)        // Check to see if there is no data in the node, default case.
        return;


    if (fromNode == toNode){                        // Checks if the node is pointing at itself.
        cout << data[toNode] << endl;
        return;
    }

    int nodeData = toNode;
    printData(fromNode, toNode = T[fromNode][toNode].path);
    cout << data[nodeData] << endl << endl;         // Actually print the data.
}   // End of printData

/*---------------------------------- printPath -----------------------------------------------------/
 *  Function that goes through and recursively prints the node that the fromNode is pointing to.    /
 --------------------------------------------------------------------------------------------------*/
void GraphM::printPath(int fromNode, int toNode) {
    if (T[fromNode][toNode].dist == INT_MAX) // Checks if there is a path.
        return;


    if (fromNode == toNode){
        cout << toNode << " ";
        return;
    }

    int pathData = toNode;
    printPath(fromNode, toNode = T[fromNode][toNode].path);

    cout << pathData << " ";
}   // End of printPath

/*---------------------------------- Default Constructor -------------------------------------------/
 *  Builds all the values in the matrix to have a distance of infinity, visited to false, and no    /
 *  path.                                                                                           /
 --------------------------------------------------------------------------------------------------*/
GraphM::GraphM() {
    size = 0;
    for (int col = 1; col < MAXNODES; col++){
        for (int row = 1; row < MAXNODES; row++){
            T[col][row].dist = C[col][row] = INT_MAX;
            T[col][row].visited = false;
            T[col][row].path = 0;
        }
    }
}   // End of default constructor.

/*---------------------------------- buildGraph ----------------------------------------------------/
 *  Function to build a graph based off the input file passed.                                      /
 *  Assumption: That the input is structured correctly and to end the graph there is an input of    /
 *  "0 0 0".                                                                                        /
 --------------------------------------------------------------------------------------------------*/
void GraphM::buildGraph(ifstream &inFile) {

    inFile >> size;                 // Sets the size of the graph that's going to be made.
    string nodeName = "";           // Name of each node.
    getline(inFile, nodeName);      // Read line

    for (int i = 1; i <= size; i++)
        data[i].setData(inFile);   // Sets node names


    int fromNode, toNode, dist;

    while (inFile >> fromNode >> toNode >> dist){
        if (fromNode == 0)
            break;  // Reads file till fromNode node is 0

        C[fromNode][toNode] = dist; // Set the cost values in the cost matrix. 
    }
}   // End of buildGraph

/*---------------------------------- findShortestPath ----------------------------------------------/
 *  Function that finds the shortest path to each node in the adjacency matrix.                     /
 --------------------------------------------------------------------------------------------------*/
void GraphM::findShortestPath() {
    for (int srcNode = 1; srcNode <= size; srcNode++){
        T[srcNode][srcNode].dist = 0;         // Set the source node distance to zero. 
        T[srcNode][srcNode].visited = true;   // Set the bool visited to true so that you don't go back to the node. 

        // For loop to find all the neighbor nodes of the current node.  
        for (int nhbrNode = 1; nhbrNode <= size; nhbrNode++){
            if (C[srcNode][nhbrNode] != INT_MAX){                   // Check the cost matrix and if the value isn't infinity, set the distance and path from the source to the neighbor. 
                T[srcNode][nhbrNode].dist = C[srcNode][nhbrNode];   // The distance is the value in the cost node matrix. 
                T[srcNode][nhbrNode].path = srcNode;                // The path is from the node that is passed in the first place.
            }
        }

        int pivotIndex = 0;
        do{
            int smallestNode = INT_MAX;
            pivotIndex = 0;

            // For loop to find the smallest node next to the source node that is passed. 
            for (int nhbrNode = 1; nhbrNode <= size; nhbrNode++){
                if (!T[srcNode][nhbrNode].visited && (C[srcNode][nhbrNode] < smallestNode)){
                    smallestNode = C[srcNode][nhbrNode];
                    pivotIndex = nhbrNode;
                }
            }

            if (pivotIndex == 0)                      // Base case.
                break; 

            T[srcNode][pivotIndex].visited = true;     // You are now moving to the node that is the smallest distance from the source. It is now visited.

            for (int index = 1; index <= size; index++){
                // Check if you are on the same node, if there's no value, or if the node has already been visited.
                if ((pivotIndex == index) || (C[pivotIndex][index] == INT_MAX) || T[srcNode][index].visited)
                    continue;

                if (T[srcNode][index].dist > (T[srcNode][pivotIndex].dist + C[pivotIndex][index])){
                    T[srcNode][index].dist =(T[srcNode][pivotIndex].dist + C[pivotIndex][index]);
                    T[srcNode][index].path = pivotIndex;
                }
            }
        }
        while (pivotIndex != 0);
    }
}   // End of findShortestPath.

/*---------------------------------- insertEdge ----------------------------------------------------/
 *  Inserts an edge into the already built matrix. It checks if there is already an edge or         /
 *  if the inserted edge is outside of the scope.                                                   /
 --------------------------------------------------------------------------------------------------*/
bool GraphM::insertEdge(int fromNode, int toNode, int distance) {
    // This if statement is to check all edge cases to make sure that you can actually insert the node into the graph.
    if ((distance != 0 && fromNode == toNode) ||    // Check if the nodes are the same.
        distance < 0 ||                             // Can't have a negative distance.
        toNode > size ||                            // The toNode is outside of the range of the graph.
        toNode < 1 ||                               // The to node can't be less than 1, source is zero.
        fromNode > size ||
        fromNode < 1){
            return false;
    }

    C[fromNode][toNode] = distance;                  // Actually inserting the edge.
    findShortestPath();                              // Run Dijkstra's algorithm to show the change.


    return true; // Edge was inserted.
}   // End of insertEdge.

/*---------------------------------- removeEdge ----------------------------------------------------/
 *  Removes an edge that's in the matrix.                                                           /
---------------------------------------------------------------------------------------------------*/
bool GraphM::removeEdge(int fromNode, int toNode) {
    // This if statement is made to make sure you can actually delete the edge that's being passed.
    if (fromNode > size || fromNode < 1 || // Can't have a node outside of the size.
        toNode > size || toNode < 1)      // The toNode can't be out of range either.
            return false;


    C[fromNode][toNode] = INT_MAX;         //  Actually removing the edge.
    findShortestPath();                    // Run Dijkstra's algorithm with change.

    return true;
}   // End of removeEdge

/*---------------------------------- Output Overload -----------------------------------------------/
 * Prints the polynomial in sorted order.                                                           /
 --------------------------------------------------------------------------------------------------*/
void GraphM::display(int fromNode, int toNode) {
    // If the edge doesn't exist then the output should show from what node to what node followed by ----.
    if (fromNode > size || fromNode < 0 ||
        toNode > size || toNode < 0){
            cout << setw(7) << fromNode << setw(7) << toNode;   // Print data.

            cout << setw(15) << "----" << endl;                 // No data to print.

            return;
    }

    // Print node fromNode and toNode data
    cout << setw(7) << fromNode << setw(7) << toNode;

    // Check all of the neighbor nodes.
    if (T[fromNode][toNode].dist != INT_MAX){
        cout << setw(12) << T[fromNode][toNode].dist << setw(15); // Print distance

        printPath(fromNode, toNode);
        cout << endl;
        printData(fromNode, toNode);
    }
    else     // No adjacent node
        cout << setw(15) << "----" << endl;


    cout << endl;
}   // End of display.

/*---------------------------------- displayAll ----------------------------------------------------/
 * Function to display all the shortest paths from each node in the matrix.                         /
 --------------------------------------------------------------------------------------------------*/
void GraphM::displayAll() {
    // Print table titles
    cout << "Description" << setw(20) << "From node" << setw(10) << "To node"<< setw(14) << "Dijkstra's"
    << setw(7) << "Path" << endl;

    for (int fromNode = 1; fromNode <= size; fromNode++){
        cout << data[fromNode] << endl << endl;     // Print node name
        for (int toNode = 1; toNode <= size; toNode++){
            if (T[fromNode][toNode].dist != 0){
                cout << setw(27) << fromNode;
                cout << setw(10) << toNode;
                // Check if there are adjacent nodes. If there is print ----.
                if (T[fromNode][toNode].dist == INT_MAX)
                    cout << setw(12) << "----" << endl;
                else{
                    // Display the distnace and call the helper function.
                    cout << setw(12) << T[fromNode][toNode].dist;
                    cout << setw(10);
                    printPath(fromNode, toNode);
                    cout << endl;
                }
            }
        }
    }
}   // End of DisplayAll.
