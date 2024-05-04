/************************************************************************************
* NIU CSCI 340 Section 1 *
* Assignment 10 
* Oluwasegun Durosinmi - z1978798 *
* *
* I certify that everything I am submitting is either provided by the professor for use in *
* the assignment, or work done by me personally. I understand that if I am caught submitting *
* the work of others (including StackOverflow or ChatGPT) as my own is an act of Academic *
* Misconduct and will be punished as such. *
* *
* * The purpose of this assignment is to  work with directed graphs. You’ll implement a class that allows a user to query various
info about a graph, which also implements several of the graph algorithms discussed in class.
************************************************************************************/

#ifndef NIU_CSCI340_GRAPH_H
#define NIU_CSCI340_GRAPH_H

// This is the file where the student should do their work.



#include "graph.decl.h"
#include <queue>
#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <functional>




using namespace std;

/**
 * @brief Get the number of vertices in the graph.
 * 
 * This function returns the number of vertices in the graph.
 * 
 * @return The number of vertices in the graph.
 */
size_t Graph::nvertices() const {
  // Function nvertices returns the number of vertices in the graph.
  return vertices.size();
}

/**
 * @brief Get the number of edges in the graph.
 * 
 * This function returns the number of edges in the graph.
 * 
 * @return The number of edges in the graph.
 */

size_t Graph::nedges() const { 
  // Function nedges returns the number of edges in the graph.
  return edges.size();
}

/**
 * @brief Assign new vertices and edges to the graph.
 * 
 * This function clears the existing vertices and edges in the graph and assigns 
 * new vertices and edges provided as input vectors.
 * 
 * @param vertices A vector containing new vertex labels.
 * @param edges A vector containing new edges.
 */

void Graph::assign(const std::vector<std::string> & vertices, const std::vector<GraphEdge> & edges) {
   // Clear existing vertices.
  this->vertices.clear();
  // Clear existing edges.
  this->edges.clear();

  // Assign new vertices and edges.
  this->vertices.assign(vertices.begin(), vertices.end());
  this->edges.assign(edges.begin(), edges.end());
}

/**
 * @brief Check if an edge exists between two vertices in the graph.
 * 
 * This function checks if there is an edge between two specified vertices in the graph.
 * 
 * @param origin The index of the origin vertex.
 * @param destination The index of the destination vertex.
 * @return True if an edge exists between the origin and destination vertices, false otherwise.
 */

bool Graph::edge_exists(size_t origin, size_t destination) const {
  // Function edge_exists checks if there is an edge from 'origin' to 'destination' in the graph.
  for(size_t i = 0; i < this->edges.size(); i++)
  {
    if(this->edges[i].origin == origin && this->edges[i].destination == destination)
    {
      return true;
    }
  }
  return false;
}

/**
 * @brief Get the weight of an edge between two vertices in the graph.
 * 
 * This function returns the weight of the edge between two specified vertices in the graph.
 * 
 * @param origin The index of the origin vertex.
 * @param destination The index of the destination vertex.
 * @return The weight of the edge between the origin and destination vertices, or INFINITY if no such edge exists.
 */

double Graph::edge_weight(size_t origin, size_t destination) const {
  // Function edge_weight returns the weight of the edge from 'origin' to 'destination' in the graph.
  for(size_t i = 0; i < this->edges.size(); i++)
  {
    if(this->edges[i].origin == origin && this->edges[i].destination == destination)
    {
      return this->edges[i].weight;
    }
  }
  return INFINITY;
}

/**
 * @brief Get the in-adjacency list of a vertex in a directed graph.
 * 
 * This function returns the in-adjacency list of a specified vertex in a directed graph.
 * 
 * @param vertex The index of the vertex.
 * @return A vector containing the in-adjacency list of the vertex.
 */

std::vector<AdjListEdge> Graph::undirected_adjacency_list(size_t vertex) const {
  vector<AdjListEdge> vec;

  for(size_t i = 0; i < this->edges.size(); i++ )
  {
    if(this->edges[i].origin == vertex)
    {
      // Create an edge from 'vertex' to 'destination' with weight 'weight'.
      AdjListEdge edge(edges[i].destination, edges[i].weight);
      // Add the edge to the adjacency list.
      vec.push_back(edge);
    } 
    
    if(this->edges[i].destination == vertex)
    {
      // Create an edge from 'origin' to 'vertex' with weight 'weight
      AdjListEdge edge(edges[i].origin, edges[i].weight);
      // Add the edge to the adjacency list.
      vec.push_back(edge);
    }
  }

  return vec;
}

