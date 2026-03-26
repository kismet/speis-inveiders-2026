//
// Created by Admin on 26/03/2026.
//
#include "gameplay.h"
#include <iostream>

void printGame() {
    for (int r = 0; r < RIGHE; r++) {
        for (int c = 0; c < COLONNE; c++) {
            std::cout << tabellone[r][c];
        }
        std::cout << std::endl;
    }
}