#include "../hpp/room.hpp"
#include <iostream>
using namespace std;

Room::Room(string name) {
    this->name = name;
    this->used = false;
}

void Room::addNeighbours(Room* s) {
    neighbours.push_back(s);
}

void Room::show() {
    cout << "Room " << name << " -> ";
    for (Room* v : neighbours)
        cout << v->name << " ";
    cout << endl;
}
