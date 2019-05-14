#include <iostream>
#include "UserInterface.h"
#include "Graph.h"

int main() {
    Graph g(5, 7);

    g.addUndirectedEdge(0, 1, 3);
    g.addUndirectedEdge(0, 2, 1);
    g.addUndirectedEdge(1, 2, 3);
    g.addUndirectedEdge(1, 3, 4);
    g.addUndirectedEdge(1, 4, 2);
    g.addUndirectedEdge(2, 3, 6);
    g.addUndirectedEdge(3, 4, 5);

    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            printf("%d ", g.adjacencyMatrix[i][j]);
        }
        printf("\n");
    }

    g.getEdgesMatrix();
    printf("\n");

    vector<pair<int, iPair>>::iterator i;
    for(i = g.edge.begin(); i != g.edge.end(); i++) {
        printf("(%d, %d): %d\n", i->second.first, i->second.second, i->first);
    }



    return 0;
}