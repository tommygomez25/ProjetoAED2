
#include "graph.h"
#include <climits>
#include <tuple>

// Constructor: nr nodes and direction (default: undirected)
graph::graph(int num, bool dir) : n(num), hasDir(dir), nodes(num + 1) {
}

// Add edge from source to destination with a certain weight
void graph::addEdge(int src, int dest, string line, double weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight, line});
    if (!hasDir) nodes[dest].adj.push_back({src, weight, line});
}

int graph::bfs(int v, int b) {
    for (int v=1; v<=n; v++) nodes[v].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v]. visited = true;
    int i = 0;
    cout << endl << "Indice paragem inicial: "<<v ;
    i++;
    bool arrived = false;
    while (q.front() != b) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
         // show node order
        for (auto e : nodes[u].adj) {
            cout <<endl << "Índice do node: "<<e.dest << "  Distancia (em paragens): " << i << "  Linha a usar: "<< e.line ;
            int w = e.dest;
            if(w == b){
                arrived = true;
                break;
            }
                //arrived = true;
            if (!nodes[w].visited) {

                q.push(w);
                nodes[w].visited = true;
            }
        }
        if(arrived)
            break;
        i++;

    }
    return i;
}



