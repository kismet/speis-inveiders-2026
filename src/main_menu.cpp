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

//TODO Completa questo codice per visualizzare "Menu"

#include <easy_sdl.h>
#include "gameplay.h"
#include "types.h"

extern GameContext_t game;

void main_menu() {
    //TODO Implementami!
    //TODO Copiami e adattami per gli altri stati
    SDL_Event event;;
    while (game.state == GAME_STATUS_MENU) {
        EDL_FrameClear();
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT ||
                (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE)) {
                }
        }
    }
}