//
// Created by Admin on 26/03/2026.
//

#ifndef SPEIS_INVEIDERS_GAMEPLAY_H
#define SPEIS_INVEIDERS_GAMEPLAY_H

extern const char MISSILE_SYMBOL;
extern const char NAVICELLA_SYMBOL;
extern const char VUOTO_SYMBOL;
extern const char NEMICO_SYMBOL;
extern const unsigned int RIGHE;
extern const unsigned int COLONNE;
extern char tabellone[27][23];

void stampaInt(int valore, char* buffer, int dim);

void printGame();

void main_menu();

void passoSinistro();

void passoDestro();

void passoDestroNemici();

bool generaSparo();

void avanzaSparo();

#endif //SPEIS_INVEIDERS_GAMEPLAY_H