#pragma once
#include <string>
#include <vector>
using namespace std;

class Room {
public:
    string name;
    vector<Room*> neighbours;
    int capacity;
    int currentAnts;

    Room(string name, int capacity = 1);
    void addNeighbours(Room* s);
    bool isFull();
    bool enter();
    void leave();
    void show();
};
