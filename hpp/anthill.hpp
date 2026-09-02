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
    Room* Sv;
    Room* Sd;
    int nbAnts;

    Anthill(int nbAnts);
    void addRoom(Room* r);
    void addAnt(Ant* a);
    void createAnts();
    vector<Ant*> allAnts();
    Room* findRoomByName(const string& name);
    void showRooms();
    void showAnts();
    vector<vector<Room*>> findAllPaths();
};
