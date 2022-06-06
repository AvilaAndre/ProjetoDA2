#ifndef PROJETODA2_MYGRAPH_H
#define PROJETODA2_MYGRAPH_H

#include <vector>

struct Edge {
private:
    int dest;
    double capacity;
    double duration;
public:
    /**
     * The constructor of the Edge struct.
     * @param dest Defines the value of maxVol and volume.
     * @param c Defines the capacity.
     * @param d Defines the duration.
     */
    Edge(int dest, double c, double d);
    /**
     * @return Returns the destination's id.
     */
    int getDest();
    /**
     * @return Returns the capacity.
     */
    double getCapacity();
    /**
     * @return Returns the duration.
     */
    double getDuration();

    friend class MyGraph;
    friend class Vertex;

};


struct Vertex {
    /**
     * Creates a Vertex object with id "i".
     * @param i
     */
    Vertex(int i);

private:
    int id;
    std::vector<Edge> adj;
    int path = -1;
    double dist = 0;
    bool visited = false;
public:
    /**
     * @return the Vertex's id.
     */
    int getID();
    /**
     * Adds an Edge to the Vertex's adj vector.
     * @param dest the Edge's destination id.
     * @param capacity the Edge's capacity.
     * @param duration the Edge's duration.
     */
    void addEdge(int dest, double capacity, double duration);

    /**
     * @return the dist variable.
     */
    double getDist();

    /**
     * Sets the dist variable as value.
     * @param value
     */
    void setDist(double value);

    /**
     * @return the adj vector.
     */
    std::vector<Edge> getAdj();

    /**
     * @return the path variable.
     */
    int getPath();
    /**
     * Sets the path variable as idx.
     * @param idx
     */
    void setPath(int idx);

    /**
     * @return if the Vertex has been visited.
     */
    bool getVisited();

    /**
     * Sets the visited variable as value.
     * @param value
     */
    void setVisited(bool value);

    friend class MyGraph;
};

class MyGraph {

    std::vector<Vertex> vertexSet;

    std::vector<std::pair<int, std::vector<int>>> find22SolutionRecursiveReacher(int self, double capacity, std::vector<bool> visited, std::vector<int> path, double minCapacity, int maxTranshipment, int dest);


public:
    /**
     * The MyGraph class constructor.
     */
    MyGraph();
    /**
     * Sets the vertexSet size as "size".
     * @param size
     */
    void setSize(int size);

    /**
     * Adds a Vertex with id "id" to the vertexSet vector.
     * @param id
     */
    void addVertex(int id);
    /**
     * Adds an Edge to the Vertex with id orig with the values dest as id, cap as capacity and duration as duration.
     * @param orig
     * @param dest
     * @param cap
     * @param duration
     */
    void addEdge(int orig, int dest, double cap, double duration);

    /**
     * @return the size of the vertexSet - 1 devido ao Vertex na posição 0 não contar.
     */
    int getNumVertex();
    /**
     * @return the vertexSet vector.
     */
    std::vector<Vertex> getVertexSet();

    /**
     *
     * @param idx
     * @return the Vertex with id "idx".
     */
    Vertex getVertex(int idx);

    /**
     * Performs the dijkstra algorithm with origin i having capacity as a priority, uses a MaxHeap.
     * @param i
     */
    void dijkstraHighestCapacityPath(int i);

    /**
     * Performs the BFS algorithm with origin orig.
     * @param orig
     */
    void BFS(int orig);

    /**
     * @param orig
     * @param dest
     * @return the path from the Vertex with id orig to the Vertex with id dest.
     */
    std::vector<int> getPath(int orig, int dest);

    /**
     * An unused solution to the 1.2 Situation that gets every possible path using recursion.
     * @param orig
     * @param dest
     * @param minCapacity
     * @param maxTranshipment
     * @return a vector with paths and their respective maximumum capacities.
     */
    std::vector<std::pair<int, std::vector<int>>> find22Solution(int orig, int dest, double minCapacity, int maxTranshipment);

    /**
     * Gets every possible path within the minCapacity capacity cap and the maxTranshipment transhipment cap.
     * @param orig
     * @param dest
     * @param minCapacity
     * @param maxTranshipment
     * @param answers
     * @return a vector with paths and their respective maximum capacities.
     */
    std::vector<std::pair<double, std::vector<int>>> find22SolutionB(int orig, int dest, double minCapacity, int maxTranshipment, int answers);

};


#endif //PROJETODA2_MYGRAPH_H
