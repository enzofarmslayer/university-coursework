// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include "grid.h"
#include "lifeutil.h"
#include <string>
int main() {

    std::cout << "Welcome to the TDDD86 Game of Life,"  << std::endl;
    std::cout << "a simulation of the lifecycle of a bacteria colony."  << std::endl;
    std::cout << "Cells (X) live and die by the following rules:"  << std::endl;
    std::cout << " - A cell with 1 or fewer neighbours dies."  << std::endl;
    std::cout << " - Locations with 2 with neighbours remain stable."  << std::endl;
    std::cout << " - Locations with 3 with neighbours will create life."  << std::endl;
    std::cout << " - A cell with 4 or more neighbours dies."  << std::endl;

    return 0;
}
