#include<iostream>
#include <vector>
#include <stack>

using namespace std;

//create a vector array for adj list with max node size 100
vector<int> adj[100];


//define a boolean array for keeping track of visited nodes
bool visited[100];


void dft(int x) {
    //create an int stack
    stack<int> nodeStack;

    //push x onto the stack and mark the node visited
    nodeStack.push(x);
    visited[x] = true;
    //cout << nodeStack.top() << " ";

    //while stack is not empty
    while(!nodeStack.empty()){
        //pop a node from stack and print it

        int top = nodeStack.top();
        nodeStack.pop();

        // Get all adjacent vertices of the popped vertex s
        int len = adj[top].size();
        for (int i =0; i < len;i++){
            nodeStack.push(adj[top][i]);
            if(!visited[adj[top][i]]){
                cout << adj[top][i] << endl;
//                cout << nodeStack.top() + " ";
            }
            visited[adj[top][i]] = true;

        }

        // If an adjacent has not been visited, then push it
        // to the stack and mark it as visited

    }







}


int main() {
    int x, y, nodes, edges;
    //read number of nodes and edges from the user
    //Ex:
    // 3

    cout << "please enter an amount of nodes: " << endl;
    cin >> nodes;
    cout << "please enter an amount of edges: " << endl;
    cin >> edges;




    //Then read the individual edge pairs(x,y) from the user and insert into the graph
    //to insert into a vector use push_back function
    //Ex:
    //0 1
    //1 2
    //0 2
    // 3
    for (int i = 0; i < edges; i++) {

        cout << "please enter the initial node" << endl;
        cin >> x;
        cout << "please enter the adjacent node" << endl;
        cin >> y;
        adj[x].push_back(y);

    }



    //print the content of graph
    //sample output:
    // adk[0] : 1-->2
    // adj[1] : 2
    // adj[2] :
    int l;
    for (int j = 0; j < nodes; j++) {
        l = adj[j].size();
        cout << j;
        for (int k = 0; k < l; k++) {
            cout << "-->" << adj[j][k];
        }
        cout << "-|" << endl;
    }



    //initialize the status of each node unvisited
    int q;
    for (int w = 0; w < nodes; w++) {
        q = adj[w].size();
        for (int z= 0; z < q; z++) {
            visited[adj[w][z]] = false;
        }
    }
//    if(visited[adj[0][0]] == false){
//        cout << "Node is not visited." << endl;
//        cout << "Node we are checking is node " << adj[0][0];
//    }




    //print the depth-first traversal of the graph



    //sample output:
    // 0 2 1
    dft(0); //write a function for implementing depth-first traversal


    return 0;
}




