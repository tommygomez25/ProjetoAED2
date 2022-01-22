#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include<dirent.h>
#include <vector>
#include "Graph.h"

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


int main() {
    vector<string> v1 = filesVector();
    vector<vector<vector<string>>> fred;
    for (int i = 0; i< v1.size(); i++){
        fred.push_back(readFile(v1[i]));
    }
    vector<vector<string>> content = readFile("stops.csv");
    Graph graph(2487, true);
    int i = 0;
    for(auto &node : graph.nodes){
        node.code = content[i][0];
        node.stop = content[i][1];
        node.zone = content[i][2];
        node.latitude = stof(content[i][3]);
        node.longitude = stof(content[i][4]);
        i++;
    }
    for(int i = 0; i < graph.nodes.size(); i++){
        cout << graph.nodes[i].stop << endl;
    }




    /for (const auto & entry : fs::directory_iterator()){
        cout << entry.path() << endl;
    }
    return 0;/
}
vector<string> filesVector(){
    vector<string> v1;
    DIR *pDIR;
    struct dirent *entry;
    if( pDIR=opendir("dataset") ){
        while(entry = readdir(pDIR)){
            if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 ){
                v1.push_back(entry->d_name);
            }
        }
        closedir(pDIR);
    }
    return v1;
}