#include "BinTree.h"
/*------------------------------- BinTree.cpp ------------------------------------------------------/
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

#include "BinTree.h"

/*---------------------------------- Constructor ---------------------------------------------------/
 *  Default Constructor - Set's the BST root to NULL                                                /
 --------------------------------------------------------------------------------------------------*/
BinTree::BinTree() {
    root = NULL;
}   // End of Constructor.

/*---------------------------------- Copy Constructor ----------------------------------------------/
 *  This creates a deep copy of the BSTree that's passed in the rhs.                                /
 --------------------------------------------------------------------------------------------------*/
BinTree::BinTree(const BinTree &rhs) {
    if(!isEmpty())
        makeEmpty(root);                                // Initialize this root to NULL.
    if (!rhs.isEmpty())
        root = deepCopy(rhs.root);
}   // End of Constructor.

/*---------------------------------- deepCopy ------------------------------------------------------/
 *  Function that recursively makes new nodes and copies the rhs data to the lhs tree. Effectively  /
 *  making a deep copy of the tree that is passed.                                                  /
 --------------------------------------------------------------------------------------------------*/
BinTree::Node *BinTree::deepCopy(const BinTree::Node *rhs) {
    if (rhs == NULL)
        return NULL;

    Node *temp = new Node;
    temp->data = rhs->data;                 // Set's the new nodes data to the node passed into the function.
    temp->left = deepCopy(rhs->left);       // Set's the nodes left equal to the rights left.
    temp->right = deepCopy(rhs->right);     // Set's the nodes right equal to the right right.
    return temp;
}

/*---------------------------------- Destructor ----------------------------------------------------/
 *  Deletes the BinTree so there is no memory leak.                                                 /
 --------------------------------------------------------------------------------------------------*/
BinTree::~BinTree() {
    makeEmpty(root);                        // Helper function.
}   // End of Destructor.

/*---------------------------------- isEmpty -------------------------------------------------------/
 *  Checks to see if the lhs BinTree is empty.                                                      /
 --------------------------------------------------------------------------------------------------*/
bool BinTree::isEmpty() const {
    return (root == NULL);                  // If the root is NULL then the BST is empty.
}   // End of isEmpty.

/*---------------------------------- makeEmpty -----------------------------------------------------/
 *  Public function that calls private to delete the BinTree.                                       /
 --------------------------------------------------------------------------------------------------*/
void BinTree::makeEmpty() {
    if(!isEmpty())
         makeEmpty(root);                    // Call to private recursive function.
}   // End of makeEmpty.

/*---------------------------------- makeEmpty Private Function ------------------------------------/
 *  Recursively deletes the data from the tree and then set's the root to NULL leaving no memory    /
 *  leaks.                                                                                          /
 --------------------------------------------------------------------------------------------------*/
void BinTree::makeEmpty(Node *current) {

    if (current != NULL) {
        makeEmpty(current->left);           // Find the leaf nodes and delete them from left to right
        makeEmpty(current->right);
        delete current;
    }
    root = NULL;                            // There's no more leaf nodes to delete. Set the root to NULL so BST empty.
}   // End of makeEmpty recursive.

/*---------------------------------- Assignment Operator -------------------------------------------/
 *  Assigns one BinTree to another.                                                                 /
 --------------------------------------------------------------------------------------------------*/
BinTree &BinTree::operator=(const BinTree &rhs) {
    if (*this != rhs) {
        makeEmpty(root);                    // Clears the tree so that it can be set to the rhs.
        root = deepCopy(rhs.root);          // Assigns the lhs to the rhs calling the recursive deepCopy function.
    }
    return *this;
}   // End of assignment operator.

/*---------------------------------- compareNodes --------------------------------------------------/
 *  Function to check if the nodes in a BinTree are equal.                                          /
 --------------------------------------------------------------------------------------------------*/
bool BinTree::compareNodes(const Node *lhs, const Node *rhs) const {

    if (lhs == NULL || rhs == NULL)         // If one is null and the other not, they are not equal.
        return false;
    if ((*lhs->data == *rhs->data) && (lhs != NULL && rhs != NULL))
        return true;                        // Both same, return true
    return ((*lhs->data == *rhs->data) &&
            compareNodes(lhs->left, rhs->left)
            && compareNodes(lhs->right, rhs->right));

}   // End of compareNodes.

/*---------------------------------- Equality Operator ---------------------------------------------/
 *  Checks if both BinTrees are equal.                                                              /
 --------------------------------------------------------------------------------------------------*/
bool BinTree::operator==(const BinTree &rhs) const {
    //Recursively check each child node for equality.
    return compareNodes(root, rhs.root);    // Calls helper function.
}   // End of equality operator.

