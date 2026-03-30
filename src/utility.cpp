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
#include <cstring>
#include <iostream>


using namespace std;
// Aiuta a convertire un numero int in puntatore char, utile per stampare EDL_DrawText()
void stampaInt(int valore, char* buffer, int dim) {
    string str = to_string(valore);
    strncpy(buffer, str.c_str(), dim);
    buffer[dim-1] = '\0'; // sicurezza alla fine di un char* il testo si chiude con un \0
}

void printGame() {
    for (int r = 0; r < RIGHE; r++) {
        for (int c = 0; c < COLONNE; c++) {
            cout << tabellone[r][c];
        }
        cout << endl;
    }
}

void inizializzaPartita (char dst[27][23], const char source[27][23]) {
    for (int r = 0; r < 27; r++) {
        for (int c = 0; c < 23; c++) {
            dst[r][c] = source[r][c];
        }
    }
}

void continuoConVittoria (char t[27][23], unsigned int &missile_time, unsigned int &movement_time) {
    missile_time_reduction = (2.0/100) * missile_time;
    movement_time_reduction = (2.0/100) * movement_time;

    missile_time -= missile_time_reduction;
    movement_time -= movement_time_reduction;

}