/**
 * @brief Get the out-adjacency list of a vertex in a directed graph.
 * 
 * This function returns the out-adjacency list of a specified vertex in a directed graph.
 * 
 * @param vertex The index of the vertex.
 * @return A vector containing the out-adjacency list of the vertex.
 */

std::vector<AdjListEdge> Graph::in_adjacency_list(size_t vertex) const {
  vector<AdjListEdge> vec;

  for(size_t i = 0; i < this->edges.size(); i++ )
  {
    if(this->edges[i].destination == vertex)
    {
      // Create an edge from 'origin' to 'vertex' with weight 'weight'.
      AdjListEdge edge(edges[i].origin, edges[i].weight);
      // Add the edge to the adjacency list.
      vec.push_back(edge);
    }
  }

  return vec;
}

/**
 * @brief Get the weighted adjacency matrix of the graph.
 * 
 * This function returns the weighted adjacency matrix of the graph.
 * 
 * @return A vector containing the weighted adjacency matrix of the graph.
 */

std::vector<AdjListEdge> Graph::out_adjacency_list(size_t vertex) const {
  vector<AdjListEdge> vec;

  for(size_t i = 0; i < this->edges.size(); i++ )
  {
    if(this->edges[i].origin == vertex)
    {
      // Create an edge from 'vertex' to 'destination' with weight 'weight'.
      AdjListEdge edge(edges[i].destination, edges[i].weight);
      // Add the edge to the adjacency list.
      vec.push_back(edge);
    } 
  }

  return vec;
}

/**
 * @brief Get the weighted adjacency matrix of the graph.
 * 
 * This function returns the weighted adjacency matrix of the graph, where each entry 
 * represents the weight of the edge between two vertices. If there is no edge between 
 * two vertices, the corresponding entry is set to INFINITY.
 * 
 * @return A vector containing the weighted adjacency matrix of the graph.
 */
std::vector <double> Graph::weighted_adjacency_matrix() const {
  vector<double> vec;

  for(size_t i = 0; i < vertices.size(); i++)
  {
    for(size_t j = 0; j < vertices.size(); j++)
    {
      // Add the weight of the edge from vertex 'i' to vertex 'j' to the matrix.
      vec.push_back(edge_weight(i,j));
    }
  }
  return vec;
}

/**
 * @brief Get the unweighted adjacency matrix of the graph.
 * 
 * This function returns the unweighted adjacency matrix of the graph, where each entry 
 * represents whether an edge exists between two vertices. If there is an edge between 
 * two vertices, the corresponding entry is set to true; otherwise, it's set to false.
 * 
 * @return A vector containing the unweighted adjacency matrix of the graph.
 */
std::vector <bool> Graph::unweighted_adjacency_matrix() const {
  vector<bool> vec;

  for(size_t i = 0; i < vertices.size(); i++)
  {
    for(size_t j = 0; j < vertices.size(); j++)
    {
      // Add whether an edge exists from vertex 'i' to vertex 'j' to the matrix.
      vec.push_back(edge_exists(i,j));
    }
  }
  return vec;
}

/**
 * @brief Get the label of a vertex with the given index.
 * 
 * This function returns the label of the vertex with the specified index.
 * 
 * @param vertex The index of the vertex.
 * @return The label of the vertex.
 */

std::string Graph::v_label(size_t vertex) const {
  // Function v_label returns the label of the vertex with the given index.
  return vertices[vertex];
}

/**
 * @brief Get the index of a vertex with the given label.
 * 
 * This function returns the index of the vertex with the specified label.
 * 
 * @param label The label of the vertex.
 * @return The index of the vertex, or a default value (000000) if the label is not found.
 */
ssize_t Graph::v_index(const std::string &label) const {
  for(size_t i = 0; i < vertices.size(); i++)
  {
    if(vertices[i] == label)
    {
      return i;
    }
  }
  // Return a default value if the label is not found.

  return 000000;

}

/**
 * @brief Perform breadth-first traversal starting from a vertex in the graph.
 * 
 * This function performs a breadth-first traversal starting from a specified vertex 
 * in the graph. It uses a user-defined function to process each visited vertex.
 * 
 * @tparam FN The type of the user-defined function for processing visited vertices.
 * @param start The starting vertex for traversal.
 * @param visitfn A function to process visited vertices.
 * @param connected_only If true, only traverse connected components starting from the given vertex.
 */
