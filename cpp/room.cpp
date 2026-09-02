#include "../hpp/room.hpp"
#include <iostream>
using namespace std;

Room::Room(string name, int capacity) {
    this->name = name;
    this->used = false;
    this->capacity = capacity;
}

void Room::addNeighbours(Room* s) {
    // Un couloir relie deux salles dans les deux sens : sans le lien
    // retour, findAllPaths() (BFS) ne peut pas traverser la salle dans
    // l'autre direction et manque des chemins valides.
    neighbours.push_back(s);
    s->neighbours.push_back(this);
}

void Room::show() {
    cout << "Room " << name << " -> ";
    for (Room* v : neighbours)
        cout << v->name << " ";
    cout << endl;
}
