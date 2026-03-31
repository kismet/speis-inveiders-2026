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
                }
                else if (tabellone[r-1][c] == NEMICO_SYMBOL) {
                    tabellone[r-1][c] = VUOTO_SYMBOL;
                    tabellone[r][c] = VUOTO_SYMBOL;
                    player.punteggio += 100;
                } else if (tabellone[r-1][c] == BARRIER_SYMBOL) {
                    checkBarriera(c);
                    tabellone[r][c] = VUOTO_SYMBOL;
                }
                else {
                    tabellone[r-1][c] = MISSILE_SYMBOL;
                    tabellone[r][c] = VUOTO_SYMBOL;
                }
            }
        }
    }
}

