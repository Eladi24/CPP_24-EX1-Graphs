// ID: 205739907
// Email: eladima66@gmail.com

#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

TEST_CASE("Test isConnected")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == false);

    vector <vector<int>> graph3 = {
        {0, 1, 0, 0, 0},
        {0, 0, 2, 0, 0},
        {0, 0, 0, 3, 0},
        {0, 0, 0, 0, -3},
        {-3, 0, 0, 0, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isConnected(g) == true);
}

TEST_CASE("Test shortestPath")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "-1");

}
TEST_CASE("Test isContainsCycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isContainsCycle(g) == false);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isContainsCycle(g) == true);

    // 4x4 matrix that reprsents a connected directed graph with a negative edges. should throw exception.
    vector<vector<int>> graph3 = {
        {0, 0, 0, 0},
        {4, 0, -6, 0},
        {0, 0, 0, 5},
        {0, -2, 0, 0}};
    g.loadGraph(graph3);
    CHECK_THROWS(ariel::Algorithms::isContainsCycle(g));
    // 4x4 matrix that reprsents a connected undirected graph with a negative edges. should throw exception.
    vector<vector<int>> graph4 = {
        {0, 4, 0, 0},
        {4, 0, -6, -2},
        {0, -6, 0, 5},
        {0, -2, 5, 0}};
    g.loadGraph(graph4);
    CHECK_THROWS(ariel::Algorithms::isContainsCycle(g));
}
TEST_CASE("Test isBipartite")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 0},
        {1, 0, 3, 0, 0},
        {0, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2, 4}, B={1, 3}");
    
    vector<vector<int>> graph4 = { 
        { 0, -1, 0, 1 },
        { 1, 0, 1, 0 },
        { 0, -1, 0, 1 },
        { 1, 0, 1, 0 } };
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1, 3}");
}

TEST_CASE("Test invalid graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));
    
   // 4x5 matrix that reprsents invalid graph.
    vector<vector<int>> graph2 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 0}};
    CHECK_THROWS(g.loadGraph(graph2));

    // 4x3 matrix that reprsents invalid graph.
    vector<vector<int>> graph3 = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0},
        {0, 0, 4}};
    CHECK_THROWS(g.loadGraph(graph3));
}

TEST_CASE("Test negativeCycle")
{
    ariel::Graph g;
    // 4x4 matrix that represents a graph with a negative cycle.
    vector<vector<int>> graph = {
        {0, 0, 0, 0},
        {4, 0, -6, 0},
        {0, 0, 0, 5},
        {0, -2, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::negativeCycle(g) == "The negative cycle is:1->2->3->1");

    vector<vector<int>> graph2 = {
        {0, 1, 0, 0},
        {0, 0, -1, 0},
        {0, 0, 0, -1},
        {-1, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::negativeCycle(g) == "The negative cycle is:0->1->2->3->0");

    vector <vector<int>> graph3 = {
        {0, 1, 0, 6},
        {4, 0, 6, 0},
        {0, 0, 0, 0},
        {0, 2, 0, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::negativeCycle(g) == "The graph does not contain a negative cycle");

    vector <vector<int>> graph4 = {
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 3, 0},
        {0, 0, 0, 0, -3},
        {-3, 0, 0, 0, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::negativeCycle(g) == "The negative cycle is:0->1->2->3->4->0");
}

TEST_CASE ("isDirected")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {1, 0, 0, 1},
        {1, 0, 0, 0}};
    g.loadGraph(graph);
    CHECK(g.isDirected() == true);

vector<vector<int>> graph2 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph2);
    CHECK(g.isDirected() == false);

    vector<vector<int>> graph3 = {
        {0, 0, 0, 0},
        {4, 0, -6, 0},
        {0, 0, 0, 5},
        {0, -2, 0, 0}};
    g.loadGraph(graph3);
    CHECK(g.isDirected() == true);
}

TEST_CASE("Test getTranspose")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {1, 0, 0, 1},
        {1, 0, 0, 0}};
   vector<vector<int>> transpose = {
        {0, 0, 1, 1},
        {1, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 1, 0}};
    g.loadGraph(graph);
    CHECK(g.getTranspose() == transpose);

    vector<vector<int>> graph2 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    vector<vector<int>> transpose2 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph2);
    CHECK(g.getTranspose() == transpose2);
}

TEST_CASE("Test countEdges")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {1, 0, 0, 1},
        {1, 0, 0, 0}};
    g.loadGraph(graph);
    CHECK(g.countEdges() == 6);

    vector<vector<int>> graph2 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph2);
    CHECK(g.countEdges() == 5);

    vector<vector<int>> graph3 = {
        {0, 0, 0, 0},
        {4, 0, -6, 0},
        {0, 0, 0, 5},
        {0, -2, 0, 0}};
    g.loadGraph(graph3);
    CHECK(g.countEdges() == 4);
}