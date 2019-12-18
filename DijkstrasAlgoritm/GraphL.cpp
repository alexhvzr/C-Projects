/*------------------------------- GraphL.cpp -------------------------------------------------------/
 * Author   : Alex van Zuiden-Rylander                                                              /
 * Class    : CSS 343 B Spring 2019 | Data Structures, Algorithms, Discrete Mathematics 2           /
 * Started  : May 7th, 2019                                                                         /
 * Modified : May 13th, 2019                                                                        /
 * -------------------------------------------------------------------------------------------------/
 * Purpose  : This class was written in to allow the user to create a graph and perform Dijkstras   /
 *            algorithm on it to find the shortest distance from one node to all the rest.          /
 * -------------------------------------------------------------------------------------------------/
 * Notes    : One can make a graph through an input file, the first number given is the number of   /
 *            nodes that are within the file and then the next X names are the names of the nodes.  /
 *            That is followed by the node value and which nodes it's pointing at in the graph.     /
 --------------------------------------------------------------------------------------------------*/


#include "GraphL.h"
#include <iomanip>

/*---------------------------------- Destructor ----------------------------------------------------/
 *  Deletes the data from the graph so there is no memory leak.                                     /
 --------------------------------------------------------------------------------------------------*/
void GraphL::emptyGraph(){
    for (int i = 1; i <= size; i++){
        graphNodeArray[i].visited = false;
        delete graphNodeArray[i].data;                                      // Delete Name.
        graphNodeArray[i].data = NULL;                                      // Set Name equal to NULL.

        if (graphNodeArray[i].edgeHead != NULL){
            EdgeNode* deletedNode = graphNodeArray[i].edgeHead;

            while (deletedNode != NULL) {                                   // Go through the Llinked list deleting all node values.
                graphNodeArray[i].edgeHead = graphNodeArray[i].edgeHead->nextEdge;
                delete deletedNode;                                         // Delete node.
                deletedNode = NULL;                                         // Point it to NULL
                deletedNode = graphNodeArray[i].edgeHead;                   // Assign the next node to be deleted.
            }
        }
    }
}   // End of emptyGraph.

/*---------------------------------- depthFirstSearchHelper ----------------------------------------/
 *  Helper function to travers through the matrix depth first.                                      /
 --------------------------------------------------------------------------------------------------*/
void GraphL::depthFirstSearchHelper(int index) {
    cout << setw(2) << index;                                    // Print node.
    graphNodeArray[index].visited = true;                        // Mark your current node as visited.
    EdgeNode* current = graphNodeArray[index].edgeHead;

    while (current != NULL){                                    // Loop through the entire list.
        if (!graphNodeArray[current->adjGraphNode].visited)     // Check if visited the node has already been visited.
            depthFirstSearchHelper(current->adjGraphNode);

        current = current->nextEdge;    // Keep moving the node to the next value in the list.
    }
} // End of depthFirstSearchHelper.

/*---------------------------------- Default Constructor -------------------------------------------/
 *  Default Constructor - Set's the graph values to NULL.                                           /
 --------------------------------------------------------------------------------------------------*/
GraphL::GraphL() {
    size = 0; // Initial size is zero for constructor.
    for (int i = 1; i < MAXNODES; i++){
        graphNodeArray[i].edgeHead = NULL;
        graphNodeArray[i].data = NULL;
        graphNodeArray[i].visited = false;
    }
}   // End of Default Constructor.

/*---------------------------------- Destructor ----------------------------------------------------/
 *  Calls the helper function to delete the entire graph.                                           /
 --------------------------------------------------------------------------------------------------*/
GraphL::~GraphL() {
    emptyGraph();
}   // End of Destructor.

/*---------------------------------- buildGraph ----------------------------------------------------/
 *  Constructor - Uses an input file to fill the graph data. Assumes that the input is structured   /
 *  correctly.                                                                                      /
 --------------------------------------------------------------------------------------------------*/
void GraphL::buildGraph(ifstream &inFile) {
    inFile >> size;                         // Sets the size.
    string name = "";
    getline(inFile, name);                  // Read line and assign name.

    // Insert edge names
    for (int index = 1; index <= size; index++){
        getline(inFile, name);
        NodeData* temp = new NodeData(name);
        graphNodeArray[index].data = temp;  // Insert names into the array at the given index.
    }

    int fromNode, toNode;

    while (inFile >> fromNode >> toNode){   // Fill Linked List with the node data.
        if (fromNode == 0)                  // Base case and you need to stop iterating through the file.
            break;

        // Check the first node for null, if that's the case insert at the front.
        if (graphNodeArray[fromNode].edgeHead == NULL){
            EdgeNode* headNode = new EdgeNode;
            headNode->adjGraphNode = toNode;                // Insert adjacent.
            graphNodeArray[fromNode].edgeHead = headNode;   // Point toNode head.
            graphNodeArray[fromNode].edgeHead->nextEdge  = NULL;
        }
        else{
            // Inserting the nodes into the linked list.
            EdgeNode* insertedNode = new EdgeNode;
            insertedNode->adjGraphNode = toNode;
            insertedNode->nextEdge = graphNodeArray[fromNode].edgeHead;
            graphNodeArray[fromNode].edgeHead = insertedNode;  // Assign as head.
        }
    }
}   // End of Build Graph Function.

/*---------------------------------- depthFirstSearch ----------------------------------------------/
 *  Parent function to go though the entire graph and calls the helper function to iterate though   /
 *  the list.                                                                                       /
 --------------------------------------------------------------------------------------------------*/
void GraphL::depthFirstSearch() {
    cout << "Depth-first ordering:";
    for (int vertex = 1; vertex <= size; ++vertex){
        if (!graphNodeArray[vertex].visited)
            depthFirstSearchHelper(vertex);
    }
    cout << endl;
}   // End of depthFirstSearch.

/*---------------------------------- displayGraph --------------------------------------------------/
 *  Function to display the nodes within the graph.                                                 /
 --------------------------------------------------------------------------------------------------*/
void GraphL::displayGraph() {
    cout << "Graph:" << endl;

    for (int i = 1; i <= size; i++){
        // Print node info.
        cout << "Node" << i << "      " << *graphNodeArray[i].data << endl;
        cout << endl;
        EdgeNode* current = graphNodeArray[i].edgeHead;

        while (current != NULL){
            // Print the list.
            cout << setw(7) << "edge " << i << setw(2) << current->adjGraphNode << endl;
            current = current->nextEdge;
        }
    }
}   // End of displayGraph.
