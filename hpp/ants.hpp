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
    Room* currentRoom();
    Room* nextRoom();
    bool hasArrived(Room* Sd);
    void move();
    void show();
};