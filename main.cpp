#include "hpp/room.hpp"
#include "hpp/ants.hpp"
#include "hpp/anthill.hpp"
using namespace std;

// TEST POUR FOURMILIERE 5
int main() {
    Room* sv  = new Room("Sv",  0);
    Room* s1  = new Room("S1",  8);
    Room* s2  = new Room("S2",  4);
    Room* s3  = new Room("S3",  2);
    Room* s4  = new Room("S4",  4);
    Room* s5  = new Room("S5",  2);
    Room* s6  = new Room("S6",  4);
    Room* s7  = new Room("S7",  2);
    Room* s8  = new Room("S8",  5);
    Room* s9  = new Room("S9",  1);
    Room* s10 = new Room("S10", 1);
    Room* s11 = new Room("S11", 1);
    Room* s12 = new Room("S12", 1);
    Room* s13 = new Room("S13", 4);
    Room* s14 = new Room("S14", 2);
    Room* sd  = new Room("Sd",  0);

    sv->addNeighbours(s1);

    s1->addNeighbours(s2);
    s1->addNeighbours(s6);

    s2->addNeighbours(s1);
    s2->addNeighbours(s3);
    s2->addNeighbours(s5);

    s3->addNeighbours(s4);

    s4->addNeighbours(s3);
    s4->addNeighbours(s5);
    s4->addNeighbours(sd);

    s5->addNeighbours(s2);
    s5->addNeighbours(s4);

    s6->addNeighbours(s7);
    s6->addNeighbours(s8);

    s7->addNeighbours(s9);
    s7->addNeighbours(s10);

    s8->addNeighbours(s11);
    s8->addNeighbours(s12);

    s9->addNeighbours(s14);

    s10->addNeighbours(s14);

    s11->addNeighbours(s8);
    s11->addNeighbours(s13);

    s12->addNeighbours(s13);

    s13->addNeighbours(s11);
    s13->addNeighbours(s12);
    s13->addNeighbours(sd);

    s14->addNeighbours(sd);

    Anthill* hill = new Anthill(50);
    hill->sv     = sv;
    hill->sd = sd;

    hill->addRoom(sv);
    hill->addRoom(s1);  hill->addRoom(s2);  hill->addRoom(s3);
    hill->addRoom(s4);  hill->addRoom(s5);  hill->addRoom(s6);
    hill->addRoom(s7);  hill->addRoom(s8);  hill->addRoom(s9);
    hill->addRoom(s10); hill->addRoom(s11); hill->addRoom(s12);
    hill->addRoom(s13); hill->addRoom(s14); hill->addRoom(sd);

    cout << "=== Graphe ===" << endl;
    hill->showRooms();

    cout << "\n=== Chemins trouves ===" << endl;
    vector<vector<Room*>> paths = hill->findAllPaths();
    cout << "Nombre de chemins : " << paths.size() << endl;
    for (auto& path : paths) {
        for (Room* r : path)
            if (r->name == "Sd"){
                cout << r->name;
            }else {
                cout << r->name << " -> ";
            }
        cout << endl;
    }

    delete sv;  delete s1;  delete s2;  delete s3;
    delete s4;  delete s5;  delete s6;  delete s7;
    delete s8;  delete s9;  delete s10; delete s11;
    delete s12; delete s13; delete s14; delete sd;
    delete hill;

    return 0;
}
