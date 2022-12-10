#include <iostream>
#include <set>
#include <vector>
#include "graph.h"
#include "util/util.h"
#include "dijkstra.h"
#include "mappic.h"

// #include "maptiles.h"
// #include "mosaiccanvas.h"

// #include "sourceimage.h"
// #include "util/util.h"

using namespace std;

// // using namespace util;
// using namespace cs225;

// void makePhotoMosaic(const string& inFile, const string& tileDir, int numTiles,
//                      int pixelsPerTile, const string& outFile);

// vector<TileImage> getTiles(string tileDir);
// bool hasImageExtension(const string& fileName);

// namespace opts
// {
//     bool help = false;
// }

int main(int argc, char** argv) {
    // pass source, shortest paths, destination
    // graph g;
    // std::cout << g.file_to_stringRoute("../test_routes.csv") << std::endl;
    // std::cout << g.file_to_stringAirport("../test_airport.csv") << std::endl;
    // string cur = "AER";
    // std::cout << "Getting longitude and latitude of AER: "<< g.getLatLong(cur).first << " " <<  g.getLatLong(cur).second << std::endl;
    //TEST 1
    vector<vector<string>> routes = {{"SFO", "1234", "ORD", "1235"}, {"SFO", "1234", "LAX", "1236"}, {"SFO", "1234", "EWR", "1237"}, {"ORD", "1235", "EWR", "1237"} , {"LAX", "1236", "EWR", "1237"}    };
    vector<vector<string>> airports_ = {{"SFO", "38", "122"}, {"ORD", "42", "88"}, {"LAX", "34", "118"}, {"EWR", "40", "74"}};
    graph g(routes, airports_);
    g.makeGraph();
    
    for (unsigned int i = 0; i < g.getMap()["LAX"].size(); i++) {
        std::cout << "last case" <<  g.getMap()["LAX"].at(i).first << std::endl;
    }
    dijkstra dij(g.getMap(), "SFO", "EWR");
    dij.dijkstra_distance();
    auto test =  dij.get_shortest_paths();
    std::cout << dij.source << " " << dij.destination <<std::endl;

    mappic map_out("../empty_map.png");    
    map_out.drawAirports(g,dij);
    
    //TEST 2

    vector<vector<string>> routes2 = {{"ORD", "1234", "SFO", "1235"}, {"ORD", "1234", "LAX", "1236"}, {"ORD", "1234", "EWR", "1237"}, {"SFO", "1235", "EWR", "1237"} , {"LAX", "1236", "EWR", "1237"}    };
    vector<vector<string>> airports_2 = {{"SFO", "38", "122"}, {"ORD", "42", "88"}, {"LAX", "34", "118"}, {"EWR", "40", "74"}};
    graph g2(routes2, airports_2);
    g2.makeGraph();
   
    dijkstra dij2(g2.getMap(), "ORD", "LAX");
    dij2.dijkstra_distance();
    auto test2 =  dij2.get_shortest_paths();
    std::cout << dij2.source << " " << dij2.destination <<std::endl;

    // mappic map_out2("../empty_map.png");    
    // map_out2.drawAirports(g2,dij2);

    return 0;
}


// void makePhotoMosaic(const string& inFile, const string& tileDir, int numTiles,
//                      int pixelsPerTile, const string& outFile)
// {
//     PNG inImage;
//     inImage.readFromFile(inFile);
//     SourceImage source(inImage, numTiles);
//     vector<TileImage> tiles = getTiles(tileDir);

//     if (tiles.empty()) {
//         cerr << "ERROR: No tile images found in " << tileDir << endl;
//         exit(2);
//     }

//     MosaicCanvas::enableOutput = true;
//     MosaicCanvas* mosaic = mapTiles(source, tiles);
//     cerr << endl;

//     if (mosaic == NULL) {
//         cerr << "ERROR: Mosaic generation failed" << endl;
//         exit(3);
//     }

//     PNG result = mosaic->drawMosaic(pixelsPerTile);
//     cerr << "Saving Output Image... ";
//     result.writeToFile(outFile);
//     cerr << "Done" << endl;
//     delete mosaic;
// }

// vector<TileImage> getTiles(string tileDir)
// {
// #if 1
//     if (tileDir[tileDir.length() - 1] != '/')
//         tileDir += '/';

//     vector<string> allFiles = get_files_in_dir(tileDir);
//     sort(allFiles.begin(), allFiles.end());

//     vector<string> imageFiles;
//     imageFiles.reserve(allFiles.size());
//     for (size_t i = 0; i < allFiles.size(); i++)
//         if (hasImageExtension(allFiles[i]))
//             imageFiles.push_back(allFiles[i]);

//     vector<TileImage> images;
//     set<LUVAPixel> avgColors;
//     for (size_t i = 0; i < imageFiles.size(); i++) {
//         cerr << "\rLoading Tile Images... ("
//              << (i + 1) << "/" << imageFiles.size()
//              << ")" << string(20, ' ') << "\r";
//         cerr.flush();
//         PNG png;
//         png.readFromFile(imageFiles.at(i));
//         TileImage next(png);

//         LUVAPixel avg = next.getAverageColor();
//         if (avgColors.count(avg) == 0) {
//             avgColors.insert(avg);
//             images.push_back(next);
//         }
//     }
//     cerr << "\rLoading Tile Images... ("
//          << imageFiles.size() << "/" << imageFiles.size()
//          << ")";
//     cerr << "... " << images.size() << " unique images loaded" << endl;
//     cerr.flush();

//     return images;
// #else
//     PNG temp;
//     vector<TileImage> tiles;
//     *temp(0, 0) = RGBAPixel(0,   0,   0);   tiles.push_back(TileImage(temp));
//     *temp(0, 0) = RGBAPixel(0,   0,   127); tiles.push_back(TileImage(temp));
//     *temp(0, 0) = RGBAPixel(0,   0,   255); tiles.push_back(TileImage(temp));
//     *temp(0, 0) = RGBAPixel(0,   127, 0);   tiles.push_back(TileImage(temp));
//     *temp(0, 0) = RGBAPixel(0,   255, 0);   tiles.push_back(TileImage(temp));
//     *temp(0, 0) = RGBAPixel(127, 0,   0);   tiles.push_back(TileImage(temp));
//     *temp(0, 0) = RGBAPixel(255, 0,   0);   tiles.push_back(TileImage(temp));
//     *temp(0, 0) = RGBAPixel(0,   127, 127); tiles.push_back(TileImage(temp));
//     *temp(0, 0) = RGBAPixel(0,   255, 255); tiles.push_back(TileImage(temp));
//     *temp(0, 0) = RGBAPixel(127, 0,   127); tiles.push_back(TileImage(temp));
//     *temp(0, 0) = RGBAPixel(255, 0,   255); tiles.push_back(TileImage(temp));
//     *temp(0, 0) = RGBAPixel(127, 127, 0);   tiles.push_back(TileImage(temp));
//     *temp(0, 0) = RGBAPixel(255, 255, 0);   tiles.push_back(TileImage(temp));
//     return tiles;
// #endif
// }

// bool hasImageExtension(const string& fileName)
// {
//     size_t dotpos = fileName.find_last_of(".");
//     if (dotpos == string::npos)
//         return false;
//     string ext = toLower(fileName.substr(dotpos + 1));
//     return (ext == "bmp" || ext == "png" || ext == "jpg" || ext == "gif"
//             || ext == "tiff");
// }
