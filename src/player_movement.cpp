//
// Created by Admin on 26/03/2026.
//
#include "gameplay.h"

void passoSinistro() {
    int indiceNave;
    for (int c = 0; c < RIGHE; c++) {
        if (tabellone[26][c] == '^') {
            indiceNave = c;
        }
    }
    if ( indiceNave != 0) {
        tabellone[26][indiceNave] = '-';
        tabellone[26][indiceNave - 1] = '^';
    }

}

void passoDestro() {
    int indiceNave;
    for (int c = 0; c < 23; c++) {
        if (tabellone[26][c] == '^') {
            indiceNave = c;
        }
    }
    if ( indiceNave != 0) {
        tabellone[26][indiceNave] = '-';
        tabellone[26][indiceNave + 1] = '^';
    }
}