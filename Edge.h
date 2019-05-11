//
// Created by kubaa on 11.05.2019.
//

#ifndef GRAPH_ALGORITHMS_EDGE_H
#define GRAPH_ALGORITHMS_EDGE_H

class Edge {
public:
    int begVer, endVer, weight;

    bool operator()(const Edge &edge1, const Edge &edge2) {
        if(edge1.weight > edge2.weight) return true;
        if(edge1.weight < edge2.weight) return false;
        return false;
    }
};

#endif //GRAPH_ALGORITHMS_EDGE_H
