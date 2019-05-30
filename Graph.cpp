//
// Created by kubaa on 11.05.2019.
//

#include "Graph.h"

using namespace std;


Graph::Graph(int v) {
    vertices = v;
    adjacencyMatrix = new int * [vertices];
    adjList = new list<iPair> [vertices];

    for(int i = 0; i < vertices; i++) {
        adjacencyMatrix[i] = new int[vertices];
        for(int j = 0; j < vertices; j++) {
            adjacencyMatrix[i][j] = 0;
        }
    }
}

Graph::~Graph() {
    for(int i = 0; i < vertices; i++) {
        delete [] adjacencyMatrix[i];
    }
    delete [] adjacencyMatrix;
    delete [] adjList;
}

void Graph::print() {
    printf("Maciez sasiedztwa: \n");
    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            printf("%5d", adjacencyMatrix[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");

    printf("Lista sasiadow: \n");
    for(int i = 0; i < vertices; i++){
        printf("u[%d]: ", i);
        list<iPair>::iterator it;
        for(it = adjList[i].begin(); it != adjList[i].end(); it++) {
            printf("(v:%d, w:%d) -> ", it->first, it->second);
        }
        printf("\n");
    }
}

void Graph::getEdgesMatrix() {

    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            int weight = adjacencyMatrix[i][j];
            if(weight != 0) {
                edge.push_back({weight, {i, j}});
            }
        }
    }
}

void Graph::getEdgesList() {
    for(int i = 0; i < vertices; i++) {
        list<iPair>::iterator it;
        for(it = adjList[i].begin(); it != adjList[i].end(); it++) {
            int weight = it->second;
            edge.push_back({weight, {i, it->first}});
        }
    }
}

