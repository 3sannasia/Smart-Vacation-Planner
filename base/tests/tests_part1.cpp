#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <locale>

#include "cs225/point.h"





// https://stackoverflow.com/a/217605
// trim from end (in place)


// TEST_CASE("KDTree::findNearestNeighbor (3D), testing that left recursion does not include the root", "[weight=1][part=1]") {
//   double coords[10][3] = {
//     {5, 3, 1}, {3, 1, 10}, {2, 0, 8}, {4, 3, 0}, {0, 2, 9},
//     {10, 10, 10}, {11, 11, 11}, {12, 12, 12}, {13, 13, 13}, {14, 14, 14}
//   };
//   double targetCoords[3] = {1, 1, 9};
//   double expectedCoords[3] = {0, 2, 9};

//   vector<Point<3>> points;
//   for (int i = 0; i < 10; ++i)
//       points.push_back(Point<3>(coords[i]));
//   Point<3> target(targetCoords);
//   Point<3> expected(expectedCoords);

//   KDTree<3> tree(points);
//   int size = 10;
//   int K = 3;
//   std::string fname = "test_result_kdtree_"+to_string(K)+"_"+to_string(size)+".kd";
//   writeKdTreeToFile(tree,fname);
//   compareBinaryFiles(fname, "../tests/expected_kdtree_"+to_string(K)+"_"+to_string(size)+".kd" );

//   REQUIRE( tree.findNearestNeighbor(target) == expected );
// }
