//
// Created by kubaa on 11.05.2019.
//

#ifndef GRAPH_ALGORITHMS_GRAPH_H
#define GRAPH_ALGORITHMS_GRAPH_H

#include <iostream>
#include <iomanip>
#include <list>
#include <queue>
#include <algorithm>
#include "DisjointSets.h"


#define INF 0x3f3f3f3f

using namespace std;

typedef pair<int, int> iPair;

class Graph {
public:
    Graph(int v, int e);
    ~Graph();
    void print();
    void dijkstraList(int s);
    void dijkstraMatrix(int s);
    void BellmanFord(int s);
    void addEdge(int u, int v, int w);
    void addUndirectedEdge(int u, int v, int w);
    void PrimList();
    void PrimMatrix();
    int kruskal();
    void getEdgesMatrix();
    vector< pair<int, iPair> > edge;
    int **adjacencyMatrix;

private:
    int vertices;
    int edges;
    list< pair<int, int> > *adjList;


};


#endif //GRAPH_ALGORITHMS_GRAPH_H
