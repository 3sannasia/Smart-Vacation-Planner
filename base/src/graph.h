#pragma once
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <fenv.h>
#include <signal.h>
#include <vector>
#include "/workspaces/cs225/teamZero/base/lib/util/util.h"
using namespace std;
class graph {
public:

//graph(string input);
void routes(string file);
string file_to_string(const string& filename);

private:
map<string,pair<string, int>> map_;
map<pair<string, string>, pair<string, string>> routes_data;
vector<vector<string>> routes_;
};
