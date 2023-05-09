// application.cpp <Starter Code>
// <Brett Arnold>
//
//
// Adam T Koehler, PhD
// University of Illinois Chicago
// CS 251, Fall 2022
//
// Project Original Variartion By:
// Joe Hummel, PhD
// University of Illinois at Chicago
//
//
// References:
// TinyXML: https://github.com/leethomason/tinyxml2
// OpenStreetMap: https://www.openstreetmap.org
// OpenStreetMap docs:
//   https://wiki.openstreetmap.org/wiki/Main_Page
//   https://wiki.openstreetmap.org/wiki/Map_Features
//   https://wiki.openstreetmap.org/wiki/Node
//   https://wiki.openstreetmap.org/wiki/Way
//   https://wiki.openstreetmap.org/wiki/Relation
//

#include <iostream>
#include <iomanip> /*setprecision*/
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include "graph.h"
#include <limits>

#include "tinyxml2.h"
#include "dist.h"
#include "osm.h"

using namespace std;
using namespace tinyxml2;

//
// Implement your standard application here
// TO DO: add a parameter for the graph you make.
//

const double INF = numeric_limits<double>::max();

BuildingInfo searchBuilding1(vector<BuildingInfo> building, string query, string query2)
{
  BuildingInfo badReturn;

  for (unsigned int i = 0; i < building.size(); i++)
  {
    if (building[i].Abbrev == query)
    {
      // cout << "Found a match at index " << i << "!" << endl;
      return building[i];
    }
    else if (building[i].Fullname.find(query) != string::npos)
    {
      return building[i];
    }
  }
  cout << "Person 1's building not found" << endl;
  return badReturn;
}

BuildingInfo searchBuilding2(vector<BuildingInfo> building, string query, string query2)
{
  BuildingInfo badReturn;

  for (unsigned int i = 0; i < building.size(); i++)
  {
    if (building[i].Abbrev == query)
    {
      // cout << "Found a match at index " << i << "!" << endl;
      return building[i];
    }
    else if (building[i].Fullname.find(query) != string::npos)
    {
      return building[i];
    }
  }
  cout << "Person 2's building not found" << endl;
  return badReturn;
}

BuildingInfo nearestBuilding(vector<BuildingInfo> building, Coordinates mid)
{
  double min = INF;
  BuildingInfo bi;

  for (unsigned int i = 0; i < building.size(); i++)
  {
    double dist = distBetween2Points(building[i].Coords.Lat, building[i].Coords.Lon, mid.Lat, mid.Lon);

    if (dist < min)
    {
      min = dist;
      bi = building[i];
    }
  }
  return bi;
}

long long nearestNode(BuildingInfo b, vector<FootwayInfo> footway, map<long long, Coordinates> nodes)
{
  long long min2 = 0;

  for (auto x : footway)
  {
    for (unsigned int i = 0; i < x.Nodes.size() - 1; i++)
    {
      long long ID = x.Nodes[i];
      Coordinates c = nodes.at(ID);
      double dist2 = distBetween2Points(b.Coords.Lat, b.Coords.Lon, c.Lat, c.Lon);

      if (dist2 < min2)
      {
        min2 = dist2;
      }
    }
  }
  return min2;
}

/*void DijkstraShortestPath(vector<FootwayInfo> startV)
{
  for (auto x : startV)
  {

  for (int i = 0; i < x.Nodes.size(); i++)
{
  FootwayInfo currentV = x.Nodes[i];
 currentV->distance = INF;
 currentV.ID = -1;
 unvisitedQueue.push_back(currentV, INF);
 // startV has a distance of 0 from itself
 startV⇢distance = 0
 while (unvisitedQueue is not empty) {
 // Visit vertex with minimum distance from startV
 currentV = DequeueMin unvisitedQueue
 for each vertex adjV adjacent to currentV {
 edgeWeight = weight of edge from currentV to adjV
 alternativePathDistance = currentV⇢distance + edgeWeight

 // If shorter path from startV to adjV is found,
 // update adjV's distance and predecessor
 if (alternativePathDistance < adjV⇢distance) {
 adjV⇢distance = alternativePathDistance
 adjV⇢predV = currentV
 }
 }
 }
  }

}*/

