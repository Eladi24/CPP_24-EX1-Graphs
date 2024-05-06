#ifndef _ALGORITHMS_HPP_
#define _ALGORITHMS_HPP_
#include <iostream>
#include <string>
#include "Graph.hpp"
using namespace std;
namespace ariel
{
    
    class Algorithms
    {
    public:

        /*
        * @brief
        * This function checks if the graph is connected.
        * A graph is connected if there is a path between every pair of vertices.
        * A directed graph is strongly connected if there is a path between every pair of vertices.
        * @param graph - Graph object.
        * @return int 1 if the graph is connected, 0 otherwise.
        */

        static int isConnected(Graph &graph);

        /*
        * @brief
        * This function finds the shortest path between two vertices.
        * The function returns the shortest path as a string.
        * @param graph - Graph object.
        * @param src - source vertex.
        * @param dest - destination vertex.
        * @return string - shortest path between src and dest.
        */

        static string shortestPath(Graph &graph, size_t src, size_t dest);

        /*
        * @brief
        * This function checks if the graph contains a cycle.
        * A cycle is a path of edges that starts and ends at the same vertex.
        * @param graph - Graph object.
        * @return string - the cycle if the graph contains a cycle or "0" otherwise.
        */
       
        static bool isContainsCycle(Graph &graph);

        /*
        * @brief
        * This function checks if the graph is bipartite.
        * A graph is bipartite if the vertices can be divided into two disjoint sets such that no two vertices in the same set are adjacent.
        * @param graph - Graph object.
        * @return string - the two disjoint sets if the graph is bipartite, "Graph is not bipartite" otherwise.
        */
        static string isBipartite(Graph &graph);

        /*
        * @brief
        * This function checks if the graph contains a negative cycle.
        * A negative cycle is a cycle whose edges sum to a negative value.
        * @param graph - Graph object.
        * 
        */
        static string negativeCycle(Graph &graph);

        /*
        * @brief
        * This function solves all-pairs shortest path, using Floyd-Warshall algorithm.
        * The function returns the shortest path between all pairs of vertices.
        * @param adjancencyMatrix - 2D vector representing the graph.
        * @return void
        *
        */
        static void floydWarshall(vector<vector<int>> &allDistances, vector<vector<int>> &next);

        /*
        * @brief
        * This function uses DFS algorithm to check if the graph is connected.
        * @param adjMat - adjacency matrix.
        * @param src - source vertex.
        * @param visited - array of visited vertices.
        * @return void
        */
        static void DFSIsConnected(vector<vector<int>> &adjMat, size_t src, vector<bool> &visited);

        /*
        * @brief
        * This function uses DFS algorithm to check if an directed graph contains a cycle.
        * @param graph - Graph object.
        * @param v - source vertex.
        * @param visited - array of visited vertices.
        * @param recStack - array of vertices in the recursion stack.
        * @return bool true if the graph contains a cycle, false otherwise.
        */
        static bool DFSIsContainsCycleDirected(Graph &graph, size_t v, vector<bool> &visited, vector<bool> &recStack, string &cycle);

        /*
        * @brief
        * This function uses DFS algorithm to check if an undirected graph contains a cycle.
        * @param graph - Graph object.
        * @param v - source vertex.
        * @param parent - parent vertex.
        * @param visited - array of visited vertices.
        * @return bool true if the graph contains a cycle, false otherwise.
        */
        static bool DFSIsContainsCycleUndirected(Graph &graph, size_t v, int parent, vector<bool> &visited, string &cycle, vector<int> &parentVec);

        /*
        * @brief
        * This function colors the vertices of the graph using two colors, to check if the graph is bipartite.
        * @param graph - Graph object.
        * @param v - source vertex.
        * @param color - array of colors.
        * @param pos - current position.
        * @return string the two disjoint sets if the graph is bipartite, "Graph is not bipartite" otherwise.
        */
       static string paintGraph(Graph &graph, size_t c, vector<int> &color, size_t pos); 

       /*
       * @brief
         * This function uses Bellman-Ford algorithm to check if the graph contains a negative cycle.
         * @param graph - Graph object.
         * @param src - source vertex.
         * @param dist - array of distances.
         * @return bool true if the graph contains a negative cycle, false otherwise.
         */
        static bool BellmanFord(Graph &graph, size_t src, vector<int> &dist, string &cycle);

    };
    
} // namespace ariel

#endif