/*---------------------------------- Not Equal Operator --------------------------------------------/
 *  Checks if two BinTrees are not equal.                                                           /
 --------------------------------------------------------------------------------------------------*/
bool BinTree::operator!=(const BinTree &rhs) const {
    return !(*this == rhs);
}   // End of inequality operator.

/*---------------------------------- insert --------------------------------------------------------/
 *  Inserts a node into the BinTree if the value doesn't exist.                                     /
 --------------------------------------------------------------------------------------------------*/
bool BinTree::insert(NodeData *str) {
//    if (root == NULL) {
//        root = new Node;
//        root->data = item;
//        root->leftChild = NULL;
//        root->rightChild = NULL;
//    }
//    else if (*item < *root->item)
//        insert(root->leftChild, item);
//    else
//        insert(root->rightChild, item);

    Node *insertedNode = new Node;
    insertedNode->data = str;
    insertedNode->left = insertedNode->right = NULL;

    if (isEmpty()) {
        root = insertedNode;                               // The tree is empty, set the root to the node inserted.
        return true;

    } else {
        Node *pointer = root;                              // Set a pointer to the root so that you can move down the tree.
        while (true) {
            if (*pointer->data == *insertedNode->data) {   // Checks if there's a duplicate node.
                delete insertedNode;                       // Deletes it if there is.
                return false;                              // Returns false because there was nothing inserted.
            }
            if (*pointer->data > *insertedNode->data) {    // Checks if the inserted nodes data is less than the existing node.
                if (pointer->left == NULL) {
                    pointer->left = insertedNode;          // If there's nothing to the left, insert the node there.
                    return true;                           // Set notInserted to false to stop the while loop.
                } else {
                    pointer = pointer->left;               // There was a value left, keep moving down the tree to the left.
                }
            } else {                                       // The inserted nodes data is greater than the existing node.
                if (pointer->right == NULL) {
                    pointer->right = insertedNode;         // If there's nothing to the right, insert the node there.
                    return true;                           // Set notInserted to false to stop the while loop.
                } else {
                    pointer = pointer->right;              // There was a value right, keep moving down the tree to the right.
                }
            }

        }
    }
}   // End of insert function.

/*---------------------------------- retrieve ------------------------------------------------------/
 *  Finds if there is a node value withing the BinTree.                                             /
 --------------------------------------------------------------------------------------------------*/
bool BinTree::retrieve(const NodeData key, NodeData *&node) const {
    Node *rootTemp = root;                              // Have a pointer pointing at the root so that you can search through the tree.
    Node *pointer = retrieveHelper(key, rootTemp);      // Call the recursive helper function.
    if (pointer != NULL)
        node = pointer->data;                           // You found the value in the BinTree, set node equal to it.
    else
        return false;                                   // You didn't find the value in the tree.


    return true;                                        // You did find the value.
}   // End of retrieve.

/*---------------------------------- retrieveHelper ------------------------------------------------/
 *  Checks if there's a value within the BinTree. Recursive function.                               /
 --------------------------------------------------------------------------------------------------*/
BinTree::Node *BinTree::retrieveHelper(const NodeData key, Node *&node) const {
    if (node == NULL)                                // If node is NULL it wasn't in the tree.
        return NULL;
    if (*node->data == key)                          // Checks to see you found the node.
        return node;
    if (*node->data > key)                           // If the node is less than the key, search the left side of the BinTree.
        return retrieveHelper(key, node->left);
    else
        return retrieveHelper(key, node->right);     // If the node is great than the key, search the right side of the BinTree.
}   // End of retrieveHelper


/*---------------------------------- getHeight Accessor --------------------------------------------/
 *  Get's a nodes height given it's data.                                                           /
 --------------------------------------------------------------------------------------------------*/
int BinTree::getHeight(const NodeData &index) const {
    Node *rt = root;                                // Set a pointer to the root so that you can search through the BinTree.
    Node *pointer = retrieveHelper(index, rt);      // Find the value in the tree.

    return getHeightHelper(pointer);                // Call the recursive function to find the height of the node given.
}   // End of getHeight.

/*---------------------------------- getHeightHelper Accessor --------------------------------------/
 *  Private recursive function to help find the BinTree height.                                     /
 --------------------------------------------------------------------------------------------------*/
int BinTree::getHeightHelper(BinTree::Node *index) const {
    if (index == NULL)                              // If the value is NULL you're past the trees leaf nodes or there wasn't a node with that value.
        return 0;

    int left = getHeightHelper(index->left);        // Count the height from the left.
    int right = getHeightHelper(index->right);      // Count the height from the right.

    if (right > left)                               // Depending on the greater value return that one.
        return (right + 1);
    else
        return (left + 1);
}   // End of getHeightHelper.

