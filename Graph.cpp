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
    if (n != m)
    {
        throw invalid_argument("Invalid graph");
    }
    this->directed = this->isDirected();

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
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
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
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            if (this->adjancencyMatrix[i][j] != 0)
            {
                count++;
            }
        }
    }
    return this->directed ? count : count / 2;
}

vector<vector<int>> Graph::getAdjacencyMatrix() 
{
    return this->adjancencyMatrix;
}


