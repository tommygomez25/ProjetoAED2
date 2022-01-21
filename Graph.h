#ifndef PROJETOAED2_GRAPH_H
#define PROJETOAED2_GRAPH_H

#include <vector>
#include <list>
#include <iostream>
#include <queue>

using namespace std;

class Graph {
public:
    struct Edge {
        int dest;   // Destination node
        int weight; // An integer weight
        string line; //
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        int dist;
        int pred;
        bool visited;
        string stop; // The name of the stop
        string code;
        string zone;
        float latitude;
        float longitude;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
     // The list of nodes being represented

    void dijkstra(int s);


    vector<Node> nodes;
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, string line,int weight = 1);

    // ----- Functions to implement in this class -----
    int dijkstra_distance(int a, int b);
    list<int> dijkstra_path(int a, int b);
    vector<Node> getNodes(){return nodes;}
    void bfs(int v, int b);
};




#endif //PROJETOAED2_GRAPH_H
