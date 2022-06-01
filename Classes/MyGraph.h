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
    void addEdge(int dest, double capacity, double duration);
    friend class Graph;

    double getDist();
    std::vector<Edge> getAdj();
};

class MyGraph {

    std::vector<Vertex> vertexSet;


public:
    MyGraph();

    void setSize(int size);

    void addVertex(int id);

    void addEdge(int orig, int dest, double cap, double duration);

    int getNumVertex();

    std::vector<Vertex> getVertexSet();

    Vertex getVertex(int idx);


    void dijkstraHighestCapacityPath(int i);
};


#endif //PROJETODA2_MYGRAPH_H
