#include <iostream>

#include "Classes/Helper.h"
#include "Classes/Graph.h"


int main() {
    std::cout << "Hello, World!" << std::endl;


    Helper help = Helper();

    Graph<Stop> graph = Graph<Stop>();

    help.loadGraphWithData(&graph);

    return 0;
}
