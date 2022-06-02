//
// Created by asus on 20/05/2022.
//

#ifndef PROJETODA2_HELPER_H
#define PROJETODA2_HELPER_H

#include <vector>
#include <fstream>
#include <iostream>

#include "MyGraph.h"


class Helper {
public:
    void loadGraphWithData(MyGraph *graphToLoad, std::string string);
    bool bfs(std::vector<std::vector<int>> rGraph, int s, int t, int parent[]);
};

#endif //PROJETODA2_HELPER_H
