#include <iostream>
#include <chrono>
#include "UserInterface.h"
#include "Graph.h"

int main() {
    srand(time(NULL));

    UserInterface ui;

    ui.selectProblem();

    return 0;
}