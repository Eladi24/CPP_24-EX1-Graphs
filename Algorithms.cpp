#include <iostream>
#include <string>
#include "Algorithms.hpp"
#include "Graph.hpp"
using namespace std;
using namespace ariel;
#define INF 99999
int Algorithms::isConnected(Graph &graph)
{
    // Create a vector to store visited vertices and initialize all vertices as not visited.
    size_t v = graph.getVertices();
    vector<vector<int>> adjacencyMatrix = graph.getAdjacencyMatrix();
    // If the graph is directed, check if it is strongly connected.
    if (graph.isDirected())
    
    {
            // Mark all the vertices as not visited.
            vector<bool> visited(v, false);
            // Do a DFS traversal starting from the first vertex.
            
            DFSIsConnected(adjacencyMatrix, 0, visited);
            // If DFS traversal does not visit all vertices, the graph is not connected.
            for (size_t i = 0; i < v; i++)
            {
                if (!visited[i])
                {
                    return 0;
                }
            }

            // Create a transpose of the adjacency matrix.
            vector<vector<int>> transposeMat = graph.getTranspose();
            // Mark all the vertices as not visited.
            visited = vector<bool>(v, false);
            // Do a DFS traversal starting from the first vertex.
            // Starting vertex must be  same starting vertex in the original graph.
            DFSIsConnected(adjacencyMatrix, 0, visited);
            // If DFS traversal does not visit all vertices, the graph is not connected.
            for (size_t i = 0; i < v; i++)
            {
                if (!visited[i])
                {
                    return 0;
                }
            }

            return 1;
    } 
    else
    {
        // Mark all the vertices as not visited.
        vector<bool> visited(v, false);
        // Do a DFS traversal starting from the first vertex.
        DFSIsConnected(adjacencyMatrix, 0, visited);
        // If DFS traversal does not visit all vertices, the graph is not connected.
        for (size_t i = 0; i < v; i++)
        {
            if (!visited[i])
            {
                return 0;
            }
        }
        return 1;
    }
}

string Algorithms::shortestPath(Graph &graph, size_t src, size_t dest)
{
    vector<vector<int>> adjacencyMatrix = graph.getAdjacencyMatrix();
    vector<int>::size_type n = adjacencyMatrix.size();
    vector<int>::size_type i, j;

    // Create a distance matrix and a next matrix.
    vector<vector<int>> dist(n, vector<int>(n, 0));
    vector<vector<int>> next(n, vector<int>(n, 0));
    // Initialize the distance matrix.
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            // If there is no edge between the vertices, set the distance to infinity.
            if (adjacencyMatrix[i][j] == 0)
            {
                dist[i][j] = INF;
                next[i][j] = -1;
            }
            else
            {
                dist[i][j] = adjacencyMatrix[i][j];
                // Set the next matrix.
                next[i][j] = j;
            }
        }
    }
    // Floyd-Warshall algorithm.
    floydWarshall(dist, next);
    // Check if there is a path between the source and destination.
    if (dist[src][dest] == INF)
    {
        return "-1";
    }
    // Reconstruct the path.
    string path = to_string(src);
    while (src != dest)
    {
        src = static_cast<size_t>(next[src][dest]);
        path += "->" + to_string(src);
    }
    return path;
}

bool Algorithms::isContainsCycle(Graph &graph)
{
    vector<int>::size_type v = graph.getVertices();
    string cycle = "The cycle is:";
    
    
    if (graph.isDirected())
    { // Mark all the vertices as not visited and not part of the recursion stack.

        vector<bool> visited(v, false);
        vector<bool> recStack(v, false);
        
        
        // Call the recursive helper function to detect cycle in different DFS trees.
        for (size_t i = 0; i < v; i++)
        {
            if (!visited[i] && DFSIsContainsCycleDirected(graph, i, visited, recStack, cycle))
            {
                cout << cycle << endl;
                return true;
            } 
        }
        
        cout << "0" << endl;
        return false;
    }
    else
    {
        // Mark all the vertices as not visited and not part of the recursion stack.
        vector<bool> visited(v, false);
        // To store parent vertices in DFS tree.
        vector<int> parentVec(v, -1); 
        // Call the recursive helper function to detect cycle in different DFS trees.
        for (size_t i = 0; i < v; i++)
        {
            if (!visited[i])
            {
                if (DFSIsContainsCycleUndirected(graph, i, -1, visited, cycle, parentVec))
                {
                    
                    cout << cycle << endl;
                    return true;
                } 
            }   
        }
        
        cout << "0" << endl;
        return false;
    }
}

