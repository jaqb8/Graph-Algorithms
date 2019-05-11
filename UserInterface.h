//
// Created by kubaa on 11.05.2019.
//

#ifndef GRAPH_ALGORITHMS_USERINTERFACE_H
#define GRAPH_ALGORITHMS_USERINTERFACE_H

#include <iostream>
#include <fstream>
#include "Graph.h"
#include "ListElem.h"


class UserInterface {
public:
    void graphGenerationMethod();
    void loadFromFile();

    bool beg = true;
    Graph *graph;

};


#endif //GRAPH_ALGORITHMS_USERINTERFACE_H
