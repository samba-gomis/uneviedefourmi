#include "../hpp/renderer.hpp"
#include <algorithm>
#include <cmath>
#include <queue>
#include <set>
#include <string>

static const int SCREEN_W = 1280;
static const int SCREEN_H = 760;
static const int HUD_H    = 90;

Renderer::Renderer(Anthill& anthill, const vector<vector<Move>>& turns)
    : anthill(anthill), turns(turns), totalTurns((int)turns.size()) {
    computeLayout();
    buildTrails();
}

// Layered layout: column = BFS distance from Sv, rooms in the same
// column are stacked and centered vertically.
void Renderer::computeLayout() {
    map<Room*, int> depth;
    queue<Room*> q;
    if (anthill.Sv != nullptr) {
        depth[anthill.Sv] = 0;
        q.push(anthill.Sv);
    }
    while (!q.empty()) {
        Room* r = q.front(); q.pop();
        for (Room* n : r->neighbours) {
            if (!depth.count(n)) {
                depth[n] = depth[r] + 1;
                q.push(n);
            }
        }
    }
    int maxDepth = 0;
    for (auto& [r, d] : depth) maxDepth = std::max(maxDepth, d);
    for (Room* r : anthill.rooms) {
        if (!depth.count(r)) { maxDepth++; depth[r] = maxDepth; } // disconnected room, own column
    }

    map<int, vector<Room*>> columns;
    for (Room* r : anthill.rooms) columns[depth[r]].push_back(r);

    int numCols = maxDepth + 1;
    float marginX  = 90.0f;
    float usableW  = SCREEN_W - 2 * marginX;
    float colSpace = numCols > 1 ? usableW / (numCols - 1) : 0.0f;
    float centerY  = HUD_H + (SCREEN_H - HUD_H) / 2.0f;
    float rowSpace = 100.0f;

    for (auto& [col, rooms] : columns) {
        int n = (int)rooms.size();
        for (int i = 0; i < n; i++) {
            float x = marginX + col * colSpace;
            float y = centerY + (i - (n - 1) / 2.0f) * rowSpace;
            layout[rooms[i]] = Vector2{x, y};
        }
    }
}

void Renderer::buildTrails() {
    vector<Ant*> ants = anthill.allAnts();
    for (Ant* a : ants) trail[a] = {anthill.Sv};

    for (auto& turnMoves : turns) {
        map<Ant*, Room*> moved;
        for (auto& m : turnMoves) moved[m.ant] = m.to;

        for (Ant* a : ants) {
            Room* prev = trail[a].back();
            Room* now  = moved.count(a) ? moved[a] : prev;
            trail[a].push_back(now);
        }
    }
}

Vector2 Renderer::roomPos(Room* r) const {
    auto it = layout.find(r);
    return it != layout.end() ? it->second : Vector2{0, 0};
}

// Small deterministic offset so ants sharing a room don't perfectly overlap.
static Vector2 jitter(int id) {
    float angle = id * 2.39996323f; // golden angle -> nicely spread spiral
    return Vector2{cosf(angle) * 9.0f, sinf(angle) * 9.0f};
}

Vector2 Renderer::antPosition(Ant* ant) const {
    int idx = (int)std::floor(simTime);
    float frac = simTime - idx;
    idx = std::clamp(idx, 0, totalTurns);
    int idxNext = std::clamp(idx + 1, 0, totalTurns);

    const vector<Room*>& t = trail.at(ant);
    Room* a = t[std::min((size_t)idx, t.size() - 1)];
    Room* b = t[std::min((size_t)idxNext, t.size() - 1)];

    Vector2 pa = roomPos(a);
    Vector2 pb = roomPos(b);
    Vector2 base = Vector2{pa.x + (pb.x - pa.x) * frac, pa.y + (pb.y - pa.y) * frac};
    Vector2 j = jitter(ant->id);
    return Vector2{base.x + j.x, base.y + j.y};
}

void Renderer::handleInput(float dt) {
    if (IsKeyPressed(KEY_SPACE)) paused = !paused;

    if (IsKeyPressed(KEY_RIGHT)) simTime = std::min((float)totalTurns, floorf(simTime) + 1.0f);
    if (IsKeyPressed(KEY_LEFT))  simTime = std::max(0.0f, ceilf(simTime) - 1.0f);
    if (IsKeyPressed(KEY_R))     simTime = 0.0f;

    if (!paused && totalTurns > 0) {
        simTime += dt / turnDuration;
        if (simTime > totalTurns) simTime = (float)totalTurns;
    }
}