void Graph::dijkstraList(int s) {
    priority_queue< iPair, vector <iPair>, greater<iPair> > pq;

    vector<int> dist(vertices, INF);
    vector<int> parent(vertices, -1);

    pq.push(make_pair(0, s));
    dist[s] = 0;

    while(!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        list< pair<int, int> >::iterator i;
        for(i = adjList[u].begin(); i != adjList[u].end(); ++i) {
            int v = (*i).first;
            int weight = (*i).second;

            // relaksacja
            if(dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    printf("Wierzcholek:    Odleglosc od zrodla:\n");
    for(int i = 0; i < vertices; i++) {
        printf("%d \t\t %d\n", i, dist[i]);
    }

    printf("\n");
    for(int i = 0; i < vertices; i++) {
        int x = parent[i];
        printf("%d. ", i);
        while(x >= 0) {
            printf("%d -> ", x);
            x = parent[x];
        }
        printf("\n");
    }

}

void Graph::addEdge(int u, int v, int w) {
    adjList[u].push_back(make_pair(v, w));
    adjacencyMatrix[u][v] = w;
}

void Graph::dijkstraMatrix(int s) {
    priority_queue< iPair, vector<iPair>, greater<>> pq;

    vector<int> dist(vertices, INF);
    vector<int> parent(vertices, -1);

    pq.push(make_pair(0, s));
    dist[s] = 0;

    while(!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for(int v = 0; v < vertices; v++) {
            if(adjacencyMatrix[u][v] && dist[u] != INF
            && dist[u] + adjacencyMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + adjacencyMatrix[u][v];
                parent[v] = u;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    printf("Wierzcholek:    Odleglosc od zrodla:\n");
    for(int i = 0; i < vertices; i++) {
        printf("%d \t\t %d\n", i, dist[i]);
    }

    printf("\n");
    for(int i = 0; i < vertices; i++) {
        int x = parent[i];
        printf("%d. ", i);
        while(x >= 0) {
            printf("%d -> ", x);
            x = parent[x];
        }
        printf("\n");
    }
}

void Graph::BellmanFordList(int s) {
    getEdgesList();
    int dist[vertices];

    for(int i = 0; i < vertices; i++) {
        dist[i] = INF;
    }
    dist[s] = 0;

    vector<int> parent(vertices, -1);

    vector< pair<int, iPair> >::iterator it;
    for(int i = 1; i <= vertices - 1; i++) {
        for(it = edge.begin(); it != edge.end(); it++) {
            int u = it->second.first;
            int v = it->second.second;
            int weight = it->first;
            if(dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
        }
    }

    for(it = edge.begin(); it != edge.end(); it++) {
        int u = it->second.first;
        int v = it->second.second;
        int weight = it->first;
        if(dist[u] != INF && dist[u] + weight < dist[v])
            printf("Graf posiada cykl ujemny.\n");
    }

    printf("Wierzcholek:    Odleglosc od zrodla:\n");
    for(int i = 0; i < vertices; i++) {
        printf("%d \t\t %d\n", i, dist[i]);
    }

    printf("\n");
    for(int i = 0; i < vertices; i++) {
        int x = parent[i];
        printf("%d. ", i);
        while(x >= 0) {
            printf("%d -> ", x);
            x = parent[x];
        }
        printf("\n");
    }
}

void Graph::BellmanFordMatrix(int s) {
    getEdgesMatrix();
    int dist[vertices];

    for(int i = 0; i < vertices; i++) {
        dist[i] = INF;
    }
    dist[s] = 0;

    vector<int> parent(vertices, -1);

    vector< pair<int, iPair> >::iterator it;
    for(int i = 1; i <= vertices - 1; i++) {
        for(it = edge.begin(); it != edge.end(); it++) {
            int u = it->second.first;
            int v = it->second.second;
            int weight = it->first;
            if(dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
        }
    }

    for(it = edge.begin(); it != edge.end(); it++) {
        int u = it->second.first;
        int v = it->second.second;
        int weight = it->first;
        if(dist[u] != INF && dist[u] + weight < dist[v]) {
            printf("Graf posiada cykl ujemny.\n");
            return;
        }
    }

    printf("Wierzcholek:    Odleglosc od zrodla:\n");
    for(int i = 0; i < vertices; i++) {
        printf("%d \t\t %d\n", i, dist[i]);
    }

    printf("\n");
    for(int i = 0; i < vertices; i++) {
        int x = parent[i];
        printf("%d. ", i);
        while(x >= 0) {
            printf("%d -> ", x);
            x = parent[x];
        }
        printf("\n");
    }
}

int Graph::PrimList() {
    priority_queue< iPair, vector <iPair>, greater<iPair> > pq;
    int src = 0;
    int mstWt = 0;
    vector<int> key(vertices, INF);         // wagi najmniejszych krawędzi
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
        mstWt += key[i];
        printf("%d - %d\n", parent[i], i);
    }

    return mstWt;
}

int Graph::PrimMatrix() {
    priority_queue<iPair, vector<iPair>, greater<>> pq;
    int src = 0;
    int mstWt = 0;
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
        mstWt += adjacencyMatrix[i][parent[i]];
        printf("%d - %d\n", parent[i], i);
    }

    return mstWt;
}

int Graph::KruskalList() {
    getEdgesList();
    int mstWt = 0;
    // sortowanie rosnąco
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

int Graph::KruskalMatrix() {
    getEdgesMatrix();
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

void Graph::makeUndirected() {
    int diagonal = 1;

    for(int i = 0; i < vertices; i++){
        for(int j = diagonal; j < vertices; j++) {
            if(adjacencyMatrix[i][j] != 0)
                adjacencyMatrix[j][i] = adjacencyMatrix[i][j];
        }
        diagonal++;
    }

    list<pair<int, int>> *reverseAdjList = new list<iPair> [vertices];
    for(int i = 0; i < vertices; i++){
        list<iPair>::iterator it;
        for(it = adjList[i].begin(); it != adjList[i].end(); it++) {
            reverseAdjList[it->first].push_back(make_pair(i, it->second));
        }
    }

    for(int i = 0; i < vertices; i++) {
        list<iPair>::iterator it;
        for(it = reverseAdjList[i].begin(); it != reverseAdjList[i].end(); it++) {
            adjList[i].push_back(make_pair(it->first, it->second));
        }
    }

    delete reverseAdjList;

}

void Graph::createSpanningTree() {
    int i = 0, j = 1;

    while(i < vertices - 1 && j < vertices) {
        int random = rand() % 10 + 1;
        adjacencyMatrix[i][j] = random;
        adjList[i].push_back(make_pair(j, random));
        i++;
        j++;
    }

}


