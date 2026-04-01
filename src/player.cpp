// Copyright 2026 Stefano Lenzi &lt;stefano@lenzi.pro&gt;
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "gameplay.h"
#include "types.h"
#include "globals.h"

void passoSinistro() {

    if ( player.x != 0) {
        if (tabellone[player.Y][player.x - 1] ==MISSILE_NEMICO_SYMBOL) {
            player.lives--;
            if (player.lives <= 0) {
                gameOver();
            }
        }
        tabellone[player.Y][player.x] = '-';
        tabellone[player.Y][player.x - 1] = NAVICELLA_SYMBOL;
        player.x --;

    }

}

void passoDestro() {

    if ( player.x != 22) {
        if (tabellone[player.Y][player.x + 1] ==MISSILE_NEMICO_SYMBOL) {
            player.lives--;
            if (player.lives <= 0) {
                gameOver();
            }
        }
        tabellone[player.Y][player.x] = '-';
        tabellone[player.Y][player.x + 1] = '^';
        player.x ++;

    }
}

void generaBomba () {

    if (player.bombs > 0) {
        for (int c = 0; c < COLONNE; c++)
        {
            if (tabellone[26][c] == NAVICELLA_SYMBOL)
            {
                if (tabellone[25][c] == BOMB_SYMBOL)
                {
                    return;
                }
                else if (tabellone[25][c] == MISSILE_SYMBOL)
                {
                    return;
                }
                else {
                    tabellone[25][c] = BOMB_SYMBOL;
                    player.bombs--;
                }
            }


        }
    }
}

void spostaBomba () {
    for (int r = 0; r < RIGHE; r++) {
        for (int c = 0; c < COLONNE; c++) {
            if (tabellone[r][c] == BOMB_SYMBOL) {
                if (tabellone [r - 1][c] == NEMICO_SYMBOL) {
                    if (tabellone[r - 2][c] == NEMICO_SYMBOL) {
                        tabellone[r - 2][c] = VUOTO_SYMBOL;
                        player.punteggio += 100;
                    }
                    if (tabellone[r - 1][c + 1] == NEMICO_SYMBOL) {
                        tabellone[r - 1][c + 1] = VUOTO_SYMBOL;
                        player.punteggio += 100;
                    }
                    if (tabellone[r - 1][c] == NEMICO_SYMBOL) {
                        tabellone[r - 1][c] = VUOTO_SYMBOL;
                        player.punteggio += 100;
                    }
                    if (tabellone[r - 1][c - 1] == NEMICO_SYMBOL) {
                        tabellone[r - 1][c - 1] = VUOTO_SYMBOL;
                        player.punteggio += 100;
                    }

                    tabellone[r][c] = VUOTO_SYMBOL;


                }
                else if (tabellone [r - 1][c] == VUOTO_SYMBOL) {
                    tabellone[r - 1][c] = BOMB_SYMBOL;
                    tabellone[r][c] = VUOTO_SYMBOL;
                }
            }
        }
    }
}

void esplodiBomba (int righe, int colonna) {
    tabellone[righe + 1][colonna] = VUOTO_SYMBOL;
    tabellone[righe][colonna + 1] = VUOTO_SYMBOL;
    tabellone[righe - 1][colonna] = VUOTO_SYMBOL;
    tabellone[righe][colonna - 1] = VUOTO_SYMBOL;
    tabellone[righe][colonna] = VUOTO_SYMBOL;
}

bool generaSparo () {
    bool sparoPossibile = true;

    if (player.spari >= 3)
    {
        sparoPossibile = false;
    }

    for (int c = 0; c < COLONNE; c++)
    {
        if (tabellone[26][c] == NAVICELLA_SYMBOL)
        {
            if (tabellone[25][c] == MISSILE_SYMBOL)
            {
                sparoPossibile = false;
            }
        }
    }

    if (sparoPossibile) {
        player.spari++;
        tabellone[player.Y-1][player.x] = MISSILE_SYMBOL;
    }
    return sparoPossibile;
}

void avanzaSparo() {
    for (int r = 0; r < RIGHE; r++) {
        for (int c = 0; c < COLONNE; c++) {
            if (tabellone[r][c] == MISSILE_SYMBOL) {
                if (r == 0) {
                    tabellone[r][c] = VUOTO_SYMBOL;
                    player.spari--;
                }
                else if (tabellone[r-1][c] == NEMICO_SYMBOL) {
                    tabellone[r-1][c] = VUOTO_SYMBOL;
                    tabellone[r][c] = VUOTO_SYMBOL;
                    player.spari--;
                    player.punteggio += 100;
                } else if (tabellone[r-1][c] == BARRIER_SYMBOL) {
                    checkBarriera(c);
                    tabellone[r][c] = VUOTO_SYMBOL;
                    player.spari--;
                } else if (tabellone[r-1][c] == BOMB_SYMBOL) {

                    tabellone[r-1][c] = VUOTO_SYMBOL;
                    tabellone[r][c] = VUOTO_SYMBOL;
                    player.spari--;
                    if (player.bombs <= 3) {
                    player.bombs++;
                    }
                }
                else {
                    tabellone[r-1][c] = MISSILE_SYMBOL;
                    tabellone[r][c] = VUOTO_SYMBOL;
                }
            }
        }
    }
}


