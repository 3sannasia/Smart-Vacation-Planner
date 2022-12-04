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
    auto cur_apt = graph_[source];
    int stops = 0;
    while (shortest_paths.size() != 3) {
        bool direct_found = false;
        for (unsigned int i = 0; i < cur_apt.size(); i++) {
            if (cur_apt.at(i).first == destination) {
                shortest_paths.push_back(pair<string, int>(destination, stops));
                direct_found = true;
            } 
            //else if (cur_apt.at(i).first == destination)
        }
        if (direct_found == false) {
            
        }
        
    }


}

vector<pair<string, int>> dijkstra::get_shortest_paths() {
    return shortest_paths;
}

// vector<int> get_three_shortest_path() {
    
// }

// sfo -> ord , lAX
// <ord, 
// to get third we must go into ord 


// ord -> sfo, 30, la, 6, dal, 8
// la _> ord

// user: sfo, ord 
// sfo: 
// < ord,9> <_, _> < _,_> <_, _> 