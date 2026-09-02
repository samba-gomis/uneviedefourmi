#include "../hpp/ants.hpp"
using namespace std;

Ant::Ant(int id) {
    this->id = id;
    this->currentPos = 0;
    this->next = nullptr;
}

void Ant::setPath(const vector<Room*>& p) {
    path = p;
    currentPos = 0;
}

Room* Ant::currentRoom() {
    return path[currentPos];
}

Room* Ant::nextRoom() {
    if (static_cast<size_t>(currentPos) + 1 < path.size())
        return path[currentPos + 1];
    return nullptr;
}

int Ant::remainingSteps() {
    return static_cast<int>(path.size()) - 1 - currentPos;
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
