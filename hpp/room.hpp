#pragma once
#include <string>
#include <vector>
using namespace std;

class Room {
public:
    string name;
    vector<Room*> neighbours;
    bool used;
    int capacity; // max number of ants allowed at once (Sv/Sd get INT_MAX)

    Room(string name, int capacity = 1);
    void addNeighbours(Room* s);
    void show();
};
