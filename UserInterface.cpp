//
// Created by kubaa on 11.05.2019.
//

#include "UserInterface.h"

void UserInterface::loadFromFile(string fileName) {
    begin = false;
    ifstream file(fileName);

    if(!file) {
        printf("Nie odnaleziono pliku.\n");
        return;
    } else {
        printf("Wczytano plik.\n");
    }

    file >> edges >> vertices >> src;

    delete g;

    g = new Graph(vertices);

    int u, v, weight;

    for(int i = 0; i < edges; i++) {
        file >> u >> v >> weight;
        g->addEdge(u, v, weight);
    }
}

void UserInterface::loadFromFileMST(string fileName) {
    begin = false;
    ifstream file(fileName);
    file >> edges >> vertices;

    if(!file) {
        printf("Nie odnaleziono pliku.\n");
        return;
    } else {
        printf("Wczytano plik.\n");
    }

    delete g;

    g = new Graph(vertices);

    int u, v, weight;

    for(int i = 0; i < edges; i++) {
        file >> u >> v >> weight;
        g->addEdge(u, v, weight);
    }
    g->makeUndirected();
}

void UserInterface::randomGraph(int v, int d) {
    begin = false;
    edges = (d*v*(v-1)) / 200;
    vertices = v;

    delete g;

    g = new Graph(vertices);

    g->createSpanningTree();

    // Ilość pozostałych krawędzi do wygenerowania
    int count = vertices - 1;
    while(count != edges) {
        int i = rand() % vertices;
        int j = rand() % vertices;
        int weight = rand() % 10 + 1;

        if(i != j && g->adjacencyMatrix[i][j] == 0) {
            g->adjacencyMatrix[i][j] = weight;
            g->adjList[i].push_back(make_pair(j, weight));
            count++;
        }
    }
}

void UserInterface::selectProblem() {
    g = new Graph(0);

    while(begin) {
        printf("=== MENU GLOWNE ===\n\n");
        printf("1. Problem najkrotszej sciezki w grafie.\n"
               "2. Problem minimalnego drzewa rozpinajacego (MST).\n"
               "3. Zakoncz.\n");

        cin >> input;
        switch (input) {
            case 1:
                selectAlgorithm(1);
                break;

            case 2:
                selectAlgorithm(2);
                break;

            case 3:
                delete g;
                return;
        }
    }
}

void UserInterface::selectAlgorithm(int problem) {
    begin = false;
    while(!begin) {
        printf("--- WYBOR ALGORYTMU ---\n\n");
        switch(problem) {
            case 1:
                printf("1. Wczytaj graf z pliku.\n"
                       "2. Wygeneruj graf losowo.\n"
                       "3. Algorytm Dijkstry.\n"
                       "4. Algorytm Forda-Bellmana\n"
                       "5. Wyswietl graf.\n"
                       "6. Powrot do menu glownego.\n");
                break;

            case 2:
                printf("1. Wczytaj graf z pliku.\n"
                       "2. Wygeneruj graf losowo.\n"
                       "3. Algorytm Prima.\n"
                       "4. Algorytm Kruskala\n"
                       "5. Wyswietl graf.\n"
                       "6. Powrot do menu glownego.\n");
                break;

        }

        cin >> input;
        switch(input) {
            case 1:
                printf("Podaj nazwe pliku: ");
                cin >> fileName;
                if(problem == 1) {
                    loadFromFile(fileName);

                }
                else if(problem == 2) {
                    loadFromFileMST(fileName);
                }
                break;

            case 2:
                printf("Podaj ilosc krawedzi: ");
                cin >> value1;
                printf("Podaj gestosc grafu: ");
                cin >> value2;
                randomGraph(value1, value2);
                break;

            case 3:
                if(problem == 1) {
                    printf("Macierzowo: \n");
                    g->dijkstraMatrix(src);
                    printf("Listowo: \n");
                    g->dijkstraList(src);
                }
                else if(problem == 2) {
                    printf("Macierzowo: \n");
                    int mstWt1 = g->PrimMatrix();
                    printf("Suma wag drzewa: %d\n\n", mstWt1);
                    printf("Listowo: \n");
                    int mstWt2 = g->PrimList();
                    printf("Suma wag drzewa: %d\n", mstWt2);
                }
                break;

            case 4:
                if(problem == 1) {
                    printf("Macierzowo: \n");
                    g->BellmanFordMatrix(src);
                    printf("Listowo: \n");
                    g->BellmanFordList(src);
                }
                else if(problem == 2) {
                    printf("Macierzowo: \n");
                    int mstWt1 = g->KruskalMatrix();
                    printf("Suma wag drzewa: %d\n\n", mstWt1);
                    printf("Listowo: \n");
                    int mstWt2 = g->KruskalList();
                    printf("Suma wag drzewa: %d\n", mstWt2);
                }
                break;

            case 5:
                g->print();
                break;

            case 6:
                begin = true;
                break;
        }
    }
}