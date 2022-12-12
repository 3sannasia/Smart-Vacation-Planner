# teamZero
CS225 Final Project: Route Finder

![World_map_political_ISO](/Documents/ORD-EWR.png)

Our ultimate goal is to inspire people to see their options when flying to a place in a graphical and quick way. We are using BFS and Dijkstra’s algorithm to ultimately provide a graphical output to the user about the various paths they can take to their destination.

# Presentation Video
https://drive.google.com/file/d/1v-j2oDiNa1ZMGOWth5DuYCJ_Bw2mev2B/view?usp=sharing

# Data
We will be using the [route](https://openflights.org/data.html#route) and [airport](https://openflights.org/data.html#airport) datasets from [OpenFlights](https://openflights.org). We filter and clean both datasets in our program.

# Code
All major files of our classes and functions are in /base/src. In this directory, files and functions for data cleaning and storage (graph.cpp), graph implementation (graph.cpp), breadth-first search algorithm (graph.cpp), Dijkstra's algorithm (dijkstra.cpp), and our map output visualization (mappic.cpp).

# Tests
Tests are located in /base/tests. Test data files are located in /base for ease of access in the form of small and complete datasets for both routes and airports.

Look below on how to run tests!

We mainly test for four components of our project, correct data parsing and storage of routes and airport data, correct graph storage and edge distance calculations, complete graph traversal of breadth-first search algorithm. We additionally check for incomplete data and if an airport cannot be found. For more info on what we are testing, please check out the comments in the /base/tests directory!

# Documents (Written Report, Project Proposal, Team Contract)
These are located in /Documents

# Running Instructions
First, make sure you are running in Docker. If not, follow these [instructions](https://courses.engr.illinois.edu/cs225/fa2022/resources/own-machine/). Second, traverse to the /teamZero/base directory. If there is already a build folder, delete it. Enter "mkdir build" then "cd build" in the terminal. Make sure you are in the directory teamZero/base/build. Run "cmake .." 

To ultimately use our program, run make && ./mosaics source_airport destination_airport (make && ./mosaics AER KZN) Fill in the source and destination with an airport of your choice in the International Air Transport Association Location Identifier 3-letter code. For example, the Sochi International Airport would be AER. The Kazan International Airport is KZN.

To run tests, make sure you are in the /base/build directory and run "make test && ./test"

# Diagrams

BFS
![map](/Documents/BFS.png)

Dijkstra
![map](/Documents/dijkstra.png)

Map Output
![map](/Documents/mapoutput.png)

