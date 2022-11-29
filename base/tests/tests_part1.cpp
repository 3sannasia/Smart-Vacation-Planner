#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <locale>
#include "graph.h"
#include "cs225/point.h"


TEST_CASE("reading in routes data") {
  graph g;
  g.file_to_stringRoute("../test_routes.csv");
  
  REQUIRE(g.getRoutesSize() == 2);
  REQUIRE( g.getRoutesVector() == 4);
  //assert length of each row
  
  //assert 
}

TEST_CASE("reading in airports data") {
    graph g;
    g.file_to_stringAirport("../test_airport.csv");
// assert size 
    REQUIRE( g.getAirportSize() == 3 );
    REQUIRE( g.getAirportRowSize(1) == 4);
    
//assert length of each row 
}

TEST_CASE("getting longitude and latitude of an airport") {
  graph g;
  g.file_to_stringRoute("../test_routes.csv");
  
  REQUIRE(g.getRoutesSize() == 2);
  REQUIRE( g.getRoutesVector() == 4);

  g.file_to_stringAirport("../test_airport.csv");
  REQUIRE( g.getAirportSize() == 3 );
  REQUIRE( g.getAirportRowSize(1) == 4);

  pair<string, string> expected = pair<string, string>("-6.081689834590001", "145.391998291");
  REQUIRE(g.getLatLong("AER") == expected);
}

TEST_CASE("Calculate distance between two airports") {
  vector<vector<string>> routes = {{"SFO", "1234", "ORD", "1235"} };
  vector<vector<string>> airports_ = {{"SFO", "38", "122"}, {"ORD", "42", "88"}};
  
  graph g(routes, airports_);

  REQUIRE(g.getRoutesSize() == 1);
  REQUIRE( g.getAirportSize() == 2);
  
  g.makeGraph();
  vector<pair<string, int>> expected;
  expected.push_back(make_pair("ORD", 1807));
  REQUIRE(expected.size() == 1);

  REQUIRE(g.getMap()["SFO"].at(0).second == 1807);
}

TEST_CASE("simple graph - 1 to 1 src to destination") {
  vector<vector<string>> routes = {{"SFO", "1234", "ORD", "1235"} };
  vector<vector<string>> airports_ = {{"SFO", "38", "122"}, {"ORD", "42", "88"}};
  
  graph g(routes, airports_);

  REQUIRE(g.getRoutesSize() == 1);
  REQUIRE( g.getAirportSize() == 2);
  
  g.makeGraph();
  vector<pair<string, int>> expected;
  expected.push_back(make_pair("ORD", 1807));
  REQUIRE(expected.size() == 1);
  // std::cout << "The size of graph is " << expected.size() << std::endl;

  REQUIRE(g.getMap()["SFO"] == expected);
}


TEST_CASE("simple graph - Multiple destinations from one airport") {
  vector<vector<string>> routes = {{"SFO", "1234", "ORD", "1235"}, {"SFO", "1234", "LAX", "1236"}  };
  vector<vector<string>> airports_ = {{"SFO", "38", "122"}, {"ORD", "42", "88"}, {"LAX", "34", "118"}};
 
  graph g(routes, airports_);

  REQUIRE(g.getRoutesSize() == 2);
  REQUIRE( g.getAirportSize() == 3);
  
  g.makeGraph();

  vector<pair<string, int>> expected ;
  expected.push_back(make_pair("ORD", 1807));
  expected.push_back(make_pair("LAX", 355));


  REQUIRE(g.getMap()["SFO"] == expected);
}


TEST_CASE("simple graph - Multiple destinations from multiple airport") {
  vector<vector<string>> routes = {{"SFO", "1234", "ORD", "1235"}, {"SFO", "1234", "LAX", "1236"},  {"LAX", "1236", "SFO", "1234"}, {"LAX", "1236", "DAL", "1334"} };
  vector<vector<string>> airports_ = {{"SFO", "38", "122"}, {"ORD", "42", "88"}, {"LAX", "34", "118"}, {"DAL", "33", "97"}};
 
  graph g(routes, airports_);

  REQUIRE(g.getRoutesSize() == 4);
  REQUIRE( g.getAirportSize() == 4);
  
  g.makeGraph();

  vector<pair<string, int>> expected_sfo;
  vector<pair<string, int>> expected_lax;

  expected_sfo.push_back(make_pair("ORD", 1807));
  expected_sfo.push_back(make_pair("LAX", 355));

  expected_lax.push_back(make_pair("SFO", 355));
  expected_lax.push_back(make_pair("DAL", 1208));


  REQUIRE(g.getMap()["SFO"] == expected_sfo);

  REQUIRE(g.getMap()["LAX"] == expected_lax);
}


TEST_CASE("bfs traversal - every airport is visited") {
  vector<vector<string>> routes = {{"SFO", "1234", "ORD", "1235"}, {"SFO", "1234", "LAX", "1236"}  };
  vector<vector<string>> airports_ = {{"SFO", "38", "122"}, {"ORD", "42", "88"}, {"LAX", "34", "118"}};
 
  graph g(routes, airports_);
  g.makeGraph();
  g.BFS("SFO");

  for (auto s : g.getGraph()) {
      REQUIRE(g.getVisited()[s.first] == true);
      cout << s.first << endl;
  }
  
  REQUIRE( g.getVisited().size() == g.getGraph().size());
}