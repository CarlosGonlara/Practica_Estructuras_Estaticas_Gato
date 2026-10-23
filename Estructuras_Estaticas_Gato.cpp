#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// PROTOTIPO DE FUNCIONES
void inicializarTablero(char tablero[3][3]);
void mostrarTablero(char tablero[3][3]);
bool jugadaValida(char tablero[3][3], int fila, int col);
bool ganador(char tablero[3][3], char jugador);
bool empate(char tablero[3][3]);

// ESTA ES LA FUNCION MAIN, DONDE SE INICIA EL JUEGO
int main() {
    // DECLARACION DE VARIABLES
    char tablero[3][3];
    char jugador = 'X';
    int fila, col;
    bool juegoFinalizado = false;

    // CONFIGURACION DEL TABLERO
    inicializarTablero(tablero);
    mostrarTablero(tablero);

    // CICLO PRINCIPAL DEL JUEGO
    while (!juegoFinalizado) {

        // VALIDACION DE JUGADAS
        bool valido = false;
        while (!valido) {
            cout << "Turno de " << jugador << ". Fila y columna (1-3): ";
            string entrada;
            if (!getline(cin, entrada)) {
                cout << "\nEntrada finalizada. Juego terminado." << endl;
                return 0;
            }

            istringstream datos(entrada);
            char extra;
            if (!(datos >> fila >> col) || (datos >> extra)) {
                cout << "Entrada invalida." << endl;
            } else {
                if (fila < 1 || fila > 3 || col < 1 || col > 3) {
                    cout << "Fila y columna deben estar entre 1 y 3." << endl;
                } else {
                    fila--;
                    col--;
                    if (jugadaValida(tablero, fila, col)) {
                        valido = true;
                    } else {
                        cout << "Jugada invalida, intente de nuevo." << endl;
                    }
                }
            }
        }

        // REGISTRO DE JUGADAS
        tablero[fila][col] = jugador;
        mostrarTablero(tablero);

        if (ganador(tablero, jugador)){
            cout << "Gana " << jugador << endl;
            juegoFinalizado = true;
        } else if (empate(tablero)) {
            cout << "Empate." << endl;
            juegoFinalizado = true;
            
        // CAMBIO DE TURNO
        } else {
            if (jugador == 'X') jugador = 'O';
            else jugador = 'X';
        } 
    }    // TERMINA WHILE PRINCIPAL


    return 0;
}

// DEFINICION DE FUNCIONES

    // CONFIGURACION DEL TABLERO, PARA ESPACIOS VACIOS
    void inicializarTablero(char tablero[3][3]) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                tablero[i][j] = ' ';
            }
        }
    }

    // MUESTRA EL TABLERO EN PANTALLA
    void mostrarTablero(char tablero[3][3]) {
        cout << "  1 2 3" << endl;
        for (int i = 0; i < 3; i++) {
            cout << i + 1 << " ";
            for (int j = 0; j < 3; j++) {
                cout << tablero[i][j];
                if (j < 2) cout << "|";
            }
            cout << endl;
            if (i < 2) cout << "  -|-|-" << endl;
        }
    }

    // VALIDA SI LA JUGADA ES CORRECTA, SI ESTA DENTRO DEL TABLERO Y SI EL ESPACIO ESTA VACIO
    bool jugadaValida(char tablero[3][3], int fila, int col) {
    return fila >= 0 && fila < 3 &&
           col >= 0 && col < 3 &&
           tablero[fila][col] == ' ';
    }

    // VERIFICA SI HAY UN GANADOR
    bool ganador(char tablero[3][3], char jugador) {
        // VERIFICA SI HAY UN GANADOR EN FILAS
        for (int i = 0; i < 3; i++) {
            if (tablero[i][0] == jugador &&
                tablero[i][1] == jugador &&
                tablero[i][2] == jugador) return true;

            // VERIFICA SI HAY UN GANADOR EN COLUMNAS
            if (tablero[0][i] == jugador &&
                tablero[1][i] == jugador &&
                tablero[2][i] == jugador) return true;
        }
        // VERIFICA SI HAY UN GANADOR EN DIAGONAL
        return (tablero[0][0] == jugador &&
                tablero[1][1] == jugador &&
                tablero[2][2] == jugador) ||
            (tablero[0][2] == jugador &&
                tablero[1][1] == jugador &&
                tablero[2][0] == jugador);
    }

    // VERIFICA SI HAY UN EMPATE
    bool empate(char tablero[3][3]) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (tablero[i][j] == ' ') return false;
            }
        }
        return true; // SI NO HAY ESPACIOS VACIOS, HAY EMPATE 
    }