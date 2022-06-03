#include <iostream>
#include <limits>
#include <algorithm>
#include <stdio.h>
#include <deque>

#include "Classes/Helper.h"

#define INF std::numeric_limits<double>::max()

void Situation11(Helper helper) {
    for (int j = 1; j < 11; ++j) {
        MyGraph graph = MyGraph();
        std::string path = "";
        if (j < 10)
            path = "in0" + std::to_string(j) + "_b";
        else
            path = "in" + std::to_string(j) + "_b";
        helper.loadGraphWithData(&graph, path);
        graph.dijkstraHighestCapacityPath(1);
        std::vector<int> roadPath = graph.getPath(1, graph.getNumVertex());
        std::cout << "Path: ";
        for (int i = 0; i < roadPath.size(); ++i) {
            std::cout << roadPath[i];
            if (i != roadPath.size()-1) std::cout << "->";
        }
        std::cout << std::endl;

        std::cout << "(" << j << ") Record: " << graph.getVertex(graph.getNumVertex()).getDist() << std::endl; //TODO: Perguntar ao user qual o que ele quer ver :)
    }
}


void Situation12(Helper helper) {
    for (int j = 0; j < 11; ++j) {
        MyGraph graph = MyGraph();
        std::string path = "";
        if (j < 10)
            path = "in0" + std::to_string(j) + "_b";
        else
            path = "in" + std::to_string(j) + "_b";

        helper.loadGraphWithData(&graph, path);

        double minCapacity = 0;
        double maxCapacity = 0;
        int minTranshipment = 0;
        int maxTranshipment = 0;

        std::cout << "CASE " << j << ":" << std::endl;

        graph.dijkstraHighestCapacityPath(1);
        std::vector<int> roadPathA = graph.getPath(1, graph.getNumVertex());

        //std::cout << "Caminho A- Capacidade:" << graph.getVertex(graph.getNumVertex()).getDist() << " - Transbordos:" << roadPathA.size() << std::endl;

        maxCapacity = (double) graph.getVertex(graph.getNumVertex()).getDist();
        maxTranshipment = roadPathA.size();


        graph.BFS(1);
        std::vector<int> roadPathB = graph.getPath(1, graph.getNumVertex());

        int record = INT_MAX/2;
        for (int i = 0; i < roadPathB.size(); ++i) {
            if (graph.getVertex(roadPathB[i]).getDist() < record) {
                record = graph.getVertex(roadPathB[i]).getDist();
            }
        }

        minCapacity = (double) record;
        minTranshipment = roadPathB.size();

        std::cout << "Minimum capacity: " << minCapacity << " Maximum capacity: " << maxCapacity << " Minimum Transhipments: " << minTranshipment << " Maximum Transhipments: " << maxTranshipment << std::endl;

        if (minCapacity == maxCapacity && minTranshipment == maxTranshipment) {
            std::cout << "Found an optimal solution!" << std::endl << std::endl;
            continue;
        }

        std::vector<std::pair<double, std::vector<int>>> paretos = graph.find22SolutionB(1, graph.getNumVertex(), minCapacity, maxTranshipment, 100);

        std::cout << "size: " << paretos.size() << std::endl;

        for (int k = 0; k < paretos.size(); ++k) {
            std::cout << k+1 << " - " << paretos[k].first << " - Path: ";
            for (int i = 0; i < paretos[k].second.size(); ++i) {
                std::cout << paretos[k].second[i];
                if (i != paretos[k].second.size()-1) std::cout << "->";
            }
            std::cout << std::endl;
        }

        std::cout << std::endl;

        //TODO: Perguntar ao user qual o que ele quer ver :)
    }
}

