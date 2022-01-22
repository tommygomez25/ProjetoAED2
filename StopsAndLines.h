//
// Created by maysa on 22/01/2022.
//

#ifndef PROJETOAED2_STOPSANDLINES_H
#define PROJETOAED2_STOPSANDLINES_H

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


int getIndexStops(string stop, map<string,int> stops){
    for(auto s : stops){
        if(stop == s.first)
            return s.second;
    }
    return -1;
}

//find closest stop to a location
Stop closestStop(double lat, double lon,const vector<Stop> &stops){
    double min = INT_MAX;
    Stop stop1("","","",0,0);
    for (auto stop : stops){
        if (haversine(lat,lon,stop.latitude,stop.longitude) < min){
            min = haversine(lat,lon,stop.latitude,stop.longitude);
            stop1 = stop;
        }
    }
    return stop1;
}



#endif //PROJETOAED2_STOPSANDLINES_H
