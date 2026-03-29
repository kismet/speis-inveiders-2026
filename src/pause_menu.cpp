//
// Created by Admin on 28/03/2026.
//
#include "easy_sdl.h"
#include "gameplay.h"
#include "types.h"

extern GameContext_t gioco;
Index_t menu2;
bool paused = true;


void Load_Pause_Assets() {
    if ( menu2.regular != NULL ) {
        //Everything already loaded so we are going to exit
        return;
    }
    menu2.regular = EDL_LoadAsset("assets/fonts/UbuntuMono-BoldItalic.ttf");
    if(menu2.regular == NULL ) {
        menu2.regular = EDL_LoadAsset("../assets/fonts/Quadrillion-Sb-It.otf");
    }

    menu2.space = EDL_LoadAsset("../assets/fonts/SpaceNova-6Rpd1.otf");
    if(menu2.space == NULL ) {
        menu2.space = EDL_LoadAsset("../assets/fonts/SpaceNova-6Rpd1.otf");
    }
    menu2.background = EDL_LoadAsset("../assets/schermate/sfondoInGame.png");

    SDL_Color red = { 255, 0, 0 };
    SDL_Color yellow = { 255, 255, 0 };
    SDL_Color purple = { 255, 0, 255 };

    //Definisco un primo stile title per il nome del gioco
    menu2.titleStyle.font = menu2.regular;
    menu2.titleStyle.size = 120;
    menu2.titleStyle.foreground = purple;

    //Definisco uno stile space cambiando font, colore e dimensione
    menu2.menuStyle = menu2.titleStyle;
    menu2.menuStyle.font = menu2.space;
    menu2.menuStyle.size = 100;
    menu2.menuStyle.foreground = yellow;

    menu2.selectedStyle = menu2.menuStyle;
    menu2.selectedStyle.foreground = red;

}

void pause_menu()
{
    Load_Pause_Assets();
    SDL_Event event;
    while (paused)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT ||
                   (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE)) {
                paused = false;
                   }
            if(event.type == SDL_EVENT_KEY_DOWN && (event.key.scancode == SDL_SCANCODE_S || event.key.scancode == SDL_SCANCODE_DOWN))
            {
                if (menu2.menuIndex+1 < 2)
                {
                    menu2.menuIndex++;
                }
            }
            if(event.type == SDL_EVENT_KEY_DOWN && (event.key.scancode == SDL_SCANCODE_W || event.key.scancode == SDL_SCANCODE_UP))
            {
                if (menu2.menuIndex-1 >= 0)
                {
                    menu2.menuIndex--;
                }
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_RETURN) {
                if (menu2.menuIndex == 0) {
                    gioco.stato = GAME_STATUS_PLAY;
                } else if (menu2.menuIndex == 1) {
                    gioco.stato = GAME_STATUS_QUIT;
                }
                //Torno al looop principale dove verrà avviata la gestione del gioco opportuna
                return;
            }
        }

        EDL_FrameClear();
        EDL_DrawAsset(0, 0, menu2.background, 0, 0.71);
        EDL_SetTextStyle(&menu2.titleStyle);
        EDL_DrawText(250, 80, 1366, 80, "PAUSE", TEXT_CENTERED);

        EDL_SetTextStyle(&menu2.menuStyle);
        if (menu2.menuIndex == 0)
        {
            EDL_SetTextStyle(&menu2.selectedStyle);
            EDL_DrawText(555, 285, 1366, 150, "Resume", TEXT_CENTERED);
            EDL_SetTextStyle(&menu2.menuStyle);
            EDL_DrawText(575, 385, 1366, 225, "Quit", TEXT_CENTERED);
        }
        else if (menu2.menuIndex == 1)
        {
            EDL_DrawText(555, 285, 1366, 150, "Resume", TEXT_CENTERED);
            EDL_SetTextStyle(&menu2.selectedStyle);
            EDL_DrawText(575, 385, 1366, 225, "Quit", TEXT_CENTERED);
        }
        EDL_FramePresent();
    }
    EDL_Destroy();
}