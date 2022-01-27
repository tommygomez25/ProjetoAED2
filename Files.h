//
// Created by maysa on 22/01/2022.
//
#include "StopsAndLines.h"


#ifndef PROJETOAED2_FILES_H
#define PROJETOAED2_FILES_H


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
        stops.emplace_back(aux[0],aux[1],aux[2],stod(aux[3]),stod(aux[4]));
        aux.clear();
    }

    return stops;

}

vector<Line> readLines() {
    {
        vector<Line> lines;
        vector<string> row;
        vector<vector<string>> content;
        fstream file("lines.csv", ios::in);
        string lineCode, lineName,lineName2, line,word;
        getline(file,line);

        while(getline(file,line)){
            row.clear();
            stringstream str(line);
            while(getline(str,word,',')){
                row.push_back(word);
            }
            content.push_back(row);
        }

        for (auto & i : content){
            lines.emplace_back(i[0],i[1]);
        }

        return lines;
    }
}

#endif //PROJETOAED2_FILES_H
