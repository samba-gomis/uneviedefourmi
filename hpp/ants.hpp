#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "room.hpp"

class Ant {
public:
    int id;
    vector<Room*> path;
    int currentPos;
    Ant* next;

    Ant(int id);
    void setPath(const vector<Room*>& p);
    Room* currentRoom();
    Room* nextRoom();
    int remainingSteps();
    bool hasArrived(Room* Sd);
    void move();
    void show();
};
