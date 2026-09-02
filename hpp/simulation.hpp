#pragma once
#include <vector>
#include "anthill.hpp"

// One ant stepping from one room to an adjacent one during a turn.
struct Move {
    Ant* ant;
    Room* from;
    Room* to;
};

// Computes how the ants cross the anthill turn by turn, respecting
// room capacities and the "one ant per corridor per turn" rule.
class Simulation {
public:
    explicit Simulation(Anthill& anthill);

    // Assigns a Sv->Sd path to every ant, then simulates turns until
    // every ant has reached Sd. Returns one vector<Move> per turn
    // (only the ants that actually moved that turn are listed).
    vector<vector<Move>> run();

    // All simple Sv->Sd paths, sorted from shortest to longest.
    // Exposed so the renderer/log can explain the assignment.
    vector<vector<Room*>> paths;

private:
    Anthill& anthill;
    void assignPaths();
};
