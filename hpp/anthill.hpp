#pragma once
#include <vector>
#include <iostream>
#include "room.hpp"
#include "ants.hpp"
#include <queue> 

class Anthill {
public:
    vector<Room*> rooms;
    Ant* head;
    Room* sv;
    Room* sd;
    vector<vector<Room*>> findAllPaths();
    int nbAnts;

    Anthill(int nbAnts);
    void addRoom(Room* r);
    void addAnt(Ant* a);
    void showRooms();
    void showAnts();
};