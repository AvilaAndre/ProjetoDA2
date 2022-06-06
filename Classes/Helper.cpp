#include "Helper.h"
#include <queue>
#include <cstring>

void Helper::loadGraphWithData(MyGraph *graphToLoad, std::string path) {
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

bool Helper::bfs(std::vector<std::vector<int>> rGraph, int s, int t, int parent[]){

    bool visited[rGraph.size()];
    std::memset(visited,0,sizeof(visited));

    std::queue<int> queue;
    queue.push(s);
    visited[s]=true;
    parent[s] = -1;

    while(!queue.empty()){
        int v = queue.front();
        queue.pop();

        for(int i = 1 ; i < rGraph.size(); i++){
            if(!visited[i] && rGraph[v][i] > 0){
                if(i == t){
                    parent[i] = v;
                    return true;
                }
                queue.push(i);
                parent[i] = v;
                visited[i] = true;
            }
        }
    }
    return false;
}


std::pair<double, std::vector<double>>  Helper::earliestStart(MyGraph graph) {
    //-------EARLIEST START--------//
    //inicializar os vetores com dados.

    std::vector<double> wait = std::vector<double>();
    std::vector<int> pred = std::vector<int>();
    std::vector<int> degree = std::vector<int>();


    wait.resize(graph.getNumVertex()+1);
    pred.resize(graph.getNumVertex()+1);
    degree.resize(graph.getNumVertex()+1);

    for (int i = 0; i < graph.getNumVertex() + 1; i++) {
        wait[i] = 0;
        pred[i] = -1;
        degree[i] = 0;
    }

    for(int j = 1; j < graph.getNumVertex()+1; j++) {
        for(Edge e: graph.getVertex(j).getAdj()) {
            degree[e.getDest()] += 1;
        }
    }

    std::vector<std::vector<double>> dGraph;

    dGraph.resize(graph.getNumVertex()+1);
    dGraph[0].resize(graph.getNumVertex()+1);

    for (int i = 1; i < graph.getNumVertex()+1; ++i) {
        dGraph[i].resize(graph.getNumVertex()+1);
        for (int k = 1; k < graph.getNumVertex()+1; ++k) {
            dGraph[i][k] = 0;
        }
        for (int k = 0 ; k < graph.getVertex(i).getAdj().size(); ++k) {
            dGraph[i][graph.getVertex(i).getAdj()[k].getDest()] = (int) graph.getVertex(i).getAdj()[k].getDuration();
        }
    }


    std::queue<int> S = std::queue<int>();

    for (int i = 1; i < graph.getNumVertex() + 1; i++) {
        if (degree[i] == 0) {
            S.push(i);
        }
    }

    double minDur = -1;
    int vf = -1;

    while (!S.empty()) {
        int v = S.front();
        S.pop();
        if (minDur < wait[v]) {
            minDur = wait[v];
            vf = v;
        }
        for(Edge e: graph.getVertex(v).getAdj()) {
            if (wait[e.getDest()] < (wait[v] + dGraph[v][e.getDest()])) {
                wait[e.getDest()] = wait[v] + dGraph[v][e.getDest()];
                pred[e.getDest()] = v;
            }
            degree[e.getDest()] -= 1;
            if (degree[e.getDest()] == 0) {
                S.push(e.getDest());
            }
        }
    }

    /*
      std::cout << "Minimum duration " << minDur << std::endl;

    for (int u = 1; u< graph.getNumVertex()+1; u++) {
        std::cout << "ES[" << u << "] " << wait[u] << " Prec[" << u << "] "<< pred[u] << std::endl;
    }

     */
    return {minDur, wait};
}

std::vector<double> Helper::latestFinish(MyGraph graph, double durMin) {
    //-------LATEST FINISH--------//
    //inicializar os vetores com dados.

    std::vector<std::vector<double>> graphT = std::vector<std::vector<double>>(); //Grafo transposto
    std::vector<std::vector<int>> graphTadj = std::vector<std::vector<int>>(); //Adjacentes no grafo transposto
    graphT.resize(graph.getNumVertex() + 1);
    graphTadj.resize(graph.getNumVertex() + 1);
    for (int i = 0; i < graph.getNumVertex()+ 1; ++i) {
        graphT[i].resize(graph.getNumVertex()+1);
    }

    std::vector<double> latestF = std::vector<double>();
    std::vector<int> degree = std::vector<int>();


    latestF.resize(graph.getNumVertex()+1);
    degree.resize(graph.getNumVertex()+1);

    for (int i = 0; i < graph.getNumVertex() + 1; i++) {
        latestF[i] = durMin;
        degree[i] = 0;
    }

    for(int j = 1; j < graph.getNumVertex() + 1; j++) {
        for(Edge e: graph.getVertex(j).getAdj()) {
            graphTadj[e.getDest()].push_back(j);
            graphT[j][e.getDest()] = e.getDuration();
        }
    }

    for(int j = 1; j < graph.getNumVertex() + 1; j++) {
        for(int e: graphTadj[j]) {
            degree[e] += 1;
        }
    }


    std::vector<std::vector<double>> dGraph;

    dGraph.resize(graph.getNumVertex()+1);
    dGraph[0].resize(graph.getNumVertex()+1);

    for (int i = 1; i < graph.getNumVertex()+1; ++i) {
        dGraph[i].resize(graph.getNumVertex()+1);
        for (int k = 1; k < graph.getNumVertex()+1; ++k) {
            dGraph[i][k] = 0;
        }
        for (int k = 0 ; k < graph.getVertex(i).getAdj().size(); ++k) {
            dGraph[i][graph.getVertex(i).getAdj()[k].getDest()] = (int) graph.getVertex(i).getAdj()[k].getDuration();
        }
    }


    std::queue<int> S = std::queue<int>();

    std::vector<int> maximus = {1};
    /*
    for (int i = 1; i < graph.getNumVertex() + 1; i++) {
        if (degree[i] > degree[maximus[0]]) {
            maximus = {i};
        }
        else if (degree[i] == degree[maximus[0]]) {
            maximus.push_back(i);
        }
    }
    for (int num: maximus) {
        S.push(num);
    }
    */


    for (int i = 1; i < graph.getNumVertex() + 1; i++) {
        if (degree[i] == 0) S.push(i);
    }


    while (!S.empty()) {
        int v = S.front();
        S.pop();
        for(int e: graphTadj[v]) {
            if (latestF[e] > latestF[v] - graphT[e][v]) {
                latestF[e] = latestF[v] - graphT[e][v];
            }
            degree[e] -= 1;
            if (degree[e] == 0) {
                S.push(e);
            }
        }
    }

    //std::cout << latestF[graph.getNumVertex()] << std::endl;


    return latestF;
}


