# Une vie de fourmi

## Présentation

Ce projet C++ simule, avec une interface graphique (raylib), le déplacement de fourmis à l'intérieur d'une fourmilière, depuis le vestibule (`Sv`) jusqu'au dortoir (`Sd`). Chaque salle intermédiaire a une capacité limitée et chaque couloir ne peut être emprunté que par une fourmi à la fois par tour ; la simulation calcule tous les chemins possibles, répartit les fourmis dessus, puis joue les déplacements tour par tour à l'écran.

## Problématique

- `Sv` représente le point d'entrée de la fourmilière (vestibule) — capacité illimitée.
- `Sd` représente l'objectif final (dortoir) — capacité illimitée.
- Les autres salles ont une capacité limitée (1 fourmi par défaut, personnalisable).
- Un couloir ne peut être traversé que par une seule fourmi par tour, dans un sens ou dans l'autre.
- Les fourmis doivent toutes rejoindre `Sd` en un minimum de tours.

## Structure du projet

- `main.cpp` : construit une fourmilière d'exemple, lance la simulation puis l'interface graphique.
- `cpp/room.cpp` / `hpp/room.hpp` : les salles et les couloirs (graphe non orienté).
- `cpp/ants.cpp` / `hpp/ants.hpp` : une fourmi, son chemin assigné et sa progression.
- `cpp/anthill.cpp` / `hpp/anthill.hpp` : la fourmilière (salles, fourmis, recherche de tous les chemins Sv→Sd par BFS).
- `cpp/simulation.cpp` / `hpp/simulation.hpp` : répartit les fourmis sur les chemins disponibles (heuristique du temps de fin projeté) puis simule les tours en respectant les capacités des salles et des couloirs.
- `cpp/renderer.cpp` / `hpp/renderer.hpp` : affichage raylib — dessine le graphe et anime les fourmis entre les positions calculées par la simulation.

## Prérequis

Le projet utilise [raylib](https://www.raylib.com/) via [MSYS2](https://www.msys2.org/) (nécessaire pour que la bibliothèque compilée soit compatible avec le compilateur MinGW) :

```bash
pacman -S mingw-w64-x86_64-raylib mingw-w64-x86_64-gdb
```

## Compilation et exécution

Depuis VS Code : ouvrir ce dossier puis appuyer sur **F5** (compile et lance avec debug), ou lancer la tâche `Run Game` (Terminal → Run Task).

En ligne de commande (PowerShell) :

```powershell
.\build.ps1
.\build\uneviedefourmi.exe
```

Équivalent manuel avec g++ :

```bash
g++ -std=c++17 main.cpp cpp/*.cpp -I C:/msys64/mingw64/include -L C:/msys64/mingw64/lib -lraylib -lopengl32 -lgdi32 -lwinmm -o build/uneviedefourmi.exe
```

(Il faut aussi copier `libraylib.dll`, `glfw3.dll`, `libgcc_s_seh-1.dll`, `libstdc++-6.dll` et `libwinpthread-1.dll` depuis `C:\msys64\mingw64\bin` à côté de l'exécutable — `build.ps1` le fait automatiquement.)

## Contrôles

- `ESPACE` : pause / reprise de la lecture automatique.
- `←` / `→` : avancer ou reculer d'un tour manuellement.
- `R` : recommencer l'animation depuis le début.
- Fermer la fenêtre pour quitter.

## Objectif pédagogique

Ce projet est idéal pour:

- comprendre la modélisation d'un système simple en C++,
- utiliser des classes pour représenter un environnement et des entités,
- manipuler des graphes pour trouver des chemins (BFS) et simuler des déplacements sous contraintes,
- afficher et animer une simulation avec une bibliothèque graphique (raylib).

