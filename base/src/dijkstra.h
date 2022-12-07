#pragma once
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <fenv.h>
#include <signal.h>
#include <vector>
#include <math.h>
#include <queue>

using namespace std;


class dijkstra {

    public:
        dijkstra( map<string,vector<pair<string, int>>> graph, string src, string dest);
        void dijkstra_distance();
        vector<pair<string, int>> get_shortest_paths();
        pair<string, int> find_path(int stops, std::vector<std::pair<std::string, int>> airports, string source);
        string source;
        string destination;
    private:
        map<string,vector<pair<string, int>>> graph_;
        vector<pair<string, int>> shortest_paths;
};