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

#include "../../include/easy_sdl.h"
#include <iostream>
#include <ctime>

using namespace std;

typedef const uint8_t cuint8_t;

// Parametri globali matrice e movimento alieni
cuint8_t righe = 27;
cuint8_t colonne = 23;
cuint8_t cella = 32;

bool versoDestra = true;

struct GameContext {
    uint8_t state;
    /*
    State:
    0 = menuMode
    1 = gameMode
    2 = pause
    3 = options
    4 = exit
    5 = gameOver
    */
} gameContext_t;

// Giocatore

void spostaPlayerADestra( int campo[righe][colonne] ) {

    bool spostato = false;

    // Scorro la riga dove è posizionato il giocatore (sempre riga 25) e sposto di uno a destra
    for ( int i = colonne - 1; i >= 0 && !spostato; i-- ) {
        if ( campo[24][i] == 2 && i < ( colonne - 1)) {
            campo[24][i] = 0;
            campo[24][i + 1] = 2;

            spostato = true;
        }
    }
}

void spostaPlayerASinistra( int campo[righe][colonne] ) {

    bool spostato = false;

    // Scorro la riga dove è posizionato il giocatore (sempre riga 25) e sposto di uno a sinistra
    for ( int i = 0; i < colonne && !spostato; i++ ) {
        if ( campo[24][i] == 2 && i > 0 ) {
            campo[24][i] = 0;
            campo[24][i - 1] = 2;

            spostato = true;
        }
    }
}

// Controllo bordi

bool destra( int campo[righe][colonne] ) {

    bool toccaDestra = false;

    for ( int i = 0; i < righe; i++ ) {
        if ( campo[i][colonne - 1] == 1 ) {
            toccaDestra = true;
        }
    }

    return toccaDestra;
}

bool sinistra( int campo[righe][colonne] ) {

    bool toccaSinistra = false;

    for ( int i = 0; i < righe; i++ ) {
        if ( campo[i][0] == 1 ) {
            toccaSinistra = true;
        }
    }

    return toccaSinistra;
}

bool basso( int campo[righe][colonne] ) {

    bool toccaBasso = false;

    for ( int i = 0; i < colonne; i++ ) {
        if ( campo[righe - 1][i] == 1 ) {
            toccaBasso = true;
        }
    }

    return toccaBasso;
}

// Movimento alieni

void spostaADestraNemici( int campo[righe][colonne] ) {

    for ( int i = 0; i < righe; i++ ) {
        for ( int j = colonne - 1; j > 0; j-- ) {
            if ( campo[i][j - 1] == 1 ) {
                campo[i][j - 1] = 0;
                campo[i][j] = 1;
            }
        }
    }
}

void spostaASinistraNemici( int campo[righe][colonne] ) {

    for ( int i = 0; i < righe; i++ ) {
        for ( int j = 0; j < colonne - 1; j++ ) {
            if ( campo[i][j + 1] == 1 ) {
                campo[i][j + 1] = 0;
                campo[i][j] = 1;
            }
        }
    }
}

void spostaInBassoNemico( int campo[righe][colonne] ) {

    for ( int i = righe - 1; i > 0; i--) {
        for ( int j = 0; j < colonne; j++ ) {
            if ( campo[i - 1][j] == 1 ) {
                campo[i - 1][j] = 0;
                campo[i][j] = 1;
            }
        }
    }
}

void spostaNemici( int campo[righe][colonne] ) {

    if ( versoDestra  ) {
        if ( !destra( campo ) ) {
            spostaADestraNemici( campo );
        } else {
            spostaInBassoNemico( campo );
            versoDestra = false;
        }
    } else {
        if ( !sinistra( campo ) ) {
            spostaASinistraNemici( campo );
        } else {
            spostaInBassoNemico( campo );
            versoDestra = true;
        }
    }
}

// Proiettili giocatore
void muoviProiettiliPlayer( int campo[righe][colonne] ) {

    for ( int i = 1; i < righe; i++ ) {
        for ( int j = 0; j < colonne; j++ ) {
            if ( campo[i][j] == 3 ) {
                campo[i][j] = 0;
                if ( campo[i - 1][j] == 1 ) {
                    campo[i - 1][j] = 0;
                } else if ( ( i - 1 ) >= 0 ) {
                    campo[i - 1][j] = 3;
                }
            }
        }
    }
}

