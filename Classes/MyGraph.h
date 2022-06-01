//
// Created by asus on 01/06/2022.
//

#ifndef PROJETODA2_MYGRAPH_H
#define PROJETODA2_MYGRAPH_H

#include <vector>

struct Edge {
private:
    int dest;
    double capacity;
    double duration;
public:
    Edge(int dest, double c, double d);
    friend class Graph;
    friend class Vertex;

    int getDest();
    double getCapacity();
    double getDuration();

    friend class MyGraph;
    friend class Vertex;

};


struct Vertex {
    Vertex(int i);

private:
    int id;
    std::vector<Edge> adj;
    int path = -1;
    double dist = 0;
    bool visited = false;
public:

    int getID();
    void addEdge(int dest, double capacity, double duration);
    friend class Graph;

    double getDist();
    void setDist(double value);

    std::vector<Edge> getAdj();

    int getPath();
    void setPath(int idx);

    bool getVisited();
    void setVisited(bool value);

    friend class MyGraph;
};

class MyGraph {

    std::vector<Vertex> vertexSet;

    std::vector<std::pair<int, std::vector<int>>> find22SolutionRecursiveReacher(int self, double capacity, std::vector<bool> visited, std::vector<int> path, double minCapacity, int maxTranshipment, int dest);


public:
    MyGraph();

    void setSize(int size);

    void addVertex(int id);

    void addEdge(int orig, int dest, double cap, double duration);

    int getNumVertex();

    std::vector<Vertex> getVertexSet();

    Vertex getVertex(int idx);

    void dijkstraHighestCapacityPath(int i);

    void BFS(int orig);

    std::vector<int> getPath(int orig, int dest);

    std::vector<std::pair<int, std::vector<int>>> find22Solution(int orig, int dest, double minCapacity, int maxTranshipment);
};


#endif //PROJETODA2_MYGRAPH_H