template <typename FN>
void Graph::breadth_first(size_t start, FN visitfn, bool connected_only) {
   
   // create visited vertices
   vector<bool> visited(vertices.size(), false); 
   // Lets create a queue
   queue<size_t> myqueue; 

 // Define lambda function to encapsulate the BFS logic
 auto breadth_first = [&](size_t v)
 {

  // Push the vertex into the queue
   myqueue.push(v); 
   visited[v] = true; 
   while (!myqueue.empty())
   { 

    // lets Get the current vertex that at the front of the queue
     size_t current = myqueue.front(); 

     myqueue.pop(); 

     // Call the visitor function for the current vertex
     visitfn(current); 

     //Lets store the adjaency list somewhere
     auto list = out_adjacency_list(current);

     // Sort the adjacency list
     sort(list.begin(), list.end(), [](const AdjListEdge& a, const AdjListEdge& b) 
     {
      return a.vertex < b.vertex;
     });

     for (const auto& edge : list)
     {

      // Lets do this if we cant visit the edge
       if (!visited[edge.vertex])
       { 
        visited[edge.vertex] = true;

        myqueue.push(edge.vertex); 
       }
     }
   }
 };

 //lets do this if the frst node has not been visited
 if (!visited[start])
 {
  // Call breadth first 
  breadth_first(start); 
 }

//perform BFS from all unvisited vertices if not connected
 if (!connected_only)
 { 
   for (size_t i = 0; i < vertices.size(); ++i)
   {
     if (!visited[i])
     {
      breadth_first(i);
     }
   }
 }
  


}

/**
 * @brief Perform depth-first traversal starting from a vertex in the graph.
 * 
 * This function performs a depth-first traversal starting from a specified vertex 
 * in the graph. It uses a user-defined function to process each visited vertex.
 * 
 * @tparam FN The type of the user-defined function for processing visited vertices.
 * @param start The starting vertex for traversal.
 * @param visitfn A function to process visited vertices.
 * @param connected_only If true, only traverse connected components starting from the given vertex.
 */

template <typename FN>
void Graph::depth_first(size_t start, FN visitfn, bool connected_only) {
// vector for vertices
 vector<bool> visited(vertices.size(), false); 

// create a stack
 stack<size_t> stack; 

 // let's use lambda function for DFS logic
 auto depth_first = [&](size_t vertex)
 {

   stack.push(vertex); 

   // While the stack is not empty
   while (!stack.empty())
   { 
     size_t current = stack.top(); 

     // Remove the vertex fromt the stack
     stack.pop(); 

     // If current vertex has not been visited
     if (!visited[current])
     { 
      visited[current] = true;

      // Call fn to perform the visit action 

      visitfn(current); 

       // Get the adjacency list of the current vertex
      auto adjacency_list = out_adjacency_list(current);

      sort(adjacency_list.begin(), adjacency_list.end(), [](const AdjListEdge& a, const AdjListEdge& b)
      { // Sort the adjacency list in descending order of vertices
       return a.vertex > b.vertex;
      });
      // For each edge in the sorted adjacency list
      for (const auto& edge : adjacency_list)
      { 
        // if we have not visited the edge
        if (!visited[edge.vertex])
        { 
         stack.push(edge.vertex); 
        }
      }
     }
   }
 };

 //lets recursively call depth first search
 if (!visited[start])
 {
  depth_first(start); 
 }

// If not connected, lets do dfs
 if (!connected_only)
 { 
   for (size_t i = 0; i < vertices.size(); ++i)
   {
     if (!visited[i])
     {
      depth_first(i);
     }
   }
 }
}

/**
 * @brief Perform Dijkstra's algorithm to find shortest paths from a source vertex.
 * 
 * This function performs Dijkstra's algorithm to find the shortest paths from a specified 
 * source vertex to all other vertices in the graph. It returns a vector containing the 
 * shortest distances and paths from the source vertex to all other vertices.
 * 
 * @param start The index of the source vertex.
 * @return A vector containing the shortest distances and paths from the source vertex.
 */

