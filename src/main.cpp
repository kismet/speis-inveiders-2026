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
#include "types.h"

//variabili di supporto per identificazione
int missile_time = START_MISSILE_TIME;
int movement_time = START_MOVEMENT_TIME;
const double MISSILE_TIME_REDUCTION= 25.0;
const double MOVEMENT_TIME_REDUCTION= 375.0;
const char MISSILE_SYMBOL = '|';
const char NAVICELLA_SYMBOL = '^';
const char VUOTO_SYMBOL = '-';
const char NEMICO_SYMBOL = 'X';
const char BARRIER_SYMBOL = 'O';
const char MISSILE_NEMICO_SYMBOL = '1';
const char MISSILE_NEMICO_E_NEMICO_SYMBOL = 'Y';
const char BOMB_SYMBOL = 'B';
const unsigned int MISSILE_BASIC_SPEED = 75;

unsigned const int START_MISSILE_TIME = 100;
unsigned const int START_MOVEMENT_TIME = 1500;

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
        {'-', '-', '-', '-', '-', 'O', '-', '-', '-', '-', '-', 'O', '-', '-', '-', '-', '-', 'O', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '^', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    };
    char tabellone[RIGHE][COLONNE];

GameContext_t gioco;
Player_t player;
Index_t interfaccia;

void Load_Interface_Assets()
{
    interfaccia.regular = EDL_LoadAsset("assets/fonts/Quadrillion-Sb-It.otf");
    if(interfaccia.regular == NULL ) {
        interfaccia.regular = EDL_LoadAsset("../assets/fonts/Quadrillion-Sb-It.otf");
    }

    SDL_Color purple = { 255, 0, 255 };
    SDL_Color white = { 255, 255, 255 };

    interfaccia.titleStyle.font = interfaccia.regular;
    interfaccia.titleStyle.size = 25;
    interfaccia.titleStyle.foreground = purple;

    interfaccia.menuStyle = interfaccia.titleStyle;
    interfaccia.menuStyle.foreground = white;
}

