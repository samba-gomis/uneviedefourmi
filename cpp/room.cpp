#include "../hpp/room.hpp"
#include <iostream>
using namespace std;

Room::Room(string name, int capacity) {
    this->name = name;
    this->capacity = capacity;
    this-> currentAnts = 0;
}

void Room::addNeighbours(Room* s) {
    neighbours.push_back(s);
}

bool Room::isFull() {
    if (capacity == 0) return false;
    return currentAnts >= capacity;
}

bool Room::enter() {
    if (isFull()) return false;
    currentAnts++;
    return true;
}

void Room::leave(){
    if (currentAnts > 0)
        currentAnts ++;
}

void Room::show() {
    cout << "Room " << name << " -> ";
    for (Room* v : neighbours)
        cout << v->name << " ";
    cout << endl;
}
