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

extern bool versoDestra;
extern int startTime;
extern Player_t player;

void sparoAlieni () {
    srand(time(0));
    int sceltaAlieno = rand() % 10; // creo il numero casuale

    int ultimaRigaAlieni;
    int colonnaAlieno;
    for (int r = 0; r < 27; r++) {
        for (int c = 0; c < 23; c++) {
            if (tabellone[r][c] == NEMICO_SYMBOL) {
                ultimaRigaAlieni = r;
            }
        }
    }

    for (int c = 0;c < 23;) {
        if (tabellone[ultimaRigaAlieni][c] == NEMICO_SYMBOL) {
            if (sceltaAlieno == 0) {
                colonnaAlieno = c;
                c = 23;
            }
            sceltaAlieno--;
        }
        if (c == 22) {
            c = 0;
        }
        else {
            c++;
        }
    }

    tabellone[ultimaRigaAlieni + 1][colonnaAlieno] = MISSILE_NEMICO_SYMBOL;

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
                else if (tabellone[r][c] == tabellone[26][c]) {
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

void spostaADestraNemici() {

    for ( int i = 0; i < RIGHE; i++ ) {
        for ( int j = COLONNE - 1; j > 0; j-- ) {
            if ( tabellone[i][j - 1] == NEMICO_SYMBOL && tabellone[i][j] == MISSILE_SYMBOL ) {
                tabellone[i][j - 1] = VUOTO_SYMBOL;
                tabellone[i][j] = VUOTO_SYMBOL;
                player.punteggio += 100;
            } else if ( tabellone[i][j - 1] == NEMICO_SYMBOL && (tabellone[i][j] == VUOTO_SYMBOL || tabellone[i][j] == BARRIER_SYMBOL )) {
                tabellone[i][j - 1] = VUOTO_SYMBOL;
                tabellone[i][j] = NEMICO_SYMBOL;
            }
        }
    }
}

void spostaASinistraNemici() {

    for ( int i = 0; i < RIGHE; i++ ) {
        for ( int j = 0; j < COLONNE - 1; j++ ) {
            if ( tabellone[i][j + 1] == NEMICO_SYMBOL && tabellone[i][j] == MISSILE_SYMBOL ) {
                tabellone[i][j + 1] = VUOTO_SYMBOL;
                tabellone[i][j] = VUOTO_SYMBOL;
                player.punteggio += 100;
            } else if ( tabellone[i][j + 1] == NEMICO_SYMBOL && tabellone[i][j] == VUOTO_SYMBOL ) {
                tabellone[i][j + 1] = VUOTO_SYMBOL;
                tabellone[i][j] = NEMICO_SYMBOL;
            }
        }
    }
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
                spostaADestraNemici();
            } else {
                spostaInBassoNemico();
                versoDestra = false;
            }
        } else {
            if ( !sinistra() ) {
                spostaASinistraNemici();
            } else {
                spostaInBassoNemico();
                versoDestra = true;
            }
        }
    }
}