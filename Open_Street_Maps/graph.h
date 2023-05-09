// graph.h <Starter Code>
// < Brett Arnold >
//
// Basic graph class using adjacency matrix representation.  Currently
// limited to a graph with at most 100 vertices.
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

#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <set>
#include <map>

using namespace std;

template <typename VertexT, typename WeightT>
class graph
{
private:
  typedef pair<VertexT, WeightT> vwPair;
  map<VertexT, set<vwPair>> adjList;

  int numVertices;
  int numEdges;

  /*struct EdgeData {
    bool     EdgeExists;
    WeightT  Weight;

    EdgeData() {
      EdgeExists = false;  // initially no edge, and no weight
    }
  };

  //
  // We are using adjacency matrix implementation, where rows
  // are the starting vertex and cols are the ending vertex.
  // We keep track of the vertices in the Vertices vector,
  // where the vertex's position in the vector --- 0, 1, 2,
  // 3, 4, 5, ... --- denotes the row in the adjacency matrix
  // where their edges are found.  Example: if vertex "ORD" is
  // in position 1 of the Vertices vector, then row 1 of
  // AdjMatrix are the edges that start at "ORD" and lead to
  // other vertices.
  //
  static constexpr int MatrixSize = 100;

  EdgeData         AdjMatrix[MatrixSize][MatrixSize];
  vector<VertexT>  Vertices;

  //
  // _LookupVertex
  //
  // Finds the vertex in the Vertices vector and returns it's
  // index position if found, otherwise returns -1.
  //
  int _LookupVertex(VertexT v) const {
    for (int i = 0; i < this->NumVertices(); ++i) {
      if (this->Vertices[i] == v)  // already in the graph:
        return i;
    }

    // if get here, not found:
    return -1;
  }*/

public:
  //
  // constructor:
  //
  // Constructs an empty graph where n is the max # of vertices
  // you expect the graph to contain.
  //
  // NOTE: the graph is implemented using an adjacency matrix.
  // If n exceeds the dimensions of this matrix, an exception
  // will be thrown to let you know that this implementation
  // will not suffice.
  //
  graph()
  {
    numVertices = 0;
    numEdges = 0;
  }

  //
  // NumVertices
  //
  // Returns the # of vertices currently in the graph.
  //
  int NumVertices() const
  {
    return this->numVertices;
  }

  //
  // NumEdges
  //
  // Returns the # of edges currently in the graph.
  //
  int NumEdges() const
  {
    return this->numEdges;
  }

  //
  // addVertex
  //
  // Adds the vertex v to the graph if there's room, and if so
  // returns true.  If the graph is full, or the vertex already
  // exists in the graph, then false is returned.
  //
  bool addVertex(VertexT v)
  {
    // add key to map
    this->adjList[v];
    numVertices++;

    return true;
  }

  //
  // addEdge
  //
  // Adds the edge (from, to, weight) to the graph, and returns
  // true.  If the vertices do not exist or for some reason the
  // graph is full, false is returned.
  //
  // NOTE: if the edge already exists, the existing edge weight
  // is overwritten with the new edge weight.
  //
  bool addEdge(VertexT from, VertexT to, WeightT weight)
  {
    vwPair edge1;
    vwPair edge2;
    edge1 = make_pair(from, weight);
    edge2 = make_pair(to, weight);
    numEdges += 2;

   adjList[from].insert(edge1);
   adjList[to].insert(edge2);

    return true;
  }

  //
  // getWeight
  //
  // Returns the weight associated with a given edge.  If
  // the edge exists, the weight is returned via the reference
  // parameter and true is returned.  If the edge does not
  // exist, the weight parameter is unchanged and false is
  // returned.
  //
  bool getWeight(VertexT from, VertexT to, WeightT &weight) const
  {
    if(adjList.at(from).find(to).first != to) // gives iterator to a vwPair, w/.first = first element in pair, w/.second = edge weight
    {
      return false;
    } 
    else
    {
      weight = adjList.at(from).find(to).second;
      return true;
    }
  }

  //
  // neighbors
  //
  // Returns a set containing the neighbors of v, i.e. all
  // vertices that can be reached from v along one edge.
  // Since a set is returned, the neighbors are returned in
  // sorted order; use foreach to iterate through the set.
  //
  set<VertexT> neighbors(VertexT v) const
  {
    return adjList.at(v);
  }

  //
  // getVertices
  //
  // Returns a vector containing all the vertices currently in
  // the graph.
  //
  vector<VertexT> getVertices() const
  {
    vector<VertexT> v;

    for(auto x: adjList)
    {
      v.push_back(x.first);
    }
    return this->v; // returns a copy:
  }

  //
  // dump
  //
  // Dumps the internal state of the graph for debugging purposes.
  //
  // Example:
  //    graph<string,int>  G(26);
  //    ...
  //    G.dump(cout);  // dump to console
  //
  void dump(ostream &output) const
  {
    output << "***************************************************" << endl;
    output << "********************* GRAPH ***********************" << endl;

    output << "**Num vertices: " << this->NumVertices() << endl;
    output << "**Num edges: " << this->NumEdges() << endl;

    output << endl;
    output << "**Vertices:" << endl;
    for (int i = 0; i < this->NumVertices(); ++i)
    {
      output << " " << i << ". " << this->Vertices[i] << endl;
    }

    output << endl;
    output << "**Edges:" << endl;
    for (int row = 0; row < this->NumVertices(); ++row)
    {
      output << " row " << row << ": ";

      for (int col = 0; col < this->NumVertices(); ++col)
      {
        if (this->AdjMatrix[row][col].EdgeExists == false)
        {
          output << "F ";
        }
        else
        {
          output << "(T,"
                 << this->AdjMatrix[row][col].Weight
                 << ") ";
        }
      }
      output << endl;
    }
    output << "**************************************************" << endl;
  }
};