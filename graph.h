#ifndef PROJETOAED2_GRAPH_H
#define PROJETOAED2_GRAPH_H

#include <vector>
#include <list>
#include <iostream>
#include <queue>
#include "minHeap.h"

using namespace std;

class graph {
public:
    struct Edge {
        int dest;   // Destination node
        double weight; // An integer weight
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

    int n;              // graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
     // The list of nodes being represented

    void dijkstra(int s, int r);


    vector<Node> nodes;
    // Constructor: nr nodes and direction (default: undirected)
    graph(int nodes, bool dir = false);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, string line,double weight = 1);

    // ----- Functions to implement in this class -----
    int dijkstra_distance(int a, int b);
    list<int> dijkstra_path(int a, int b);
    vector<Node> getNodes(){return nodes;}
    int bfs(int v, int b);
};




#endif //PROJETOAED2_GRAPH_H
