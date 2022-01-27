#include <iostream>
#include <fstream>
#include <sstream>
#include "graph.h"
#include <map>
#include "Files.h"

using namespace std;

void printPath(list<tuple<string, string, string>> path) {
    for (auto it = path.begin(); it != path.end(); it++) {
        if (it == path.begin()) {
            cout << get<0>(*it) << "(" << get<1>(*it) << ")" << " -> ";
        } else if ((*it) == path.back()) {
            cout << get<2>(*it) << " - " << get<0>(*it) << "(" << get<1>(*it) << ")";
        } else {
            cout << get<2>(*it) << " - " << get<0>(*it) << "(" << get<1>(*it) << ")" << " -> ";
        }
    }
}

void clearEdges(graph &graph) {
    for (int i = 1; i <= graph.n; i++) {
        graph.nodes[i].adj.clear();
    }
}

void addClosestStops(graph &graph, int v, double userDistance) {
    for (int r = 1; r <= graph.n; r++) graph.nodes[r].visited = false;
    queue<int> q;
    q.push(v);
    graph.nodes[v].visited = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        auto adjacentStops = graph.nodes[u].adj;

        for (int stop = 1; stop <= graph.n; stop++) {
            bool found = false;
            for (const auto& adjacent: adjacentStops) { // para nao criar edges repetidas
                if (adjacent.dest == stop) found = true;
            }
            if (u == stop || found) continue;

            double distance = haversine(graph.nodes[u].latitude, graph.nodes[u].longitude, graph.nodes[stop].latitude,
                                        graph.nodes[stop].longitude);

            if (distance <= userDistance) {
                if (graph.nodes[u].code == "O0" || graph.nodes[u].code == "D0")
                    cout << graph.nodes[stop].code;
                graph.addEdge(u, stop, "a pé", 1.0);
            }
        }

        for (const auto& e: graph.nodes[u].adj) {
            int w = e.dest;
            if (!graph.nodes[w].visited) {
                q.push(w);
                graph.nodes[w].visited = true;
            }
        }
    }
}

void createEdgesForMinChanges(const string& direction, const vector<Stop> &stops, const map<string, int> &stopsIndex, graph &graph,
                         int dayJourney) {

    vector<Line> lines = readLines();
    string line;
    for (auto & i : lines) {
        ifstream file;
        string lineCode = i.code;
        if (dayJourney == 0) {
            if (lineCode == "1M" || lineCode == "3M" || lineCode == "4M" || lineCode == "5M" || lineCode == "7M" ||
                lineCode == "8M" || lineCode == "9M" || lineCode == "10M" || lineCode == "11M" || lineCode == "12M" ||
                lineCode == "13M")
                continue;
        } else {
            if (lineCode != "1M" && lineCode != "3M" && lineCode != "4M" && lineCode != "5M" && lineCode != "7M" &&
                lineCode != "8M" && lineCode != "9M" && lineCode != "10M" && lineCode != "11M" && lineCode != "12M" &&
                lineCode != "13M")
                continue;
        }

        file.open("line_" + lineCode + "_" + direction + ".csv");
        getline(file, line); // para ignorar a primeira linha
        vector<string> lineCodes; // todos os códigos dos STOPS dessa linha

        while (getline(file, line)) {
            lineCodes.push_back(line);
        }

        if (lineCodes.empty()) continue;

        for (unsigned j = 0; j < lineCodes.size() - 1; j++) {
            int stopIndexParent = getIndexStops(lineCodes[j], stopsIndex);
            int stopIndexChild = getIndexStops(lineCodes[j + 1], stopsIndex);
            double distance = 0.0;
            graph.addEdge(stopIndexParent, stopIndexChild, lineCode, distance);
        }
    }
}

