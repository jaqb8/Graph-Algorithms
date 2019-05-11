//
// Created by kubaa on 11.05.2019.
//

#include "Graph.h"

using namespace std;

Graph::Graph(int v, int e) {
    vertices = v;
    edges = e;
    adjacencyMatrix = new int * [vertices];
    adjacencyList = new ListElem * [vertices];
    E = new Edge[edges];

    adjList = new list<iPair> [vertices];
}

Graph::~Graph() {

}

void Graph::print() {
    cout << "Maciez sasiedztwa: " << endl;
    int i;

    cout << "       ";
    for(i = 0; i < edges; i++) {
        cout << setw(3) << i;
    }

    cout << endl << "       ";
    for(i = 0; i < edges; i++) {
        cout << setw(3) << "-";
    }

    cout << endl;

    for(i = 0; i < vertices; i++) {
        cout << setw(3) << i << " | ";
        for(int j = 0; j < edges; j++) cout << adjacencyMatrix[i][j];
        cout << endl;
    }

    cout << endl;

    cout << endl << endl << "Lista sasiadow: " << endl;
    for(i = 0; i < vertices; i++) {
        cout << "[" << i << "] = ";
        e1 = adjacencyList[i];
        while(e1) {
            cout << setw(3) << e1->data << "(" << e1->weight << ")";
            e1 = e1->next;
        }
        cout << endl;
    }
}

void Graph::dijkstraList(int s) {
    priority_queue< iPair, vector <iPair>, greater<iPair> > pq;

    vector<int> dist(vertices, INF);

    pq.push(make_pair(0, s));
    dist[s] = 0;

    while(!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        list< pair<int, int> >::iterator i;
        for(i = adjList[u].begin(); i != adjList[u].end(); ++i) {
            int v = (*i).first;
            int weight = (*i).second;

            if(dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    printf("Vertex    Distance from source\n");
    for(int i = 0; i < vertices; i++) {
        printf("%d \t\t %d\n", i, dist[i]);
    }

}

void Graph::addEdge(int u, int v, int w) {
    adjList[u].push_back(make_pair(v, w));
    //adjList[v].push_back(make_pair(u, w));
}