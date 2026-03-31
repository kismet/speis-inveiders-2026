
#include <iostream>

#include "../../include/easy_sdl.h"
#include "gameplay.h"
#include <windows.h>
#include <string>
#include "types.h"

BarrierContext_t barr1;
BarrierContext_t barr2;
BarrierContext_t barr3;

void inizializzaBarriere()
{
    barr1.colonna = 5;
    barr2.colonna = 11;
    barr3.colonna = 17;
}
void checkVitaBarriera() {
    if (barr1.lives<=0) {
        tabellone[24][barr1.colonna]=VUOTO_SYMBOL;
    }
    if (barr2.lives<=0) {
        tabellone[24][barr2.colonna]=VUOTO_SYMBOL;
    }
    if (barr3.lives<=0) {
        tabellone[24][barr3.colonna]=VUOTO_SYMBOL;
    }
}
void checkBarriera(int c) {
    switch (c) {
        case 5: barr1.lives--;
            break;
        case 11: barr2.lives--;
            break;
        case 17: barr3.lives--;
            break;
    }
    checkVitaBarriera();

}
