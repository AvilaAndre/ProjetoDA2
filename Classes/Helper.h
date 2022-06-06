#ifndef PROJETODA2_HELPER_H
#define PROJETODA2_HELPER_H

#include <vector>
#include <fstream>
#include <iostream>

#include "MyGraph.h"


class Helper {
public:
    /**
     * This functions reads a text file on path "string" and fills the "graphToLoad" with data.
     * @param graphToLoad
     * @param string
     */
    void loadGraphWithData(MyGraph *graphToLoad, std::string string);

    /**
     * Performs a bfs, made specifically for the Edmond-Karp algorithm.
     * @param rGraph a matrix graph.
     * @param s the starting point (start).
     * @param t the finishing point (target).
     * @param parent an array with the parents of each node.
     * @return if a path to the target has been achieved.
     */
    bool bfs(std::vector<std::vector<int>> rGraph, int s, int t, int parent[]);

    /**
     * Performs the critical path's earliest start algorithm.
     * @param graph
     * @return the minimum duration and the earliest start for each node in a pair.
     */
    std::pair<double, std::vector<double>>  earliestStart(MyGraph graph);

    /**
     * Performs the critical path's latest finish algorithm.
     * @param graph
     * @param durMin
     * @return the earliest start for each node.
     */
    std::vector<double> latestFinish(MyGraph graph, double durMin);
};

#endif //PROJETODA2_HELPER_H
