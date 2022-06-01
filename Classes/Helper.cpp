//
// Created by asus on 20/05/2022.
//

#include "Helper.h"
#include "Stop.h"


void Helper::loadGraphWithData(MyGraph *graphToLoad, std::string path) {
    std::vector<Stop> stops;
    std::ifstream MyReadFile("../Input/" + path +".txt");
    int first_line = 0;
    if (MyReadFile.is_open()) {
        std::string line;
        while (getline(MyReadFile, line)) {
            if (first_line == 0) {
                first_line++;
                std::string vertexs = line.substr(0, line.find(' '));

                graphToLoad->setSize(stoi(vertexs));
            }
            else {
                int last_space = 0;
                std::string origin = line.substr(last_space, line.find(' '));
                last_space = last_space + 1 + line.find(' ');
                std::string destination = line.substr(last_space, line.substr(last_space).find(' '));
                last_space = last_space + 1 + line.substr(last_space).find(' ');
                std::string capacity = line.substr(last_space, line.substr(last_space).find(' '));
                last_space = last_space + 1 + line.substr(last_space).find(' ');
                std::string duration = line.substr(last_space, line.substr(last_space).find(' '));
                //stops->emplace_back(std::stoi(origin), std::stoi(destination), std::stoi(capacity), std::stoi(duration));
                //graph.addVertex(stops[i]);
                graphToLoad->addEdge(stoi(origin), stoi(destination), std::stod(capacity), std::stod(duration));
                //DEBUG: std::cout << "Connection " << origin << " with " << destination << " capacity: " << capacity << " duration: " << duration << std::endl;
            }
        }
    }
    else {
        std::cout << "Failed to open" << std::endl;
    }
    // Close the MyReadFile
    MyReadFile.close();
    return;

}