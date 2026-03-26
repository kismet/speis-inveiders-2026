//
// Created by Admin on 26/03/2026.
//
#include "gameplay.h"
#include <string>
#include <cstring>

// Aiuta a convertire un numero int in puntatore char, utile per stampare EDL_DrawText()
void stampaInt(int valore, char* buffer, int dim) {
    std::string str = std::to_string(valore);
    strncpy(buffer, str.c_str(), dim);
    buffer[dim-1] = '\0'; // sicurezza alla fine di un char* il testo si chiude con un \0
}