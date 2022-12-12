#include "graph.h"
using namespace std;

// Empty Constructor
graph::graph()
{
}

// For testing this sets routes and airports
graph::graph(vector<vector<string>> routes, vector<vector<string>> airports)
{
  routes_ = routes;
  airports_ = airports;
}

// Returns graph
map<string, vector<pair<string, int>>> graph::getGraph()
{
  return graph_;
}

// Returns graph
map<string, vector<pair<string, int>>> graph::getMap()
{
  return graph_;
}

// BFS traversal on the graph from starting airport s
void graph::BFS(string s)
{
  queue<string> _queue;

  visited[s] = true;
  _queue.push(s);

  while (!_queue.empty())
  {
    s = _queue.front();
    _queue.pop();

    for (auto adj : graph_[s])
    {
      if (!visited[adj.first])
      {
        visited[adj.first] = true;
        _queue.push(adj.first);
      }
    }
  }
}

// Constructs data using routes and airport data
void graph::makeGraph()
{
  for (unsigned i = 0; i < routes_.size(); i++)
  {
    string src = routes_[i][0];
    string dest = routes_[i][2];
    int dist = calculateDist(src, dest);
    // if long lat not found skip
    if (dist == 0)
    {
      continue;
    }
    if (graph_.find(src) != graph_.end())
    {
      graph_.at(src).push_back(make_pair(dest, dist));
    }
    else
    {
      vector<pair<string, int>> temp;
      temp.push_back(make_pair(dest, dist));
      graph_.insert({src, temp});
    }
  }
}

// Gets the longitude and latitude of the aiport source IATA
pair<string, string> graph::getLatLong(string airport_code)
{
  for (size_t i = 0; i < airports_.size(); i++)
  {
    if (airports_.at(i).at(0) == airport_code)
    {
      return pair<string, string>(airports_.at(i).at(1), airports_.at(i).at(2));
    }
  }
  return pair<string, string>("-1", "-1");
}

// Converts latitude or longitude degrees to radians
long double graph::toRadians(const long double degree)
{
  long double one_deg = (M_PI) / 180;
  return (one_deg * degree);
}

// Calculates and returns the miles between two airports
long int graph::calculateDist(string source, string destination)
{
  pair<string, string> src = getLatLong(source);
  pair<string, string> dest = getLatLong(destination);

  // if long lat of either not found skip
  if ((src.first == "-1" && src.second == "-1") || (dest.second == "-1" && dest.first == "-1"))
  {
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

  // Use R = 3956 for miles
  long double miles_conversion = 3956;

  dist = dist * miles_conversion;
  return (int)dist;
}

// Gets the airport elements in each row
size_t graph::getAirportRowSize(int i)
{
  return airports_.at(i).size();
}

// Get visited map for each airport seen in BFS
map<string, bool> graph::getVisited()
{
  return visited;
}

// Gets the amount of rows in the airport data
size_t graph::getAirportSize()
{
  return airports_.size();
}

// Reads and cleans routes csv and stores necessary data to routes_ vector
string graph::file_to_stringRoute(const string &filename)
{

  ifstream ifs(filename);
  string line;
  if (ifs.is_open())
  {
    while (ifs >> line)
    {
      size_t pos = line.find("\\N");
      if (pos != string::npos)
      {
        continue;
      }
      vector<string> temp;
      int k = SplitString(line, ',', temp);
      vector<string> correct_temp;

      // Stores just the data we need
      for (size_t idx = 2; idx < 6; idx++)
      {
        correct_temp.push_back(temp.at(idx));
      }
      if (!correct_temp.empty())
      {
        routes_.push_back(correct_temp);
      }
    }
    ifs.close();
  }
  return "";
}

// Returns routes vector's size
size_t graph::getRoutesSize()
{
  return routes_.size();
}

// Returns routes vector
size_t graph::getRoutesVector()
{
  return routes_[0].size();
}

// Reads and cleans routes csv and stores necessary data to airports_ vector
string graph::file_to_stringAirport(const string &filename)
{
  ifstream ifs(filename);
  string line;
  if (ifs.is_open())
  {
    while (getline(ifs, line))
    {
      // error checking
      size_t pos = line.find("\\N");
      if (pos != string::npos)
      {
        continue;
      }
      vector<string> temp;
      int k = SplitString(line, ',', temp);

      vector<string> correct_temp;

      for (size_t i = 0; i < temp.size(); i++)
      {
        // storing 4th, 6th, 7th, and 8th indexed values
        if (i == 6 || i == 7 || i == 8)
        {
          correct_temp.push_back(temp.at(i));
        }
        if (i == 4)
        {
          correct_temp.push_back(temp.at(i).substr(1, 3));
        }
      }
      if (!correct_temp.empty())
      {
        airports_.push_back(correct_temp);
      }
    }
    ifs.close();
  }
  return "";
}