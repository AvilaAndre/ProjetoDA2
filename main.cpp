#include <iostream>
#include <limits>
#include <algorithm>
#include <stdio.h>
#include <deque>
#include <queue>

#include "Classes/Helper.h"

#define INF std::numeric_limits<double>::max()

void buildPath(std::string *path, int number) {
    if (number < 10)
        *path = "in0" + std::to_string(number) + "_b";
    else
        *path = "in" + std::to_string(number) + "_b";
}

void Situation11(Helper helper) {
    std::cout << "* Exercise 1.1" << std::endl;

    for (int j = 1; j < 11; ++j) {
        MyGraph graph = MyGraph();

        std::string path = "";
        buildPath(&path, j);

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
    std::cout << "* Exercise 1.2" << std::endl;

    for (int j = 0; j < 11; ++j) {
        MyGraph graph = MyGraph();

        std::string path = "";
        buildPath(&path, j);

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

void path_printer(std::vector<std::deque<int>> *encaminhamentos) {
    for (auto road: *encaminhamentos) {
        for (int i = 0; i < road.size(); ++i) {
            std::cout << road[i];
            if (i != road.size()-1) std::cout << "->";
        }
        std::cout << std::endl;
    }
}

bool path_finder(std::vector<std::vector<int>> &rGraph, int &s, int &t, int parent[],
                 int &u, int &v, std::vector<std::deque<int>> &encaminhamentos,
                 int &dimension, int &extra) {

    std::deque<int> caminho = {};
    int minCap = INT_MAX;
    for (v = t; v != s; v = parent[v]) {
        u = parent[v];
        //std::cout << "dimension\t" << dimension <<"\trGraph\t" << rGraph[u][v] << "\n";
        caminho.push_front(v);
        if (minCap > rGraph[u][v]) {
            minCap = rGraph[u][v];
        }
    }

    caminho.push_front(s);
    encaminhamentos.push_back(caminho);

    for (v = t; v != s; v = parent[v]) {
        u = parent[v];
        rGraph[u][v] -= minCap;
        rGraph[v][u] += minCap;
    }

    if (minCap < dimension) {
        dimension -= minCap;
        return true;
    } else {
        extra = minCap - dimension;
        dimension = 0;
        return false;
    }
}

void Situation21(Helper helper) {
    std::cout << "* Exercise 2.1" << std::endl;

    int graph_number;
    std::cout << "What graph do you want to use? (number 1-10)" << std::endl;
    std::cin >> graph_number;

    int dimension;
    std::cout << "What dimension do you want?";
    std::cin >> dimension;

    MyGraph graph = MyGraph();

    std::string path = "";
    buildPath(&path, graph_number);

    std::cout << "CASE " << graph_number << std::endl;
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
    int extra = 0; //free capacity
    bool peopleToGo = true;

    while (helper.bfs(rGraph, s, t, parent) && peopleToGo) {
        peopleToGo = path_finder(rGraph, s, t, parent,
                    u, v, encaminhamentos, dimension, extra);
    }

    if (dimension == 0) {
        std::cout << "Possible paths:" << std::endl;
        path_printer(&encaminhamentos);
    } else {
        std::cout << "There are no possible paths for this dimension of people\n";
        return;
    }

    //Exercise 2.2
    bool valid_option;
    std::cout << "Do you want to increase the number of people in the group?" << std::endl;
    do {
        valid_option = true;
        char user_answer;
        std::cout << "(y/n)" << std::endl;
        std::cin >> user_answer;

        switch (user_answer) {
            case 'y':
                int add;
                std::cout << "How many people do you want to add to the group?" << std::endl;
                std::cin >> add;
                if (add <= extra) {
                    std::cout << "The paths are the same: " << std::endl;
                    path_printer(&encaminhamentos);
                } else {
                    add -= extra;
                    peopleToGo = true;
                    while (helper.bfs(rGraph, s, t, parent) && peopleToGo) {
                        peopleToGo = path_finder(rGraph, s, t, parent,
                                                 u, v, encaminhamentos, add, extra);
                    }
                    if (add == 0) {
                        std::cout << "Possible paths:" << std::endl;
                        path_printer(&encaminhamentos);
                    } else {
                        std::cout << "There are no possible paths for this many people!\n";
                    }

                }
                break;
            case 'n':
                return;
            default:
                valid_option = false;
                std::cin.clear();
                std::cin.ignore(100, '\n');
                std::cout << "Invalid option. Please try again." << std::endl;
        }
    } while (!valid_option);

}

void Situation23(Helper helper) {
    std::cout << "* Exercise 2.3" << std::endl;

    for (int j = 1; j < 11; ++j) {
        MyGraph graph = MyGraph();

        std::string path = "";
        buildPath(&path, j);

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

void Situation24(Helper helper) {
    std::cout << "* Exercise 2.4" << std::endl;

    for (int j = 0; j < 11; ++j) {
        MyGraph graph = MyGraph();

        std::string path = "";
        buildPath(&path, j);

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

        std::pair<double, std::vector<double>> ans1 = helper.earliestStart(graph);


        std::cout << "The group would meet again at the destination after " << ans1.first << " hours, minimum." << std::endl;
    }
}

void Situation25(Helper helper) {
    std::cout << "* Exercise 2.5" << std::endl;

    for (int j = 0; j < 11; ++j) {
        MyGraph graph = MyGraph();

        std::string path = "";
        buildPath(&path, j);
        
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

        std::pair<double, std::vector<double>> ans1 = helper.earliestStart(graph);


        std::vector<double> ans2 = helper.latestFinish(graph, ans1.first);

        /*
        for (int u = 1; u< graph.getNumVertex()+1; u++) {
            std::cout << "ES[" << u << "] " << ans1.second[u] << " LF[" << u << "] "<< ans2[u] << std::endl;
        }


        for (int i = 1; i < graph.getNumVertex() + 1; ++i) {
            for (Edge e: graph.getVertex(i).getAdj()) {
                double es = ans1.second[i];
                double lf = ans2[e.getDest()];
                double ls = lf - e.getDuration();
                double ft = ls - es;
                double fl = ans1.second[e.getDest()] - es - e.getDuration();
                std::cout << i << "->" << e.getDest();
                std::cout << " ES " << es;
                std::cout << " LF "<< lf;
                std::cout << " LS " << ls;
                std::cout << " FT " << ft;
                std::cout << " FL " << fl;
                std::cout << std::endl;
            }
        }

        */

        double biggestFT = 0;
        std::vector<int> waitingPlaces = {};

        for (int i = 1; i < graph.getNumVertex() + 1; ++i) {
            for (Edge e: graph.getVertex(i).getAdj()) {
                double ft = ans2[e.getDest()] - e.getDuration() - ans1.second[i];
                if (ft > biggestFT) {
                    biggestFT = ft;
                    waitingPlaces = {i};
                } else if (ft == biggestFT) {
                    waitingPlaces.push_back(i);
                }
            }
        }

        std::cout << "The largest amount of time someone will need to wait is " << biggestFT << " hours." << std::endl;
        std::cout << "The waiting will be done in nodes ";
        for (int no: waitingPlaces)
            std::cout << no << " ";
        std::cout << "." << std::endl;
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
                Situation21(help);
                break;
            case 23 :
                Situation23(help);
                break;
            case 24 :
                Situation24(help);
                break;
            case 25 :
                Situation25(help);
                break;
            case 0 :
                separator();
                exit(0);
            default:
                std::cout << "\n Invalid input!\n";
        }
    }
}