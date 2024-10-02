#include "Colorette.h"
#include <iostream>

int main() {
    int numJugadores;
    std::cout << "Ingrese el número de jugadores (3-5): ";
    std::cin >> numJugadores;

    Colorette juego(numJugadores);
    juego.jugarPartida();

    return 0;
}