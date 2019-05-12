//
// Created by kubaa on 11.05.2019.
//

#include "Graph.h"

using namespace std;


Graph::Graph(int v, int e) {
    vertices = v;
    edges = 0;
    adjacencyMatrix = new int * [vertices];
    adjacencyList = new ListElem * [vertices];
    edgeArray = new Edge[edges];

    adjList = new list<iPair> [vertices];

    for(int i = 0; i < vertices; i++) adjacencyMatrix[i] = new int[vertices];
    for(int i = 0; i < vertices; i++)
        for(int j = 0; j < vertices; j++) adjacencyMatrix[i][j] = 0;

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

//    cout << endl << endl << "Lista sasiadow: " << endl;
//    for(i = 0; i < vertices; i++) {
//        cout << "[" << i << "] = ";
//        e1 = adjacencyList[i];
//        while(e1) {
//            cout << setw(3) << e1->data << "(" << e1->weight << ")";
//            e1 = e1->next;
//        }
//        cout << endl;
//    }
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
    adjacencyMatrix[u][v] = w;

    Edge *temp = new Edge[edges+1];
    for(int i = 0; i < edges; i++) {
        temp[i].src = edgeArray[i].src;
        temp[i].dest = edgeArray[i].dest;
        temp[i].weight = edgeArray[i].weight;
    }
    temp[edges].src = u;
    temp[edges].dest = v;
    temp[edges].weight = w;

    edges++;

    delete [] edgeArray;
    edgeArray = temp;

}

int Graph::minDistance(int *dist, bool *sptSet) {
    int min = INF, min_index;

    for(int v = 0; v < vertices; v++) {
        if(sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    }

    return min_index;
}

void Graph::dijkstraMatrix(int s) {
    int dist[vertices];
    bool sptSet[vertices];

    for(int i = 0; i < vertices; i++) {
        dist[i] = INF, sptSet[i] = false;
    }

    dist[s] = 0;

    for(int count = 0; count < vertices - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for(int v = 0; v < vertices; v++) {
            if(!sptSet[v] && adjacencyMatrix[u][v] && dist[u] != INF
            && dist[u] + adjacencyMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + adjacencyMatrix[u][v];
            }
        }
    }

    printf("Vertex    Distance from source\n");
    for(int i = 0; i < vertices; i++) {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

void Graph::BellmanFord(int s) {
    int dist[vertices];

    for(int i = 0; i < vertices; i++) {
        dist[i] = INF;
    }
    dist[s] = 0;

    for(int i = 1; i <= vertices - 1; i++) {
        for(int j = 0; j < edges; j++) {
            int u = edgeArray[j].src;
            int v = edgeArray[j].dest;
            int weight = edgeArray[j].weight;
            if(dist[u] != INF && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }

    for(int i = 0; i < edges; i++) {
        int u = edgeArray[i].src;
        int v = edgeArray[i].dest;
        int weight = edgeArray[i].weight;
        if(dist[u] != INF && dist[u] + weight < dist[v])
            printf("Graf posiada cykl ujemny.\n");
    }

    printf("Vertex    Distance from source\n");
    for(int i = 0; i < vertices; i++) {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}