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
    string linha_a_usar;
    multimap<string,string> stops;
    for (int v=1; v<=n; v++) nodes[v].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].dist = 0;
    nodes[v].visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        if ( u == b){
            //return nodes[b].dist;
            break;
        }

        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (w == b) {
                linha_a_usar = e.line;
            }
            //cout << e.line << " - " << nodes[w].stop << endl;
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
    return -1;
}






