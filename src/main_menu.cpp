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
#include "types.h"
#include "gameplay.h"

extern GameContext_t gioco;
Index_t menu;

bool running = true;

void Load_Module_Assets() {
    if ( menu.regular != NULL ) {
        //Everything already loaded so we are going to exit
        return;
    }
    menu.regular = EDL_LoadAsset("assets/fonts/UbuntuMono-BoldItalic.ttf");
    if(menu.regular == NULL ) {
        menu.regular = EDL_LoadAsset("../assets/fonts/Quadrillion-Sb-It.otf");
    }

    menu.space = EDL_LoadAsset("../assets/fonts/SpaceNova-6Rpd1.otf");
    if(menu.space == NULL ) {
        menu.space = EDL_LoadAsset("../assets/fonts/SpaceNova-6Rpd1.otf");
    }
    menu.background = EDL_LoadAsset("../assets/schermate/sfondoMainMenu.png");

    SDL_Color red = { 255, 0, 0 };
    SDL_Color yellow = { 255, 255, 0 };
    SDL_Color purple = { 255, 0, 255 };

    //Definisco un primo stile title per il nome del gioco
    menu.titleStyle.font = menu.regular;
    menu.titleStyle.size = 120;
    menu.titleStyle.foreground = purple;

    //Definisco uno stile space cambiando font, colore e dimensione
    menu.menuStyle = menu.titleStyle;
    menu.menuStyle.font = menu.space;
    menu.menuStyle.size = 100;
    menu.menuStyle.foreground = yellow;

    menu.selectedStyle = menu.menuStyle;
    menu.selectedStyle.foreground = red;

}

void main_menu()
{
    Load_Module_Assets();
    SDL_Event event;
    inizializzaPartita(tabellone, TABELLONE);
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT ||
                (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE)) {
                running = false;
                }
            if(event.type == SDL_EVENT_KEY_DOWN && (event.key.scancode == SDL_SCANCODE_S || event.key.scancode == SDL_SCANCODE_DOWN))
            {
                if (menu.menuIndex+1 < 3)
                {
                    menu.menuIndex++;
                }
            }
            if(event.type == SDL_EVENT_KEY_DOWN && (event.key.scancode == SDL_SCANCODE_W || event.key.scancode == SDL_SCANCODE_UP))
            {
                if (menu.menuIndex-1 >= 0)
                {
                    menu.menuIndex--;
                }
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_RETURN) {
                if (menu.menuIndex == 0) {
                    gioco.stato = GAME_STATUS_PLAY;
                } else if (menu.menuIndex == 1) {
                    gioco.stato = GAME_STATUS_CREDITS;
                } else if (menu.menuIndex == 2) {
                    gioco.stato = GAME_STATUS_QUIT;
                }
                //Torno al looop principale dove verrà avviata la gestation del gioco opportuna
                return;
            }
        }

        EDL_FrameClear();
        EDL_DrawAsset(0, 0, menu.background, 0, 0.71);
        EDL_SetTextStyle(&menu.titleStyle);
        EDL_DrawText(0,70, 1366, 80, "SPEIS INVEIDERS", TEXT_CENTERED);

        EDL_SetTextStyle(&menu.menuStyle);
        if (menu.menuIndex == 0)
        {
            EDL_SetTextStyle(&menu.selectedStyle);
            EDL_DrawText(0,285, 1366, 125, "Play", TEXT_CENTERED);
            EDL_SetTextStyle(&menu.menuStyle);
            EDL_DrawText(0,385, 1366, 200, "Credits", TEXT_CENTERED);
            EDL_DrawText(0,485, 1366, 275, "Quit", TEXT_CENTERED);
        }
        else if (menu.menuIndex == 1)
        {
            EDL_DrawText(0,285, 1366, 125, "Play", TEXT_CENTERED);
            EDL_SetTextStyle(&menu.selectedStyle);
            EDL_DrawText(0,385, 1366, 200, "Credits", TEXT_CENTERED);
            EDL_SetTextStyle(&menu.menuStyle);
            EDL_DrawText(0,485, 1366, 275, "Quit", TEXT_CENTERED);
        }
        else if (menu.menuIndex == 2)
        {
            EDL_DrawText(0,285, 1366, 125, "Play", TEXT_CENTERED);
            EDL_DrawText(0,385, 1366, 200, "Credits", TEXT_CENTERED);
            EDL_SetTextStyle(&menu.selectedStyle);
            EDL_DrawText(0,485, 1366, 275, "Quit", TEXT_CENTERED);
        }

        EDL_FramePresent();
    }
    EDL_Destroy();
}
