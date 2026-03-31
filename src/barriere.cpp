
#include <iostream>

#include "../../include/easy_sdl.h"
#include "gameplay.h"
#include <windows.h>
#include <string>
#include "types.h"

BarrierContext_t barriere[23];

void inizializzaBarriere()
{
    barriere[1].colonna = 5;
    barriere[2].colonna = 11;
    barriere[3].colonna = 17;

    barriere[1].lives = 3;
    barriere[2].lives = barriere[1].lives;
    barriere[3].lives = barriere[1].lives;
}

void checkVitaBarriera() {
    if (barriere[1].lives<=0) {
        tabellone[24][barriere[1].colonna]=VUOTO_SYMBOL;
    }
    if (barriere[2].lives<=0) {
        tabellone[24][barriere[2].colonna]=VUOTO_SYMBOL;
    }
    if (barriere[3].lives<=0) {
        tabellone[24][barriere[3].colonna]=VUOTO_SYMBOL;
    }
}

void checkBarriera(int c) {
    switch (c) {
        case 5: barriere[1].lives--;
            break;
        case 11: barriere[2].lives--;
            break;
        case 17: barriere[3].lives--;
            break;
    }
    checkVitaBarriera();

}
