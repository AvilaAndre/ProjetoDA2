#include <iostream>
#include <limits>

#include "Classes/Helper.h"

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
        for (int i = 1; i <= graph.getNumVertex(); ++i) {
        }

        std::cout << "(" << j << ") Record: " << graph.getVertex(graph.getNumVertex()).getDist() << std::endl; //TODO: Perguntar ao user qual o que ele quer ver :)
    }


    return;
}



void separator() {
    std::cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << std::endl;
}

int main() {
    int n;

    while (true) {
        Helper help = Helper();
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
                Situation11(help);
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