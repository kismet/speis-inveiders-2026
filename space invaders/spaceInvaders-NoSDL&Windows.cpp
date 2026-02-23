#include <iostream>
#include <string>
#include <windows.h>
#include <cstdio>
#include <conio.h>

namespace spaceInvaders{
    typedef const unsigned int fisso;
    fisso righe = 20, colonne = 35;
    char matrice[righe][colonne];
    char giocatore = 'X';
    char nemico = 'O';
    char vuoto = '-';
    char proiettile = 'I';
    using std::cout;
}

using namespace spaceInvaders;

class Giocatore{
public:
    class Movement{
    public:
        char checkMovimento(int c){
            switch (c){
                case 'W': case 'w': return 'w';
                case 'A': case 'a': return 'a';
                case 'S': case 's': return 's';
                case 'D': case 'd': return 'd';
                default: return '0';
            }
        }

        void muovi(char movimento){
            for (int i = 0; i < righe; i++){
                for (int j = 0; j < colonne; j++){
                    if (matrice[i][j] == giocatore ){
                        int newI = i;
                        int newJ = j;

                        switch (movimento){
                            case 'w': newI = i - 1; break;
                            case 's': newI = i + 1; break;
                            case 'a': newJ = j - 1; break;
                            case 'd': newJ = j + 1; break;
                            default: return;
                        }

                        if (newI >= 0 && newI < righe &&
                            newJ >= 0 && newJ < colonne &&
                            matrice[newI][newJ] == vuoto)
                        {
                            matrice[i][j] = vuoto;
                            matrice[newI][newJ] = giocatore;
                        }
                        return;
                    }
                }
            }
        }
    };

    class Proj{
    public:
        bool checkSpara(int c){
            return (c == '=' || c == 'e' || c == 'E' || c == 'i' || c == 'I');
        }

        void spara(){
            for (int i = 0; i < righe; i++){
                for (int j = 0; j < colonne; j++){
                    if (matrice[i][j] == giocatore ){
                        if (i - 1 >= 0 && matrice[i - 1][j] == vuoto){
                            matrice[i - 1][j] = proiettile;
                        }
                    }
                }
            }        
        }

        void aggiornaProiettili(){
            for (int i = 0; i < righe; i++){
                for (int j = 0; j < colonne; j++){
                    if (matrice[i][j] == proiettile){
                        if (i - 1 >= 0){
                            if (matrice[i - 1][j] == vuoto){
                                matrice[i - 1][j] = proiettile;
                                matrice[i][j] = vuoto;
                            }
                            else if (matrice[i - 1][j] == nemico){
                                matrice[i - 1][j] = vuoto;
                                matrice[i][j] = vuoto;
                            }
                            else{
                                matrice[i][j] = vuoto;
                            }
                        }
                        else{
                            matrice[i][j] = vuoto;
                        }
                    }
                }
            }
        }
    };

    Movement movement;
    Proj proj;
};

int inizializzaMatrice(){
    int cont = 0;
    for (int i = 0; i < righe; i++){
        for (int j = 0; j < colonne; j++){
            matrice[i][j] = vuoto;
        }
    }
    matrice[righe - 1][colonne / 2] = giocatore;
    for (int i = 0; i < righe - 10; i += 2){
        for (int j = 0; j < colonne; j += 2){
            matrice[i][j] = nemico;
            cont++;
        }
    }
    return cont;
}

bool checkVittoria(){
    for (int i = 0; i < righe; i++){
        for (int j = 0; j < colonne; j++){
            if (matrice[i][j] == nemico){
                return false;
            }
        }
    }
    return true;
}

void stampa(){
    std::string frame;
    for (int i = 0; i < righe; i++){
        for (int j = 0; j < colonne; j++){
            frame += matrice[i][j];
            frame += ' ';
        }
        frame += '\n';
    }
    std::cout << frame << std::flush;
}

int main(){
    int numNemici = inizializzaMatrice();
    bool running = true;
    Giocatore p;
    int contaProj = 0;

    while (running){
        if (_kbhit()){
            int key = _getch();
            if (key == 27){
                running = false;
                continue;
            }
            if (key == 0 || key == 224){
                key = _getch();
            }

            char mov = p.movement.checkMovimento(key);
            p.movement.muovi(mov);

            if (p.proj.checkSpara(key)){
                p.proj.spara();
                contaProj++;
            }
        }

        p.proj.aggiornaProiettili();

        system("cls");
        stampa();
        Sleep(50);
        if (contaProj >= numNemici){
            if (checkVittoria()){
                system("cls");
                cout << "hai vinto!";
                return 0;
            }
        }
    }
}
