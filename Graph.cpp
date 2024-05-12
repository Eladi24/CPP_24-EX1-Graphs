// ID: 205739907
// Email: eladima66@gmail.com

#include <iostream>
#include <vector>
#include "Graph.hpp"
using ariel::Graph;
using namespace std;

Graph::Graph()
{
    this->vertices = 0;
    this->edges = 0;
    this->directed = false;
}

Graph::~Graph()
{
    
}

void Graph::loadGraph(vector<vector<int>> graph)
{
    this->adjancencyMatrix = graph;
    this->vertices = graph.size();
    size_t n = graph.size();
    size_t m = graph[0].size();

    // If the graph is not a square matrix, throw an exception.
    if (n != m)
    {
        throw invalid_argument("Invalid graph");
    }
    this->directed = this->isDirected();
    this->edges = this->countEdges();

}

void Graph::printGraph()
{
    cout << "Graph with " << this->vertices << " vertices and " << this->countEdges() << " edges." << endl;

}

size_t Graph::getVertices()
{
    return this->vertices;
}

size_t Graph::getEdges()
{
    return this->edges;
}

bool Graph::isDirected()
{
    size_t n = this->adjancencyMatrix.size();
    size_t m = this->adjancencyMatrix[0].size();

    // Iterate over the matrix and check if the graph is directed.
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {   
            // If the graph is directed, the adjacency matrix is not symmetric.
            if (this->adjancencyMatrix[i][j] != this->adjancencyMatrix[j][i])
            {
                return true;
            }
        }
    }
    return false;
}

size_t Graph::countEdges()
{
    size_t n = this->adjancencyMatrix.size();
    size_t m = this->adjancencyMatrix[0].size();
    size_t count = 0;

    // Iterate over the matrix and count the number of edges.
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            // If the value is not 0, then there is an edge.
            if (this->adjancencyMatrix[i][j] != 0)
            {
                count++;
            }
        }
    }
    // If the graph is directed, return the count, if the graph is undirected, then every edge is counted twice.
    return this->directed ? count : count / 2;
}

vector<vector<int>> Graph::getAdjacencyMatrix() 
{
    return this->adjancencyMatrix;
}

vector<vector<int>> Graph::getTranspose()
{
    size_t n = this->adjancencyMatrix.size();
    size_t m = this->adjancencyMatrix[0].size();
    vector<vector<int>> transpose(n, vector<int>(m, 0));

    for (size_t i = 0; i < n; i++)
    {
        
        for (size_t j = 0; j < m; j++)
        {
            transpose[j][i] = this->adjancencyMatrix[i][j];
        }
    }
    return transpose;
}


