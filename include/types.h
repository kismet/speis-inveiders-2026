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

#ifndef SPEIS_INVEIDERS_TYPES_H
#define SPEIS_INVEIDERS_TYPES_H

#include "easy_sdl.h"


typedef enum GameStaus {
    GAME_STATUS_MENU,
    GAME_STATUS_PLAY,
    GAME_STATUS_PAUSE,
    GAME_STATUS_QUIT,
    GAME_STATUS_CREDITS
    //TODO complete by students
} GameStatus_t;

typedef struct BarrierContext {
    int colonna;
    int lives;
} BarrierContext_t;

typedef struct GameContext {
    GameStatus_t stato;
    int level;
    int primaColonnaAlieni = 7;
} GameContext_t;

typedef struct Player {
    int x = 11;
    const int Y = 26;
    unsigned int spari = 0;
    int punteggio = 0;
    int lives = 3;
    Easy_Asset_t *navicella;
    int bombs = 3;
} Player_t;

typedef struct Index {
    Easy_Asset_t * regular = NULL;
    Easy_Asset_t * space = NULL;
    TextStyle_t titleStyle;
    TextStyle_t menuStyle;
    TextStyle_t selectedStyle;
    TextStyle_t extraStyle;
    Easy_Asset_t* background;
    int menuIndex = 0;
} Index_t;

#endif //SPEIS_INVEIDERS_TYPES_H
