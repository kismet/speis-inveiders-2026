/*
* Copyright 2026 Stefano Lenzi &lt;stefano@lenzi.pro&gt;
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TYPES_H
#define TYPES_H
#include <cstdint>

#define GAME_STATUS_MENU 0
#define GAME_STATUS_PLAYING 1
#define GAME_STATUS_PAUSA 2
#define GAME_STATUS_GAME_OVER 3
#define GAME_STATUS_GAME_OPTIONS 4
//TODO Aggiungere altre "costanti" se necessario per gli stati

typedef struct GameContext {
 uint8_t state;
 uint64_t score;
 uint16_t level;
 uint8_t difficulty;
} GameContext_t;

#endif