std::vector<size_t> Graph::toposort() const {
   // Initialize an array to store the in-degree of each vertex.
  vector<size_t> in_degree(vertices.size(), 0);


  for(size_t i = 0; i < vertices.size(); i++)
  {
     // Get the in-adjacency list for vertex 'i'.
    vector<AdjListEdge> vec = in_adjacency_list(i);
    // Store the size of the in-adjacency list as the in-degree of vertex 'i'.
    in_degree[i] = vec.size();
  }

// Use priority queue to ensure consistent order
  std::priority_queue<size_t, std::vector<size_t>, std::greater<size_t>> q; 
  
  
  for(size_t i = 0; i < vertices.size(); i++)
  {
    // If the in-degree of vertex 'i' is zero.
    if(in_degree[i] == 0)
    {
      // Push vertex 'i' to the priority queue.
      q.push(i);
    }
  }

  // Initialize a counter to keep track of the number of visited vertices.

  size_t count = 0;

  // Initialize a vector to store the topological order.

  vector<size_t> top_order;

  // While the priority queue is not empty.

  while(!q.empty())
  {
    // Get the vertex with the minimum value from the priority queue.
    size_t u = q.top();
    // Remove the vertex from the priority queue.
    q.pop();
    // Add the vertex to the topological order.
    top_order.push_back(u);

    // Update the in-degree of adjacent vertices.
    vector<AdjListEdge> myvec = out_adjacency_list(u);
    for(auto it = myvec.begin(); it != myvec.end(); it++)
    {
      // Decrement the in-degree of the adjacent vertex and if it becomes zero.
      if(--in_degree[it->vertex] == 0)
      {
        // Push the adjacent vertex to the priority queue.
        q.push(it->vertex);
      }
    }
    // Increment the counter.

    count++;


      // If the counter exceeds the number of vertices 

     if(count > vertices.size())
      {
        // Return the current topological order.
        return top_order;
      }
  }

  // Return the topological order.

  return top_order;

}

/**
 * @brief Perform Dijkstra's algorithm to find shortest paths from a source vertex.
 * 
 * This function performs Dijkstra's algorithm to find the shortest paths from a specified 
 * source vertex to all other vertices in the graph. It returns a vector containing the 
 * shortest distances and paths from the source vertex.
 * 
 * @param start The index of the source vertex.
 * @return A vector containing the shortest distances and paths from the source vertex.
 * @note This function assumes that the graph does not contain negative edge weights.
 * If the graph contains negative edge weights, Dijkstra's algorithm may produce incorrect results.
 */
    
std::vector<dijkstra_row> Graph::dijkstra(size_t start) const {
    // Initialize the result table with default values
    std::vector<dijkstra_row> result(vertices.size());
    
    // Initialize the result table with proper vertex indices and default values
    for (size_t i = 0; i < vertices.size(); ++i) {
        result[i].vertex = i;
        result[i].shortest_known = INFINITY;
        result[i].came_from = -1;
        result[i].visited = false;
    }
    
    // Set the shortest distance from the source vertex to itself as 0
    result[start].shortest_known = 0;

    // Create a priority queue to store vertices and their distances
    std::priority_queue<std::pair<double, size_t>, std::vector<std::pair<double, size_t>>, std::greater<>> pq;
    pq.push({0.0, start});

    while (!pq.empty()) {
       // auto [dist, u] = pq.top();
       auto u = pq.top();
       pq.pop();

        // If the vertex has already been visited, skip it
        if (result[u.second].visited)
            continue;

        // Mark the vertex as visited
        result[u.second].visited = true;

        // Update distances to adjacent vertices
        for (const auto& edge : edges) {
            if (edge.origin == u.second) {  // Ensure we only consider outgoing edges
                size_t neighbor = edge.destination;
                double weight = edge.weight;

                // Relaxation step: Update shortest_known if a shorter path is found
                if (result[neighbor].shortest_known > result[u.second].shortest_known + weight) {
                    result[neighbor].shortest_known = result[u.second].shortest_known + weight;
                    result[neighbor].came_from = u.second;

                    // Push the updated distance and vertex to the priority queue
                    pq.push({result[neighbor].shortest_known, neighbor});
                }
            }
        }
    }


    //  Check for negative weights first
    for (size_t i = 0; i < edges.size(); ++i) {
        const auto& edge = edges[i];
        if (edge.weight < 0) {
            std::cerr << "Error: Dijkstra's algorithm does not support graphs with negative edge weights.\n";
            return {};  // Return an empty vector to indicate failure due to negative weights
        }
    }


    return result;
}


#endif /* NIU_CSCI340_GRAPH_H */
