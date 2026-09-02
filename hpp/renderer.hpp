#pragma once
#include <map>
#include <vector>
#include "raylib.h"
#include "anthill.hpp"
#include "simulation.hpp"

// Draws the anthill graph and animates the ants moving turn by turn,
// interpolating smoothly between the discrete positions the Simulation
// computed. This is the only file that includes raylib.
class Renderer {
public:
    Renderer(Anthill& anthill, const vector<vector<Move>>& turns);
    void run();

private:
    Anthill& anthill;
    vector<vector<Move>> turns;
    int totalTurns;

    map<Room*, Vector2> layout;
    map<Ant*, vector<Room*>> trail; // trail[ant][k] = room ant is in after turn k

    float simTime  = 0.0f; // in "turns" (fractional)
    bool  paused   = false;
    float turnDuration = 0.9f; // seconds per turn while auto-playing

    void computeLayout();
    void buildTrails();
    void handleInput(float dt);
    Vector2 roomPos(Room* r) const;
    Vector2 antPosition(Ant* ant) const;
    void draw();
};
