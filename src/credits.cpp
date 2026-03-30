//
// Created by hp on 30/03/2026.
//
#include "gameplay.h"
#include "easy_sdl.h"
#include "types.h"

extern GameContext_t gioco;
Index_t crediti;
bool stampaCredits = true;

void Load_Credits_Assets() {
    crediti.space = EDL_LoadAsset("../assets/fonts/Quadrillion-Sb-It.otf");
    if(crediti.space == NULL ) {
        crediti.space = EDL_LoadAsset("../assets/fonts/Quadrillion-Sb-It.otf");
    }

    crediti.background = EDL_LoadAsset("../assets/schermate/sfondoInGame.png");

    SDL_Color white = { 255, 255, 255 };
    SDL_Color red = { 255, 0, 0 };
    SDL_Color purple = { 255, 0, 255 };

    crediti.titleStyle.font = crediti.space;
    crediti.titleStyle.size = 150;
    crediti.titleStyle.foreground = purple;

    crediti.menuStyle = crediti.titleStyle;
    crediti.menuStyle.size = 30;
    crediti.menuStyle.foreground = white;

    crediti.selectedStyle = crediti.menuStyle;
    crediti.selectedStyle.size = 15;
    crediti.selectedStyle.foreground = red;
}

void credits() {
    Load_Credits_Assets();
    SDL_Event event;
    while (stampaCredits)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT ||
                   (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE)) {
                gioco.stato = GAME_STATUS_QUIT;
                stampaCredits = false;
                   }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_RETURN) {
                if (crediti.menuIndex == 0) {
                    gioco.stato = GAME_STATUS_MENU;
                }
                return;
            }
        }

        EDL_FrameClear();
        EDL_DrawAsset(0, 0, crediti.background, 0, 0.71);
        EDL_SetTextStyle(&crediti.titleStyle);
        EDL_DrawText(250, 80, 1366, 80, "CREDITS", TEXT_CENTERED);

        EDL_SetTextStyle(&crediti.menuStyle);
        if (crediti.menuIndex == 0)
        {
            EDL_DrawText(555, 190, 1366, 100, "Lorenzo Buono", TEXT_CENTERED);
            EDL_DrawText(555, 215, 1366, 100, "Luca Calcagni", TEXT_CENTERED);
            EDL_DrawText(555, 240, 1366, 100, "Leonardo Capezzuoli", TEXT_CENTERED);
            EDL_DrawText(555, 265, 1366, 100, "Alessandro Ciardelli", TEXT_CENTERED);
            EDL_DrawText(555, 290, 1366, 100, "Amos Clipa", TEXT_CENTERED);
            EDL_DrawText(555, 315, 1366, 100, "Andrea Di Modugno", TEXT_CENTERED);
            EDL_DrawText(555, 340, 1366, 100, "Andy Dushku", TEXT_CENTERED);
            EDL_DrawText(555, 365, 1366, 100, "Lorenzo Esposito", TEXT_CENTERED);
            EDL_DrawText(555, 390, 1366, 100, "Michele Gargiulo", TEXT_CENTERED);
            EDL_DrawText(555, 415, 1366, 100, "Duccio Ghelli", TEXT_CENTERED);
            EDL_DrawText(555, 440, 1366, 100, "Alessio Giangrave'", TEXT_CENTERED);
            EDL_DrawText(555, 465, 1366, 100, "Gianmarco Landucci", TEXT_CENTERED);
            EDL_DrawText(555, 490, 1366, 100, "Marco Mannucci", TEXT_CENTERED);
            EDL_DrawText(555, 515, 1366, 100, "Marco Pandolfi", TEXT_CENTERED);
            EDL_DrawText(555, 540, 1366, 100, "Dario Salatti", TEXT_CENTERED);
            EDL_DrawText(555, 565, 1366, 100, "Gianmarco Tosi", TEXT_CENTERED);
            EDL_DrawText(555, 590, 1366, 100, "Elia Turini", TEXT_CENTERED);
            EDL_DrawText(555, 615, 1366, 100, "Gioele Zoppi", TEXT_CENTERED);
            EDL_SetTextStyle(&crediti.selectedStyle);
            EDL_DrawText(555, 660, 1366, 100, "PRESS ENTER TO RETURN TO MAIN MENU", TEXT_CENTERED);
        }
        EDL_FramePresent();
    }
    EDL_Destroy();
}