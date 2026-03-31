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
int schermo = EDL_DEFAULT_WINDOW_WIDTH;

void Load_Credits_Assets() {
    crediti.space = EDL_LoadAsset("../assets/fonts/Quadrillion-Sb-It.otf");
    if(crediti.space == NULL ) {
        crediti.space = EDL_LoadAsset("../assets/fonts/Quadrillion-Sb-It.otf");
    }

    crediti.background = EDL_LoadAsset("../assets/schermate/sfondoInGame.png");

    SDL_Color white = { 255, 255, 255 };
    SDL_Color orange = { 255, 165, 0 };
    SDL_Color purple = { 255, 0, 255 };

    crediti.titleStyle.font = crediti.space;
    crediti.titleStyle.size = 110;
    crediti.titleStyle.foreground = purple;

    crediti.menuStyle = crediti.titleStyle;
    crediti.menuStyle.size = 20;
    crediti.menuStyle.foreground = white;

    crediti.selectedStyle = crediti.titleStyle;
    crediti.selectedStyle.size = 30;
    crediti.selectedStyle.foreground = orange;
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
        EDL_DrawText(250, 80, 1366, 60, "CREDITS", TEXT_CENTERED);

        EDL_SetTextStyle(&crediti.menuStyle);
        if (crediti.menuIndex == 0)
        {
            //PROFESSORI
            EDL_DrawText(555, 160, schermo/2, 140, "Stefano Lenzi", TEXT_CENTERED);
            EDL_DrawText(555, 185, schermo/2, 140, "Enio Parlanti", TEXT_CENTERED);
            EDL_DrawText(555, 210, schermo/2, 140, "Marilena Simone", TEXT_CENTERED);

            //GRAFICA
            EDL_DrawText(555, 255, schermo/2, 200, "Leonardo Capezzuoli", TEXT_CENTERED);
            EDL_DrawText(555, 280, schermo/2, 200, "Lorenzo Esposito", TEXT_CENTERED);
            EDL_DrawText(555, 305, schermo/2, 200, "Gianmarco Landucci", TEXT_CENTERED);
            EDL_DrawText(555, 330, schermo/2, 200, "Dario Salatti", TEXT_CENTERED);
            EDL_DrawText(555, 355, schermo/2, 200, "Gianmarco Tosi", TEXT_CENTERED);

            //PROGRAMMAZIONE
            EDL_DrawText(555, 400, schermo/2, 260, "Leonardo Capezzuoli", TEXT_CENTERED);
            EDL_DrawText(555, 425, schermo/2, 260, "Amos Clipa", TEXT_CENTERED);
            EDL_DrawText(555, 450, schermo/2, 260, "Michele Gargiulo", TEXT_CENTERED);
            EDL_DrawText(555, 475, schermo/2, 260, "Marco Mannucci", TEXT_CENTERED);
            EDL_DrawText(555, 500, schermo/2, 260, "Marco Pandolfi", TEXT_CENTERED);
            EDL_DrawText(555, 525, schermo/2, 260, "Elia Turini", TEXT_CENTERED);

            //GESTIONE
            EDL_DrawText(555, 160, schermo+683, 140, "Lorenzo Buono", TEXT_CENTERED);
            EDL_DrawText(555, 185, schermo+683, 140, "Amos Clipa", TEXT_CENTERED);
            EDL_DrawText(555, 210, schermo+683, 140, "Andrea Di Modugno", TEXT_CENTERED);
            EDL_DrawText(555, 235, schermo+683, 140, "Alessio Giangrave'", TEXT_CENTERED);
            EDL_DrawText(555, 260, schermo+683, 140, "Gianmarco Landucci", TEXT_CENTERED);
            EDL_DrawText(555, 285, schermo+683, 140, "Marco Mannucci", TEXT_CENTERED);

            //SUPPORTO
            EDL_DrawText(555, 320, schermo+683, 200, "Lorenzo Buono", TEXT_CENTERED);
            EDL_DrawText(555, 345, schermo+683, 200, "Luca Calcagni", TEXT_CENTERED);
            EDL_DrawText(555, 370, schermo+683, 200, "Alessandro Ciardelli", TEXT_CENTERED);
            EDL_DrawText(555, 395, schermo+683, 200, "Alessio Giangrave'", TEXT_CENTERED);
            EDL_DrawText(555, 420, schermo+683, 200, "Gianmarco Landucci", TEXT_CENTERED);
            EDL_DrawText(555, 445, schermo+683, 200, "Marco Pandolfi", TEXT_CENTERED);
            EDL_DrawText(555, 470, schermo+683, 200, "Gianmarco Tosi", TEXT_CENTERED);
            EDL_DrawText(555, 495, schermo+683, 200, "Joele Zoppi", TEXT_CENTERED);

            //COMUNICAZIONE
            EDL_DrawText(555, 525, schermo+683, 260, "Andrea Di Modugno", TEXT_CENTERED);
            EDL_DrawText(555, 550, schermo+683, 260, "Duccio Ghelli", TEXT_CENTERED);

            EDL_DrawText(555, 685, 1366, 110, "PRESS ENTER TO RETURN TO MAIN MENU", TEXT_CENTERED);

            EDL_SetTextStyle(&crediti.selectedStyle);
            EDL_DrawText(555, 140, schermo/2, 120, "PROFESSORI", TEXT_CENTERED);
            EDL_DrawText(555, 270, schermo/2, 120, "GRAFICA", TEXT_CENTERED);
            EDL_DrawText(555, 415, schermo/2, 180, "PROGRAMMAZIONE", TEXT_CENTERED);
            EDL_DrawText(555, 140, schermo+683, 120, "GESTIONE", TEXT_CENTERED);
            EDL_DrawText(555, 335, schermo+683, 120, "SUPPORTO", TEXT_CENTERED);
            EDL_DrawText(555, 540, schermo+683, 180, "COMUNICAZIONE", TEXT_CENTERED);
        }
        EDL_FramePresent();
    }
    EDL_Destroy();
}

/*
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
EDL_DrawText(555, 630, 1366, 100, "Joele Zoppi", TEXT_CENTERED);
*/