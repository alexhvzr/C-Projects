/*------------------------------- BinTree.h --------------------------------------------------------/
 * Author   : Alex van Zuiden-Rylander                                                              /
 * Class    : CSS 343 B Spring 2019 | Data Structures, Algorithms, Discrete Mathematics 2           /
 * Started  : April 18, 2019                                                                        /
 * Modified : April 25, 2019                                                                        /
 * -------------------------------------------------------------------------------------------------/
 * Purpose  : This class was written in to allow the user to create Binary Search Tree's.           /
 *            One can also turn a tree into an array and then back into a binary search             /
 *            tree. Once this is done, it will be a balanced binary search tree.                    /
 * -------------------------------------------------------------------------------------------------/
 * Notes    : One can make a tree through an input file, the assumptions are that there will be a   /
 *            space between all values in the input and the signal to end will be two $ signs       /
 *            like "$$".                                                                            /
 --------------------------------------------------------------------------------------------------*/
#ifndef CSS343ASSIGNMENT2BST_BINTREE_H
#define CSS343ASSIGNMENT2BST_BINTREE_H

#include "nodedata.h"

class BinTree {
    /*
     * Everything that is a support function that is recursively called is going to be
     * private so that the user isn't bothered with it. The default of a class is private.
     * so everything before public: is going to be private be default.
    */
    struct Node {
        NodeData *data;                        // pointer to data object
        Node *left;                            // left subtree pointer
        Node *right;                        // right subtree pointer
    };
    Node *root = NULL;                                // root of the tree

// utility functions
    void toArrayHelper(Node *, NodeData *[], int &);

    void sideways(Node *, int) const;            // provided below, helper for displaySideways()
    // Helper recursive functions.
    void makeEmpty(Node *);

    Node *deepCopy(const Node *);

    bool compareNodes(const Node *, const Node *) const;

    Node *retrieveHelper(const NodeData, Node *&) const;

    int getHeightHelper(Node *) const;

    Node *arrayToBSTreeHelper(NodeData *[], int, int);

    Node *findMinHelper(Node *);

    void inOrderHelper(Node *) const;

public:
    BinTree();                                // constructor
    BinTree(const BinTree &);                // copy constructor
    ~BinTree();                                // destructor, calls makeEmpty
    bool isEmpty() const;                    // true if tree is empty, otherwise false
    BinTree &operator=(const BinTree &);

    bool operator==(const BinTree &) const;

    bool operator!=(const BinTree &) const;

    bool insert(NodeData *);

    bool retrieve(const NodeData, NodeData *&) const;

    void displaySideways() const;            // provided below, displays the tree sideways
    int getHeight(const NodeData &) const;

    void bstreeToArray(NodeData *[]);

    void arrayToBSTree(NodeData *[]);

    Node &findMin(Node *);

    void makeEmpty();

    friend ostream &operator<<(ostream &, const BinTree &);

};


#endif //CSS343ASSIGNMENT2BST_BINTREE_H
