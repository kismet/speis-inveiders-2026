//
// Created by Admin on 26/03/2026.
//
#include "gameplay.h"
#include "types.h"

extern  Player_t player;

void passoSinistro() {
    /*int indiceNave;
    for (int c = 0; c < RIGHE; c++) {
        if (tabellone[26][c] == '^') {
            indiceNave = c;
        }
    }*/



    if ( player.x != 0) {
        tabellone[player.Y][player.x] = '-';
        tabellone[player.Y][player.x - 1] = '^';
        player.x --;
    }

}

void passoDestro() {
    /*int indiceNave;
    for (int c = 0; c < 23; c++) {
        if (tabellone[26][c] == '^') {
            indiceNave = c;
        }
    }*/


    if ( player.x != 22) {
        tabellone[player.Y][player.x] = '-';
        tabellone[player.Y][player.x + 1] = '^';
        player.x ++;
    }
}

bool generaSparo () {
    bool sparoPossibile = true;

    for (int r = 0; r < RIGHE; r++) {
        for (int c = 0; c < COLONNE; c++) {
            if (tabellone[r][c] == MISSILE_SYMBOL) {
                sparoPossibile = false;
            }
        }
    }

    if (sparoPossibile) {
        for (int r = 0; r < RIGHE; r++) {
            for (int c = 0; c < COLONNE; c++) {
                if (tabellone[r][c] == NAVICELLA_SYMBOL) {
                    tabellone[r-1][c] = MISSILE_SYMBOL;
                }
            }
        }
    }
    return sparoPossibile;
}

void avanzaSparo() {
    for (int r = 0; r < RIGHE; r++) {
        for (int c = 0; c < COLONNE; c++) {
            if (tabellone[r][c] == MISSILE_SYMBOL) {
                if (tabellone[r-1][c] == NEMICO_SYMBOL or tabellone[r-1][c] == 'Y' or tabellone[r-1][c] == 'Z') {
                    tabellone[r-1][c] = VUOTO_SYMBOL;
                    tabellone[r][c] = VUOTO_SYMBOL;
                }else {
                    tabellone[r-1][c] = MISSILE_SYMBOL;
                    tabellone[r][c] = VUOTO_SYMBOL;
                }
            }
        }
    }
}

