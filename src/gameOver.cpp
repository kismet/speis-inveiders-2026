//
// Created by Admin on 28/03/2026.
//
#include "gameplay.h"
#include "easy_sdl.h"
#include "types.h"

extern GameContext_t gioco;
Index_t over;
bool gOver = true;

void Load_Over_Assets() {
    if ( over.space != NULL ) {
        //Everything already loaded so we are going to exit
        return;
    }
    over.space = EDL_LoadAsset("../assets/fonts/Quadrillion-Sb-It.otf");
    if(over.space == NULL ) {
        over.space = EDL_LoadAsset("../assets/fonts/Quadrillion-Sb-It.otf");
    }
    over.regular = EDL_LoadAsset("../assets/fonts/SpaceNova-6Rpd1.otf");
    if(over.regular == NULL)
    {
        over.regular = EDL_LoadAsset("../assets/fonts/SpaceNova-6Rpd1.otf");
    }
    over.background = EDL_LoadAsset("../assets/schermate/sfondoInGame.png");

    SDL_Color red = { 255, 0, 0 };
    SDL_Color yellow = { 255, 255, 0 };
    SDL_Color purple = { 255, 0, 255 };

    over.titleStyle.font = over.space;
    over.titleStyle.size = 150;
    over.titleStyle.foreground = purple;

    over.menuStyle.font = over.regular;
    over.menuStyle.size = 100;
    over.menuStyle.foreground = yellow;

    over.selectedStyle = over.menuStyle;
    over.selectedStyle.foreground = red;

}

void gameOver() {
    for (int c = 0; c < COLONNE; c++) {
        if (tabellone[26][c] == NEMICO_SYMBOL) {
            Load_Over_Assets();
            SDL_Event event;
            while (gOver)
            {
                while (SDL_PollEvent(&event))
                {
                    if (event.type == SDL_EVENT_QUIT ||
                           (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE)) {
                        gOver = false;
                           }
                    if(event.type == SDL_EVENT_KEY_DOWN && (event.key.scancode == SDL_SCANCODE_S || event.key.scancode == SDL_SCANCODE_DOWN))
                    {
                        if (over.menuIndex+1 < 3)
                        {
                            over.menuIndex++;
                        }
                    }
                    if(event.type == SDL_EVENT_KEY_DOWN && (event.key.scancode == SDL_SCANCODE_W || event.key.scancode == SDL_SCANCODE_UP))
                    {
                        if (over.menuIndex-1 >= 0)
                        {
                            over.menuIndex--;
                        }
                    }
                    if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_RETURN) {
                        if (over.menuIndex == 0) {
                            gioco.stato = GAME_STATUS_MENU;
                        } else if (over.menuIndex == 1) {
                            resetStatusPlay();
                            gioco.stato = GAME_STATUS_PLAY;
                        } else if (over.menuIndex == 2) {
                            gioco.stato = GAME_STATUS_QUIT;
                        }
                        //Torno al looop principale dove verrà avviata la gestione del gioco opportuna
                        return;
                    }
                }

                // TODO sistemare i font della schermata game over
                EDL_FrameClear();
                EDL_DrawAsset(0, 0, over.background, 0, 0.71);
                EDL_SetTextStyle(&over.titleStyle);
                EDL_DrawText(250,150, 1366, 80, "GAME OVER", TEXT_CENTERED);

                EDL_SetTextStyle(&over.menuStyle);
                if (over.menuIndex == 0)
                {
                    EDL_SetTextStyle(&over.selectedStyle);
                    EDL_DrawText(555,285, 1366, 125, "Main menu", TEXT_CENTERED);
                    EDL_SetTextStyle(&over.menuStyle);

                    EDL_DrawText(575,385, 1366, 200, "Restart", TEXT_CENTERED);
                    EDL_DrawText(575,485, 1366, 275, "Exit", TEXT_CENTERED);
                }
                else if (over.menuIndex == 1)
                {
                    EDL_DrawText(555, 285, 1366, 125, "Main menu", TEXT_CENTERED);
                    EDL_SetTextStyle(&over.selectedStyle);
                    EDL_DrawText(575, 385, 1366, 200, "Restart", TEXT_CENTERED);
                    EDL_SetTextStyle(&over.menuStyle);
                    EDL_DrawText(575, 485, 1366, 275, "Exit", TEXT_CENTERED);
                }
                else if (over.menuIndex == 2)
                {
                    EDL_DrawText(555, 285, 1366, 125, "Main menu", TEXT_CENTERED);
                    EDL_DrawText(575, 385, 1366, 200, "Restart", TEXT_CENTERED);
                    EDL_SetTextStyle(&over.selectedStyle);
                    EDL_DrawText(575, 485, 1366, 275, "Exit", TEXT_CENTERED);
                }
                EDL_FramePresent();
            }
            EDL_Destroy();
        }
    }
}