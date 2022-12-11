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
     graph g;
     g.file_to_stringRoute("../test_routes.csv");
     g.file_to_stringAirport("../test_airport.csv");

    g.makeGraph();
    
    dijkstra dij(g.getMap(), "ORD", "EWR");
    dij.dijkstra_distance();
    auto test =  dij.get_shortest_paths();
    std::cout << dij.source << " " << dij.destination <<std::endl;
    std::cout <<test.size() <<std::endl;
    mappic map_out("../empty_map.png");    
    map_out.drawAirports(g,dij);
    
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
