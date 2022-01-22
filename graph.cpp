#include "graph.h"
#include <climits>
#include <tuple>
#include <map>

// Constructor: nr nodes and direction (default: undirected)
graph::graph(int num, bool dir) : n(num), hasDir(dir), nodes(num + 1) {
}

// Add edge from source to destination with a certain weight

void graph::addEdge(int src, int dest,string line, double weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight, line});
    if (!hasDir) nodes[dest].adj.push_back({src, weight, line});
}

int graph::bfs(int v, int b) {
    int dist = -1;
    string linha_a_usar;
    multimap<string,string> stops;
    for (int v=1; v<=n; v++) nodes[v].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].dist = 0;
    nodes[v].visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        if (u == b){
            dist = nodes[b].dist;
            break;
        }

        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (w == b) {
                linha_a_usar = e.line;
            }
            cout << e.line << " - " << nodes[w].stop << endl;
            stops.insert(make_pair(e.line,nodes[w].stop));
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].dist = nodes[u].dist + 1;
            }
        }
    }
    cout << "A linha que deve usar : " << linha_a_usar << endl;
    cout << "As paragens sao as seguintes: " ;
    for (auto const& stop : stops){
        if (stop.first == linha_a_usar ){
            cout << stop.second << " - " ;
        }
    }
    return dist;
}


void graph::dijkstra(int s, int r) {
    MinHeap<int, int> q(n, -1);
    for (int v=1; v<=n; v++) {
        nodes[v].dist = INT_MAX/2;
        q.insert(v, INT_MAX/2);
        nodes[v].visited = false;
    }
    nodes[s].dist = 0;
    q.decreaseKey(s, 0);
    nodes[s].pred = s;
    bool arrived = false;
    while (q.getSize()>0 && !arrived) {
        int u = q.removeMin();
        // cout << "Node " << u << " with dist = " << nodes[u].dist << endl;
        nodes[u].visited = true;
        for (auto e : nodes[u].adj) {
            int v = e.dest;
            int w = e.weight;
            if (!nodes[v].visited && nodes[u].dist + w < nodes[v].dist) {
                nodes[v].dist = nodes[u].dist + w;
                q.decreaseKey(v, nodes[v].dist);
                nodes[v].pred = u;
            }
            if(v == r) arrived = true;
        }
    }
}

int graph::dijkstra_distance(int a, int b) {
    dijkstra(a,b);
    if (nodes[b].dist == INT_MAX/2) return -1;
    return nodes[b].dist;
}

list<string> graph::dijkstra_path(int a, int b) {
    dijkstra(a,b);
    list<string> path;
    if (nodes[b].dist == INT_MAX / 2) return path;
    path.push_back(nodes[b].stop);
    int v = b;
    while (v != a) {
        v = nodes[v].pred;
        path.push_front(nodes[v].stop);
    }
    return path;
}