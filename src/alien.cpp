#include "gameplay.h"
#include "SDL3/SDL_timer.h"
#include "types.h"

extern bool versoDestra;

extern int startTime;
extern Player_t player;

bool destra() {

    bool toccaDestra = false;

    for ( int i = 0; i < RIGHE; i++ ) {
        if ( tabellone[i][COLONNE - 1] == NEMICO_SYMBOL ) {
            toccaDestra = true;
        }
    }

    return toccaDestra;
}

bool sinistra() {

    bool toccaSinistra = false;

    for ( int i = 0; i < RIGHE; i++ ) {
        if ( tabellone[i][0] == NEMICO_SYMBOL ) {
            toccaSinistra = true;
        }
    }

    return toccaSinistra;
}

bool basso() {

    bool toccaBasso = false;

    for ( int i = 0; i < COLONNE; i++ ) {
        if ( tabellone[RIGHE - 1][i] == NEMICO_SYMBOL ) {
            toccaBasso = true;
        }
    }

    return toccaBasso;
}

void spostaADestraNemici() {

    for ( int i = 0; i < RIGHE; i++ ) {
        for ( int j = COLONNE - 1; j > 0; j-- ) {
            if ( tabellone[i][j - 1] == NEMICO_SYMBOL && tabellone[i][j] == MISSILE_SYMBOL ) {
                tabellone[i][j - 1] = VUOTO_SYMBOL;
                tabellone[i][j] = VUOTO_SYMBOL;
                player.punteggio += 100;
            } else if ( tabellone[i][j - 1] == NEMICO_SYMBOL && tabellone[i][j] == VUOTO_SYMBOL ) {
                tabellone[i][j - 1] = VUOTO_SYMBOL;
                tabellone[i][j] = NEMICO_SYMBOL;
            }
        }
    }
}

void spostaASinistraNemici() {

    for ( int i = 0; i < RIGHE; i++ ) {
        for ( int j = 0; j < COLONNE - 1; j++ ) {
            if ( tabellone[i][j + 1] == NEMICO_SYMBOL && tabellone[i][j] == MISSILE_SYMBOL ) {
                tabellone[i][j + 1] = VUOTO_SYMBOL;
                tabellone[i][j] = VUOTO_SYMBOL;
                player.punteggio += 100;
            } else if ( tabellone[i][j + 1] == NEMICO_SYMBOL && tabellone[i][j] == VUOTO_SYMBOL ) {
                tabellone[i][j + 1] = VUOTO_SYMBOL;
                tabellone[i][j] = NEMICO_SYMBOL;
            }
        }
    }
}

void spostaInBassoNemico() {

    for ( int i = RIGHE - 1; i > 0; i--) {
        for ( int j = 0; j < COLONNE; j++ ) {
            if ( tabellone[i - 1][j] == NEMICO_SYMBOL ) {
                tabellone[i - 1][j] = VUOTO_SYMBOL;
                tabellone[i][j] = NEMICO_SYMBOL;
            }
        }
    }
}

void spostaNemici() {

    if (startTime+500 < SDL_GetTicks()) {
        startTime = SDL_GetTicks();
        if ( versoDestra  ) {
            if ( !destra() ) {
                spostaADestraNemici();
            } else {
                spostaInBassoNemico();
                versoDestra = false;
            }
        } else {
            if ( !sinistra() ) {
                spostaASinistraNemici();
            } else {
                spostaInBassoNemico();
                versoDestra = true;
            }
        }
    }
}

void muoviProiettiliAlieni() {

    for ( int i = RIGHE - 2 ; i >= 0; i-- ) {
        for ( int j = 0; j < COLONNE; j++ ) {
            if ( tabellone[i][j] == 4 ) {
                tabellone[i][j] = VUOTO_SYMBOL;
                if ( tabellone[i + 1][j] == 2 ) {
                    //TODO Qual'è il significato di ucciso, attualmente rimosso perchè gli aliene non sparano
                    //ucciso = 1;
                } else {
                    tabellone[i + 1][j] = 4;
                }
            }
        }
    }
}
