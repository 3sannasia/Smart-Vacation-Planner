# **Project Proposal**


## 
**<span style="text-decoration:underline;">Leading Question</span>**

Given the airport route data from the link we have provided below in the data format section, we decided on finding the top five shortest paths between two airports for people who want to fly between two locations. We will incorporate a twist in the form of evaluating flight time vs. distance between airports to find the five shortest paths. Our ultimate goal is to inspire people to see their options when flying to a place in a graphical and quick way. We plan on using BFS and Dijkstra’s algorithm to ultimately provide a graphical output to the user about the various paths they can take. 

Traversal:



1. Breadth First Search 
* We will use this traversal to keep traversing until we found five satisfactory routes between the two locations the user has passed in. 

Algorithms:



1. Dijkstra’s algorithm
* We will use this algorithm to find the shortest path between two airports
2. Graphic Output - uncovered option
* Over a map PNG, we will draw the top five shortest paths between two locations/airports, so the user can visually see his/her options 
* Essentially recolor png to show our paths
* We plan to color least mile paths in a different color than least flight time paths and maybe add more “top five” paths using our data if time persists.


## **<span style="text-decoration:underline;">Data Acquisition and Processing</span>**

We will be using the routes dataset from [OpenFlights](https://openflights.org/data.html#route).


## **Data Format**

Our input dataset consists of files obtained from OpenFlights datasets. The first file contains a list of routes between airports, with each line containing the airline, source airport, destination airport, number of stops and necessary equipment. To make interpreting the data easier we will also use the airlines and airports datasets, which map the airport and airline acronyms to its full name and the airport to their location.

The first file is approximately 2 MB large, and the other 2 are less than 400KB. Because such a large dataset may become difficult to work with, we will be using a smaller portion of the data, focusing on more recent years.


## **Data Correction **

To limit existing errors in our dataset, we will institute a number of checks. The first check will look for null values. Since we will not be using information regarding equipment or airline ID, we will only remove null elements related to source airport, destination airport, and number of stops.

**Data Storage**

Our possible paths will be stored in a graph where nodes represent airports, and edges represent flight time. We will use that to calculate five closest paths between two airports. This graph will be represented as a map where the key is a string and the value is a vector of pairs (string, int). The key will be an airport and the vector of pairs will include a list of airports (first argument) that a plane from the key airport can fly to and their respective flight times(second argument). The space complexity of this map will be O(n), as it is dependent on the number of key-value pairs in the dataset.



## 
**<span style="text-decoration:underline;">Graph Algorithms </span>**


### 
**Function Inputs**



* The two airports we are going to look for paths between. 

### 
**Function Outputs**

* The 5 shortest paths between the two airports in the form of a vector of coordinate pairs. The shortests path may either be in terms of flight time or the distance. (we will do both if time permits)

### 
**Function Efficiency**

* Dijkstra’s algorithm using our map graph. BFS will take about O(n). Dijkstra’s algorithm will take about O(n + m) where n is the vertices and m is the edges. However, since we are using a map that takes in a string and outputs a vector of pairs we must traverse through to find the next airport that will lead to the destination airport or the destination airport itself. Finding the neighbors of each airport would be O(2m) , which is O(m). Therefore, we believe function efficiency will be an overall runtime of O(n + m) since O(n + m) is bigger than O(m).
* If we think of a faster solution over the course of the project, we will attempt to implement it.

## 
**Timeline**


#### 
**Week 1 (Nov 4th)**

1. Set up/plan necessary classes and dependencies
2. Set up and test a small dataset to get familiar with date interpretation

#### 
**Week 2 (Nov 11th)**

1. Write basic graphic output code and process our data input into a graph
2. Begin shortest path algorithm (Dijkstra’s algorithm) 

#### 
**Week 3 (Nov 18th)**

1. Finish and test shortest path algorithm (Dijkstra’s algorithm) 
2. Work on BFS graph traversing algorithm

#### 
**Week 4 (Nov 25th)**

1. Continue working on graphic output code and BFS graph algorithm

#### 
**Week 5 (Dec 2nd)**

1. Final testing of BFS, Dijkstra’s algorithm, and graphic output in conjunction

#### 
**Week 6 (Dec 9th)**

1. Documentation Clean up 
2. Code clean up 
3. Prepare for presentation 