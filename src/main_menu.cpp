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

extern GameContext_t gioco;

Easy_Asset_t * regular = NULL;
Easy_Asset_t * space = NULL;
TextStyle_t titleStyle;
TextStyle_t menuStyle;
TextStyle_t selectedStyle;


int menuIndex = 0;
bool running = true;

void Load_Module_Assets() {
    if ( regular != NULL ) {
        //Everything already loaded so we are going to exit
        return;
    }
    regular = EDL_LoadAsset("assets/fonts/UbuntuMono-BoldItalic.ttf");
    if(regular == NULL ) {
        regular = EDL_LoadAsset("../assets/fonts/UbuntuMono-BoldItalic.ttf");
    }

    space = EDL_LoadAsset("../libs/edl/assets/fonts/SpaceNova-6Rpd1.otf");
    if(space == NULL ) {
        space = EDL_LoadAsset("../libs/edl/assets/fonts/SpaceNova-6Rpd1.otf");
    }

    SDL_Color red = { 255, 0, 0 };
    SDL_Color yellow = { 255, 255, 0 };
    SDL_Color purple = { 255, 0, 255 };

    //Definisco un primo stile title per il nome del gioco
    titleStyle.font = regular;
    titleStyle.size = 150;
    titleStyle.foreground = purple;

    //Definisco uno stile space cambiando font, colore e dimensione
    menuStyle = titleStyle;
    menuStyle.font = space;
    menuStyle.size = 80;
    menuStyle.foreground = yellow;

    selectedStyle = menuStyle;
    selectedStyle.foreground = red;

}

void main_menu()
{
    Load_Module_Assets();
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT ||
                (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE)) {
                running = false;
                }
            if(event.type == SDL_EVENT_KEY_DOWN && (event.key.scancode == SDL_SCANCODE_S || event.key.scancode == SDL_SCANCODE_DOWN))
            {
                if (menuIndex+1 <= 3)
                {
                    menuIndex++;
                }
            }
            if(event.type == SDL_EVENT_KEY_DOWN && (event.key.scancode == SDL_SCANCODE_W || event.key.scancode == SDL_SCANCODE_UP))
            {
                if (menuIndex-1 >= 0)
                {
                    menuIndex--;
                }
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_RETURN) {
                if (menuIndex == 0) {
                    gioco.stato = 1;
                } else if (menuIndex == 1) {
                    gioco.stato = 3;
                } else if (menuIndex == 3) {
                    gioco.stato = 5;
                }
                //Torno al looop principale dove verrà avviata la gestione del gioco opportuna
                return;
            }
        }

        EDL_FrameClear();
        EDL_SetTextStyle(&titleStyle);
        EDL_DrawText(120,70,"SPEIS INVEIDERS");

        EDL_SetTextStyle(&menuStyle);
        if (menuIndex == 0)
        {
            EDL_SetTextStyle(&selectedStyle);
            EDL_DrawText(555,285,"Play");
            EDL_SetTextStyle(&menuStyle);
            EDL_DrawText(465,385,"Settings");
            EDL_DrawText(475,485,"Credits");
            EDL_DrawText(575,585,"Quit");
        }
        else if (menuIndex == 1)
        {
            EDL_DrawText(555,285,"Play");
            EDL_SetTextStyle(&selectedStyle);
            EDL_DrawText(465,385,"Settings");
            EDL_SetTextStyle(&menuStyle);
            EDL_DrawText(475,485,"Credits");
            EDL_DrawText(575,585,"Quit");
        }
        else if (menuIndex == 2)
        {
            EDL_DrawText(555,285,"Play");
            EDL_DrawText(465,385,"Settings");
            EDL_SetTextStyle(&selectedStyle);
            EDL_DrawText(475,485,"Credits");
            EDL_SetTextStyle(&menuStyle);
            EDL_DrawText(575,585,"Quit");
        }
        else if (menuIndex == 3)
        {
            EDL_DrawText(555,285,"Play");
            EDL_DrawText(465,385,"Settings");
            EDL_DrawText(475,485,"Credits");
            EDL_SetTextStyle(&selectedStyle);
            EDL_DrawText(575,585,"Quit");
        }

        EDL_FramePresent();
    }
    EDL_Destroy();
}