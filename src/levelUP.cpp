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

#include "easy_sdl.h"
#include "gameplay.h"
#include "types.h"

extern Player_t player;
extern GameContext_t gioco;
Index_t lvlUP;
bool newLevel = false;

bool nemiciVivi()
{
    for (int r = 0; r < RIGHE-1; r++)
    {
        for (int c = 0; c < COLONNE; c++)
        {
            if (tabellone[r][c] == NEMICO_SYMBOL)
            {
                return true;
            }
        }
    }
    gioco.level += 1;
    newLevel = true;
    return false;
}

void Load_NewLevel_Assets() {
    if ( lvlUP.regular != NULL ) {
        //Everything already loaded so we are going to exit
        return;
    }
    lvlUP.regular = EDL_LoadAsset("assets/fonts/Quadrillion-Sb-It.otf");
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
        Load_NewLevel_Assets();
        SDL_Event event;
        while (newLevel)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_EVENT_QUIT ||
                    (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE))
                {
                    newLevel = false;
                    gioco.stato = GAME_STATUS_QUIT;
                }
                if (event.type == SDL_EVENT_KEY_DOWN && (event.key.scancode == SDL_SCANCODE_S || event.key.scancode ==
                    SDL_SCANCODE_DOWN))
                {
                    if (lvlUP.menuIndex + 1 < 3)
                    {
                        lvlUP.menuIndex++;
                    }
                }
                if (event.type == SDL_EVENT_KEY_DOWN && (event.key.scancode == SDL_SCANCODE_W || event.key.scancode ==
                    SDL_SCANCODE_UP))
                {
                    if (lvlUP.menuIndex - 1 >= 0)
                    {
                        lvlUP.menuIndex--;
                    }
                }
                if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_RETURN)
                {
                    if (lvlUP.menuIndex == 0)
                    {
                        //TODO aumenta difficolta'
                        inizializzaPartita(tabellone, TABELLONE);
                        gioco.stato = GAME_STATUS_PLAY;
                    }
                    else if (lvlUP.menuIndex == 1)
                    {
                        player.punteggio = 0;
                        gioco.level = 1;
                        gioco.stato = GAME_STATUS_MENU;
                    }
                    else if (lvlUP.menuIndex == 2)
                    {
                        gioco.stato = GAME_STATUS_QUIT;
                    }
                    //Torno al looop principale dove verrà avviata la gestione del gioco opportuna
                    return;
                }
            }


            EDL_FrameClear();
            EDL_DrawAsset(0, 0, lvlUP.background, 0, 0.71);
            EDL_SetTextStyle(&lvlUP.titleStyle);
            EDL_DrawText(250, 80, 1366, 80, "LEVEL PASSED", TEXT_CENTERED);

            EDL_SetTextStyle(&lvlUP.menuStyle);
            if (lvlUP.menuIndex == 0)
            {
                EDL_SetTextStyle(&lvlUP.selectedStyle);
                EDL_DrawText(0,285, 1366, 125, "New level", TEXT_CENTERED);
                EDL_SetTextStyle(&lvlUP.menuStyle);
                EDL_DrawText(0,385, 1366, 200, "Main menu", TEXT_CENTERED);
                EDL_DrawText(0,485, 1366, 275, "Quit", TEXT_CENTERED);
            }
            else if (lvlUP.menuIndex == 1)
            {
                EDL_DrawText(0,285, 1366, 125, "New level", TEXT_CENTERED);
                EDL_SetTextStyle(&lvlUP.selectedStyle);
                EDL_DrawText(0,385, 1366, 200, "Main menu", TEXT_CENTERED);
                EDL_SetTextStyle(&lvlUP.menuStyle);
                EDL_DrawText(0,485, 1366, 275, "Quit", TEXT_CENTERED);
            }
            else if (lvlUP.menuIndex == 2)
            {
                EDL_DrawText(0,285, 1366, 125, "New level", TEXT_CENTERED);
                EDL_DrawText(0,385, 1366, 200, "Main menu", TEXT_CENTERED);
                EDL_SetTextStyle(&lvlUP.selectedStyle);
                EDL_DrawText(0,485, 1366, 275, "Quit", TEXT_CENTERED);
            }
            EDL_FramePresent();
        }
        EDL_Destroy();
    }
}