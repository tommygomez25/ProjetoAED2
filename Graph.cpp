//
// Created by maysa on 19/01/2022.
//

#include "graph.h"
#include <climits>

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, int weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight});
    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}


// ----------------------------------------------------------
// 1) Algoritmo de Dijkstra e caminhos mais curtos
// ----------------------------------------------------------

// ..............................
// a) Distância entre dois nós
// TODO
int Graph::dijkstra_distance(int a, int b) {
    for ( unsigned int  i = 1; i < nodes.size();i++){
        nodes[i].visited = false;
        nodes[i].dist = INT_MAX;
    }
    nodes[a].dist = 0;

    MinHeap<int,int> minHeap(nodes.size(),-1);
    for (unsigned int i = 1; i < nodes.size();i++){
        minHeap.insert(i,nodes[i].dist);
    }

    while (minHeap.getSize() > 0){
        int index = minHeap.removeMin();
        nodes[index].visited = true;

        for (auto adjacent : nodes[index].adj){
            int j = adjacent.dest;
            if (nodes[j].visited == false && nodes[index].dist + adjacent.weight < nodes[j].dist){
                nodes[j].dist = nodes[index].dist + adjacent.weight;
                minHeap.decreaseKey(j,nodes[j].dist);
            }
        }
    }
    if (nodes[b].dist == INT_MAX){
        return -1;
    }
    return nodes[b].dist;
}

// ..............................
// b) Caminho mais curto entre dois nós
// TODO
list<int> Graph::dijkstra_path(int a, int b) {
    list<int> path;

    for ( unsigned int  i = 1; i < nodes.size();i++){
        nodes[i].visited = false;
        nodes[i].dist = INT_MAX;
    }
    nodes[a].dist = 0;
    nodes[a].pred = a;

    MinHeap<int,int> minHeap(nodes.size(),-1);
    for (unsigned int i = 1; i < nodes.size();i++){
        minHeap.insert(i,nodes[i].dist);
    }

    while (minHeap.getSize() > 0){

        int index = minHeap.removeMin();
        nodes[index].visited = true;

        for (auto adjacent : nodes[index].adj){

            int j = adjacent.dest;

            if (nodes[j].visited == false && nodes[index].dist + adjacent.weight < nodes[j].dist){
                nodes[j].dist = nodes[index].dist + adjacent.weight;
                minHeap.decreaseKey(j,nodes[j].dist);
                nodes[j].pred = index;
            }
        }
    }
    if (nodes[b].dist != INT_MAX) {
        int i = b;
        path.push_front(i);
        while (i != a) {
            path.push_front(nodes[i].pred);
            i = nodes[i].pred;
        }
    }

    return path;
}
