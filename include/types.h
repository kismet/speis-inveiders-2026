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

#ifndef SPEIS_INVEIDERS_TYPES_H
#define SPEIS_INVEIDERS_TYPES_H


typedef enum GameStaus {
    GAME_STATUS_MENU,
    GAME_STAUS_PLAY,
    GAME_STATUS_OPTIONS,
    GAME_STATUS_QUIT
    //TODO complete by students
} GameStatus_t;

typedef struct GameContext {
    GameStatus_t stato;
} GameContext_t;

typedef struct Player {
    int x;
    int y;
    int spariRimasti = 0;
    int punteggio;
    int lives;
} Player_t;

#endif //SPEIS_INVEIDERS_TYPES_H