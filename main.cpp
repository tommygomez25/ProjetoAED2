#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <dirent.h>
#include <cmath>
#include "graph.h"
#include <map>
#include <set>
#include "Files.h"

using namespace std;

void addClosestStops(graph &graph, int v, double userDistance){
    for (int v=1; v<=graph.n; v++) graph.nodes[v].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    graph.nodes[v]. visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();

        //cout << u << " "; // show node order

        auto adjacentStops = graph.nodes[u].adj;

        for(unsigned int stop = 1; stop <= graph.n; stop++){
            bool found = false;
            for(auto adjacent: adjacentStops){ // para nao criar edges repetidas
                if(adjacent.dest == stop) found = true;
            }
            if(u == stop || found) continue;

            double distance = haversine(graph.nodes[u].latitude,graph.nodes[u].longitude,graph.nodes[stop].latitude,graph.nodes[stop].longitude);
            if ( u == 1340){
                cout << "distancia entre LUCM2 e " << stop << "= " << distance<< endl;
            }
            if(distance <= userDistance) {
                if (u == 1340){
                    cout << u << " até " << stop << "com distancia " << distance << endl;
                }
                graph.addEdge(u,stop,"a pé",distance);
            }
        }

        for (auto e : graph.nodes[u].adj) {
            int w = e.dest;
            if (!graph.nodes[w].visited) {
                q.push(w);
                graph.nodes[w].visited = true;
            }
        }
    }
}

void createEdges(string direction, const vector<Stop> &stops, const map<string,int> &stopsIndex, graph &graph){
    vector<Line> lines = readLinesTony();
    string line;
    for (unsigned int i = 0 ; i < lines.size() ; i++){
        ifstream file;
        string lineCodeAnterior;
        if (i>=1){
            lineCodeAnterior = lines[i-1].code;
        }
        string lineCode = lines[i].code;
        double distance = 0.0;
        if (lineCode != lineCodeAnterior){
            distance = 1.0;
        }
        file.open("line_" + lineCode + "_" + direction + ".csv");
        getline(file,line); // para ignorar a primeira linha
        vector<string> lineCodes; // todos os códigos dos STOPS dessa linha

        while (getline(file,line)){
            lineCodes.push_back(line);
        }

        if (lineCodes.size() == 0) continue;

        for (unsigned j = 0 ; j < lineCodes.size()-1; j++){

            int stopIndexParent = getIndexStops(lineCodes[j], stopsIndex);
            int stopIndexChild = getIndexStops(lineCodes[j + 1], stopsIndex);

            graph.addEdge(stopIndexParent,stopIndexChild,lineCode,distance);
        }
    }
}

int main(){
    vector<Stop> stops = readStops();
    graph graph1(2487,true);
    string line;
    int distanceBetweenStops;

    map<string,int> stopsIndex;

    // adicionar os nós ao graph , cada nó representa uma paragem
    for(unsigned int i = 1; i < graph1.getNodes().size(); i++){
        graph1.nodes[i].code = stops[i-1].code;
        graph1.nodes[i].stop = stops[i-1].name;
        graph1.nodes[i].zone = stops[i-1].zone;
        graph1.nodes[i].latitude = stops[i-1].latitude;
        graph1.nodes[i].longitude = stops[i-1].longitude;
        stopsIndex.insert(make_pair(stops[i-1].code,i));
    }

    createEdges("0",stops,stopsIndex,graph1);
    createEdges("1",stops,stopsIndex,graph1);

    //addClosestStops(graph1,1,0.1);
    //list<tuple<string,string,string>> path1 = graph1.dijkstra_path(2165,1661);
    graph1.dijkstra(1340, 1067);
    list<tuple<string,string,string>> path = graph1.dijkstra_path(1340,1067);
    cout << graph1.nodes[1067].dist;

    //list<tuple<string,string,string>> path = graph1.bfs_path(1340,1067);

    //list<tuple<string,string,string>> path = graph1.dijkstra_path(2177,913);

    for(auto it = path.begin(); it != path.end(); it++){
        cout << get<2>(*it)<< " - " <<get<0>(*it) << "(" << get<1>(*it) << ")" <<  " -> ";
    }
    //cout << haversine(graph1.nodes[1340].latitude, graph1.nodes[1340].longitude, graph1.nodes[1261].latitude, graph1.nodes[1261].longitude);

    return EXIT_SUCCESS;
}

