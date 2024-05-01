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
    vector<bool> visited(v, false);
    // Start DFS traversal from the first vertex.
    DFSIsConnected(graph, 0, visited);
    // Check is all vertices are visited.
    for (size_t i = 0; i < v; i++)
    {   
        // If there is a vertex that is not visited, the graph is not connected.
        if (!visited[i])
        {
            return 0;
        }
    }
    return 1;
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
            }
            else
            {
                dist[i][j] = adjacencyMatrix[i][j];
            }
            // Set the next matrix.
            next[i][j] = j;
        }
    }
    // Floyd-Warshall algorithm.
    floydWarshall(dist);
    // Check if there is a path between the source and destination.
    if (dist[src][dest] == INF)
    {
        return "-1";
    }
    // Reconstruct the path.
    string path = to_string(src);
    while (src != dest)
    {
        src = static_cast<size_t> (next[src][dest]);
        path += "->" + to_string(src);
    }
    return path;
}

bool Algorithms::isContainsCycle(Graph &graph)
{
    vector<int>::size_type v = graph.getVertices();
    if (graph.isDirected())
    {   // Mark all the vertices as not visited and not part of the recursion stack.
        
        vector<bool> visited(v, false);
        vector <bool> recStack(v, false);

        // Call the recursive helper function to detect cycle in different DFS trees.
        for (size_t i = 0; i < v; i++)
        {
            if (!visited[i] && DFSIsContainsCycleDirected(graph, i, visited, recStack))
            {
                cout << "The cycle is: " + to_string(i) << endl;
                return true;
            }
        }
        cout << "0" << endl;
        return false;
    }
    else {
        // Mark all the vertices as not visited and not part of the recursion stack.
        vector<bool> visited(v, false);

        // Call the recursive helper function to detect cycle in different DFS trees.
        for (size_t i = 0; i < v; i++)
        {
            if (!visited[i]) {
                if (DFSIsContainsCycleUndirected(graph, i, -1, visited))
                {
                    cout << "The cycle is: " + to_string(i) << endl;
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
            string res = paintGraph(graph, 0, color, i);
            if (res == "0")
            {
                return "0";
            }
            
            // Use the modulo operator to alternate between adding vertices to set A and set B.
            // If i is even, add the vertices to set A, otherwise add them to set B.
            if (i % 2 == 0)
            {
                setA += res;
            }
            else
            {
                setB += res;
            }
        }
        return "The graph is bipartite: A={" + setA + "}, B={" + setB + "}.";
        
    }
    // Strat coloring the first vertex with 0.
    size_t pos = 0;
    return paintGraph(graph, 0, color, pos);
}

string Algorithms::negativeCycle(Graph &graph)
{
    return "0";
}

void Algorithms::DFSIsConnected(Graph &graph, size_t src, vector<bool> &visited)
{
    // Mark the current vertex as visited.
    visited[src] = true;
    // Recur for all the vertices adjacent to this vertex.
    //vector<int>::iterator i;
    vector<vector<int>> adjancencyMatrix = graph.getAdjacencyMatrix();
    size_t v = graph.getVertices();
    for (size_t i = 0; i < v; i++)
    {
        // If the vertex is not visited, then recur for it.
        if (!visited[i])
        {
            // Recur for the adjacent vertices.
            DFSIsConnected(graph, i, visited);
        }
    }
}

void Algorithms::floydWarshall(vector<vector<int>> &allDistances)
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
                }
            }
        }
    }
}

bool Algorithms::DFSIsContainsCycleDirected(Graph &graph, size_t v, vector<bool> &visited, vector<bool> &recStack) 
{
    if (!visited[v])
    {
        // Mark the current node as visited and part of the recursion stack.
        visited[v] = true;
        recStack[v] = true;
        
        // Recur for all the vertices adjacent to this vertex.
        //vector<int>::iterator i;
        vector<vector<int>> adjancencyMatrix = graph.getAdjacencyMatrix();
        size_t v = graph.getVertices();
        for (size_t i = 0; i < v; i++)
        {
            if (!visited[i] && DFSIsContainsCycleDirected(graph, i, visited, recStack))
            {
                return true;
            }
            else if (recStack[i])
            {
                return true;
            }
        }
    }

    // Remove the vertex from the recursion stack.
    recStack[v] = false;
    return false;
}

bool Algorithms::DFSIsContainsCycleUndirected(Graph &graph, size_t src, int parent, vector<bool> &visited)
{
    // Mark the current node as visited.
    visited[src] = true;

    // Recur for all the vertices adjacent to this vertex.
    //vector<int>::iterator i;
    vector<vector<int>> adjancencyMatrix = graph.getAdjacencyMatrix();
    size_t v = graph.getVertices();
    for (size_t i = 0; i < v; i++)
    {
        // If an adjacent is not visited, then recur for that adjacent.
        if (!visited[i])
        {
            if (DFSIsContainsCycleUndirected(graph, i, src, visited))
            {
                return true;
            }
        }
        // If an adjacent is visited and not parent of the current vertex, then there is a cycle.
        else if (i != parent)
        {
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
    //vector<int>::iterator i;
    vector<vector<int>> adjancencyMatrix = graph.getAdjacencyMatrix();
    size_t v = graph.getVertices();
    for (size_t i = 0; i < v; i++)
    {
        // If the adjacent vertex is connected
        if (adjancencyMatrix[pos][i])
        {
            // If the adjacent vertex is not colored, color it with 1-c and recur.
            if (color[i] == -1) {
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
