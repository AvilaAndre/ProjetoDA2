#include <iostream>
#include <limits>

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
            std::cout << i;
            if (i != roadPath.size()-1) std::cout << "->";
        }
        std::cout << std::endl;

        std::cout << "(" << j << ") Record: " << graph.getVertex(graph.getNumVertex()).getDist() << std::endl; //TODO: Perguntar ao user qual o que ele quer ver :)
    }
}


void Situation12(Helper helper) {
    for (int j = 1; j < 11; ++j) {
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

        //std::cout << "Caminho B- Capacidade:" << record << " - Transbordos:" << roadPathB.size() << std::endl;

        minCapacity = (double) record;
        minTranshipment = roadPathB.size();

        std::cout << "Minumum capacity: " << minCapacity << " Maximum capacity: " << maxCapacity << " Minimum Transhipments: " << minTranshipment << " Maximum Transhipments: " << maxTranshipment << std::endl;

        if (minCapacity == maxCapacity && minTranshipment == maxTranshipment) {
            std::cout << "Found an optimal solution!" << std::endl << std::endl;
            continue;
        }

        /*
        std::vector<std::pair<int, std::vector<int>>> paretos = graph.find22Solution(1, graph.getNumVertex(), minCapacity, maxTranshipment);

        std::cout << "size: " << paretos.size() << std::endl;

        for (int k = 0; k < paretos.size(); ++k) {
            std::cout << "Pareto-otimo capacidade: "<< paretos[k].first << std::endl;
            std::cout << "Path: ";
            for (int i = 0; i < paretos[k].second.size(); ++i) {
                std::cout << i;
                if (i != paretos[k].second.size()-1) std::cout << "->";
            }
            std::cout << std::endl;
        }
        */

        std::cout << std::endl;

        //TODO: Perguntar ao user qual o que ele quer ver :)
    }
}

void Situation21(/*Graph<Stop> graph*/) {
    std::cout << "Exercise 2.1" << std::endl;
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
                Situation21(/*graph*/);
                break;
            case 22 :
                //Situation22(/*graph*/);
                break;
            case 23 :
                //Situation23(/*graph*/);
                break;
            case 24 :
                //Situation24(/*graph*/);
                break;
            case 25 :
                //Situation25(/*graph*/);
                break;
            case 0 :
                separator();
                exit(0);
            default:
                std::cout << "\n Invalid input!\n";
        }
    }
}