//
// Created by kubaa on 11.05.2019.
//

#ifndef GRAPH_ALGORITHMS_GRAPH_H
#define GRAPH_ALGORITHMS_GRAPH_H

#include "ListElem.h"
#include <iostream>
#include <iomanip>
#include <list>
#include <queue>


#define INF 0x3f3f3f3f

using namespace std;

typedef pair<int, int> iPair;

struct Edge {
    int src, dest, weight;
};

class Graph {
public:
    Graph(int v, int e);
    ~Graph();
    void print();
    void dijkstraList(int s);
    void dijkstraMatrix(int s);
    void BellmanFord(int s);
    int minDistance(int dist[], bool sptSet[]);
    void addEdge(int u, int v, int w);
    struct Edge *edgeArray;
    int **adjacencyMatrix;
    ListElem **adjacencyList;


private:
    int vertices;
    int edges;
    ListElem *e1, *e2;
    list< pair<int, int> > *adjList;

};


#endif //GRAPH_ALGORITHMS_GRAPH_H
