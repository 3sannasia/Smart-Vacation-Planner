# teamZero
CS225 Final Project: Route Finder

![World_map_political_ISO](https://user-images.githubusercontent.com/54860072/206866561-f355532b-4ac6-40c8-afe6-4e42b4a0232e.png)

Our ultimate goal is to inspire people to see their options when flying to a place in a graphical and quick way. We are using BFS and Dijkstra’s algorithm to ultimately provide a graphical output to the user about the various paths they can take to their destination.

# Presentation Video
We'll Link it here

# Data
We will be using the [route](https://openflights.org/data.html#route) and [aiport](https://openflights.org/data.html#airport) datasets from [OpenFlights](https://openflights.org). We filter and clean both datasets in our program.

# Code
All major files of our classes and functions are in /base/src. In this directory, files and functions for data cleaning and storage, graph implementation, breadth-first search algorithm, Dijkstra's algorithm, and our map output visualization.

# Tests
Tests are located in /base/tests.

Look below on how to run tests!

We mainly test for four components of our project, correct data parsing and storage of routes and airport data, correct graph storage and edge distance calculations, complete graph traversal of breadth-first search algorithm. We additionally check for incomplete data and if an airport cannot be found. For more info on what we are testing, please check out the comments in the /base/tests directory!

# Documents (Written Report, Project Proposal, Team Contract)
These are located in /Documents

# Running Instructions
First, make sure you are running in Docker. If not, follow these [instructions](https://courses.engr.illinois.edu/cs225/fa2022/resources/own-machine/). Second, traverse to the /base directory. If there is already a build folder, delete it. Type each "mkdir build" and "cd build" in the terminal separately (should be in teamZero/base/build). Run "cmake .." 

To ultimately use our program, run make && ./main source_airport destination_airport. Fill in the source and destination with an airport of your choice in the International Air Transport Association Location Identifier 3-letter code. For example, the San Francisco International Airport would be SFO. The Chicago O'Hare International Airport is ORD.

To run tests, make sure you are in the /base/build directory and run "make test && ./test"

# Diagrams
