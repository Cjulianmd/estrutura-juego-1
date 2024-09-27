#include "juego.h"

void iniciarJuego() {
    int numJugadores;
    std::cout << "Ingrese el número de jugadores (3-5): ";
    std::cin >> numJugadores;
    int numPartidas = 1;

    Colorette juego(numJugadores, numPartidas);

    for (int i = 0; i < numPartidas; i++) {
        juego.jugarPartida();
    }

    juego.mostrarResultadoFinal();
}
