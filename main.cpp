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

int main(){
    vector<Line> lines = readLinesTony();
    vector<Stop> stops = readStops();
    graph graph1(2487,true);
    string line;

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
            double distance = haversine(stops[stopIndexParent-1].latitude,
                                        stops[stopIndexParent-1].longitude,
                                        stops[stopIndexChild-1].latitude,
                                        stops[stopIndexChild-1].longitude);
            if(stops[stopIndexParent].name == "LUIS CAMÕES")
                cout << endl <<stops[stopIndexParent-1].name << " - " << stops[stopIndexChild-1].name << "," << distance << endl;
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
            double distance = haversine(stops[stopIndexParent-1].latitude,
                                        stops[stopIndexParent-1].longitude,
                                        stops[stopIndexChild-1].latitude,
                                        stops[stopIndexChild-1].longitude);

            if(stops[stopIndexParent-1].name == "LUIS CAMÕES"){
                cout << stopIndexParent<< " - " << stopIndexChild;
                cout << endl <<stops[stopIndexParent-1].name << " - " << stops[stopIndexChild-1].name << "," << distance << endl;
            }
            graph1.addEdge(stopIndexParent,stopIndexChild,lineCode,distance);
        }
    }

//    list<tuple<string,string,string>> path = graph1.dijkstra_path(1340,1067);
    cout << graph1.bfs(1340,1067);

    //list<tuple<string,string,string>> path = graph1.dijkstra_path(2177,913);

/*    for(auto it = path.begin(); it != path.end(); it++){
        cout << get<2>(*it)<< " - " <<get<0>(*it) << "(" << get<1>(*it) << ")" <<  " -> ";
    }*/
    //cout << haversine(graph1.nodes[1340].latitude, graph1.nodes[1340].longitude, graph1.nodes[1261].latitude, graph1.nodes[1261].longitude);

    return EXIT_SUCCESS;
}

