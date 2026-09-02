#include "../hpp/simulation.hpp"
#include <algorithm>
#include <map>
#include <set>
using namespace std;

Simulation::Simulation(Anthill& anthill) : anthill(anthill) {}

static pair<Room*, Room*> corridorKey(Room* a, Room* b) {
    return a < b ? make_pair(a, b) : make_pair(b, a);
}

void Simulation::assignPaths() {
    paths = anthill.findAllPaths();
    sort(paths.begin(), paths.end(), [](const vector<Room*>& a, const vector<Room*>& b) {
        return a.size() < b.size();
    });

    if (paths.empty()) return; // no route from Sv to Sd

    vector<Ant*> ants = anthill.allAnts();
    sort(ants.begin(), ants.end(), [](Ant* a, Ant* b) { return a->id < b->id; });

    // Greedy load balancing: each ant joins whichever path currently has
    // the shortest projected finish time (ants already on it * its length).
    vector<int> load(paths.size(), 0);
    for (Ant* ant : ants) {
        size_t best = 0;
        for (size_t p = 1; p < paths.size(); p++) {
            long long scoreP    = (long long)(load[p] + 1) * (long long)paths[p].size();
            long long scoreBest = (long long)(load[best] + 1) * (long long)paths[best].size();
            if (scoreP < scoreBest) best = p;
        }
        ant->setPath(paths[best]);
        load[best]++;
    }
}

vector<vector<Move>> Simulation::run() {
    assignPaths();

    vector<vector<Move>> turns;
    vector<Ant*> ants = anthill.allAnts();
    if (ants.empty() || paths.empty()) return turns;

    map<Room*, int> occupancy; // intermediate rooms only, Sv/Sd are unlimited

    const int MAX_TURNS = 10000; // safety net against an unexpected deadlock
    for (int t = 0; t < MAX_TURNS; t++) {
        vector<Ant*> pending;
        for (Ant* ant : ants)
            if (!ant->hasArrived(anthill.Sd))
                pending.push_back(ant);

        if (pending.empty()) break;

        // Ants closest to Sd move first: they free up the rooms that the
        // ants behind them need, within that same turn.
        sort(pending.begin(), pending.end(), [](Ant* a, Ant* b) {
            if (a->remainingSteps() != b->remainingSteps())
                return a->remainingSteps() < b->remainingSteps();
            return a->id < b->id;
        });

        set<pair<Room*, Room*>> busyCorridors;
        vector<Move> turnMoves;

        for (Ant* ant : pending) {
            Room* from = ant->currentRoom();
            Room* to   = ant->nextRoom();
            if (to == nullptr) continue;

            auto key = corridorKey(from, to);
            if (busyCorridors.count(key)) continue;
            if (to != anthill.Sd && occupancy[to] >= to->capacity) continue;

            busyCorridors.insert(key);
            if (from != anthill.Sv) occupancy[from]--;
            if (to != anthill.Sd) occupancy[to]++;
            ant->move();
            turnMoves.push_back({ant, from, to});
        }

        if (turnMoves.empty()) break; // deadlock safeguard
        turns.push_back(turnMoves);
    }

    return turns;
}
