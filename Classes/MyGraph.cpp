//
// Created by asus on 01/06/2022.
//

#include "MyGraph.h"
#include "MaxHeap.h"
#include <limits>
#include <cstddef>
#include <iostream>
#include <algorithm>
#include <queue>

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

int Vertex::getPath() {
    return this->path;
}

void Vertex::setPath(int idx) {
    this->path = idx;
}

bool Vertex::getVisited() {
    return this->visited;
}

void Vertex::setVisited(bool value) {
    this->visited = value;
}

int Vertex::getID() {
    return this->id;
}

MyGraph::MyGraph() = default;

void MyGraph::setSize(int size) {
    this->vertexSet = vector<Vertex>();
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

std::vector<int> MyGraph::getPath(int orig, int dest) {
    std::vector<int> roadPath = std::vector<int>();
    int before = dest;
    while (before != orig) {
        before = getVertex(before).path;
        if (before == -1) {
            break;
        }
        roadPath.push_back(before);
    }
    std::reverse(roadPath.begin(),roadPath.end());
    return roadPath;
}

void MyGraph::dijkstraHighestCapacityPath(int origin) {
    for(auto v : vertexSet) {
        v.setDist(0);
        v.setPath(-1);
    }
    vertexSet[origin].setDist(INF);
    MaxHeap<int, double> q(getNumVertex(), -1);

    for (int k = 1; k <= getNumVertex(); k++) {
        q.insert(k, vertexSet[k].getDist());
    }
    while( q.getSize() > 0 ) {
        auto v = q.removeMax().first;
        for(auto e : vertexSet[v].getAdj()) {
            if (min(vertexSet[v].getDist(), e.getCapacity()) > vertexSet[e.getDest()].getDist()) {
                vertexSet[e.getDest()].setDist(min(vertexSet[v].getDist(), e.getCapacity()));
                vertexSet[e.getDest()].setPath(v);
                q.increaseKey(e.getDest(), e.getCapacity());
            }
        }
    }
}

void MyGraph::BFS(int orig) {
    for(auto v : vertexSet) {
        v.setDist(0);
        v.setPath(-1);
        v.setVisited(false);
    }

    std::queue<int> queue;
    vertexSet[orig].setVisited(true);
    queue.push(orig);

    while(!queue.empty())
    {
        int s = queue.front();
        queue.pop();

        for (auto adj: vertexSet[s].getAdj())
        {
            if (!vertexSet[adj.getDest()].getVisited() && adj.getCapacity() > 0)
            {
                vertexSet[adj.getDest()].setVisited(true);
                vertexSet[adj.getDest()].setPath(s);
                vertexSet[adj.getDest()].setDist(adj.capacity);
                queue.push(adj.getDest());
            }
        }
    }
}


vector<pair<int, vector<int>>> MyGraph::find22SolutionRecursiveReacher(int self, double capacity, vector<bool> visited, vector<int> path, double minCapacity, int maxTranshipment, int dest) {
    //std::cout << "New branch!" << self << std::endl;
    if (capacity < minCapacity) {
        //std::cout << "Capacity smaller than the minimum. " << capacity << "<" << minCapacity << std::endl;
        return {{-1, vector<int>()}};
    }

    if (path.size() > maxTranshipment) {
        //std::cout << "Surpassed maximum transhipments. " << path.size() << ">" << maxTranshipment << std::endl;
        return {{-1, vector<int>()}};
    }
    if (self == dest) {
        //std::cout << "Found the destination!" << std::endl;
        return {{capacity, path}};
    }

    path.push_back(self);
    vector<pair<int, vector<int>>> ans = {};

    for (Edge e : vertexSet[self].adj) {
        //std::cout << "visited: " << visited[e.dest] << std::endl;
        if (!visited[e.dest]) {
            visited[e.dest] = true;
            vector<pair<int, vector<int>>> response = find22SolutionRecursiveReacher(e.dest, min(capacity, e.capacity), visited, path, minCapacity,
                                           maxTranshipment, dest);
            for (int i = 0; i < response.size(); ++i) {
                if (response[i].first != -1) {
                    ans.push_back(response[i]);
                }
            }
        }
    }

    if (ans.size() == 0){
        //std::cout << "This branch had no answers!" << std::endl;
        return {{-1, vector<int>()}};
    } else return ans;

}


vector<pair<int, vector<int>>> MyGraph::find22Solution(int orig, int dest, double minCapacity, int maxTranshipment) {
    vector<bool> visited(vertexSet.size(), false);
    vector<int> path = vector<int>();

    visited[orig] = true;

    vector<pair<int, vector<int>>> ans = vector<pair<int, vector<int>>>();

    for (Edge e : vertexSet[orig].adj) {
        //std::cout << "visited: " << visited[e.dest] << std::endl;
        visited[e.dest] = true;
        vector<pair<int, vector<int>>> response = find22SolutionRecursiveReacher(e.dest, e.capacity, visited, path, minCapacity, maxTranshipment, dest);
        for (int i = 0; i < response.size(); ++i) {
            if (response[i].first != -1) {
                ans.push_back(response[i]);
            }
        }
    }

    if (ans.empty()) return {};
    else return ans;
}

vector<pair<double, vector<int>>> MyGraph::find22SolutionB(int orig, int dest, double minCapacity, int maxTranshipment, int answers) {
    vector<pair<double, vector<int>>> workingPaths = vector<pair<double, vector<int>>>();

    vector<pair<double, vector<int>>> paths = vector<pair<double, vector<int>>>();

    workingPaths.push_back({INF, {orig}});


    while (!workingPaths.empty()) {
        if (answers > 0 && paths.size() >= answers)
            return paths;
        if (vertexSet[workingPaths[0].second[workingPaths[0].second.size()-1]].adj.size() > 0) {
            vector<Edge> adjacents = vertexSet[workingPaths[0].second[workingPaths[0].second.size()-1]].adj;
            pair<double, vector<int>> base = workingPaths[0];
            if (base.second.size() >= maxTranshipment+1 || base.first < minCapacity) {
                workingPaths.erase(workingPaths.begin());
                //std::cout << "reached maximum number of transhipments" << std:: endl;
                continue;
            }
            for (int i = 0; i < adjacents.size(); ++i) {
                if (i == adjacents.size() - 1) {
                    if (adjacents[i].dest == dest) {
                        base.second.push_back(adjacents[i].dest);
                        base.first = min(base.first, adjacents[i].capacity);
                        if (base.first >= minCapacity)
                            paths.push_back(base);
                        workingPaths.erase(workingPaths.begin());
                    } else {
                        workingPaths[0].second.push_back(adjacents[i].dest);
                        workingPaths[0].first = min(workingPaths[0].first, adjacents[0].capacity);
                    }
                } else {
                    if (adjacents[i].dest == dest) {
                        pair<double, vector<int>> pair2add(base);
                        pair2add.second.push_back(adjacents[i].dest);
                        pair2add.first = min(pair2add.first, adjacents[i].capacity);
                        if (pair2add.first >= minCapacity)
                            paths.push_back(pair2add);
                    } else {
                        pair<double, vector<int>> pair2add(base);
                        pair2add.second.push_back(adjacents[i].dest);
                        pair2add.first = min(pair2add.first, adjacents[i].capacity);
                        if (pair2add.first >= minCapacity)
                            workingPaths.push_back(pair2add);
                    }
                }
            }
        }
        else {
            workingPaths.erase(workingPaths.begin());
        }
    }

    return paths;
}


