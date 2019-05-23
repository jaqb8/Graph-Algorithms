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
#include <fstream>
#include "DisjointSets.h"


#define INF 0x3f3f3f3f

using namespace std;

typedef pair<int, int> iPair;

class Graph {
public:
    Graph(int v);
    ~Graph();
    void print();
    void addEdge(int u, int v, int w);
    void dijkstraList(int s);
    void dijkstraMatrix(int s);
    void BellmanFordList(int s);
    void BellmanFordMatrix(int s);
    int PrimList();
    int PrimMatrix();
    int KruskalList();
    int KruskalMatrix();

private:
    int vertices;
    list< pair<int, int> > *adjList;
    int **adjacencyMatrix;
    vector< pair<int, iPair> > edge;
    void makeUndirected();
    void createSpanningTree();
    void getEdgesMatrix();
    void getEdgesList();

    friend class UserInterface;

};


#endif //GRAPH_ALGORITHMS_GRAPH_H
