//
// Created by kubaa on 11.05.2019.
//

#include "Graph.h"

using namespace std;


Graph::Graph(int v, int e) {
    vertices = v;
    edges = 0;
    adjacencyMatrix = new int * [vertices];
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

void Graph::getEdgesMatrix() {
    int diagonal = 1;

    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < diagonal; j++) {
            int weight = adjacencyMatrix[i][j];
            if(weight != 0) {
                edge.push_back({weight, {i, j}});
            }
        }
        diagonal++;
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
    adjacencyMatrix[u][v] = w;
    edge.push_back({w, {u, v}});

}

void Graph::dijkstraMatrix(int s) {
    priority_queue< iPair, vector<iPair>, greater<>> pq;

    vector<int> dist(vertices, INF);

    pq.push(make_pair(0, s));
    dist[s] = 0;

    while(!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for(int v = 0; v < vertices; v++) {
            if(adjacencyMatrix[u][v] && dist[u] != INF
            && dist[u] + adjacencyMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + adjacencyMatrix[u][v];
                pq.push(make_pair(dist[v], v));
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

    vector< pair<int, iPair> >::iterator it;
    for(int i = 1; i <= vertices - 1; i++) {
        for(it = edge.begin(); it != edge.end(); it++) {
            int u = it->second.first;
            int v = it->second.second;
            int weight = it->first;
            if(dist[u] != INF && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }

    for(it = edge.begin(); it != edge.end(); it++) {
        int u = it->second.first;
        int v = it->second.second;
        int weight = it->first;
        if(dist[u] != INF && dist[u] + weight < dist[v])
            printf("Graf posiada cykl ujemny.\n");
    }

    printf("Vertex    Distance from source\n");
    for(int i = 0; i < vertices; i++) {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

void Graph::addUndirectedEdge(int u, int v, int w) {
    adjList[u].push_back((make_pair(v, w)));
    adjList[v].push_back((make_pair(u, w)));

    adjacencyMatrix[u][v] = w;
    adjacencyMatrix[v][u] = w;

    //edge.push_back({w, {u, v}});
}

void Graph::PrimList() {
    priority_queue< iPair, vector <iPair>, greater<iPair> > pq;
    int src = 0;
    vector<int> key(vertices, INF);
    vector<int> parent(vertices, -1);
    vector<bool> inMST(vertices, false);

    pq.push(make_pair(0, src));
    key[src] = 0;

    while(!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;
        list< pair<int, int> >::iterator i;
        for(i = adjList[u].begin(); i != adjList[u].end(); ++i) {
            int v = (*i).first;
            int weight = (*i).second;

            if(inMST[v] == false && key[v] > weight) {
                key[v] = weight;
                pq.push(make_pair(key[v], v));
                parent[v] = u;
            }
        }
    }
    for(int i = 1; i < vertices; ++i) {
        printf("%d - %d : %d\n", parent[i], i, key[i]);
    }
}

void Graph::PrimMatrix() {
    priority_queue<iPair, vector<iPair>, greater<>> pq;
    int src = 0;
    vector<int> parent(vertices, -1);
    vector<int> key(vertices, INF);
    vector<bool> inMST(vertices, false);

    pq.push(make_pair(0, src));
    key[src] = 0;

    while(!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;
        for(int v = 0; v < vertices; v++) {
            if(adjacencyMatrix[u][v] && inMST[v] == false &&
            adjacencyMatrix[u][v] < key[v]) {
                parent[v] = u;
                key[v] = adjacencyMatrix[u][v];
                pq.push(make_pair(key[v], v));
            }
        }
    }


    for(int i = 1; i < vertices; i++) {
        printf("%d - %d : %d\n", parent[i], i, adjacencyMatrix[i][parent[i]]);
    }
}

int Graph::kruskal() {
    int mstWt = 0;
    sort(edge.begin(), edge.end());

    DisjointSets ds(vertices);

    vector< pair<int, iPair> >::iterator i;
    for(i = edge.begin(); i != edge.end(); i++) {
        int u = i->second.first;
        int v = i->second.second;

        int setU = ds.find(u);
        int setV = ds.find(v);

        if(setU != setV) {
            printf("%d - %d\n", u, v);
            mstWt += i->first;
            ds.merge(setU, setV);
        }
    }
    return mstWt;
}

