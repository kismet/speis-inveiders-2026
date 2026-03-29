//
// Created by Admin on 29/03/2026.
//

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