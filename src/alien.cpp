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
#include "SDL3/SDL_timer.h"
#include "types.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "globals.h"

void sparoAlieni () {
    int colonnaAlieno = rand() % 8; // creo il numero casuale

    int ultimaRigaAlieni = -1;
    colonnaAlieno += gioco.primaColonnaAlieni;
    int contatoreColonne = 0, contatorRighe = 0;
    bool continua = true;

    for (int r = 0; r < RIGHE - 1; r++) {
        if (tabellone[r][colonnaAlieno] == NEMICO_SYMBOL) {
            ultimaRigaAlieni = r;
        }
    }

    if (ultimaRigaAlieni < RIGHE - 1) {
        tabellone[ultimaRigaAlieni + 1][colonnaAlieno] = MISSILE_NEMICO_SYMBOL;
    }

}

void avanzoSparoAlieni () {
    for (int r = 26; r >= 0; r--) {
        for (int c = 22; c >= 0; c--) {
            if (tabellone[r][c] == MISSILE_NEMICO_SYMBOL) {
                if (tabellone[r+1][c] == NAVICELLA_SYMBOL) {
                    if (player.lives > 0) {
                        tabellone[r+1][c] = NAVICELLA_SYMBOL;
                        player.lives--;
                    }
                    if (player.lives <= 0) {
                        tabellone[r+1][c] = VUOTO_SYMBOL;
                        gameOver();
                    }
                    tabellone[r][c] = VUOTO_SYMBOL;
                }
                else if (tabellone[r+1][c] == VUOTO_SYMBOL) {
                    tabellone[r+1][c] = MISSILE_NEMICO_SYMBOL;
                    tabellone[r][c] = VUOTO_SYMBOL;
                }
                else if (tabellone[r+1][c] == BARRIER_SYMBOL) {
                    checkBarriera(c);
                    tabellone[r][c] = VUOTO_SYMBOL;
                }
                else if (tabellone[r][c] == tabellone[26][c]) {
                    tabellone[r][c] = VUOTO_SYMBOL;
                }
                else if (r == RIGHE - 1) {
                    tabellone[r][c] = VUOTO_SYMBOL;
                }
            }
        }
    }
}

bool destra() {

    bool toccaDestra = false;

    for ( int i = 0; i < RIGHE; i++ ) {
        if ( tabellone[i][COLONNE - 1] == NEMICO_SYMBOL ) {
            toccaDestra = true;
        }
    }

    return toccaDestra;
}

bool sinistra() {

    bool toccaSinistra = false;

    for ( int i = 0; i < RIGHE; i++ ) {
        if ( tabellone[i][0] == NEMICO_SYMBOL ) {
            toccaSinistra = true;
        }
    }

    return toccaSinistra;
}

bool basso() {

    bool toccaBasso = false;

    for ( int i = 0; i < COLONNE; i++ ) {
        if ( tabellone[RIGHE - 1][i] == NEMICO_SYMBOL ) {
            toccaBasso = true;
        }
    }

    return toccaBasso;
}

void spostaDestraNemici() {
    for ( int r = 0; r < RIGHE; r++ ) {
        for ( int c = 22; c >= 0; c-- ) {
            if ( tabellone[r][c] == NEMICO_SYMBOL ) {

                if ( tabellone[r][c + 1] == VUOTO_SYMBOL ) {

                    tabellone[r][c] = VUOTO_SYMBOL;
                    tabellone[r][c + 1] = NEMICO_SYMBOL;
                }

                else if (tabellone[r][c + 1] == MISSILE_SYMBOL) {
                    player.spari--;
                    tabellone[r][c] = VUOTO_SYMBOL;
                    tabellone[r][c + 1] = VUOTO_SYMBOL;
                }

                else if (tabellone[r][c + 1] == MISSILE_NEMICO_SYMBOL) {
                    tabellone[r][c] = MISSILE_NEMICO_SYMBOL;
                    tabellone[r][c + 1] = NEMICO_SYMBOL;
                }
            }
        }
    }
    gioco.primaColonnaAlieni++;
}

void spostaSinistraNemici() {
    for ( int r = 0; r < RIGHE; r++ ) {
        for ( int c = 0; c < COLONNE; c++ ) {
            if ( tabellone[r][c] == NEMICO_SYMBOL ) {

                if ( tabellone[r][c - 1] == VUOTO_SYMBOL ) {

                    tabellone[r][c] = VUOTO_SYMBOL;
                    tabellone[r][c - 1] = NEMICO_SYMBOL;
                }

                else if (tabellone[r][c - 1] == MISSILE_SYMBOL) {
                    player.spari--;
                    tabellone[r][c] = VUOTO_SYMBOL;
                    tabellone[r][c - 1] = VUOTO_SYMBOL;
                }

                else if (tabellone[r][c - 1] == MISSILE_NEMICO_SYMBOL) {

                    tabellone[r][c] = MISSILE_NEMICO_SYMBOL;
                    tabellone[r][c - 1] = NEMICO_SYMBOL;
                }
            }
        }
    }
    gioco.primaColonnaAlieni--;
}

void spostaInBassoNemico() {

    for ( int i = RIGHE - 1; i > 0; i--) {
        for ( int j = 0; j < COLONNE; j++ ) {
            if ( tabellone[i - 1][j] == NEMICO_SYMBOL && tabellone[i][j] != MISSILE_SYMBOL ) {
                tabellone[i - 1][j] = VUOTO_SYMBOL;
                tabellone[i][j] = NEMICO_SYMBOL;
            }
            else if ( tabellone[i - 1][j] == NEMICO_SYMBOL && tabellone[i][j] == MISSILE_SYMBOL ) {
                tabellone[i - 1][j] = VUOTO_SYMBOL;
                tabellone[i][j] = VUOTO_SYMBOL;
                player.spari--;
                player.punteggio += 100;
            }
        }
    }
    if (basso())
    {
        gameOver();
    }
}

void spostaNemici() {

    if (startTime+500UL < SDL_GetTicks()) {
        startTime = SDL_GetTicks();
        if ( versoDestra  ) {
            if ( !destra() ) {
                spostaDestraNemici();
            } else {
                spostaInBassoNemico();
                versoDestra = false;
            }
        } else {
            if ( !sinistra() ) {
                spostaSinistraNemici();
            } else {
                spostaInBassoNemico();
                versoDestra = true;
            }
        }
    }
}