// Proiettili alieni
void muoviProiettiliAlieni( int campo[righe][colonne], int &ucciso) {

    for ( int i = righe - 2 ; i >= 0; i-- ) {
        for ( int j = 0; j < colonne; j++ ) {
            if ( campo[i][j] == 4 ) {
                campo[i][j] = 0;
                if ( campo[i + 1][j] == 2 ) {
                    ucciso = 1;
                } else {
                    campo[i + 1][j] = 4;
                }
            }
        }
    }
}

// Stampa Menu
void stampaMenu( int voce, TextStyle_t &principale, TextStyle_t &evidenziato ) {

    // Menu
    EDL_SetTextStyle( &principale );
    EDL_DrawText( 400, 50, "SPEIS INVADERS" );

    if ( voce == 0 ) {
        EDL_SetTextStyle( &evidenziato );
        EDL_DrawText( 500, 250, "INIZIA" );
    } else {
        EDL_SetTextStyle( &principale );
        EDL_DrawText( 500, 250, "INIZIA" );
    }

    if ( voce == 1 ) {
        EDL_SetTextStyle( &evidenziato );
        EDL_DrawText( 500, 350, "OPZIONI" );
    } else {
        EDL_SetTextStyle( &principale );
        EDL_DrawText( 500, 350, "OPZIONI" );
    }

    if ( voce == 2 ) {
        EDL_SetTextStyle( &evidenziato );
        EDL_DrawText( 500, 450, "ESCI" );
    } else {
        EDL_SetTextStyle( &principale );
        EDL_DrawText( 500, 450, "ESCI" );
    }
}

// Sparo Navicella
void sparoNavicella( bool sparo, int campoDaGioco[righe][colonne] ) {
    // Sparo Navicella
    if ( sparo ) {
        bool impostato = false;

        for ( int i = 0; i < colonne && !impostato; i++ ) {
            if( campoDaGioco[24][i] == 2 ) {
                campoDaGioco[23][i] = 3;

                impostato = true;
            }
        }

        // Resetto sparo
        sparo = false;
    }
}

// sparo alieni
void sparoAlieni(uint64_t tempoCorrente, uint64_t ultimoSparo, int campoDaGioco[righe][colonne]) {
    if ( tempoCorrente - ultimoSparo > 2000 ) {
        int colonneRand = rand() % colonne;

        bool impostato = false;

        for ( int i = righe - 1; i >= 0 && !impostato; i-- ) {
            if ( campoDaGioco[i][colonneRand] == 1 && i < righe - 1 ) {
                campoDaGioco[i + 1][colonneRand] = 4;

                impostato = true;
            }
        }

        ultimoSparo = tempoCorrente;
    }
}
void spostoNemici(uint64_t tempoCorrente, int ucciso, int campoDaGioco[righe][colonne], uint64_t ultimoMovimento){
    if ( tempoCorrente - ultimoMovimento > 700 ) {
        spostaNemici( campoDaGioco );

        if ( basso( campoDaGioco ) ) {
            ucciso = 1;
        }
        ultimoMovimento = tempoCorrente;
    }

}

void spostoPlayer(bool destraPlayer, bool sinistraPlayer, int campoDaGioco[righe][colonne]) {
    if ( destraPlayer ) {
        spostaPlayerADestra( campoDaGioco );
    } else if ( sinistraPlayer ) {
        spostaPlayerASinistra( campoDaGioco );
    }
}