void createEdgesForMinDistance(const string& direction, const vector<Stop> &stops, const map<string, int> &stopsIndex, graph &graph,
                          int dayJourney) {

    vector<Line> lines = readLines();
    string line;
    for (auto & i : lines) {
        ifstream file;
        string lineCode = i.code;
        if (dayJourney == 0) {
            if (lineCode == "1M" || lineCode == "3M" || lineCode == "4M" || lineCode == "5M" || lineCode == "7M" ||
                lineCode == "8M" || lineCode == "9M" || lineCode == "10M" || lineCode == "11M" || lineCode == "12M" ||
                lineCode == "13M")
                continue;
        } else {
            if (lineCode != "1M" && lineCode != "3M" && lineCode != "4M" && lineCode != "5M" && lineCode != "7M" &&
                lineCode != "8M" && lineCode != "9M" && lineCode != "10M" && lineCode != "11M" && lineCode != "12M" &&
                lineCode != "13M")
                continue;
        }
        file.open("line_" + lineCode + "_" + direction + ".csv");
        getline(file, line); // para ignorar a primeira linha
        vector<string> lineCodes; // todos os códigos dos STOPS dessa linha

        while (getline(file, line)) {
            lineCodes.push_back(line);
        }

        if (lineCodes.empty()) continue;

        for (unsigned j = 0; j < lineCodes.size() - 1; j++) {
            int stopIndexParent = getIndexStops(lineCodes[j], stopsIndex);
            int stopIndexChild = getIndexStops(lineCodes[j + 1], stopsIndex);
            double distance = haversine(stops[stopIndexParent - 1].latitude, stops[stopIndexParent - 1].longitude,
                                        stops[stopIndexChild - 1].latitude, stops[stopIndexChild - 1].longitude);
            graph.addEdge(stopIndexParent, stopIndexChild, lineCode, distance);
        }
    }
}

void createEdgesForMinZone(const string& direction, const vector<Stop> &stops, const map<string, int> &stopsIndex, graph &graph, int dayJourney) {

    vector<Line> lines = readLines();
    string line;
    for (auto & i : lines) {
        ifstream file;
        string lineCode = i.code;
        if (dayJourney == 0) {
            if (lineCode == "1M" || lineCode == "3M" || lineCode == "4M" || lineCode == "5M" || lineCode == "7M" ||
                lineCode == "8M" || lineCode == "9M" || lineCode == "10M" || lineCode == "11M" || lineCode == "12M" ||
                lineCode == "13M")
                continue;
        } else {
            if (lineCode != "1M" && lineCode != "3M" && lineCode != "4M" && lineCode != "5M" && lineCode != "7M" &&
                lineCode != "8M" && lineCode != "9M" && lineCode != "10M" && lineCode != "11M" && lineCode != "12M" &&
                lineCode != "13M")
                continue;
        }
        file.open("line_" + lineCode + "_" + direction + ".csv");
        getline(file, line); // para ignorar a primeira linha
        vector<string> lineCodes; // todos os códigos dos STOPS dessa linha

        while (getline(file, line)) {
            lineCodes.push_back(line);
        }

        if (lineCodes.empty()) continue;

        for (unsigned j = 0; j < lineCodes.size() - 1; j++) {
            int stopIndexParent = getIndexStops(lineCodes[j], stopsIndex);
            int stopIndexChild = getIndexStops(lineCodes[j + 1], stopsIndex);
            double distance = 0;

            if (stops[stopIndexParent - 1].zone != stops[stopIndexChild - 1].zone &&
                !stops[stopIndexParent - 1].zone.empty()) {
                distance = 1.0;
            }
            graph.addEdge(stopIndexParent, stopIndexChild, lineCode, distance);
        }
    }
}

void getLocalStop(double localLatitude, double localLongitude, graph &graph1, map<string, int> &stopsIndex, bool origin) {

    graph1.n += 1;
    if (origin) {
        graph::Node node = {list<graph::Edge>(),0,0,false,"Origin","O0"," ",localLatitude,localLongitude,""};
        graph1.nodes.push_back(node);
        stopsIndex.insert(make_pair("O0", graph1.n));

    } else {
        graph::Node node = {list<graph::Edge>(),0,0,false,"Destination","D0"," ",localLatitude, localLongitude,""};
        graph1.nodes.push_back(node);
        stopsIndex.insert(make_pair("D0", graph1.n));
    }
}

void addClosestStopsIfDistance(graph &graph,float userDistance){
    if (userDistance > 0.0){
        addClosestStops(graph,1,userDistance);
    }
}