void Renderer::draw() {
    ClearBackground(Color{22, 24, 32, 255});
    DrawRectangleGradientV(0, HUD_H, SCREEN_W, SCREEN_H - HUD_H, Color{28, 31, 42, 255}, Color{18, 19, 26, 255});

    // --- corridors ---
    set<pair<Room*, Room*>> drawn;
    for (Room* r : anthill.rooms) {
        for (Room* n : r->neighbours) {
            auto key = r < n ? std::make_pair(r, n) : std::make_pair(n, r);
            if (drawn.count(key)) continue;
            drawn.insert(key);
            DrawLineEx(roomPos(r), roomPos(n), 3.0f, Color{80, 86, 104, 255});
        }
    }

    // --- rooms ---
    for (Room* r : anthill.rooms) {
        Vector2 p = roomPos(r);
        Color fill = Color{56, 61, 78, 255};
        Color ring = Color{110, 118, 140, 255};
        float radius = 30.0f;
        if (r == anthill.Sv) { fill = Color{46, 133, 85, 255};  ring = Color{110, 220, 160, 255}; radius = 36.0f; }
        if (r == anthill.Sd) { fill = Color{86, 63, 158, 255};  ring = Color{170, 140, 240, 255}; radius = 36.0f; }

        DrawCircleV(Vector2{p.x + 3, p.y + 4}, radius, Color{0, 0, 0, 70}); // soft shadow
        DrawCircleV(p, radius, fill);
        DrawCircleLines((int)p.x, (int)p.y, radius, ring);

        int tw = MeasureText(r->name.c_str(), 18);
        DrawText(r->name.c_str(), (int)(p.x - tw / 2.0f), (int)(p.y - 9), 18, RAYWHITE);

        if (r != anthill.Sv && r != anthill.Sd && r->capacity > 1) {
            std::string cap = "x" + std::to_string(r->capacity);
            DrawText(cap.c_str(), (int)(p.x - 10), (int)(p.y + radius + 4), 14, Color{150, 156, 176, 255});
        }
    }

    // --- ants ---
    vector<Ant*> ants = anthill.allAnts();
    std::sort(ants.begin(), ants.end(), [](Ant* a, Ant* b) { return a->id < b->id; });
    for (Ant* a : ants) {
        Vector2 p = antPosition(a);
        Color c = ColorFromHSV(fmodf(a->id * 47.0f, 360.0f), 0.7f, 0.95f);
        DrawCircleV(p, 9.0f, Color{0, 0, 0, 90});
        DrawCircleV(Vector2{p.x - 1, p.y - 1}, 8.0f, c);
        DrawCircleLines((int)p.x - 1, (int)p.y - 1, 8.0f, RAYWHITE);
    }

    // --- HUD ---
    DrawRectangle(0, 0, SCREEN_W, HUD_H, Color{16, 17, 23, 255});
    DrawText("Une vie de fourmi", 24, 12, 26, RAYWHITE);

    int arrived = 0;
    for (Ant* a : ants) if (a->hasArrived(anthill.Sd)) arrived++;
    int shownTurn = std::min((int)std::ceil(simTime), totalTurns);
    std::string status = "Tour " + std::to_string(shownTurn) + " / " + std::to_string(totalTurns) +
                          "   -   Arrivees : " + std::to_string(arrived) + " / " + std::to_string((int)ants.size());
    DrawText(status.c_str(), 24, 46, 20, Color{200, 205, 220, 255});

    std::string controls = paused ? "PAUSE" : "LECTURE";
    controls += "  -  [ESPACE] pause/lecture  [<-][->]  tour a tour  [R] recommencer";
    int cw = MeasureText(controls.c_str(), 16);
    DrawText(controls.c_str(), SCREEN_W - cw - 24, 32, 16, Color{150, 156, 176, 255});

    if (totalTurns == 0) {
        const char* msg = "Aucun chemin trouve entre Sv et Sd !";
        int mw = MeasureText(msg, 28);
        DrawText(msg, (SCREEN_W - mw) / 2, SCREEN_H / 2, 28, Color{230, 120, 120, 255});
    } else if (simTime >= totalTurns) {
        std::string msg = "Toutes les fourmis sont arrivees en " + std::to_string(totalTurns) + " tours !";
        int mw = MeasureText(msg.c_str(), 24);
        DrawRectangle((SCREEN_W - mw) / 2 - 20, HUD_H + 16, mw + 40, 44, Color{20, 90, 60, 220});
        DrawText(msg.c_str(), (SCREEN_W - mw) / 2, HUD_H + 28, 24, Color{190, 255, 220, 255});
    }
}

void Renderer::run() {
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    InitWindow(SCREEN_W, SCREEN_H, "Une vie de fourmi");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        handleInput(GetFrameTime());
        BeginDrawing();
        draw();
        EndDrawing();
    }

    CloseWindow();
}
