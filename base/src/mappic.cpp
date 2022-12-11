#include "mappic.h"
#include "cmath"

// #include "cs225/Animation.h"

mappic::mappic(const std::string output) : output_file_name(output) {
    this->png = new cs225::PNG(1406,625);
    png->readFromFile("../globe.png");    
   // std::cout << png->readFromFile("./World_map_political_ISO.png") << std::endl; 
}

mappic::~mappic() {
    delete this->png;
}

std::pair<int, int> mappic::convertCoordsToPixel(double latitude, double longitude) {
 
    if (longitude < -180 || longitude > 180 || latitude < -90 || latitude > 90) {
        std::cout << "Warning. Airport with coordinates " << latitude << ", " << longitude << " are invalid and may not print!" << std::endl;
    }
    int x = ((longitude*map_width)/360) - 150;
    if (longitude < LEFT_SIDE_LONG) {
         x = this->map_width + x;
    } 
    //-3 was just trial and error specific to b/w map
    int y =((latitude*map_height)/180) + 100;
    // double imageNorthLat = 59.545457;  // Latitude of the image's northern edge
	// double imageSouthLat = 49.431947;  // Latitude of the image's southern edge

	// double imageWestLong = -11.140137; // Longitude of the image's western edge
	// double imageEastLong = 2.757568;   // Longitude of the image's eastern edge

	// double imageLongPixels = 900;		// Width of the image in pixels
	// double imageLatPixels = 900;		// Height of the image in pixels

	// double pixelsPerLat = imageLatPixels / (imageNorthLat - imageSouthLat);
	// double pixelsPerLong = imageLongPixels / (imageEastLong - imageWestLong);

	// double x = (longitude-imageWestLong) * pixelsPerLong;
	// double y = abs(latitude-imageNorthLat) * pixelsPerLat;
    // std::cout << x << " "<<y<< std::endl;

    // double FE = 180; // false easting
    // double radius = (map_width / (2 * 3.1415926));

    // double latRad = (latitude * 3.1415926) / 180;
    
    // double lonRad = (longitude * 3.1415926) / 180;

    // double x = (lonRad * radius) - 30;
    
    // double yFromEquator = radius * log(tan(3.1415926 / 4 + latRad / 2));
    // double y = (map_height / 2) - yFromEquator;


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
    std::cout << "HERE   " << d.source << " "<< coords_source.first << " " << coords_source.second << std::endl;
    drawAirport(coords_source, RED);
    
    png->writeToFile(output_file_name);
}

void mappic::drawAirport(const std::pair<double, double> coords, cs225::HSLAPixel color) {
   
    auto pixel_coords = convertCoordsToPixel(coords.first, coords.second);
    std::cout << color.h <<" "<< pixel_coords.first << " " << pixel_coords.second << std::endl;
    for (int x = std::max(0, pixel_coords.first - (this->map_width/AIRPORT_SIZE_MULTIPLIER)); x < std::min(this->map_width, pixel_coords.first + (this->map_width/AIRPORT_SIZE_MULTIPLIER)); ++x)  {
         std::cout << "enter" <<std::endl;
        for (int y = std::max(0, pixel_coords.second - (this->map_width/AIRPORT_SIZE_MULTIPLIER)); y < std::min(this->map_height, pixel_coords.second + this->map_width/AIRPORT_SIZE_MULTIPLIER);++y) {
            std::cout << "yuh" << std::endl;
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