int main() {

    vector<Stop> stops = readStops();
    graph graph1(2487, true);
    string line;

    map<string, int> stopsIndex;

    // adicionar os nós ao graph , cada nó representa uma paragem
    for (unsigned int i = 1; i < graph1.getNodes().size(); i++) {
        graph1.nodes[i].code = stops[i - 1].code;
        graph1.nodes[i].stop = stops[i - 1].name;
        graph1.nodes[i].zone = stops[i - 1].zone;
        graph1.nodes[i].latitude = stops[i - 1].latitude;
        graph1.nodes[i].longitude = stops[i - 1].longitude;
        stopsIndex.insert(make_pair(stops[i - 1].code, i));
    }

    int option;
    float userDistance;
    string dep, arrival;
    int depIndex, arrivalIndex;
    int dayJourney;
    double depLatitude, depLongitude, destLatitude, destLongitude;
    do {
        cout << endl << "Deseja inserir coordenadas de origem ou paragem? (c/p)";
        char decision;
        cin >> decision;
        if (decision == 'p') {
            cout << endl << "Qual a paragem de partida? ";
            cin >> dep;
        }
        if (decision == 'c') {
            cout << endl << "Qual a latitude de partida? ";
            cin >> depLatitude;
            cout << endl << "Qual a longitude de partida? ";
            cin >> depLongitude;
            getLocalStop(depLatitude, depLongitude, graph1, stopsIndex, true);
            dep = "O0";
        }

        cout << endl << "Deseja inserir coordenadas de destino ou paragem? (c/p)" ;
        char decision2;
        cin >> decision2;
        if (decision2 == 'p') {
            cout << endl << "Qual a paragem de destino? ";
            cin >> arrival;
        }
        if (decision2 == 'c') {
            cout << endl << "Qual a latitude de destino? ";
            cin >> destLatitude;
            cout << endl << "Qual a longitude de destino? ";
            cin >> destLongitude;
            getLocalStop(destLatitude, destLongitude, graph1, stopsIndex, false);
            arrival = "D0";
        }
        depIndex = getIndexStops(dep, stopsIndex);
        arrivalIndex = getIndexStops(arrival, stopsIndex);

        cout << endl << "Qual a distancia maxima entre paragens que esta disposto a andar a pe? (em kms) ";
        cin >> userDistance;
        cout << endl << "E uma viagem diurna ou noturna? (0/1) ";
        cin >> dayJourney;

        cout << endl << "1 - Menor numero de paragens" << endl << "2 - Menor distancia" << endl
             << "3 - Menos mudancas de autocarro" << endl;
        cout << "4 - Mais barato" << endl;
        cout << "0 - Exit" << endl;

        cout << endl << "Escolha uma opcao: ";

        clearEdges(graph1);
        cin >> option;
        list<tuple<string, string, string>> path;
        switch (option) {
            case 1:
                createEdgesForMinChanges("0", stops, stopsIndex, graph1, dayJourney);
                createEdgesForMinChanges("1", stops, stopsIndex, graph1, dayJourney);
                addClosestStopsIfDistance(graph1,userDistance);
                path = graph1.bfs_path(depIndex, arrivalIndex);
                if(!path.empty())
                    printPath(path);
                else
                    cout << "Nao ha nenhum caminho possivel com a distancia a pe fornecida, tente com uma distancia maior";
                break;
            case 2:
                createEdgesForMinDistance("0", stops, stopsIndex, graph1, dayJourney);
                createEdgesForMinDistance("1", stops, stopsIndex, graph1, dayJourney);
                addClosestStopsIfDistance(graph1,userDistance);
                path = graph1.dijkstra_path_minDistance(depIndex, arrivalIndex);
                if(!path.empty())
                    printPath(path);
                else
                    cout << "Nao ha nenhum caminho possivel com a distancia a pe fornecida, tente com uma distancia maior";
                break;
            case 3:
                createEdgesForMinChanges("0", stops, stopsIndex, graph1, dayJourney);
                createEdgesForMinChanges("1", stops, stopsIndex, graph1, dayJourney);
                addClosestStopsIfDistance(graph1,userDistance);
                path = graph1.dijkstra_path_minChanges(depIndex, arrivalIndex);
                if(!path.empty())
                    printPath(path);
                else
                    cout << "Nao ha nenhum caminho possivel com a distancia a pe fornecida, tente com uma distancia maior";
                break;
            case 4:
                createEdgesForMinZone("0", stops, stopsIndex, graph1, dayJourney);
                createEdgesForMinZone("1", stops, stopsIndex, graph1, dayJourney);
                addClosestStopsIfDistance(graph1,userDistance);
                path = graph1.dijkstra_path_minZones(depIndex, arrivalIndex);
                if(!path.empty())
                    printPath(path);
                else
                    cout << "Nao ha nenhum caminho possivel com a distancia a pe fornecida, tente com uma distancia maior";
                break;

        }
        cout << endl<< "------" << endl;
        if (decision == 'c') {
            graph1.nodes.pop_back();
            graph1.n -= 1;
        }
        if (decision2 == 'c') {
            graph1.nodes.pop_back();
            graph1.n -= 1;
        }
    } while (option != 0);

    return EXIT_SUCCESS;
}

