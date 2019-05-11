//
// Created by kubaa on 11.05.2019.
//

#include "UserInterface.h"

using namespace std;

void UserInterface::loadFromFile() {
    beg = false;
    ListElem *e1;
    string s, name;
    int a = 0;
    int vertices, edges;

    cout << "Podaj nazwe pliku: ";
    cin >> name;

    ifstream file(name);
    if(!file) {
        cout << "Nie udalo sie otworzyc pliku!" << endl;
        beg = true;
    }
    else
    {
        file >> edges >> vertices;
        if(!file || edges < vertices - 1 || vertices <= 1 ||
        edges > (vertices * (vertices - 1))) {
            cout << "Plk jest uszkodzony, lub dane sa zapisane w zlym formacie." << endl;
            beg = true;
        }
        else
        {
            graph = new Graph(vertices, edges);
            while(!file.eof()) {
                file >> graph->E[a].begVer >> graph->E[a].endVer >> graph->E[a].weight;
                if(graph->E[a].begVer >= vertices || graph->E[a].endVer >= vertices ||
                graph->E[a].weight < 1) {
                    cout << "Krawedzie w pliku sa zle okreslone." << endl;
                    beg = true;
                    break;
                }
                
                if(file) a++;
                else {
                    cout << "Krawedzie w pliku sa zle okreslone." << endl;
                    beg = true;
                    break;
                }
            }
            
            if(a == edges) {
                for(int i = 0; i < vertices; i++) graph->adjacencyMatrix[i] = new int[vertices];
                for(int i = 0; i < vertices; i++)
                    for(int j = 0; j < vertices; j++) graph->adjacencyMatrix[i][j] = 0;

                for(int i = 0; i < vertices; i++) graph->adjacencyList[i] = nullptr;
                
                for(int i = 0; i < edges; i++) {
                    int begVer = graph->E[i].begVer;
                    int endVer = graph->E[i].endVer;
                    e1 = new ListElem;
                    e1->data = endVer;
                    e1->weight = graph->E[i].weight;
                    e1->next = graph->adjacencyList[begVer];
                    graph->adjacencyList[begVer] = e1;
                    graph->adjacencyMatrix[begVer][endVer] = 1;
                }
                file.close();

            }
        }
    }
}