int main(int argc, char* argv[]) {

    EDL_Init();

    // Seed random
    srand(time(NULL));

    // Carico Sprite e Font
    // Navicella
    Easy_Asset_t * navicella = EDL_LoadAsset( "Assets/Sprite/friendlyShip.PNG" );
    if ( !navicella ) {
        navicella = EDL_LoadAsset( "../Assets/Sprite/friendlyShip.PNG" );
    }

    // Alieni
    Easy_Asset_t * alieni = EDL_LoadAsset( "Assets/Sprite/alien1.PNG" );
    if ( !alieni ) {
        alieni = EDL_LoadAsset( "../Assets/Sprite/alien1.PNG" );
    }

    // Proiettili navicella
    Easy_Asset_t * proiettiliNavicella = EDL_LoadAsset( "Assets/Sprite/friendlyProj.PNG" );
    if ( !proiettiliNavicella ) {
        proiettiliNavicella = EDL_LoadAsset( "../Assets/Sprite/friendlyProj.PNG" );
    }

    // Proiettili alieni
    Easy_Asset_t * proiettiliAlieni = EDL_LoadAsset( "Assets/Sprite/alienProj.PNG" );
    if ( !proiettiliAlieni ) {
        proiettiliAlieni = EDL_LoadAsset( "../Assets/Sprite/alienProj.PNG" );
    }

    // Font normale
    Easy_Asset_t * fontRegular = EDL_LoadAsset( "Assets/Fonts/UbuntuMono-Regular.ttf" );
    if( fontRegular == NULL ){
        fontRegular = EDL_LoadAsset( "../Assets/Fonts/UbuntuMono-Regular.ttf" );
    }

    // Grassetto
    Easy_Asset_t * fontGrassetto = EDL_LoadAsset( "Assets/Fonts/UbuntuMono-Bold.ttf" );
    if( fontGrassetto == NULL ){
        fontGrassetto = EDL_LoadAsset( "../Assets/Fonts/UbuntuMono-Bold.ttf" );
    }

    // Corsivo
    Easy_Asset_t * fontCorsivo = EDL_LoadAsset( "Assets/Fonts/UbuntuMono-Italic.ttf" );
    if( fontCorsivo == NULL ){
        fontCorsivo = EDL_LoadAsset( "../Assets/Fonts/UbuntuMono-Italic.ttf" );
    }

    // Corsivo grassetto
    Easy_Asset_t * fontCorsivoGrassetto = EDL_LoadAsset( "Assets/Fonts/UbuntuMono-BoldItalic.ttf" );
    if( fontCorsivoGrassetto == NULL ) {
        fontCorsivoGrassetto = EDL_LoadAsset( "../Assets/Fonts/UbuntuMono-BoldItalic.ttf" );
    }

    // Controllo che i font siano stati caricati
    if (!fontRegular || !fontGrassetto || !fontCorsivo || !fontCorsivoGrassetto) {
        cout << "Errore caricamento font!" << endl;
        cout << "fontRegular: " << fontRegular << endl;
        cout << "fontGrassetto: " << fontGrassetto << endl;
        cout << "fontCorsivo: " << fontCorsivo << endl;
        cout << "fontCorsivoGrassetto: " << fontCorsivoGrassetto << endl;
        return 1;
    }

    // Colori

    SDL_Color bianco = { 255, 255, 255 };
    SDL_Color nero = { 0, 0, 0 };

    SDL_Color rosso = { 255, 0, 0 };
    SDL_Color verde = { 0, 255, 0 };
    SDL_Color blu = { 0, 0, 255 };

    SDL_Color giallo = { 255, 255, 0 };
    SDL_Color ciano = { 0, 255, 255 };
    SDL_Color magenta = { 255, 0, 255 };

    SDL_Color arancione = { 255, 165, 0 };
    SDL_Color viola = { 128, 0, 128 };
    SDL_Color rosa = { 255, 192, 203 };

    SDL_Color grigio = { 128, 128, 128 };
    SDL_Color grigio_scuro = { 64, 64, 64 };
    SDL_Color grigio_chiaro = { 192, 192, 192 };

    SDL_Color marrone = { 139, 69, 19 };
    SDL_Color oro = { 255, 215, 0 };
    SDL_Color argento = { 192, 192, 192 };

    SDL_Color turchese = { 64, 224, 208 };
    SDL_Color indaco = { 75, 0, 130 };
    SDL_Color lime = { 191, 255, 0 };

    // Set stili
    TextStyle_t principale;
    principale.font = fontRegular;
    principale.size = 50;
    principale.foreground = bianco;
    EDL_SetTextStyle(&principale);

    TextStyle_t evidenziato = principale;
    evidenziato.foreground = lime;
    evidenziato.size = 70;
    EDL_SetTextStyle(&evidenziato);

    TextStyle_t gameOver;
    gameOver.font = fontGrassetto;
    gameOver.size = 100;
    gameOver.foreground = rosso;
    EDL_SetTextStyle( &gameOver );

    TextStyle_t fps;
    fps.font = fontRegular;
    fps.size = 30;
    fps.foreground = bianco;
    EDL_SetTextStyle( &fps );

    /*
    Campo da gioco con le dimensioni stabilite
    0 = vuoto
    1 = alieno
    2 = player
    3 = proiettile player
    4 = proiettile alieno

    Numero di alieni 12x5
    */

    int campoDaGioco[righe][colonne] = {
        {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    // Posiziono il giocatore
    campoDaGioco[24][11] = 2;

    bool running = true;

    int voce = 0;

    bool destraPlayer = false;
    bool sinistraPlayer = false;
    bool sparo = false;

    int ucciso = 0;     // 0 = vivo, 1 = morto

    Uint64 ultimoMovimento = 0;
    Uint64 ultimoSparo = 0;

    int contatoreFPS = 0;
    int attualiFPS = 0;
    Uint64 tempoPassatoFPS = SDL_GetTicks();

    SDL_Event event;

    while ( running ) {

        // Resetto destra e sinistra
        destraPlayer = false;
        sinistraPlayer = false;

        // Controllo eventi
        while ( SDL_PollEvent( &event )) {
            /*
            TODO
            if ( event.type == SDL_EVENT_KEY_DOWN ) {
                if ( event.key.scancode == SDL_SCANCODE_W || event.key.scancode == SDL_SCANCODE_UP ) {
                    gameContext_t.state =
                }// w, s e up e down = movimento voci menù
                if (event.key.scancode==SDL_SCANCODE_...); // enter = entrare voce selezionata
                if (event.key.scancode==SDL_SCANCODE_...); // esc = exit
                if (event.key.scancode==SDL_SCANCODE_...); // in game mov = ad e frecce
                if (event.key.scancode==SDL_SCANCODE_...); // p = pausa, movimento tipo menù.
                // if (event.key.scancode==SDL_SCANCODE_... && if in pausa); r = return, da implementare.
            }
            */
        }

        // Prendo il tempo
        uint64_t tempoCorrente = SDL_GetTicks();

        EDL_FrameClear();

        switch ( gameContext_t.state ) {
            case 0:
                stampaMenu( voce, principale, evidenziato);
                break;
            case 1:

                // Sposto
                sparoNavicella( sparo, campoDaGioco );
                sparoAlieni(tempoCorrente, ultimoSparo, campoDaGioco);
                spostoNemici(tempoCorrente, ucciso, campoDaGioco, ultimoMovimento);
                spostoPlayer(destraPlayer, sinistraPlayer, campoDaGioco);
                muoviProiettiliPlayer( campoDaGioco );
                muoviProiettiliAlieni( campoDaGioco, ucciso );
                break;
            case 2: //pause


                // Stampo
                for ( int i = 0; i < righe; i++ ) {
                    for ( int j = 0; j < colonne; j++ ) {
                        int x = j * cella;
                        int y = i * cella;

                        if ( campoDaGioco[i][j] == 1 ) {
                            EDL_DrawAsset( x, y, alieni, 0, 0.01 );
                        } else if ( campoDaGioco[i][j] == 2 ) {
                            EDL_DrawAsset( x, y, navicella , 0, 0.01 );
                        } else if ( campoDaGioco[i][j] == 3 ) {
                            EDL_DrawAsset( x, y, proiettiliNavicella );
                        } else if ( campoDaGioco[i][j] == 4 ) {
                            EDL_DrawAsset( x, y, proiettiliAlieni );
                        }
                    }
                }
                break;
            default:
                break;
        }

        // Calcolo FPS
        contatoreFPS++;
        Uint64 tempoAttualeFPS = SDL_GetTicks();

        if ( tempoAttualeFPS - tempoPassatoFPS >= 1000 ) {
            attualiFPS = contatoreFPS;
            contatoreFPS = 0;
            tempoPassatoFPS = tempoAttualeFPS;
        }

        // Disegno FPS
        EDL_SetTextStyle( &fps );

        char fpsText[32];
        snprintf(fpsText, sizeof(fpsText), "FPS: %d", attualiFPS);

        EDL_DrawText(1150, 10, fpsText);

        if ( ucciso ) {
            EDL_SetTextStyle( &gameOver );
            EDL_DrawText( 400,200 ,"GAME OVER" );

            // Fermo il gioco
            running = false;
        }

        EDL_FramePresent();

        // Blocco a circa 60 FPS
        SDL_Delay( 16 );
    }

    EDL_Destroy();
    return 0;
}