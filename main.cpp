#include <iostream>

#include "Classes/Helper.h"

void Situation11(Graph<Stop> graph) {
    graph.dijkstraShortestPath(1);
    std::cout << "Hello World!" << std::endl;
    std::cout << graph.getNumVertex() << std::endl;
    int record = 0;
    for (int i = 1; i < graph.getNumVertex(); ++i) {
        std::cout << i << "- " << graph.getVertexDist(i) << std::endl;
        for (auto edge: graph.getVertexSet()[i]->adj) {
            if (edge.capacity > record) {
                record = edge.capacity;
            }
        }
    }

    std::cout << "Record: " << record << std::endl;

    return;
}



void separator() {
    std::cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << std::endl;
}

int main() {
    int n;

    while (true) {
        Helper help = Helper();
        Graph<Stop> graph = Graph<Stop>();
        help.loadGraphWithData(&graph);
        separator();
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
            case 1:
                Situation11(graph);
                break;
            case 2 :
                break;
            case 3 :
                break;
            case 0 :
                separator();
                exit(0);
            default:
                std::cout << "\n Invalid input!\n";
        }
    }
}