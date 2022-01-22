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
        stops.push_back(Stop(aux[0],aux[1],aux[2],stod(aux[3]),stod(aux[4])));
        aux.clear();
    }

    return stops;

}

vector<Line> readLinesTony() {
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

        for (unsigned int i =0 ; i < content.size();i++){
            lines.push_back(Line(content[i][0],content[i][1]));
        }

        return lines;
    }
}

#endif //PROJETOAED2_FILES_H
