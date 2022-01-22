#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <dirent.h>
#include <cmath>
#include "Graph.h"
#include <map>
#include <set>
#include "Files.h"

using namespace std;

int main(){
    vector<Line> lines = readLinesTony();
    vector<Stop> stops = readStops();
    graph graph1(2487,true);
    string line;

    map<int,string> stopsIndex;

    // adicionar os nós ao graph , cada nó representa uma paragem
    for(unsigned int i = 1; i < graph1.getNodes().size(); i++){
        graph1.nodes[i].code = stops[i-1].code;
        graph1.nodes[i].stop = stops[i-1].name;
        graph1.nodes[i].zone = stops[i-1].zone;
        graph1.nodes[i].latitude = stops[i-1].latitude;
        graph1.nodes[i].longitude = stops[i-1].longitude;
        stopsIndex.insert(make_pair(i,stops[i-1].code));
    }


    for (unsigned int i = 0 ; i < lines.size() ; i++){ // direção 0
        ifstream file;
        string lineCode = lines[i].code;
        file.open("line_" + lineCode + "_" + "0.csv");
        getline(file,line); // para ignorar a primeira linha
        vector<string> lineCodes; // todos os códigos dos STOPS dessa linha

        while (getline(file,line)){
            lineCodes.push_back(line);
        }

        for (unsigned j = 0 ; j < lineCodes.size()-1; j++){
            int stopIndexParent = getIndexStops(lineCodes[j], stopsIndex);
            int stopIndexChild = getIndexStops(lineCodes[j + 1], stopsIndex);
            double distance = haversine(stops[stopIndexParent].latitude,
                                        stops[stopIndexParent].longitude,
                                        stops[stopIndexChild].latitude,
                                        stops[stopIndexChild].longitude);
            graph1.addEdge(stopIndexParent,stopIndexChild,lineCode,distance);
        }
    }

    for (unsigned int i = 0 ; i < lines.size() ; i++){ // direção 1
        ifstream file;
        string lineCode = lines[i].code;
        file.open("line_" + lineCode + "_" + "1.csv");
        getline(file,line); // para ignorar a primeira linha
        vector<string> lineCodes; // todos os códigos dos STOPS dessa linha


        while (getline(file,line)){
            lineCodes.push_back(line);
        }
        if (lineCodes.size() == 0) continue; // há linhas que não têm direção 1

        for (unsigned j = 0 ; j < lineCodes.size()-1; j++){
            int stopIndexParent = getIndexStops(lineCodes[j], stopsIndex);
            int stopIndexChild = getIndexStops(lineCodes[j + 1], stopsIndex);
            double distance = haversine(stops[stopIndexParent].latitude,
                                        stops[stopIndexParent].longitude,
                                        stops[stopIndexChild].latitude,
                                        stops[stopIndexChild].longitude);
            graph1.addEdge(stopIndexParent,stopIndexChild,lineCode,distance);
        }
    }
    //cout << graph1.bfs(1347,557);
    //cout << graph1.bfs(1217,1125) << endl;
    //cout << graph1.bfs(1340,1067) << endl;
    list<string> path = graph1.dijkstra_path(1359,1067);
    //list<string> path = graph1.dijkstra_path(1359,1088);
    for (auto it = path.begin(); it != path.end(); it++){
        cout << *it << endl;
    }
    //cout << graph1.bfs(1340,1266) << endl;
    cout << endl;
    //cout << graph1.bfs(2175,420) << endl;
    //cout << graph1.bfs(1359,1088) << endl; // no 603 sao 29 paragens , no 604 sao 14
    //cout << graph1.bfs(1087,1172) << endl;
    return EXIT_SUCCESS;
}

