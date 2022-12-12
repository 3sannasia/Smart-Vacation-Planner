#pragma once
#include <iostream>
#include <vector>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dijkstra.h"
#include "graph.h"

class mappic
{
public:
    mappic(const string output_file_name);

    ~mappic();

    void drawAirports(graph g, dijkstra d);
    void drawAirport(const std::pair<double, double> coords, cs225::HSLAPixel color);

    std::pair<double, double> convertDouble(std::pair<string, string> str_pair);

    cs225::PNG *getPNG();
    cs225::PNG *png;

    const int map_width = 1160;
    const int map_height = 899;

private:
    const std::string output_file_name;

    const int LEFT_SIDE_LONG = -167;

    cs225::HSLAPixel LIGHT_BLUE = {216, 1, .8, 1};
    cs225::HSLAPixel GREEN = {0, 1, .5};
    cs225::HSLAPixel RED = {120, 1, .25};

    const int AIRPORT_SIZE_MULTIPLIER = 200;

    std::vector<std::pair<double, double>> airport_coords;

    std::pair<int, int> convertCoordsToPixel(double latitude, double longitude);
};
