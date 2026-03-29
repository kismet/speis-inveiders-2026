//
// Created by Admin on 29/03/2026.
//
#include "easy_sdl.h"
#include "gameplay.h"
#include "types.h"

extern GameContext_t gioco;
Index_t lvlUP;
bool newLevel = true;

bool nemiciVivi()
{
    for (int r = 0; r < RIGHE-1; r++)
    {
        for (int c = 0; c < COLONNE; c++)
        {
            if (tabellone[r][c] == NEMICO_SYMBOL)
            {
                return false;
            }
        }
    }
    return true;
}

void Load_NewLevel_Assets() {
    if ( lvlUP.regular != NULL ) {
        //Everything already loaded so we are going to exit
        return;
    }
    lvlUP.regular = EDL_LoadAsset("assets/fonts/UbuntuMono-BoldItalic.ttf");
    if(lvlUP.regular == NULL ) {
        lvlUP.regular = EDL_LoadAsset("../assets/fonts/Quadrillion-Sb-It.otf");
    }

    lvlUP.space = EDL_LoadAsset("../assets/fonts/SpaceNova-6Rpd1.otf");
    if(lvlUP.space == NULL ) {
        lvlUP.space = EDL_LoadAsset("../assets/fonts/SpaceNova-6Rpd1.otf");
    }
    lvlUP.background = EDL_LoadAsset("../assets/schermate/sfondoInGame.png");

    SDL_Color red = { 255, 0, 0 };
    SDL_Color yellow = { 255, 255, 0 };
    SDL_Color purple = { 255, 0, 255 };

    lvlUP.titleStyle.font = lvlUP.regular;
    lvlUP.titleStyle.size = 120;
    lvlUP.titleStyle.foreground = purple;

    lvlUP.menuStyle = lvlUP.titleStyle;
    lvlUP.menuStyle.font = lvlUP.space;
    lvlUP.menuStyle.size = 100;
    lvlUP.menuStyle.foreground = yellow;

    lvlUP.selectedStyle = lvlUP.menuStyle;
    lvlUP.selectedStyle.foreground = red;

}

void levelUP()
{
    if (!nemiciVivi())
    {
        //TODO stampa scritte per accedere al livello successivo
    }
}