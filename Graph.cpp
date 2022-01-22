
#include "Graph.h"
#include <climits>

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest,string line, int weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight, line});
    if (!hasDir) nodes[dest].adj.push_back({src, weight, line});
}

void Graph::bfs(int v, int b) {
    for (int v=1; v<=n; v++) nodes[v].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v]. visited = true;
    int i = 0;
    cout << endl << "Indice paragem inicial: "<<v ;
    i++;
    while (q.front() != b) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
         // show node order
        for (auto e : nodes[u].adj) {
            cout <<endl << "Índice do node: "<<e.dest << "  Distancia (em paragens): " << i << "  Linha a usar: "<< e.line ;
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
            }
        }
        i++;

    }
}

void Graph::dijkstra(int s) {
    MinHeap<int,int> q(n,-1);
}




