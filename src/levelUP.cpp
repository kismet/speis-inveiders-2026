//
// Created by Admin on 29/03/2026.
//
#include "gameplay.h"

bool nemiciVivi()
{
    for (int r = 0; r < RIGHE-1; r++)
    {
        for (int c = 0; c < COLONNE; c++)
        {
            if (tabellone[r][c] == NEMICO_SYMBOL)
            {
                return false;
            }
        }
    }
    return true;
}

void levelUP()
{
    if (!nemiciVivi())
    {
        //TODO stampa scritte per accedere al livello successivo
    }
}