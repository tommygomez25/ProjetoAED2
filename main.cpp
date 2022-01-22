#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <dirent.h>
#include <cmath>
#include "Graph.h"
#include <map>
#include <set>

using namespace std;

struct Line{
    string code;
    string name;
public:
    Line(const string &code, const string &name){
        this->code = code;
        this->name = name;
    }
};

struct Stop{
    string code;
    string name;
    string zone;
    double latitude;
    double longitude;
public:
    Stop(const string &code, const string &name,const string &zone,const double &latitude, const double &longitude){
        this->code = code;
        this->name = name;
        this->zone = zone;
        this->latitude = latitude;
        this-> longitude = longitude;
    }
};

static double haversine(double lat1, double lon1,
                        double lat2, double lon2)
    {
        // distance between latitudes
        // and longitudes
        double dLat = (lat2 - lat1) *
                      M_PI / 180.0;
        double dLon = (lon2 - lon1) *
                      M_PI / 180.0;

        // convert to radians
        lat1 = (lat1) * M_PI / 180.0;
        lat2 = (lat2) * M_PI / 180.0;

        // apply formulae
        double a = pow(sin(dLat / 2), 2) +
                   pow(sin(dLon / 2), 2) *
                   cos(lat1) * cos(lat2);
        double rad = 6371;
        double c = 2 * asin(sqrt(a));
        return rad * c;
    }

vector<string> filesVector(){
    vector<string> v1;
    DIR *pDIR;
    struct dirent *entry;
    if( pDIR=opendir("C:\\Users\\jffma\\CLionProjects\\ProjetoAED2\\dataset") ){
        while(entry = readdir(pDIR)){
            if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 ){
                v1.push_back(entry->d_name);
            }
        }
        closedir(pDIR);
    }

    return v1;
}

vector<vector<string>> readFile(string filename){
    fstream file;
    file.open(filename);
    string line, value;
    vector<string> row;
    vector<vector<string>> content;
    while(getline(file, line)){
        stringstream str(line);
        row.clear();
        while(getline(str, value, ',')){
            row.push_back(value);
        }
        content.push_back(row);

    }
    return content;
}

vector<string> readFileTony(const string &filename){
    ifstream file;
    file.open(filename);
    string line, value;
    getline(file,line);
    int num = stoi(line);
    vector<string> stops(num);
    unsigned int index = 0;
    while(getline(file, line)){
        stops[index] = line;
        index++;
    }
    return stops;
}

vector<Line> readLinesTony(){
    vector<Line> lines;
    ifstream file;
    file.open("lines.csv");
    string lineCode, lineName, line;
    getline(file,line);

    istringstream iss;

    while(getline(file,line,',')){
        istringstream iss(line);
        iss >> lineCode;
        iss >> lineName;
        lines.push_back(Line(lineCode,lineName));
    }
    return lines;
}

vector<Stop> readStops(){
    vector<Stop> stops;
    ifstream file;
    file.open("stops.csv");
    string stopCode, stopName, stopZone, stopLatitude, stopLongitude, line;
    getline(file,line);
    string value;
    vector<string> aux;
    while(getline(file, line)){
        stringstream str(line);
        while(getline(str, value, ',')){
            aux.push_back(value);
        }
        stops.push_back(Stop(aux[0],aux[1],aux[2],stod(aux[3]),stod(aux[4])));
        aux.clear();
    }

/*    while(getline(file,line)){
        istringstream iss(line);
        iss >> stopCode;
        iss >> stopName;
        iss >> stopZone;
        iss >> stopLatitude;
        iss >> stopLongitude;
        stops.push_back(Stop(stopCode,stopName,stopZone,stof(stopLatitude),stof(stopLongitude)));
    }*/
    return stops;

}

int getIndexStops(string stop, map<string,int> stops){
    for(auto s : stops){
        if(stop == s.first)
            return s.second;
    }
    return -1;
}


int main() {
    vector<string> v1 = filesVector();
    vector<vector<string>> fred;
    vector<string> codLines;

    //--------//------//

    vector<Line> lines = readLinesTony();
    vector<Stop> stops = readStops();
    Graph graph1(2487,true);
    map<string,int> stopsIndex;

    for(unsigned int i = 1; i < graph1.getNodes().size(); i++){
        graph1.nodes[i].code = stops[i-1].code;
        graph1.nodes[i].stop = stops[i-1].name;
        graph1.nodes[i].zone = stops[i-1].zone;
        graph1.nodes[i].latitude = stops[i-1].latitude;
        graph1.nodes[i].longitude = stops[i-1].longitude;
        stopsIndex.insert(make_pair(stops[i-1].code,i));
    }

    for(auto filename: v1){
        vector<string> lineStops;
        if(filename != "stops.csv" && filename != "lines.csv" && filename != "ProjetoAED2.exe" && !readFileTony(filename).empty()){
            lineStops = readFileTony(filename);
            cout << "Filename: " << filename << endl;
            stringstream cod(filename);
            string code;
            getline(cod, code, '_');
            getline(cod, code, '_');
            codLines.push_back(code);

            for(unsigned int i = 0; i < lineStops.size() - 1; i++) {
                int stopIndexParent = getIndexStops(lineStops[i], stopsIndex);
                int stopIndexChild = getIndexStops(lineStops[i + 1], stopsIndex);

                double distance = haversine(stops[stopIndexParent].latitude,
                                         stops[stopIndexParent].longitude,
                                         stops[stopIndexChild].latitude,
                                         stops[stopIndexChild].longitude);

                cout << "distance " << i << ": " << distance << endl;

                graph1.addEdge(stopIndexParent, stopIndexChild, code, distance);
            }

        }
    }

/*

    for (int i = 0; i< v1.size(); i++){
        if(v1[i] != "stops.csv" && v1[i] != "lines.csv" && v1[i] != "ProjetoAED2.exe"){
            if(!readFileTony(v1[i]).empty()){
                fred.push_back(readFileTony(v1[i]));
                stringstream cod(v1[i]);
                string code;
                getline(cod, code, '_');
                getline(cod, code, '_');
                codLines.push_back(code);
            }

        }
    }
    map<string,int> stops;
    vector<vector<string>> content = readFile("stops.csv");

    // Criação do Graph
    Graph graph(2487, true);
    int i = 1;
    for(int j = 1; j < graph.nodes.size(); j++){
        graph.nodes[j].code = content[i][0];
        graph.nodes[j].stop = content[i][1];
        graph.nodes[j].zone = content[i][2];
        graph.nodes[j].latitude = stof(content[i][3]);
        graph.nodes[j].longitude = stof(content[i][4]);
        stops.insert(make_pair(graph.nodes[j].code, i));
        i++;
    }

    for(int i = 0; i < fred.size(); i++){
        for(int j = 0; j < fred[i].size()-1; j++){
            int index = getIndexStops(fred[i][j], stops);
            graph.addEdge(index, getIndexStops(fred[i][j+1],stops), codLines[i]);
        }
    }*/
    vector<string> linhas;
    cout << endl <<graph1.bfs(1, 1263);
    int distance = graph1.bfs(1, 1263);
    int i = 0;
    for(auto a : graph1.nodes[1].adj){
        if(i < distance){
            //tava  a pensar fazer aquilo q disse no grupo
        }
    }
}


