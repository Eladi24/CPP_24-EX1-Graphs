#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include <vector>
#include <iostream>
using namespace std;
namespace ariel
{

    class Graph
    {
    private:
        vector<vector<int>> adjancencyMatrix;
        size_t vertices;
        size_t edges;
        bool directed;

    public:
        // Constructor
        Graph();
        // Destructor
        ~Graph();

        /*
        * @brief
        * This function loads the graph from a 2D vector.
        * The graph is represented as an adjacency matrix.
        * The graph can be directed or undirected.
        * The graph can be weighted or unweighted.
        * @param graph - 2D vector representing the graph.
        * @return void
        */

        void loadGraph(vector<vector<int>> graph);
        
        /*
        * @brief
        * This function prints the graph.
        * @return void        
        */
        
        void printGraph();

        /*
        * @brief
        * This function returns the number of vertices in the graph.
        * @return size_t - number of vertices in the graph.
        */

        size_t getVertices();

        /*
        * @brief
        * This function returns the number of edges in the graph.
        * @return size_t - number of edges in the graph.
        */

        size_t getEdges();

        /*
        * @brief
        * This function checks if the graph is directed.
        * @return bool - true if the graph is directed, false otherwise.
        */
        bool isDirected();

        /*
        * @brief
        * This counts the number of edges in the graph.
        * @return size_t - number of edges in the graph.
        */
        size_t countEdges();
        
        /*
        * @brief
        * This function returns the adjacency matrix of the graph.
        * @return vector<vector<int>> - adjacency matrix of the graph.
        */
        vector<vector<int>> getAdjacencyMatrix();

        /*
        * @brief
        * This function returns the transpose of the adjacency matrix.
        * @return vector<vector<int>> - transpose of the adjacency matrix.
        */
        vector<vector<int>> getTranspose();

        /*
        * @brief
        * This function returns the degree of a vertex in the graph.
        * @param vertex - vertex to check.
        * @return size_t - degree of the vertex.
        */

        size_t getDegree(size_t vertex);
    };
}

#endif