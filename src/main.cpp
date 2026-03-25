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

#include <chrono>
#include <thread>
#include <iostream>

#include "../../include/easy_sdl.h"
#include <windows.h>
//#include <SDL3/SDL.h>
#include <string>

//variabili di supporto per identificazione
const char MISSILE_SYMBOL = '|';
const char NAVICELLA_SYMBOL = '^';
const char VUOTO_SYMBOL = '-';
const char NEMICO_SYMBOL = 'X';

const unsigned int RIGHE = 27;
const unsigned int COLONNE = 23;

typedef struct gameContext {
    uint8_t stato;
} GameContext_t;

bool versoDestra = true;

    //creazione della matrice

    char tabellone[RIGHE][COLONNE] = {
        {'-', '-', '-', '-', '-', '-', '-', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', 'O', '-', 'O', '-', 'O', '-', 'O', '-', 'O', '-', 'O', '-', 'O', '-', 'O', '-', 'O', '-', 'O', '-', 'O', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '^', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    };


GameContext_t gioco;

// Aiuta a convertire un numero int in puntatore char, utile per stampare EDL_DrawText()
void stampaInt(int valore, char* buffer, size_t dim) {
    std::string str = std::to_string(valore);
    strncpy(buffer, str.c_str(), dim);
    buffer[dim-1] = '\0'; // sicurezza alla fine di un char* il testo si chiude con un \0
}


void print(char t[][COLONNE]) {
    for (int r = 0; r < RIGHE; r++) {
        for (int c = 0; c < COLONNE; c++) {
            std::cout << t[r][c];
        }
        std::cout << std::endl;
    }
}

void passoSinistro(char t[RIGHE][COLONNE]) {
    int indiceNave;
    for (int c = 0; c < RIGHE; c++) {
        if (t[26][c] == '^') {
            indiceNave = c;
        }
    }
    if ( indiceNave != 0) {
        t[26][indiceNave] = '-';
        t[26][indiceNave - 1] = '^';
    }

}

void passoDestro(char t[RIGHE][COLONNE]) {
    int indiceNave;
    for (int c = 0; c < 23; c++) {
        if (t[26][c] == '^') {
            indiceNave = c;
        }
    }
    if ( indiceNave != 0) {
        t[26][indiceNave] = '-';
        t[26][indiceNave + 1] = '^';
    }
}

void passoDestroNemici(char t[RIGHE][COLONNE]) {
    if (versoDestra) {
        for (int i=0; i<RIGHE; i++) {
            if (t[i][COLONNE] == 'X') {}
        }
    }
}

bool generaSparo (char t[27][23]) {
    bool sparoPossibile = true;

    for (int r = 0; r < 27; r++) {
        for (int c = 0; c < 23; c++) {
            if (t[r][c] == MISSILE_SYMBOL) {
                sparoPossibile = false;
            }
        }
    }

    if (sparoPossibile) {
        for (int r = 0; r < 27; r++) {
            for (int c = 0; c < 23; c++) {
                if (t[r][c] == NAVICELLA_SYMBOL) {
                    t[r-1][c] = MISSILE_SYMBOL;
                }
            }
        }
    }
    return sparoPossibile;
}

void avanzaSparo(char t [27][23]) {
    for (int r = 0; r < 27; r++) {
        for (int c = 0; c < 23; c++) {
            if (t[r][c] == MISSILE_SYMBOL) {
                if (t[r-1][c] == NEMICO_SYMBOL or t[r-1][c] == 'Y' or t[r-1][c] == 'Z') {
                    t[r-1][c] = VUOTO_SYMBOL;
                    t[r][c] = VUOTO_SYMBOL;
                }else {
                    t[r-1][c] = MISSILE_SYMBOL;
                    t[r][c] = VUOTO_SYMBOL;
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    //inizializzazione
    EDL_Init();

    //robe per movimento
    int padding =20;
    int rotation=5;
    int xnave=100;
    int ynave=100;

    //creazione variabili per la gestione del tabellone
    char CTabellone[2];
    char* buffer;
    int yscritta = 520, xscritta = 500;

    //font e immagine nave
    Easy_Asset_t * font = EDL_LoadAsset("../assets/fonts/UbuntuMono-Regular.ttf");
    Easy_Asset_t *navicella = EDL_LoadAsset("../assets/sprites/navicella.PNG");
    Easy_Asset_t *nemico = EDL_LoadAsset("../assets/sprites/alieno.PNG");

    uint64_t tempoAvanzoSparo;

    //variabili per i while e la selezione
    int highliner = 0;
    bool running = true;
    bool playRunning = false;

    gioco.stato = 0;

    SDL_Event event;

    //per il calcolo degli FPS
    int fps=0; // valore perr frame per second
    char valore_FPS[64]; // variabile di test per stampare fps

    /*
    if(font == NULL ) {
        font = EDL_LoadAsset("../assets/fonts/UbuntuMono-Regular.ttf");
    }
    */
    SDL_Color white = {255, 255, 255};
    SDL_Color yellow = {255, 255, 0};


    //creazione degli stili
    TextStyle_t style;
    style.font = font;
    style.size = 50;
    style.foreground = white;
    EDL_SetTextStyle(&style);

    TextStyle_t stileGiallo = style;
    stileGiallo.foreground = yellow;
    stileGiallo.size = 70;
    EDL_SetTextStyle(&stileGiallo);

    TextStyle_t style_print;
    style_print.font = font;
    style_print.size = 25;
    style_print.foreground = white;
    EDL_SetTextStyle(&style_print);

    int tempoPassato=SDL_GetTicks();
    int tempoProiettile=SDL_GetTicks();
    //assegno il valore iniziale degli fps a 0
    stampaInt(0, valore_FPS, 64);


    tempoAvanzoSparo = SDL_GetTicks();

    for (int i = 0; i < RIGHE / 2; i = i + 5) {
        for (int j = 0; j < COLONNE; j = j + 5) {
            tabellone[i][j] = 'X';
        }
    }

    while (running) {
        // conteggia gli fps
        fps++;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
                gioco.stato = 5;
                }

            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                if (gioco.stato != 1) {
                    running = false;
                    gioco.stato = 5;
                }
                else {
                    gioco.stato = 2;
                }

                }

            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_S) {
                //aumento selezione

                highliner++;

                if (highliner > 2) {
                    highliner = 0;
                }

            }

            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_W) {
                //diminuzione selezione

                highliner--;

                if (highliner < 0) {
                    highliner = 2;
                }

            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_RETURN) {
                if (highliner == 0) {
                    gioco.stato = 1;
                }
                else if (highliner == 1) {
                    gioco.stato = 3;
                }
                else {
                    running = false;
                }

            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_RIGHT) {
                if ( gioco.stato == 0 ) {
                    xnave=xnave+padding;
                }
                else if ( gioco.stato == 1 ) {
                    passoDestro(tabellone);
                }

            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_LEFT) {
                if ( gioco.stato == 0 ) {
                    xnave=xnave-padding;
                }
                else if ( gioco.stato == 1 ) {
                    passoSinistro(tabellone);
                }

            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_UP) {
                ynave=ynave-padding;

            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_DOWN) {
                ynave=ynave+padding;

            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_Q) {
                rotation = ((rotation-padding) % 360);

            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_E) {
                rotation = ((rotation+padding) % 360);

            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_SPACE) {
                generaSparo(tabellone);
            }

        }
        if (gioco.stato == 1) {
            EDL_FrameClear();

            yscritta = 150;
            xscritta = 400;

            EDL_SetTextStyle(&style_print);

            for (int r = 0; r < 27; r++) {
                for (int c = 0; c < 23; c++) {

                    CTabellone[0] = tabellone[r][c];
                    CTabellone[1] = '\0';
                    if (CTabellone[0] == 'X') {
                        EDL_DrawAsset(xscritta,yscritta,nemico, 180, 1);
                    }
                    else if (CTabellone[0] == NAVICELLA_SYMBOL) {
                        EDL_DrawAsset(xscritta,yscritta,navicella, 0, 1);
                    }
                    else if (CTabellone[0] == MISSILE_SYMBOL) {
                        EDL_DrawText(xscritta,yscritta, "|");
                    }

                    xscritta = xscritta + 20;

                }

                yscritta = yscritta + 20;
                xscritta = 400;

            }
            if (SDL_GetTicks() - tempoAvanzoSparo >= 100) {
                avanzaSparo(tabellone);
                tempoAvanzoSparo = SDL_GetTicks();
            }

            EDL_FramePresent();
        }
        else if (gioco.stato == 0) {
            Easy_Asset_t *pathMenu = EDL_LoadAsset("../assets/sprites/mainMenu.png");

            EDL_FrameClear();
            style.size = 100;
            EDL_SetTextStyle(&style);
            EDL_DrawAsset(0, 0, pathMenu, 0, 12);
            EDL_DrawText(1080/1.8,50, "SPEIS INVEIDERS");
            if (highliner == 0) {
                EDL_SetTextStyle(&stileGiallo);
            }
            style.size = 50;
            EDL_DrawText(1080/1.2,325,"play");
            EDL_SetTextStyle(&style);
            if (highliner == 1) {
                EDL_SetTextStyle(&stileGiallo);
            }
            EDL_DrawText(640,430,"opzioni");
            EDL_SetTextStyle(&style);
            if (highliner == 2) {
                EDL_SetTextStyle(&stileGiallo);
            }
            EDL_DrawText(640,510,"esci");
            EDL_SetTextStyle(&style);

            // calcola la differenza di almeno 1 sec per resettare e valorizzare fps
            Uint64 diffTempo = (SDL_GetTicks()-tempoPassato);

            if (diffTempo >= 1000) {
                stampaInt(fps,valore_FPS,64);
                fps=0;
                tempoPassato=SDL_GetTicks();

            }
            EDL_DrawText(1,1,"FPS: ");
            EDL_DrawText(100,1,valore_FPS);
            EDL_DrawAsset(xnave, ynave, navicella, rotation,10);

            EDL_FramePresent();


        }
        else if (gioco.stato == 2) {
            EDL_FrameClear();
            Easy_Asset_t *pathPause = EDL_LoadAsset("../assets/sprites/pauseMenu.png");
            EDL_DrawAsset(1920/2, 1080/2, pathPause, 0, 7);
            EDL_DrawText(540,250,"PAUSA");
            if (highliner == 0) {
                EDL_SetTextStyle(&stileGiallo);
            }
            EDL_DrawText(540,350,"continua");
            EDL_SetTextStyle(&style);
            if (highliner == 1) {
                EDL_SetTextStyle(&stileGiallo);
            }
            EDL_DrawText(540,430,"impostazioni");
            EDL_SetTextStyle(&style);
            if (highliner == 2) {
                EDL_SetTextStyle(&stileGiallo);
            }
            EDL_DrawText(540,510,"esci");
            EDL_SetTextStyle(&style);

            EDL_FramePresent();

        }
        else if (gioco.stato == 3) {
            EDL_FrameClear();

            EDL_DrawText(540,250,"OPZIONI");
            if (highliner == 0) {
                EDL_SetTextStyle(&stileGiallo);
            }
            EDL_DrawText(540,350,"idk"); // da decidere
            EDL_SetTextStyle(&style);
            if (highliner == 1) {
                EDL_SetTextStyle(&stileGiallo);
            }
            EDL_DrawText(540,430,"bho"); // da decidere
            EDL_SetTextStyle(&style);
            if (highliner == 2) {
                EDL_SetTextStyle(&stileGiallo);
            }
            EDL_DrawText(540,510,"esci");
            EDL_SetTextStyle(&style);

            EDL_FramePresent();
        }
    }

    EDL_Destroy();
    return 0;
}


