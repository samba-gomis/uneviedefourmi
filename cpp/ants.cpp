#include "../hpp/ants.hpp"
#include <iostream>
using namespace std;

Ant::Ant(int id) {
    this->id = id;
    this->currentPos = 0;
    this->next = nullptr;
}

Room* Ant::currentRoom() {
    return path[currentPos];
}

Room* Ant::nextRoom() {
    if (currentPos + 1 < path.size())
        return path[currentPos + 1];
    return nullptr;
}

bool Ant::hasArrived(Room* Sd) {
    return currentRoom() == Sd;
}

void Ant::move() {
    if (nextRoom() != nullptr)
        currentPos++;
}

void Ant::show() {
    cout << "f" << id << " - ";
    for (Room* r : path)
        cout << r->name << " - ";
    cout << endl;
}