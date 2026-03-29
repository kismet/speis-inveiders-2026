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

#ifndef SPEIS_INVEIDERS_GAMEPLAY_H
#define SPEIS_INVEIDERS_GAMEPLAY_H

extern const char MISSILE_SYMBOL;
extern const char NAVICELLA_SYMBOL;
extern const char VUOTO_SYMBOL;
extern const char NEMICO_SYMBOL;
extern const char BARRIER_SYMBOL;
extern const unsigned int RIGHE;
extern const unsigned int COLONNE;
extern const unsigned int MISSILE_BASIC_SPEED;
extern char tabellone[27][23];

void main_menu();

void pause_menu();

void stampaInt(int valore, char* buffer, int dim);

void printGame();

void main_menu();

void passoSinistro();

void passoDestro();

bool generaSparo();

void avanzaSparo();

void spostaInBassoNemico();

void spostaASinistraNemici();

void spostaADestraNemici();

bool destra();

bool sinistra();

bool basso();

void spostaNemici();

void gameOver();

void resetStatusPlay();

void inizializzaPartita (char dst[27][23], const char source[27][23]);

#endif //SPEIS_INVEIDERS_GAMEPLAY_H
