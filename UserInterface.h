//
// Created by kubaa on 11.05.2019.
//

#ifndef GRAPH_ALGORITHMS_USERINTERFACE_H
#define GRAPH_ALGORITHMS_USERINTERFACE_H

#include <iostream>
#include <fstream>
#include <chrono>
#include "Graph.h"

using namespace std;


class UserInterface {
private:
    int vertices;
    int edges;
    int src = 0;
    bool begin = true;
    int input, value1, value2;
    string fileName;

public:
    void loadFromFile(string fileName);
    void loadFromFileMST(string fileName);
    void randomGraph(int v, int d);
    void selectProblem();
    void selectAlgorithm(int problem);
    Graph *g;
};


#endif //GRAPH_ALGORITHMS_USERINTERFACE_H
