#include "hpp/room.hpp"
using namespace std;

// TEST ROOM 
int main() {
    Room* sv = new Room("Sv");
    Room* s1 = new Room("S1");
    Room* s2 = new Room("S2");

    sv->addNeighbours(s1);
    sv->addNeighbours(s2);

    sv->show();
    s1->show();

    delete sv; delete s1; delete s2;
    return 0;
}

