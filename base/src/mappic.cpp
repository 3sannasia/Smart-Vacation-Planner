#include "mappic.h"
#include "cmath"

// #include "cs225/Animation.h"

mappic::mappic(const std::string output) : output_file_name(output) {
    this->png = new cs225::PNG(1160,899);
    png->readFromFile("../globe.png");    
  }

mappic::~mappic() {
    delete this->png;
}

std::pair<int, int> mappic::convertCoordsToPixel(double latitude, double longitude) {
 
    if (longitude < 0 || longitude > 180 || latitude < 0 || latitude > 90) {
        return std::pair<int, int>(-1, -1);
    }
    
    int x = ((longitude*map_width)/360) + 50;
    if (longitude < LEFT_SIDE_LONG) {
         x = this->map_width + x;
    } 

    int y =((latitude*map_height)/180) + 100;

    return std::pair<int, int>(x, y);
}

void mappic::drawAirports(graph g, dijkstra d) {
      
    for (auto x : d.get_shortest_paths()) {
        const std::pair<double, double> coords_shortest_path = convertDouble(g.getLatLong(x.first));
        drawAirport(coords_shortest_path, LIGHT_BLUE);    
    }
    const std::pair<double, double> coords_dest = convertDouble(g.getLatLong(d.destination));
    drawAirport(coords_dest, GREEN);
    const std::pair<double, double> coords_source = convertDouble(g.getLatLong(d.source));
    drawAirport(coords_source, RED);
    
    
    png->writeToFile(output_file_name);
}

void mappic::drawAirport(const std::pair<double, double> coords, cs225::HSLAPixel color) {
   
    auto pixel_coords = convertCoordsToPixel(coords.first, coords.second);
    if (pixel_coords.first == -1) {
        return;
    }
  
    for (int x = std::max(0, pixel_coords.first - (this->map_width/AIRPORT_SIZE_MULTIPLIER)); x < std::min(this->map_width, pixel_coords.first + (this->map_width/AIRPORT_SIZE_MULTIPLIER)); ++x)  {
      
        for (int y = std::max(0, pixel_coords.second - (this->map_width/AIRPORT_SIZE_MULTIPLIER)); y < std::min(this->map_height, pixel_coords.second + this->map_width/AIRPORT_SIZE_MULTIPLIER);++y) {

            png->getPixel(x, y).h = color.h;
            png->getPixel(x, y).s = color.s;
            png->getPixel(x, y).l = color.l;
            png->getPixel(x, y).a = color.a;
        }
    }
}


void mappic::drawFlight(std::pair<double, double> coorda, std::pair<double, double> coordb, cs225::HSLAPixel color) {
    std::pair<int, int> first_pixel = convertCoordsToPixel(coorda.first, coorda.second);
    std::pair<int, int> second_pixel = convertCoordsToPixel(coordb.first, coordb.second);
    if (first_pixel.first > second_pixel.first) {
        std::swap(first_pixel, second_pixel);
    }

    //pseudocode based on https://en.wikipedia.org/wiki/Line_drawing_algorithm
    auto dx = second_pixel.first - first_pixel.first;
    auto dy = second_pixel.second - first_pixel.second;

    for (int x = first_pixel.first; x < second_pixel.first; ++x) {
        int y = first_pixel.second + dy * (x - first_pixel.first) / dx;
        png->getPixel(x - 1, y) = color;
        png->getPixel(x, y) = color;
        png->getPixel(x + 1, y) = color;
    }
}


std::pair<double, double> mappic::convertDouble(std::pair<string, string> str_pair) {
    return std::pair<double, double>(stod(str_pair.first), stod(str_pair.second));
}


void mappic::drawPrebuiltMap(cs225::HSLAPixel route_color = {216, 1, .7, 1}) {

    cs225::HSLAPixel color;
    for (unsigned long f = 0; f < airport_coords.size(); ++f) {
        std::pair<int, int> pixel_coords = convertCoordsToPixel(airport_coords[f].first, airport_coords[f].second);
        if (f == 0) {
            color = RED;
        } else if (f == airport_coords.size() - 1) {
            color = GREEN;
        } else {
            color = LIGHT_BLUE;
        }

        drawAirport(airport_coords[f], color);
    }

    for (unsigned long f = 0; f < this->airport_coords.size() - 1; ++f) {
        drawFlight(airport_coords[f], airport_coords[f + 1], route_color);
    }

    png->writeToFile(output_file_name);
}

cs225::PNG* mappic::getPNG() {
    return this->png;
}
