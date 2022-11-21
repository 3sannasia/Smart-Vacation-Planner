#include "graph.h"

// graph::graph(string input) {
    
// }

pair<string, string> graph::getLongLat(string IATA) {
  for (size_t i = 0; i < airports_.size(); i++) {
    cout << "IATA THING is " << airports_.at(i).at(0).substr(1, 3) << " " << IATA<< endl;
    if (airports_.at(i).at(0).substr(1, 3) == IATA) {
      return pair<string, string>(airports_.at(i).at(1), airports_.at(i).at(2));
    }
  }
  return pair<string, string>("NOT FOUND", "NOT FOUND");
}

size_t graph::getAirportRowSize(int i) {
  return airports_.at(i).size();
}

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
      routes_.push_back(correct_temp);
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

        if ( i == 4 || i == 6 || i == 7 || i == 8) {
          correct_temp.push_back(temp.at(i));
        }
        
       }
       airports_.push_back(correct_temp);
    }
    ifs.close();
  }

  for (size_t i = 0; i < airports_.size(); i++) {
    for  (size_t j = 0; j < airports_.at(i).size(); j++) {
      cout << airports_.at(i).at(j) << " ";
    }
        cout<< endl;
  }
  cout << "Airport Size: " << routes_.size() << endl;
  return "";
}