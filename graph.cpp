#include "graph.h"
#include <climits>
#include <tuple>
#include <map>
#include <algorithm>

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
    //list<int> distances;
    int dist = -1;
    string linha_a_usar;
    multimap<string,string> stops;
    for (int v=1; v<=n; v++) {nodes[v].visited = false;
                              nodes[v].dist = 10000.0;}
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].dist = 0;
    //distances.push_back(nodes[v].dist);
    nodes[v].visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        /*if (u == b){
            dist = nodes[b].dist;
            return dist;
        }*/

        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                //cout << e.line << " - " << nodes[w].stop << endl;
                q.push(w);
                nodes[w].visited = true;
                nodes[w].dist = nodes[u].dist + 1.0;
                nodes[w].pred = u;
                nodes[w].line = e.line;
            }
        }
    }
/*
    cout << "As paragens sao as seguintes: " ;
    for (auto const& stop : stops){
        if (stop.first == linha_a_usar ){
            cout << stop.second << " - " ;
        }
    }*/
    return dist;
}

list<tuple<string,string,string>> graph::bfs_path(int a, int b) {
    bfs(a,b);
    list<tuple<string,string,string>> path;
    if (nodes[b].dist == INT_MAX / 2) return path;
    path.emplace_back(nodes[b].stop,nodes[b].code, nodes[b].line);
    int v = b;
    int i = 0;
    while (v != a ) {
        v = nodes[v].pred;
        path.push_front(make_tuple(nodes[v].stop,nodes[v].code, nodes[v].line));
    }
    return path;
}


queue<string> graph::dijkstra(int s, int r) {
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
    queue<string> usedLines;
    while (q.getSize()>0 && !arrived) {
        int u = q.removeMin();
        //cout << "PRED " << nodes[nodes[u].pred].stop << "(" << nodes[nodes[u].pred].code << ")" << endl;
        // cout << "STOP " << nodes[u].stop << "(" << nodes[u].code << ")" << " with dist = " << nodes[u].dist << endl;
        nodes[u].visited = true;
        for (auto e : nodes[u].adj) {
            int i = 0;
            int v = e.dest;
            if (nodes[u].line != e.line){
                e.weight++;
            }
            //cout << v << endl;
            double w = e.weight;
            if (!nodes[v].visited && nodes[u].dist + w < nodes[v].dist ) {
                nodes[v].line = e.line;
                nodes[v].dist = nodes[u].dist + w;
                q.decreaseKey(v, nodes[v].dist);
                nodes[v].pred = u;
            }
            if(!nodes[v].visited && nodes[u].dist + w == nodes[v].dist && nodes[u].line == e.line){
                nodes[v].line = nodes[u].line;
            }

            if(v == r) arrived = true;
        }
    }
    return usedLines;
}

int graph::dijkstra_distance(int a, int b) {
    dijkstra(a,b);
    if (nodes[b].dist == INT_MAX/2) return -1;
    return nodes[b].dist;
}

list<tuple<string,string,string>> graph::dijkstra_path(int a, int b) {
    dijkstra(a,b);
    list<tuple<string,string,string>> path;
    if (nodes[b].dist == INT_MAX / 2) return path;
    path.emplace_back(nodes[b].stop,nodes[b].code, nodes[b].line);
    int v = b;
    while (v != a) {
        v = nodes[v].pred;
        path.push_front(make_tuple(nodes[v].stop,nodes[v].code, nodes[v].line));
    }
    return path;
}



void graph::addCloseStops(int v, int userDistance) {

}