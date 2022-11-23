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
    //if long lat not found skip
    if (dist == 0) {
      continue;
    }
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

// Calculate distance between two airports 
// int graph::calculateDist(string src_airport, string dest_airport) {
//   pair<string, string> src_latlong = getLatLong(src_airport);
//   pair<string, string> dest_latlong = getLatLong(dest_airport);
//   // long double src_lat = stod(src_latlong.first) / 57.29577951;
//   // long double src_long = stod(src_latlong.second) / 57.29577951;
//   // long double dest_lat = stod(dest_latlong.first) / 57.29577951;
//   // long double dest_long = stod(dest_latlong.second) / 57.29577951;

//   long double src_lat = stod(src_latlong.first);
//   long double src_long = stod(src_latlong.second);
//   long double dest_lat = stod(dest_latlong.first);
//   long double dest_long = stod(dest_latlong.second);

//   // Distance, d = 3963.0 * arccos[(sin(lat1) * sin(lat2)) + cos(lat1) * cos(lat2) * cos(long2 – long1)]
//   double dist = 3963.0 * acos((sin(src_lat)) * sin(dest_lat)) + cos(src_lat) * cos(dest_lat) * cos(dest_long - src_long);
//   cout << "DISTANCE BETWEEN SFO ORD IS " << distance(src_lat, src_long,dest_lat, dest_long) << endl;
//   // return int(distance);=
//   return 0;
// }

long double graph::toRadians(const long double degree)
{
    long double one_deg = (M_PI) / 180;
    return (one_deg * degree);
}

long int graph::calculateDist(string source, string destination)
{
    pair<string, string> src = getLatLong(source);
    pair<string, string> dest = getLatLong(destination);

    //if long lat of either not found skip
    if ((src.first == "-1" && src.second == "-1") || (dest.second == "-1" && dest.first == "-1")) {
      return 0;
    }

    long double lat1 = toRadians(stod(src.first));
    long double long1 = toRadians(stod(src.second));
    long double lat2 = toRadians(stod(dest.first));
    long double long2 = toRadians(stod(dest.second));
     
    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1;
 
    long double dist = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlong / 2), 2);
 
    dist = 2 * asin(sqrt(dist));

    // Kilometers, R = 6371
    // Use R = 3956 for miles
    long double miles_conversion = 3956;
    
    dist = dist * miles_conversion;
      cout << "DISTANCE BETWEEN SFO ORD IS " << int(dist) << endl;
    return (int)dist;
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