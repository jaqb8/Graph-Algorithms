#include <iostream>
#include "UserInterface.h"
#include "Graph.h"

int main() {
    Graph g(6, 6);
    g.addEdge(0, 1, 3);
    g.addEdge(0, 4, 3);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 3);
    g.addEdge(2, 5, 1);
    g.addEdge(3, 1, 3);
    g.addEdge(4, 5, 2);
    g.addEdge(5, 0, 6);
    g.addEdge(5, 3, 1);

    g.dijkstraList(0);

    return 0;
}