string Algorithms::isBipartite(Graph &graph)
{
    // Initialize all vertices as not colored.
    vector<int>::size_type v = graph.getVertices();
    vector<int> color(v, -1);
    string setA = "", setB = "";

    // Call the recursive helper function to check if the graph is bipartite.
    for (size_t i = 0; i < v; i++)
    {
        // If the vertex is not colored, color it and all connected vertices.
        if (color[i] == -1)
        {
            if (paintGraph(graph, 0, color, i) == "0")
            {
                return "0";
            }
        }
    }

    // Assign vertices to sets A and B based on their color
    for (size_t i = 0; i < v; i++)
    {
        if (color[i] == 0)
        {
            setA += to_string(i) + ", ";
        }
        else if (color[i] == 1)
        {
            setB += to_string(i) + ", ";
        }
    }

    // Remove the trailing comma and space from each set
    if (!setA.empty())
    {
        setA = setA.substr(0, setA.size() - 2);
    }
    if (!setB.empty())
    {
        setB = setB.substr(0, setB.size() - 2);
    }

    return "The graph is bipartite: A={" + setA + "}, B={" + setB + "}";
}

string Algorithms::negativeCycle(Graph &graph)
{
    // Create a distance matrix.
    size_t V = graph.getVertices();
    vector<int> dist(V, INF);
    string cycle = "The negative cycle is:";

    // call BellmanFord function to check if there is a negative cycle
    if (BellmanFord(graph, 0, dist, cycle))
    {
        cout << "The graph contains a negative cycle." << endl;
        return cycle;
    }

    return "The graph does not contain a negative cycle.";
}

void Algorithms::DFSIsConnected(vector<vector<int>> &adjMat, size_t src, vector<bool> &visited)
{
    // Mark the current vertex as visited.
    visited[src] = true;
    size_t V = adjMat.size();
    // Recur for all the vertices adjacent to this vertex.
    for (size_t i = 0; i < V; i++)
    {
       if (adjMat[src][i])
       {
              if (!visited[i])
              {
                DFSIsConnected(adjMat, i, visited);
              }
         
       }
    }
}

