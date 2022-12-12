#include "mappic.h"
#include "cmath"

//  Create constructor that takes in file name to output coloring to.

mappic::mappic(const std::string output) : output_file_name(output)
{
    this->png = new cs225::PNG(1160, 899);
    png->readFromFile("../globe.png");
}

// destructor
mappic::~mappic()
{
    delete this->png;
}

// helper function of draw airport, takes in latitude and longitude and calculates scaled coordinate
// for map image
std::pair<int, int> mappic::convertCoordsToPixel(double latitude, double longitude)
{

    if (longitude < 0 || longitude > 180 || latitude < 0 || latitude > 90)
    {
        return std::pair<int, int>(-1, -1);
    }

    int x = ((longitude * map_width) / 360) + 50;
    if (longitude < LEFT_SIDE_LONG)
    {
        x = this->map_width + x;
    }

    int y = ((latitude * map_height) / 180) + 100;

    return std::pair<int, int>(x, y);
}

/**
 Takes in graph and dijkstra and draws source, destination, and stops of airports in shortest paths
 */

void mappic::drawAirports(graph g, dijkstra d)
{

    for (auto x : d.get_shortest_paths())
    {
        const std::pair<double, double> coords_shortest_path = convertDouble(g.getLatLong(x.first));
        drawAirport(coords_shortest_path, LIGHT_BLUE);
    }
    const std::pair<double, double> coords_dest = convertDouble(g.getLatLong(d.destination));
    drawAirport(coords_dest, GREEN);
    const std::pair<double, double> coords_source = convertDouble(g.getLatLong(d.source));
    drawAirport(coords_source, RED);

    png->writeToFile(output_file_name);
}

// Converts latitude and longitude to double
std::pair<double, double> mappic::convertDouble(std::pair<string, string> str_pair)
{
    return std::pair<double, double>(stod(str_pair.first), stod(str_pair.second));
}

/**
 Draws airport onto screen. Helper function of drawAirports, takes in color and coordinates to draw on.
 Draws it as a square with Color color if in valid coordinates
 */
void mappic::drawAirport(const std::pair<double, double> coords, cs225::HSLAPixel color)
{

    auto pixel_coords = convertCoordsToPixel(coords.first, coords.second);
    if (pixel_coords.first == -1)
    {
        return;
    }

    for (int x = std::max(0, pixel_coords.first - (this->map_width / AIRPORT_SIZE_MULTIPLIER)); x < std::min(this->map_width, pixel_coords.first + (this->map_width / AIRPORT_SIZE_MULTIPLIER)); ++x)
    {

        for (int y = std::max(0, pixel_coords.second - (this->map_width / AIRPORT_SIZE_MULTIPLIER)); y < std::min(this->map_height, pixel_coords.second + this->map_width / AIRPORT_SIZE_MULTIPLIER); ++y)
        {

            png->getPixel(x, y).h = color.h;
            png->getPixel(x, y).s = color.s;
            png->getPixel(x, y).l = color.l;
            png->getPixel(x, y).a = color.a;
        }
    }
}

// Returns PNG of map

cs225::PNG *mappic::getPNG()
{
    return this->png;
}
