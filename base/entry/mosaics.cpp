#include <iostream>
#include <set>
#include <vector>
#include "graph.h"
#include "util/util.h"
#include "dijkstra.h"
#include "mappic.h"


using namespace std;


int main(int argc, char** argv) {
    // pass source, shortest paths, destination
    // graph g;
    // std::cout << g.file_to_stringRoute("../test_routes.csv") << std::endl;
    // std::cout << g.file_to_stringAirport("../test_airport.csv") << std::endl;
    // string cur = "AER";
    // std::cout << "Getting longitude and latitude of AER: "<< g.getLatLong(cur).first << " " <<  g.getLatLong(cur).second << std::endl;
    
    vector<vector<string>> routes = {{"SFO", "1234", "ORD", "1235"}, {"SFO", "1234", "LAX", "1236"}, {"SFO", "1234", "EWR", "1237"}, {"ORD", "1235", "EWR", "1237"} , {"LAX", "1236", "EWR", "1237"}    };
    vector<vector<string>> airports_ = {{"SFO", "38", "122"}, {"ORD", "42", "88"}, {"LAX", "34", "118"}, {"EWR", "34", "119"}};
    graph g(routes, airports_);
    g.makeGraph();
    
    for (unsigned int i = 0; i < g.getMap()["LAX"].size(); i++) {
        std::cout << "last case" <<  g.getMap()["LAX"].at(i).first << std::endl;
    }
    dijkstra dij(g.getMap(), "SFO", "EWR");
    dij.dijkstra_distance();
    auto test =  dij.get_shortest_paths();
    std::cout << dij.source << " " << dij.destination <<std::endl;

    mappic map_out("../World_map_political_ISO.png");    

    map_out.drawAirports(g,dij);


    return 0;
}