int main(int argc, char* argv[]) {

    //inizializzazione
    EDL_Init();
    srand(time(0));
    gioco.level = 1;

    char stampaPunteggio[1000];
    char stampaLivello[1000];
    char stampaBombe[1000];

    //creazione variabili per la gestione del tabellone
    char CTabellone[2];
    char* buffer;
    int yscritta = 520, xscritta = 500;

    //font e immagine nave
    player.navicella  = EDL_LoadAsset("../assets/sprites/navicella.PNG");
    Easy_Asset_t *nemico = EDL_LoadAsset("../assets/sprites/alieno.PNG");
    Easy_Asset_t *sparoNemico = EDL_LoadAsset("../assets/sprites/proiettileAlieno.PNG");
    Easy_Asset_t *sparo = EDL_LoadAsset("../assets/sprites/proiettileNavicella.PNG");
    Easy_Asset_t *background = EDL_LoadAsset("../assets/schermate/sfondoInGame.png");
    Easy_Asset_t *cuore = EDL_LoadAsset("../assets/sprites/cuore.png");
    Easy_Asset_t *barriera = EDL_LoadAsset("../assets/sprites/scudoProiettili.png");
    Easy_Asset_t *bomba = EDL_LoadAsset("../assets/sprites/bomba.png");
    Load_Interface_Assets();
    uint64_t tempoAvanzoSparo;
    uint64_t tempoAvanzoSparoAlieno;
    uint64_t tempoSparoAlieno;
    uint64_t tempoBomba;

    //variabili per i while e la selezione
    int highliner = 0;
    bool running = true;

    gioco.stato = GAME_STATUS_MENU;

    SDL_Event event;

    //per il calcolo degli FPS
    int fps=0; // valore per frame per second
    char valore_FPS[64]; // variabile di test per stampare fps

    //assegno il valore iniziale degli fps a 0
    stampaInt(0, valore_FPS, 64);

    tempoAvanzoSparo = SDL_GetTicks();
    tempoAvanzoSparoAlieno = SDL_GetTicks();
    tempoSparoAlieno = SDL_GetTicks();
    tempoBomba = SDL_GetTicks();

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

            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_F) {
                generaBomba();
            }

        }
        if (gioco.stato == GAME_STATUS_PLAY) {
            EDL_FrameClear();
            int xCuori = 725;
            int xBomba = 100;
            EDL_DrawAsset(0, 0, background, 0, 0.71);

            spostaNemici();

            EDL_SetTextStyle(&interfaccia.menuStyle);
            stampaInt(gioco.level, stampaLivello, 64);
            stampaInt(player.punteggio, stampaPunteggio, 64);
            //TODO posizionati punteggi in attesa di font stile e posizione
            EDL_DrawText(425, 50, stampaPunteggio);
            EDL_DrawText(1000, 50, stampaLivello);
            for (int i = player.lives; i > 0; i--) {
                EDL_DrawAsset(xCuori, 42, cuore, 0, 0.3);
                xCuori += 40;
            }
            for (int i = player.bombs; i > 0; i--) {
                EDL_DrawAsset(xBomba, 500, bomba, 0, 0.3);
                xBomba += 40;
            }

            xCuori = 725;

            EDL_SetTextStyle(&interfaccia.titleStyle);
            EDL_DrawText(290,50, "POINTS:");
            EDL_DrawText(875,50, "LEVEL:");
            EDL_DrawText(600,50, "LIVES:");

            yscritta = 130*scalaCoordinate;
            xscritta = 465*scalaCoordinate;

            for (int r = 0; r < 27; r++) {
                for (int c = 0; c < 23; c++) {

                    CTabellone[0] = tabellone[r][c];
                    CTabellone[1] = '\0';
                    if (CTabellone[0] == NEMICO_SYMBOL) {
                        EDL_DrawAsset(xscritta,yscritta,nemico, 0, 0.16);
                    }
                    else if (CTabellone[0] == MISSILE_NEMICO_E_NEMICO_SYMBOL) {
                        EDL_DrawAsset(xscritta,yscritta,nemico, 0, 0.16);
                        EDL_DrawAsset(xscritta,yscritta,sparoNemico, 180, 0.1);
                    }
                    else if (CTabellone[0] == NAVICELLA_SYMBOL) {
                        EDL_DrawAsset(xscritta,yscritta,player.navicella, 0, 0.16);
                    }
                    else if (CTabellone[0] == MISSILE_SYMBOL) {
                        EDL_DrawAsset(xscritta,yscritta,sparo, 0, 0.1);
                    }
                    else if (CTabellone[0] == MISSILE_NEMICO_SYMBOL) {
                        EDL_DrawAsset(xscritta,yscritta,sparoNemico, 180, 0.1);

                    }else if (CTabellone[0] == BARRIER_SYMBOL) {
                        EDL_DrawAsset(xscritta,yscritta,barriera, 0, 0.16);
                    }else if (CTabellone[0] == BOMB_SYMBOL) {
                        EDL_DrawAsset(xscritta,yscritta,bomba, 0, 0.16);
                    }

                    xscritta = xscritta + 40*scalaCoordinate;

                }

                yscritta = yscritta + 33*scalaCoordinate;
                xscritta = 465*scalaCoordinate;

            }

            if (SDL_GetTicks() - tempoBomba >= 200) {
                spostaBomba();
                tempoBomba = SDL_GetTicks();
            }

            if (SDL_GetTicks() - tempoAvanzoSparo >= 100) {
                avanzaSparo();
                tempoAvanzoSparo = SDL_GetTicks();
            }

            if (SDL_GetTicks() - tempoAvanzoSparoAlieno >= missile_time) {
                levelUP();
                avanzoSparoAlieni();
                tempoAvanzoSparoAlieno = SDL_GetTicks();
            }

            if (SDL_GetTicks() - tempoSparoAlieno >= movement_time) {
                sparoAlieni();
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
        else if (gioco.stato == GAME_STATUS_CREDITS) {
            credits();
        }
    }

    EDL_Destroy();
    return 0;
}