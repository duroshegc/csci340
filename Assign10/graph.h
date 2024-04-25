#ifndef NIU_CSCI340_GRAPH_H
#define NIU_CSCI340_GRAPH_H

// This is the file where the student should do their work.



#include "graph.decl.h"
#include <queue>
#include <stack>
#include <vector>
#include <iostream>

using namespace std;

size_t Graph::nvertices() const {
  return vertices.size();
}
size_t Graph::nedges() const { 
  return edges.size();
}

void Graph::assign(const std::vector<std::string> & vertices, const std::vector<GraphEdge> & edges) {
  this->vertices.clear();
  this->edges.clear();

  this->vertices.assign(vertices.begin(), vertices.end());
  this->edges.assign(edges.begin(), edges.end());
}

bool Graph::edge_exists(size_t origin, size_t destination) const {
  for(size_t i = 0; i < this->edges.size(); i++)
  {
    if(this->edges[i].origin == origin && this->edges[i].destination == destination)
    {
      return true;
    }
  }
  return false;
}

double Graph::edge_weight(size_t origin, size_t destination) const {
  for(size_t i = 0; i < this->edges.size(); i++)
  {
    if(this->edges[i].origin == origin && this->edges[i].destination == destination)
    {
      return this->edges[i].weight;
    }
  }
  return INFINITY;
}

std::vector<AdjListEdge> Graph::undirected_adjacency_list(size_t vertex) const {
  vector<AdjListEdge> vec;

  for(size_t i = 0; i < this->edges.size(); i++ )
  {
    if(this->edges[i].origin == vertex)
    {
      AdjListEdge edge(edges[i].destination, edges[i].weight);
      vec.push_back(edge);
    } 
    
    if(this->edges[i].destination == vertex)
    {
      AdjListEdge edge(edges[i].origin, edges[i].weight);
      vec.push_back(edge);
    }
  }

  return vec;
}

std::vector<AdjListEdge> Graph::in_adjacency_list(size_t vertex) const {
  vector<AdjListEdge> vec;

  for(size_t i = 0; i < this->edges.size(); i++ )
  {
    if(this->edges[i].destination == vertex)
    {
      AdjListEdge edge(edges[i].origin, edges[i].weight);
      vec.push_back(edge);
    }
  }

  return vec;
}

std::vector<AdjListEdge> Graph::out_adjacency_list(size_t vertex) const {
  vector<AdjListEdge> vec;

  for(size_t i = 0; i < this->edges.size(); i++ )
  {
    if(this->edges[i].origin == vertex)
    {
      AdjListEdge edge(edges[i].destination, edges[i].weight);
      vec.push_back(edge);
    } 
  }

  return vec;
}

std::vector <double> Graph::weighted_adjacency_matrix() const {
  // XXX You must implement this.
  return {};
}

std::vector <bool> Graph::unweighted_adjacency_matrix() const {
  // XXX You must implement this.
  return {};
}

std::string Graph::v_label(size_t vertex) const {
  // XXX You must implement this.
  return "wrong";
}

ssize_t Graph::v_index(const std::string &label) const {
  // XXX You must implement this.
  return -1; }

template <typename FN>
void Graph::breadth_first(size_t start, FN visitfn, bool connected_only) {
  // XXX You must implement this.
}

template <typename FN>
void Graph::depth_first(size_t start, FN visitfn, bool connected_only) {
  // XXX You must implement this.
}

std::vector<size_t> Graph::toposort() const {
  // XXX You must implement this.
  return {};
}
    
std::vector<dijkstra_row> Graph::dijkstra(size_t start) const {
  // XXX You must implement this.
  return {};
}


#endif /* NIU_CSCI340_GRAPH_H */
