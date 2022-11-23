#include "graph.h"
using namespace std;

//gonna make an empty constructor
graph::graph() {
  
}

//sfo ----> ord
// sfo ----> AER
map<string,vector<pair<string, int>>> graph::getMap() {
  return graph_;
}

void graph::makeGraph() {
// src_code -> <<dest_code, distance><>>
  for (unsigned i = 0; i < routes_.size(); i++) {
    string src = routes_[i][0];
    string dest = routes_[i][2];
    int dist = calculateDist(src, dest);
    if (graph_.find(src) != graph_.end()) {
        graph_.at(src).push_back(make_pair(dest, dist));
    }
    else {
      vector<pair<string, int>> temp;
      temp.push_back(make_pair(dest, dist));
      graph_.insert({src, temp});
    }
  }
  
}

//For testing, we can put in our own routes and airport data and make the expected graph we want to test against
graph::graph(vector<vector<string>> routes, vector<vector<string>> airports) {
  routes_ = routes;
  airports_ = airports;
}

//Gets the longitude and latitude of the aiport source IATA
pair<string, string> graph::getLatLong(string airport_code) {
  for (size_t i = 0; i < airports_.size(); i++) {
    if (airports_.at(i).at(0) == airport_code) {
      return pair<string, string>(airports_.at(i).at(1), airports_.at(i).at(2));
    }
  }
  return pair<string, string>("-1", "-1");
}

//Calculate distance between two airports 
int graph::calculateDist(string src_airport, string dest_airport) {
  pair<string, string> src_latlong = getLatLong(src_airport);
  pair<string, string> dest_latlong = getLatLong(dest_airport);

  // Distance, d = 3963.0 * arccos[(sin(lat1) * sin(lat2)) + cos(lat1) * cos(lat2) * cos(long2 – long1)]
  double distance = 3963.0 * acos((sin(stod(src_latlong.first)) * sin(stod(dest_latlong.first))) + cos(stod(src_latlong.first)) * cos(stod(dest_latlong.first)) * cos(stod(dest_latlong.second) - stod(src_latlong.second)));
  cout << "DISTANCE BETWEEN SFO ORD IS " << distance << endl;
  // return int(distance);
  return 0;
}

//Gets the airport elements in each row
size_t graph::getAirportRowSize(int i) {
  return airports_.at(i).size();
}

//Gets the amount of rows in the airport data
size_t graph::getAirportSize() {
  return airports_.size();
}

string graph::file_to_stringRoute(const string& filename){

ifstream ifs(filename);
  string line; 
  if (ifs.is_open()) {
    while (ifs >> line) {
    size_t pos = line.find("\\N");
    if (pos != string::npos) {
      continue;
    }
    vector<string> temp;
      int k = SplitString(line, ',', temp);
      vector<string> correct_temp;
      for (size_t idx = 2; idx < 6; idx++) {
          correct_temp.push_back(temp.at(idx));
      }
      if (!correct_temp.empty()) {
         routes_.push_back(correct_temp);
       }
    }
    ifs.close();
  }

  for (size_t i = 0; i < routes_.size(); i++) {
    for  (size_t j = 0; j < routes_.at(i).size(); j++) {
      cout << routes_.at(i).at(j) << " ";
    }
        cout<< endl;
  }
  cout << "Routes Size: " << routes_.size() << endl;
  return "";
}
size_t graph::getRoutesSize() {
  return routes_.size();
}

size_t graph::getRoutesVector() {
  return routes_[0].size();
}
 //4,6,7, 8
string graph::file_to_stringAirport(const string& filename){
ifstream ifs(filename);
  string line; 
  if (ifs.is_open()) {
    while (getline(ifs, line)) {
    size_t pos = line.find("\\N");
    if (pos != string::npos) {
      continue;
    }
    vector<string> temp;
      int k = SplitString(line, ',', temp);
 
      vector<string> correct_temp;
      
      for (size_t i = 0; i < temp.size(); i++) {

        if ( i == 6 || i == 7 || i == 8) {
          correct_temp.push_back(temp.at(i));
        }
        if (i == 4) {
          correct_temp.push_back(temp.at(i).substr(1, 3));
        }
       }
       if (!correct_temp.empty()) {
        airports_.push_back(correct_temp);
       }
    }
    ifs.close();
  }

  for (size_t i = 0; i < airports_.size(); i++) {
    for  (size_t j = 0; j < airports_.at(i).size(); j++) {
      cout << airports_.at(i).at(j) << " ";
    }
        cout<< endl;
  }
  cout << "Airport Size: " << airports_.size() << endl;
  return "";
}