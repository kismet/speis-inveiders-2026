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
#include "easy_sdl.h"
#include "types.h"

using namespace std;

extern GameContext_t gioco;
extern char tabellone[27][23];
extern Player_t player;
extern bool versoDestra;

void resetStatusPlay()
{
    player.punteggio=0;
    player.x=11;

    for (int i=0; i<RIGHE; i++)
    {
        for (int j=0; j<COLONNE; j++)
        {
            tabellone[i][j]=VUOTO_SYMBOL;
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 7; j <= 15; j++) {
            tabellone[i][j] = NEMICO_SYMBOL;
        }
    }

    tabellone[26][11]=NAVICELLA_SYMBOL;

    gioco.stato=GAME_STATUS_PLAY;
}