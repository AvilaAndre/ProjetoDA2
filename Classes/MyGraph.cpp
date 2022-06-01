//
// Created by asus on 01/06/2022.
//

#include "MyGraph.h"
#include "MaxHeap.h"
#include <limits>
#include <cstddef>
#include <iostream>

#define INF std::numeric_limits<double>::max()

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

void Vertex::setDist(double value) {
    this->dist = value;
}

std::vector<Edge> Vertex::getAdj() {
    return this->adj;
}

void Vertex::setPath(int idx) {
    this->path = idx;
}

int Vertex::getID() {
    return this->id;
}

MyGraph::MyGraph() = default;

void MyGraph::setSize(int size) {
    this->vertexSet.empty();
    for (int i = 0; i <= size; ++i) {
        addVertex(i);
    }
}

void MyGraph::addVertex(int id) {
    vertexSet.emplace_back(id);
}

void MyGraph::addEdge(int orig, int dest, double cap, double dur) {
    //std::cout << "orig" << orig << " dest:" << dest << " capacity:" << cap <<" duration:" << dur << std::endl;
    vertexSet[orig].addEdge(dest, cap, dur);
}

int MyGraph::getNumVertex() {
    return vertexSet.size()-1;
}

std::vector<Vertex> MyGraph::getVertexSet() {
    return vertexSet;
}

Vertex MyGraph::getVertex(int idx) {
    return vertexSet[idx];
}

void MyGraph::dijkstraHighestCapacityPath(int origin) {
    for(auto v : vertexSet) {
        v.setDist(0);
        v.setPath(-1);
    }
    vertexSet[origin].setDist(INF);
    MaxHeap<int, double> q(getNumVertex(), -1);



    //std:cout << s.getDist() << "-" << s.getDist() << std::endl;
    for (int k = 1; k <= getNumVertex(); k++) {
        q.insert(k, vertexSet[k].getDist());
    }
    while( q.getSize() > 0 ) {
        auto v = q.removeMax().first;
        for(auto e : vertexSet[v].getAdj()) {
            //std::cout << min(vertexSet[v].getDist(), e.getCapacity()) << ">" << vertexSet[e.getDest()].getDist() << std::endl;
            if (min(vertexSet[v].getDist(), e.getCapacity()) > vertexSet[e.getDest()].getDist()) {
                vertexSet[e.getDest()].setDist(min(vertexSet[v].getDist(), e.getCapacity()));
                vertexSet[e.getDest()].setPath(v);
                q.increaseKey(e.getDest(), e.getCapacity());
            }
        }
    }
}
