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
  g.file_to_stringRoute("/workspaces/CS225/teamZero/data/test_routes.csv");
  
  REQUIRE(g.getRoutesSize() == 2);
  REQUIRE( g.getRoutesVector() == 4);
  //assert length of each row
  
  //assert 
}

TEST_CASE("reading in airports data") {
    graph g;
    g.file_to_stringAirport("/workspaces/CS225/teamZero/data/test_airport.csv");
// assert size 
    REQUIRE( g.getAirportSize() == 3 );
    REQUIRE( g.getAirportRowSize(1) == 4);
    
//assert length of each row 

 
}
