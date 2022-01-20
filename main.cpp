#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <dirent.h>
#include "Graph.h"
#include <map>

using namespace std;
//namespace fs = std::filesystem;

vector<string> filesVector();

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

vector<string> readFileTony(string filename){
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
    for (int i = 0; i< v1.size(); i++){
        if(v1[i] != "stops.csv" && v1[i] != "lines.csv" && v1[i] != "ProjetoAED2.exe"){
            if(!readFileTony(v1[i]).empty())
                fred.push_back(readFileTony(v1[i]));}
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
            graph.addEdge(index, getIndexStops(fred[i][j+1],stops));
        }
    }

    for(auto stops: graph.nodes[2174].adj){
        cout << stops.dest << endl;
    }

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