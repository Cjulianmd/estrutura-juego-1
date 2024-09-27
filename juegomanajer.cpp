#include "juego.h"
//ingresar los datos basicos
void iniciarJuego() {
    int numJugadores;
    std::cout << "Ingrese el número de jugadores (3-5): ";
    std::cin >> numJugadores;
    // este dato sirve para si se desea jugar varias partidas seguido y que todas sumen puntos al final
    int numPartidas = 1;

    Colorette juego(numJugadores, numPartidas);

    for (int i = 0; i < numPartidas; i++) {
        juego.jugarPartida();
    }

    juego.mostrarResultadoFinal();
}
