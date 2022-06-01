//
// Created by asus on 01/06/2022.
//

#include "MyGraph.h"


Edge::Edge(int destination, double c, double d) : dest(destination), capacity(c), duration(d) {

}


int Edge::getDest() {
    return dest;
}

double Edge::getCapacity() {
    return this->capacity;
}

double Edge::getDuration() {
    return this->duration;
}


Vertex::Vertex(int i) {
    this->id = i;
}

void Vertex::addEdge(int dest, double capacity, double duration) {
    this->adj.emplace_back(dest, capacity, duration);
}

double Vertex::getDist() {
    return this->dist;
}

std::vector<Edge> Vertex::getAdj() {
    return this->adj;
}

MyGraph::MyGraph() = default;

void MyGraph::setSize(int size) {
    this->vertexSet.empty();
    for (int i = 0; i < size; ++i) {
        addVertex(i);
    }
}

void MyGraph::addVertex(int id) {
    vertexSet.emplace_back(id);
}

void MyGraph::addEdge(int orig, int dest, double cap, double dur) {
    vertexSet[orig].addEdge(dest, cap, dur);
}

int MyGraph::getNumVertex() {
    return vertexSet.size();
}

std::vector<Vertex> MyGraph::getVertexSet() {
    return vertexSet;
}

Vertex MyGraph::getVertex(int idx) {
    return vertexSet[idx];
}

void MyGraph::dijkstraHighestCapacityPath(int i) {

}