//mariana 2.1 tentativa -------------------------------------------------------------------
int fordFulkerson(Helper helper, std::vector<std::vector<int>> graph, int s, int t) {

    int V = graph.size();

    //residual graph
    std::vector<std::vector<int>> rGraph;

    for (int i = 1; i < V; i++) {
        for (int j = 1; j < V; j++) {
            rGraph[i][j] = graph[i][j];
        }
    }
    int parent[V];

    int max_flow = 0;

    while (helper.bfs(rGraph, s, t, parent)) {
        int path_flow = INT_MAX;

        for (int n = t; n != s; n = parent[n]) {
            int m = parent[n];
            path_flow = std::min(path_flow, rGraph[m][n]);
        }

        for (int n = t; n != s; n = parent[n]) {
            int m = parent[n];
            rGraph[m][n] -= path_flow;
            rGraph[n][m] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

void Situation21(Helper helper) {

    std::cout << "Exercise 2.1" << std::endl;
    for (int j = 1; j < 11; ++j) {
        MyGraph graph = MyGraph();
        //MyGraph rGraph = MyGraph();
        std::string path = "";
        if (j < 10)
            path = "in0" + std::to_string(j) + "_b";
        else
            path = "in" + std::to_string(j) + "_b";
        helper.loadGraphWithData(&graph, path);

        std::cout << "creating rGraph" << std::endl;

        std::vector<std::vector<int>> rGraph;
        rGraph.resize(graph.getNumVertex() + 1);
        rGraph.emplace_back();
        rGraph[0].resize(graph.getNumVertex() + 1);

        std::cout << "creating rGraph for loop" << std::endl;
        for (int i = 1; i < graph.getNumVertex() + 1; ++i) {
            rGraph[i].resize(graph.getNumVertex() + 1);
            for (int k = 1; k < graph.getNumVertex() + 1; ++k) {
                rGraph[i][k] = 0;
            }
            for (int k = 1; k < graph.getVertex(i).getAdj().size(); ++k) {
                rGraph[i][graph.getVertex(i).getAdj()[k].getDest()] = (int) graph.getVertex(
                        i).getAdj()[k].getCapacity();
            }
        }
        std::cout << "The maximum possible flow is " << fordFulkerson(helper, rGraph, 0, 5);
    }
}
//mariana 2.1 FIM tentativa ---------------------------------------------------------------

void Situation22(Helper helper) {
    for (int j = 1; j < 11; ++j) {
        MyGraph graph = MyGraph();
        std::string path = "";
        if (j < 10)
            path = "in0" + std::to_string(j) + "_b";
        else
            path = "in" + std::to_string(j) + "_b";
        helper.loadGraphWithData(&graph, path);
        graph.dijkstraHighestCapacityPath(1);
        std::vector<int> roadPath = graph.getPath(1, graph.getNumVertex());
        std::cout << "Path: ";
        for (int i = 0; i < roadPath.size(); ++i) {
            std::cout << i;
            if (i != roadPath.size()-1) std::cout << "->";
        }
        std::cout << std::endl;

        std::cout << "(" << j << ") Record: " << graph.getVertex(graph.getNumVertex()).getDist() << std::endl; //TODO: Perguntar ao user qual o que ele quer ver :)
    }
}



void Situation23(Helper helper) {
    //----
    for (int j = 1; j < 11; ++j) {
        MyGraph graph = MyGraph();
        //MyGraph rGraph = MyGraph();
        std::string path = "";
        if (j < 10)
            path = "in0" + std::to_string(j) + "_b";
        else
            path = "in" + std::to_string(j) + "_b";


        std::cout << "CASE " << j << std::endl;
        helper.loadGraphWithData(&graph, path);


        std::vector<std::vector<int>> rGraph;

        rGraph.resize(graph.getNumVertex()+1);
        rGraph[0].resize(graph.getNumVertex()+1);

        for (int i = 1; i < graph.getNumVertex()+1; ++i) {
            rGraph[i].resize(graph.getNumVertex()+1);
            for (int k = 1; k < graph.getNumVertex()+1; ++k) {
                rGraph[i][k] = 0;
            }
            for (int k = 0 ; k < graph.getVertex(i).getAdj().size(); ++k) {
                rGraph[i][graph.getVertex(i).getAdj()[k].getDest()] = (int) graph.getVertex(i).getAdj()[k].getCapacity();
            }
        }


        std::vector<std::deque<int>> encaminhamentos = {};
        int u, v;
        int parent[graph.getNumVertex()+1];
        int s = 1;
        int t = graph.getNumVertex();
        int max_flow = 0;

        while (helper.bfs(rGraph, s, t, parent)) {
            int path_flow = INT_MAX;
            std::deque<int> caminho = {};
            for (v = t; v != s; v = parent[v]) {
                u = parent[v];
                caminho.push_front(v);
                path_flow = std::min(path_flow, rGraph[u][v]);
            }
            caminho.push_front(s);
            encaminhamentos.push_back(caminho);


            for (v = t; v != s; v = parent[v]) {
                u = parent[v];
                rGraph[u][v] -= path_flow;
                rGraph[v][u] += path_flow;
            }

            max_flow += path_flow;
        }

        std::cout << "Maximum group dimension " << max_flow << std::endl;
        std::cout << "Possible paths:" << std::endl;
        for (auto road: encaminhamentos) {
            for (int i = 0; i < road.size(); ++i) {
                std::cout << road[i];
                if (i != road.size()-1) std::cout << "->";
            }
            std::cout << std::endl;
        }
    }
}

void separator() {
    std::cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << std::endl;
}

int main() {
    int n;

    while (true) {
        Helper help = Helper();
        separator();
        std::cout << "* Situations: 11, 12, 21, 22, 23, 24, 25" << std::endl;
        std::cout << "* PRESS 0 TO QUIT" << std::endl << "*" << std::endl;
        std::cout << "* Situation:";
        std::cin >> n;
        std::cout << "*" << std::endl;
        if (std::cin.eof()) {
            separator();
            exit(1);
        }
        if (!std::cin.good()) {
            std::cout << "\n Invalid input!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (n) {
            case 11:
                Situation11(help);
                break;
            case 12 :
                Situation12(help);
                break;
            case 21 :
                Situation21(help);
                break;
            case 22 :
                //Situation22(/*graph*/);
                break;
            case 23 :
                Situation23(help);
                break;
            case 24 :
                //Situation24(/*graph*/);
                break;
            case 25 :
                //Situation25(/*graph*/);
                break;
            case 4:
                Situation22(help);
                break;
            case 0 :
                separator();
                exit(0);
            default:
                std::cout << "\n Invalid input!\n";
        }
    }
}