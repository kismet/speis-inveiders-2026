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

#include <iostream>

#include "../../include/easy_sdl.h"
#include "gameplay.h"
#include <windows.h>

#include <string>
#include "gameplay.h"
#include "types.h"




//variabili di supporto per identificazione
const char MISSILE_SYMBOL = '|';
const char NAVICELLA_SYMBOL = '^';
const char VUOTO_SYMBOL = '-';
const char NEMICO_SYMBOL = 'X';
const char BARRIER_SYMBOL = 'O';
const char MISSILE_NEMICO_SYMBOL = '1';
const unsigned int MISSILE_BASIC_SPEED = 75;

const unsigned int RIGHE = 27;
const unsigned int COLONNE = 23;
const float scalaCoordinate=0.71;


bool versoDestra = true;

int startTime = SDL_GetTicks();

    //creazione della matrice
    const char TABELLONE[RIGHE][COLONNE] = {
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
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', 'O', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '^', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    };
    char tabellone[RIGHE][COLONNE];


GameContext_t gioco;
Player_t player;

void passoDestroNemici() {
    if (versoDestra) {
        for (int i=0; i<RIGHE; i++) {
            if (tabellone[i][COLONNE] == 'X') {}
        }
    }
}

int main(int argc, char* argv[]) {
    //inizializzazione
    EDL_Init();
    inizializzaPartita (tabellone, TABELLONE);

    char stampaPunteggio[1000];


    //creazione variabili per la gestione del tabellone
    char CTabellone[2];
    char* buffer;
    int yscritta = 520, xscritta = 500;

    //font e immagine nave
    Easy_Asset_t * font = EDL_LoadAsset("../assets/fonts/UbuntuMono-Regular.ttf");
    player.navicella  = EDL_LoadAsset("../assets/sprites/navicella.PNG");
    Easy_Asset_t *nemico = EDL_LoadAsset("../assets/sprites/alieno.PNG");
    Easy_Asset_t *background = EDL_LoadAsset("../assets/schermate/sfondoInGame.png");
    uint64_t tempoAvanzoSparo;
    uint64_t tempoSparoAlieno;

    //variabili per i while e la selezione
    int highliner = 0;
    bool running = true;
    bool playRunning = false;

    gioco.stato = GAME_STATUS_MENU;

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
    tempoSparoAlieno = SDL_GetTicks();

    while (running) {
        // conteggia gli fps
        fps++;


        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
                gioco.stato = GAME_STATUS_QUIT;
            }
            if (gioco.stato == GAME_STATUS_PAUSE && event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_RETURN) {
                if (highliner == 0) {
                    gioco.stato = GAME_STATUS_PLAY;
                }else if (highliner == 1) {
                    running = false;
                }
            }

            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                if (gioco.stato != GAME_STATUS_PLAY) {
                    running = false;
                    gioco.stato = GAME_STATUS_QUIT;
                }
                else {
                    gioco.stato = GAME_STATUS_PAUSE;
                }

                }

            if ((event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_S)||(event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_DOWN))  {
                //aumento selezione

                highliner++;

                if (highliner > 2) {
                    highliner = 0;
                }

            }

            if ((event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_W)||(event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_UP)) {
                //diminuzione selezione

                highliner--;

                if (highliner < 0) {
                    highliner = 2;
                }

            }
           if ((event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_RIGHT)||(event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_D)) {

                if ( gioco.stato == 1 ) {
                    passoDestro();
                }

            }
            if ((event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_LEFT)||(event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_A)) {
                if ( gioco.stato == 1 ) {
                    passoSinistro();
                }

            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_SPACE) {
                generaSparo();
            }

        }
        if (gioco.stato == 1) {
            EDL_FrameClear();


            EDL_DrawAsset(0, 0, background, 0, 0.71);

            spostaNemici();

            stampaInt(player.punteggio, stampaPunteggio, 64);
            //TODO posizionati punteggi in attesa di font stile e posizione
            EDL_DrawText(550, 50, stampaPunteggio);

            yscritta = 130*scalaCoordinate;
            xscritta = 465*scalaCoordinate;

            EDL_SetTextStyle(&style_print);

            for (int r = 0; r < 27; r++) {
                for (int c = 0; c < 23; c++) {

                    CTabellone[0] = tabellone[r][c];
                    CTabellone[1] = '\0';
                    if (CTabellone[0] == NEMICO_SYMBOL) {
                        EDL_DrawAsset(xscritta,yscritta,nemico, 0, 0.16);
                    }
                    else if (CTabellone[0] == NAVICELLA_SYMBOL) {
                        EDL_DrawAsset(xscritta,yscritta,player.navicella, 0, 0.16);
                    }
                    else if (CTabellone[0] == MISSILE_SYMBOL) {
                        EDL_DrawText(xscritta,yscritta, "|");
                    }
                    else if (CTabellone[0] == MISSILE_NEMICO_SYMBOL) {
                        EDL_DrawText(xscritta,yscritta, "1");
                    }
                    else if (CTabellone[0] == BARRIER_SYMBOL) {
                        EDL_DrawText(xscritta,yscritta, "O");
                    }

                    xscritta = xscritta + 40*scalaCoordinate;

                }

                yscritta = yscritta + 33*scalaCoordinate;
                xscritta = 465*scalaCoordinate;

            }
            if (SDL_GetTicks() - tempoAvanzoSparo >= 100) {
                avanzaSparo();
                //avanzoSparoAlieni(tabellone);
                tempoAvanzoSparo = SDL_GetTicks();
            }

            if (SDL_GetTicks() - tempoSparoAlieno >= 1500) {
                //sparoAlieni(tabellone);
                tempoSparoAlieno = SDL_GetTicks();
            }

            EDL_FramePresent();
        }
        else if (gioco.stato == GAME_STATUS_MENU) {
            main_menu();
        }
        else if (gioco.stato == GAME_STATUS_PAUSE) {
            //Easy_Asset_t *pathPause = EDL_LoadAsset("../assets/schermate/schermoPausa.png");
            //EDL_DrawAsset(0, 0, pathPause, 0, 1);
            pause_menu();
        }
        else if (gioco.stato == GAME_STATUS_QUIT) {
            running = false;
        }
    }

    EDL_Destroy();
    return 0;
}