void application(map<long long, Coordinates> &Nodes, vector<FootwayInfo> &Footways,
                 vector<BuildingInfo> &Buildings, graph<long long, double> G)
{
  string person1Building, person2Building;

  cout << endl;
  cout << "Enter person 1's building (partial name or abbreviation), or #> ";
  getline(cin, person1Building);

  while (person1Building != "#")
  {
    cout << "Enter person 2's building (partial name or abbreviation)> ";
    getline(cin, person2Building);

    // MILESTONE 7: Search Buildings 1 and 2
    BuildingInfo building1, building2, biCall;
    building1 = searchBuilding1(Buildings, person1Building, person2Building); // !!!!!!!!!!!!!!!!!!!!!!!!111111
    building2 = searchBuilding2(Buildings, person2Building, person2Building);

    // MILESTONE 8: Locate Center Building
    Coordinates midpoint;
    midpoint = centerBetween2Points(building1.Coords.Lat, building1.Coords.Lon, building2.Coords.Lat, building2.Coords.Lon);

    BuildingInfo minDist = nearestBuilding(Buildings, midpoint);

    // MILESTONE 9: Find Nearest Nodes from buildings 1, 2 & Center
    long long dist = nearestNode(building1, Footways, Nodes);

    // TODO MILESTONE 10: Run Dijkstra’s Algorithm
    // DijkstraShortestPath(Footways);

    // TODO MILESTONE 11: Print path (path found! break)

    // TODO MILESTONE 11: Find Second Nearest Destination (loop again)
    //}

    //
    // TO DO: lookup buildings, find nearest start and dest nodes, find center
    // run Dijkstra's alg from each start, output distances and paths to destination:
    //

    // cout << "Person 1's building not found" << endl;
    // cout << "Person 2's building not found" << endl;

    //
    // another navigation?
    //
    cout << endl;
    cout << "Enter person 1's building (partial name or abbreviation), or #> ";
    getline(cin, person1Building);
  }
}

int main()
{
  // maps a Node ID to it's coordinates (lat, lon)
  map<long long, Coordinates> Nodes;
  // info about each footway, in no particular order
  vector<FootwayInfo> Footways;
  // info about each building, in no particular order
  vector<BuildingInfo> Buildings;
  XMLDocument xmldoc;

  cout << "** Navigating UIC open street map **" << endl;
  cout << endl;
  cout << std::setprecision(8);

  string def_filename = "map.osm";
  string filename;

  cout << "Enter map filename> ";
  getline(cin, filename);

  if (filename == "")
  {
    filename = def_filename;
  }

  //
  // Load XML-based map file
  //
  if (!LoadOpenStreetMap(filename, xmldoc))
  {
    cout << "**Error: unable to load open street map." << endl;
    cout << endl;
    return 0;
  }

  //
  // Read the nodes, which are the various known positions on the map:
  //
  int nodeCount = ReadMapNodes(xmldoc, Nodes);

  //
  // Read the footways, which are the walking paths:
  //
  int footwayCount = ReadFootways(xmldoc, Footways);

  //
  // Read the university buildings:
  //
  int buildingCount = ReadUniversityBuildings(xmldoc, Nodes, Buildings);

  //
  // Stats
  //
  assert(nodeCount == (int)Nodes.size());
  assert(footwayCount == (int)Footways.size());
  assert(buildingCount == (int)Buildings.size());

  cout << endl;
  cout << "# of nodes: " << Nodes.size() << endl;
  cout << "# of footways: " << Footways.size() << endl;
  cout << "# of buildings: " << Buildings.size() << endl;

  graph<long long, double> G;

  // MILESTONE 5: add vertices
  for (auto e : Nodes)
  {
    G.addVertex(e.first);
  }

  //  MILESTONE 6: add edges
  for (auto x : Footways)
  {
    for (unsigned int i = 0; i < x.Nodes.size() - 1; i++)
    {
      long long ID = x.Nodes[i];
      long long ID2 = x.Nodes[i + 1];
      Coordinates c, c2;
      c = Nodes.at(ID);
      c2 = Nodes.at(ID2);
      double distance = distBetween2Points(c.Lat, c.Lon, c2.Lat, c2.Lon);

      G.addEdge(x.Nodes[i], x.Nodes[i + 1], distance);
    }
  }

  // uncomment below after MILESTONE 6

  //
  // build the graph, output stats:
  //

  cout << "# of vertices: " << G.NumVertices() << endl;
  cout << "# of edges: " << G.NumEdges() << endl;
  cout << endl;

  //
  // Menu
  //
  string userInput;
  cout << "Enter \"a\" for the standard application or "
       << "\"c\" for the creative component application> ";
  getline(cin, userInput);
  if (userInput == "a")
  {
    // TO DO: add argument for the graph you make.
    application(Nodes, Footways, Buildings, G);
  }
  else if (userInput == "c")
  {
    // TO DO: add arguments
    // creative();
  }
  //
  // done:
  //
  cout << "** Done **" << endl;
  return 0;
}
