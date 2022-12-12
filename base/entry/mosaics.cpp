#include <iostream>
#include <set>
#include <vector>
#include "graph.h"
#include "util/util.h"
#include "dijkstra.h"
#include "mappic.h"

using namespace std;

// pass destination and source airport IATA codes
int main(int argc, char **argv)
{
    // making graph object
    graph g;

    // reading in csv files
    g.file_to_stringRoute("../routes_data.csv");
    g.file_to_stringAirport("../airports.csv");

    g.makeGraph();

    // calling dijkstra's algorithm on graph to find shortest paths
    dijkstra dij(g.getMap(), argv[1], argv[2]);
    dij.dijkstra_distance();

    // drawing source, destination, and possible stops to ../empty_map.png
    mappic map_out("../empty_map.png");
    map_out.drawAirports(g, dij);

    return 0;
}
