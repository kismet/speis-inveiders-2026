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
#include "globals.h"

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
    crediti.titleStyle.size = 140;
    crediti.titleStyle.foreground = purple;

    crediti.menuStyle = crediti.titleStyle;
    crediti.menuStyle.size = 25;
    crediti.menuStyle.foreground = white;

    crediti.selectedStyle = crediti.menuStyle;
    crediti.selectedStyle.size = 20;
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
            EDL_DrawText(555, 155, 1366, 100, "Stefano Lenzi", TEXT_CENTERED);
            EDL_DrawText(555, 180, 1366, 100, "Enio Parlanti", TEXT_CENTERED);
            EDL_DrawText(555, 205, 1366, 100, "Lorenzo Buono", TEXT_CENTERED);
            EDL_DrawText(555, 230, 1366, 100, "Luca Calcagni", TEXT_CENTERED);
            EDL_DrawText(555, 255, 1366, 100, "Leonardo Capezzuoli", TEXT_CENTERED);
            EDL_DrawText(555, 280, 1366, 100, "Alessandro Ciardelli", TEXT_CENTERED);
            EDL_DrawText(555, 305, 1366, 100, "Amos Clipa", TEXT_CENTERED);
            EDL_DrawText(555, 330, 1366, 100, "Andrea Di Modugno", TEXT_CENTERED);
            EDL_DrawText(555, 355, 1366, 100, "Andy Dushku", TEXT_CENTERED);
            EDL_DrawText(555, 380, 1366, 100, "Lorenzo Esposito", TEXT_CENTERED);
            EDL_DrawText(555, 405, 1366, 100, "Michele Gargiulo", TEXT_CENTERED);
            EDL_DrawText(555, 430, 1366, 100, "Duccio Ghelli", TEXT_CENTERED);
            EDL_DrawText(555, 455, 1366, 100, "Alessio Giangrave'", TEXT_CENTERED);
            EDL_DrawText(555, 480, 1366, 100, "Gianmarco Landucci", TEXT_CENTERED);
            EDL_DrawText(555, 505, 1366, 100, "Marco Mannucci", TEXT_CENTERED);
            EDL_DrawText(555, 530, 1366, 100, "Marco Pandolfi", TEXT_CENTERED);
            EDL_DrawText(555, 555, 1366, 100, "Dario Salatti", TEXT_CENTERED);
            EDL_DrawText(555, 580, 1366, 100, "Gianmarco Tosi", TEXT_CENTERED);
            EDL_DrawText(555, 605, 1366, 100, "Elia Turini", TEXT_CENTERED);
            EDL_DrawText(555, 630, 1366, 100, "Gioele Zoppi", TEXT_CENTERED);
            EDL_SetTextStyle(&crediti.selectedStyle);
            EDL_DrawText(555, 675, 1366, 100, "PRESS ENTER TO RETURN TO MAIN MENU", TEXT_CENTERED);
        }
        EDL_FramePresent();
    }
    EDL_Destroy();
}