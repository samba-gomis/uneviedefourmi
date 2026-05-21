#pragma once
#include <string>
#include <vector>
using namespace std;

class Room {
public:
    string name;
    vector<Room*> neighbours;
    bool used;

    Room(string name);
    void addNeighbours(Room* s);
    void show();
};
