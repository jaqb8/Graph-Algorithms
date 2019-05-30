//
// Created by kubaa on 14.05.2019.
//

#ifndef GRAPH_ALGORITHMS_DISJOINTSETS_H
#define GRAPH_ALGORITHMS_DISJOINTSETS_H

class DisjointSets {
public:
    int *parent, *rank;
    int n;

    DisjointSets(int n) {
        this->n = n;
        parent = new int[n + 1];
        rank = new int[n + 1];      // ranga == "wysokość" drzewa

        for(int i = 0; i <= n; i++) {
            rank[i] = 0;
            parent[i] = i;
        }
    }

    // zwraca id zbioru do którego należy u
    int find(int u) {
        if(u != parent[u]) parent[u] = find(parent[u]);
        return parent[u];
    }

    void merge(int x, int y) {
        x = find(x), y = find(y);

        if(rank[x] > rank[y]) parent[y] = x;
        else parent[x] = y;

        // jeśli drzewa mają równe rangi
        // to waga drzewa wynikowego zwiększa się o 1
        if(rank[x] == rank[y]) rank[y]++;
    }
};

#endif //GRAPH_ALGORITHMS_DISJOINTSETS_H
