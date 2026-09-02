#include "hpp/room.hpp"
#include "hpp/ants.hpp"
#include "hpp/anthill.hpp"
#include "hpp/simulation.hpp"
#include "hpp/renderer.hpp"
using namespace std;

// Builds a sample anthill: 8 fourmis partent de Sv (vestibule) et
// doivent rejoindre Sd (dortoir) en traversant les salles, avec
// plusieurs chemins possibles et des salles a capacite limitee.
Anthill* buildSampleAnthill() {
    Anthill* hill = new Anthill(8);

    Room* Sv = new Room("Sv", 999);
    Room* Sd = new Room("Sd", 999);
    Room* S1 = new Room("S1", 1);
    Room* S2 = new Room("S2", 2);
    Room* S3 = new Room("S3", 1);
    Room* S4 = new Room("S4", 1);
    Room* S5 = new Room("S5", 2);
    Room* S6 = new Room("S6", 1);

    for (Room* r : {Sv, S1, S2, S3, S4, S5, S6, Sd})
        hill->addRoom(r);

    Sv->addNeighbours(S1);
    Sv->addNeighbours(S2);
    S1->addNeighbours(S3);
    S2->addNeighbours(S3);
    S2->addNeighbours(S4);
    S3->addNeighbours(S5);
    S4->addNeighbours(S5);
    S3->addNeighbours(Sd);
    S5->addNeighbours(Sd);
    S4->addNeighbours(S6);
    S6->addNeighbours(Sd);

    hill->Sv = Sv;
    hill->Sd = Sd;
    hill->createAnts();

    return hill;
}

int main() {
    Anthill* hill = buildSampleAnthill();

    Simulation sim(*hill);
    vector<vector<Move>> turns = sim.run();

    Renderer renderer(*hill, turns);
    renderer.run();

    for (Ant* a : hill->allAnts()) delete a;
    for (Room* r : hill->rooms) delete r;
    delete hill;
    return 0;
}
