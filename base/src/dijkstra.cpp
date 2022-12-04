#include "dijkstra.h"
using namespace std;

dijkstra::dijkstra( map<string,vector<pair<string, int>>> graph, string src, string dest) {
    graph_ = graph;
    source = src;
    destination = dest;
}
void dijkstra::dijkstra_distance() { 
    //Only place in this vector what is DIRECTLY connected to the DESTINATION
    // shortest_paths.push_back(pair<string, int>(ABC, 2)); pushback airport and number of stops
    if (!graph_.count(source)) { //error checking
        std::cout << "doesnt exit" << std::endl;
        shortest_paths.clear();
        return;
    }
    auto cur_apts = graph_[source];
    int stops = 0;
    bool found = false;
    int min = 0;
    while (shortest_paths.size() != 3) {
        if (find_path(stops, cur_apts) != pair<string, int>("", 0)) {
            shortest_paths.push_back(find_path(stops, cur_apts));
            found = true;
        }
        stops++;
        for (unsigned int i = 0; i < cur_apts.size(); i++) {
            if (cur_apts.at(i).first == destination) {
                continue;
            }
            if (find_path(stops, graph_[cur_apts.at(i).first]) != pair<string, int>("", 0)) {
                shortest_paths.push_back(find_path(stops, cur_apts));
            }
        }
        while (cur_apts.at(min).first != destination) {
            min++;
        }
        cur_apts = graph_[cur_apts.at(cur).first];
    }
}
pair<string, int> dijkstra::find_path(int stops, std::vector<std::pair<std::string, int>> airports) {
    for (unsigned int i = 0; i < airports.size(); i++) {
            if (airports.at(i).first == destination) {
                return pair<string, int>(destination, stops);
            } 
    }
    return pair<string, int>("", 0);
}

vector<pair<string, int>> dijkstra::get_shortest_paths() {
    return shortest_paths;
} 
// sfo -> ord , lAX
// <ord, 
// to get third we must go into ord 


// ord -> sfo, 30, la, 6, dal, 8
// la _> ord

// user: sfo, ord 
// sfo: 
// < ord,9> <_, _> < _,_> <_, _> 