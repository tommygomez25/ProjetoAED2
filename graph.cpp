
#include "Graph.h"
#include <climits>
#include <tuple>

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest,string line, double weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight, line});
    if (!hasDir) nodes[dest].adj.push_back({src, weight, line});
}

int Graph::bfs(int v, int b) {
    for (int v=1; v<=n; v++) nodes[v].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v]. visited = true;
    int i = 0;
    cout << endl << "Indice paragem inicial: "<<v ;
    i++;
    bool arrived = false;
    while (q.front() != b && !arrived) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
         // show node order
        for (auto e : nodes[u].adj) {
            cout << endl << "Índice do node: "<< e.dest << "  Distancia (em paragens): " << i << "  Linha a usar: "<< e.line << endl ;
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
        i++;

    }
    return i;
}

void Graph::dijkstra(int s, int r) {
    MinHeap<int,int> q(n,-1);
    for (int v = 1; v <= n; v++){
        nodes[v].dist = INT_MAX/2;
        q.insert(v, INT_MAX/2);
        nodes[v].visited = false;
    }
    nodes[s].dist = 0;
    q.decreaseKey(s,0);
    bool arrived = false;
    while(q.getSize() > 0 && !arrived){
        int u = q.removeMin();
        nodes[u].visited = true;
        //cout << endl << "Arrived to node " << u << " with dist = " << nodes[u].dist << endl;
        for(auto e: nodes[u].adj){
            int v = e.dest;
            int w = e.weight;
            if(!nodes[v].visited && nodes[u].dist + w < nodes[v].dist){
                nodes[v].dist = w + nodes[u].dist;
                q.decreaseKey(v,nodes[v].dist);
                nodes[v].pred = u;
                //cout << "improved node " << v << " to dist " << nodes[v].dist << endl;
            }
            if(v == r) arrived = true;
        }
    }
}

int Graph::dijkstra_distance(int a, int b) {
    dijkstra(a,b);
    if(nodes[b].dist == INT_MAX) return -1;
    return nodes[b].dist;
}

list<int> Graph::dijkstra_path(int a, int b) {
    dijkstra(a,b);
    list<int> path;
    if(nodes[b].dist == INT_MAX) return path;
    path.push_back(b);
    int v = b;
    while(v != a){
        v = nodes[v].pred;
        path.push_front(v);
    }
    return path;
}