/*---------------------------------- bstreeToArray -------------------------------------------------/
 *  Converts the BinTree to an array.                                                               /
 --------------------------------------------------------------------------------------------------*/
void BinTree::bstreeToArray(NodeData *array[]) {
    int index = 0;
    toArrayHelper(root, array, index);              // Calls the helper funciton to make the array.
    makeEmpty(root);                                // Deletes the old BinTree.
}   // End of bstreeToArray.

/*---------------------------------- toArrayHelper -------------------------------------------------/
 *  Recursive helper function that sets the values into the array in order.                         /
 --------------------------------------------------------------------------------------------------*/
void BinTree::toArrayHelper(Node *current, NodeData *array[], int &index) {

    if (current != NULL) {
        toArrayHelper(current->left, array, index);     // In order visits the nodes left, current, and then right.
        array[index++] = current->data;  // This function goes left, sets current, then goes right.
        toArrayHelper(current->right, array, index);
    }

}   // End of toArrayHelper.

/*---------------------------------- arrayToBSTree -------------------------------------------------/
 *  Take an in order array of nodes and make it into a BinTree.                                     /
 --------------------------------------------------------------------------------------------------*/
void BinTree::arrayToBSTree(NodeData *array[]) {
    int end = 0;

    for (int i = 0; i < 100; ++i)                    // Find the ending index of the array, once there's a NULL value there's no more Nodes.
        if (array[i] == NULL) {
            end = i - 1;                             // Set end to the end value.
            break;
        }


    root = arrayToBSTreeHelper(array, 0, end);       // Call the helper function to recursively build the BST.

    for (int j = 0; j < 100; ++j)                    // Clear the array of all value.
        array[j] = NULL;


}   // End of arrayToBSTree.

/*---------------------------------- arrayToBSTreeHelper -------------------------------------------/
 *  Recursive helper function that set's the trees node values.                                     /
 --------------------------------------------------------------------------------------------------*/
BinTree::Node *BinTree::arrayToBSTreeHelper(NodeData **array, int begin, int end) {
    if (end < begin)                                                    // Base case.
        return NULL;


    int middle = (begin + end) / 2;                                     // Find the middle index.
    Node *temp = new Node;                                              // Create a new Node.

    temp->data = array[middle];                                         // Set the nodes data to the array at the index.

    temp->left = arrayToBSTreeHelper(array, begin, middle - 1);         // Set temp's left node.
    temp->right = arrayToBSTreeHelper(array, middle + 1, end);          // Set temp's right node.

    return temp;
}

/*---------------------------------- findMin -------------------------------------------------------/
 *  Finds the node with the lowest value in the BinTree.                                            /
 --------------------------------------------------------------------------------------------------*/
BinTree::Node &BinTree::findMin(BinTree::Node *index) {
    return *findMinHelper(index);                                       // Calls helper function.
}   // End of findMin.

/*---------------------------------- findMinHelper -------------------------------------------------/
 *  Finds the lowest nodes value.                                                                   /
 --------------------------------------------------------------------------------------------------*/
BinTree::Node *BinTree::findMinHelper(BinTree::Node *rt) {
    if (rt == NULL)
        return NULL;                // Value wasn't there.

    if (rt->left == NULL)           // Return the lowest value.
        return rt;
    else
        findMinHelper(rt->left);    // Recursively find the lowest value.

}

/*---------------------------------- Output Overload -----------------------------------------------/
 * Prints the polynomial in sorted order.                                                           /
 --------------------------------------------------------------------------------------------------*/
ostream &operator<<(ostream &out, const BinTree &a) {
    a.inOrderHelper(a.root);    // Helper function to print the tree in order.
    out << endl;
    return out;
}   // End Output Overload.

/*---------------------------------- inOrderHelper -------------------------------------------------/
 *  Get's the coefficient given the degree as an input.                                             /
 --------------------------------------------------------------------------------------------------*/
void BinTree::inOrderHelper(Node *current) const {
    if (current != NULL) {
        inOrderHelper(current->left);    // Prints out the nodes in order (left, current, right).
        cout << *current->data << " ";
        inOrderHelper(current->right);
    }
}   // End inOrderHelper.

//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const {
    sideways(root, 0);
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node *current, int level) const {
    if (current != NULL) {
        level++;
        sideways(current->right, level);

        // indent for readability, 4 spaces per depth level
        for (int i = level; i >= 0; i--) {
            cout << "    ";
        }

        cout << *current->data << endl;        // display information of object
        sideways(current->left, level);
    }
}