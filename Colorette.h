#ifndef COLORETTE_H
#define COLORETTE_H

#include "Mazo.h"
#include "Jugador.h"
#include <vector>

class Colorette {
public:
    Colorette(int numJugadores);
    void jugarPartida();

private:
    Mazo mazo;
    std::vector<std::vector<Carta>> filas;
    std::vector<bool> filasDisponibles;
    std::vector<Jugador> jugadores;
    int jugadorActual;
    bool ultimaRonda;

    void inicializarFilas();
    void mostrarEstadoJuego();
    void tomarYPonerCarta();
    void tomarFila();
    void contarPuntosJugadores();
};

#endif