void Algorithms::floydWarshall(vector<vector<int>> &allDistances, vector<vector<int>> &next)
{
    vector<int>::size_type i, j, k;
    vector<int>::size_type n = allDistances.size();

    // Add all vertices one by one to the set of intermediate vertices.
    for (k = 0; k < n; k++)
    {
        // Pick all vertices as source one by one.
        for (i = 0; i < n; i++)
        {
            // Pick all vertices as destination for the above picked source.
            for (j = 0; j < n; j++)
            {

                // If vertex k is on the shortest path from i to j, then update the value of dist[i][j].
                if (allDistances[i][j] > (allDistances[i][k] + allDistances[k][j]) && (allDistances[k][j] != INF && allDistances[i][k] != INF))
                {
                    allDistances[i][j] = allDistances[i][k] + allDistances[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}

bool Algorithms::DFSIsContainsCycleDirected(Graph &graph, size_t v, vector<bool> &visited, vector<bool> &recStack, string &cycle)
{
    // Mark the current node as visited and part of the recursion stack.
    if (!visited[v])
    {
        visited[v] = true;
        recStack[v] = true;
        
        // Recur for all the vertices adjacent to this vertex.
        vector<vector<int>> adjancencyMatrix = graph.getAdjacencyMatrix();
        size_t n = adjancencyMatrix[v].size();
        for (size_t i = 0; i < n; i++)
        {
            if (adjancencyMatrix[v][i])
            {
                if (!visited[i] && DFSIsContainsCycleDirected(graph, i, visited, recStack, cycle))
                {
                    cycle += "->" + to_string(v);
                    return true;
                }
                else if (recStack[i])
                {
                    cycle += "->" +  to_string(i);
                    return true;
                }
            }
        }
    }
    recStack[v] = false;
    
    return false;
}

bool Algorithms::DFSIsContainsCycleUndirected(Graph &graph, size_t src, int parent, vector<bool> &visited, string &cycle, vector<int> &parentVec)
{
    // Mark the current node as visited.
    visited[src] = true;
    parentVec[src] = parent;
    // Recur for all the vertices adjacent to this vertex.
    vector<vector<int>> adjancencyMatrix = graph.getAdjacencyMatrix();
    size_t n = adjancencyMatrix[src].size();
    for (size_t i = 0; i < n; i++)
    {
        if (adjancencyMatrix[src][i] && !visited[i])
        {
            if (DFSIsContainsCycleUndirected(graph, i, src, visited, cycle, parentVec))
            {
                return true;
            }
        }
        // If an adjacent is visited and not parent of the current vertex, then there is a cycle.
        else if (adjancencyMatrix[src][i] && i != parent)
        {
            cycle = "The cycle is:" + to_string(i);
            
            
            for (size_t j = src; j != i; j = static_cast<size_t> (parentVec[j]))
            {
                cycle += "->" + to_string(j);
            }
            cycle += "->" + to_string(i);
            return true;
        }
    }

    return false;
}


string Algorithms::paintGraph(Graph &graph, size_t c, vector<int> &color, size_t pos)
{
    // If the current vertex is already colored with the same color, the graph is not bipartite.
    if (color[pos] != -1 && color[pos] != c)
    {
        return "0";
    }

    // Color the pos as c and all its adjacent as 1-c.
    color[pos] = c;
    string res = to_string(pos) + ", ";

    // Recur for all the vertices adjacent to this vertex.
    // vector<int>::iterator i;
    vector<vector<int>> adjancencyMatrix = graph.getAdjacencyMatrix();
    size_t v = graph.getVertices();
    for (size_t i = 0; i < v; i++)
    {
        // If the adjacent vertex is connected
        if (adjancencyMatrix[pos][i])
        {
            // If the adjacent vertex is not colored, color it with 1-c and recur.
            if (color[i] == -1)
            {
                string temp = paintGraph(graph, 1 - c, color, i);
                if (temp == "0")
                {
                    return "0";
                }
                res += temp;
            }

            // If the adjacent vertex is already colored with the same color, the graph is not bipartite.
            if (color[i] != -1 && color[i] != 1 - c)
            {
                return "0";
            }
        }
    }
    return res;
}

bool Algorithms::BellmanFord(Graph &graph, size_t src, vector<int> &dist, string &cycle)
{
    size_t V = graph.getVertices();
    vector<vector<int>> adjancencyMatrix = graph.getAdjacencyMatrix();
    // Initialize the distance from the source to itself as 0.
    dist[src] = 0;
    // Create to store the parent of each vertex.
    
    // Relax all edges |V| - 1 times.
    // A simple shortest path from src to any other vertex can have at-most |V| - 1 edges.
    for (size_t i = 0; i < V - 1; i++)
    {
        for (size_t u = 0; u < V; u++)
        {
            for (size_t v = 0; v < V; v++)
            {

                if (dist[u] != INF && dist[u] + adjancencyMatrix[u][v] < dist[v])
                {
                    dist[v] = dist[u] + adjancencyMatrix[u][v];
                    
                }
            }
        }
    }

    // Check for negative-weight cycles. The above step guarantees the shortest distance if there is no negative cycle.
    // If we get a shorter path, then there is a cycle.
    for (size_t u = 0; u < V; u++)
    {
        for (size_t v = 0; v < V; v++)
        {
            if (dist[u] != INF && dist[u] + adjancencyMatrix[u][v] < dist[v])
            {
                
                return true;
            }
        }
    }
    return false;
}
