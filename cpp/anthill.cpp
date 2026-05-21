#include "../hpp/anthill.hpp"
using namespace std;

Anthill::Anthill(int nbAnts) {
    this->nbAnts = nbAnts;
    this->head = nullptr;
    this->Sv = nullptr;
    this->Sd = nullptr;
}

void Anthill::addRoom(Room* r) {
    rooms.push_back(r);
}

void Anthill::addAnt(Ant* a) {
    a->next = head;
    head = a;
}

void Anthill::showRooms() {
    cout << "=== Salles ===" << endl;
    for (Room* r : rooms)
        r->show();
}

void Anthill::showAnts() {
    cout << "=== Fourmis ===" << endl;
    Ant* current = head;
    while (current != nullptr) {
        current->show();
        current = current->next;
    }
    
}

vector<vector<Room*>> Anthill::findAllPaths() {
    vector<vector<Room*>> result;
    queue<vector<Room*>> file;
    file.push({Sv});

    while (!file.empty()) {
        vector<Room*> path = file.front();
        file.pop();
        Room* current = path.back();

        // chemin complet trouvé !
        if (current == Sd) {
            result.push_back(path);
            continue;
        }

        for (Room* neighbour : current->neighbours) {
            // éviter les cycles
            bool alreadyIn = false;
            for (Room* r : path)
                if (r == neighbour) { 
                    alreadyIn = true; 
                    break; 
                }

            if (!alreadyIn) {
                vector<Room*> newPath = path;
                newPath.push_back(neighbour);
                file.push(newPath);
            }
        }
    }
    return result;
}
