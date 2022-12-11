#include "dijkstra.h"
using namespace std;

dijkstra::dijkstra( map<string,vector<pair<string, int>>> graph, string src, string dest) {
    graph_ = graph;
    source = src;
    destination = dest;
}

void dijkstra::dijkstra_distance() {  // for one or two stops
    if (!graph_.count(source)) { //error checking
        std::cout << "doesnt exit" << std::endl;
        shortest_paths.clear();
        return;
    }
    auto current_airports = graph_[source];
    int stops = 0;

    //find direct flights
    if (find_path(stops, current_airports, source) != pair<string, int>("", 0)) {
        std::cout << "enter?" << std::endl;
        shortest_paths.push_back(find_path(stops, current_airports, source));
    }
    stops++;

    //find 1 stop flights  

    for (unsigned int i = 0; i < current_airports.size(); i++) {
        std::cout << source << std::endl;
        if (current_airports.at(i).first == destination) {
                 std::cout << "dont go here" << std::endl;
            continue;
        }

        if (find_path(stops,  graph_[current_airports.at(i).first], current_airports.at(i).first) != pair<string, int>("", 0)) {
            shortest_paths.push_back(find_path(stops, graph_[current_airports.at(i).first], current_airports.at(i).first));
        }
    }

    // find top 3 shortest paths
    auto dist = shortest_paths;
    shortest_paths.clear();
    for (unsigned min = 0; min < 3 && min < dist.size(); min++) {
        
        shortest_paths.push_back(dist[min]);
    }
    
}
pair<string, int> dijkstra::find_path(int stops, std::vector<std::pair<std::string, int>> airports, string source) {
    std::cout << source << std::endl;
    for (unsigned int i = 0; i < airports.size(); i++) {
            if (airports.at(i).first == destination) {
                return pair<string, int>(source , stops);
            } 
    }
    return pair<string, int>("", 0);
}

vector<pair<string, int>> dijkstra::get_shortest_paths() {
    return shortest_paths;
} 