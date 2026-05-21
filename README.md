# Une vie de fourmi

## Présentation

Ce projet C++ simule le déplacement de fourmis à l'intérieur d'une fourmilière, depuis le vestibule (`Sv`) jusqu'au dortoir (`Sd`). L'objectif est de modéliser le parcours des fourmis à travers les différentes pièces et de gérer leur progression dans l'architecture de la fourmilière.

## Problématique

- `Sv` représente le point d'entrée de la fourmilière (vestibule).
- `Sd` représente l'objectif final (dortoir).
- Les fourmis doivent se déplacer de `Sv` vers `Sd` en traversant les zones définies dans la fourmilière.
- Le code cherche à organiser et simuler ce déplacement de manière claire et structurée.

## Structure du projet

- `main.cpp` : point d'entrée du programme.
- `cpp/anthill.cpp` : implémentation de la gestion de la fourmilière.
- `cpp/ants.cpp` : gestion des fourmis et de leurs déplacements.
- `cpp/room.cpp` : définition des pièces et des connexions.
- `hpp/anthill.hpp` : déclarations pour la fourmilière.
- `hpp/ants.hpp` : déclarations pour les fourmis.
- `hpp/room.hpp` : déclarations pour les pièces.

## Compilation

Pour compiler le projet, utilisez une commande similaire à :

```bash
g++ main.cpp cpp/*.cpp -I hpp -o uneviedefourmi
```

## Exécution

Après compilation, lancez le programme :

```bash
./uneviedefourmi
```

## Objectif pédagogique

Ce projet est idéal pour:

- comprendre la modélisation d'un système simple en C++,
- utiliser des classes pour représenter un environnement et des entités,
- manipuler des graphes ou des réseaux de salles pour simuler des déplacements.

