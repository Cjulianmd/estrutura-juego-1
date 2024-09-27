#ifndef CLASES_H
#define CLASES_H

#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <iostream>
#include <map>

struct Carta {
    std::string color;
    int valor;
    bool esUltimaRonda;
    bool esComodin;
};

struct Jugador {
    std::string nombre;
    std::vector<Carta> mano;
    bool activo;
    int puntuacion;
};

class Colorette {
private:
    std::vector<Carta> mazo;
    std::vector<std::vector<Carta>> filas;
    std::vector<Jugador> jugadores;
    int jugadorActual;
    bool ultimaRonda;
    int numPartidas;
    int partidaActual;

    void crearMazo();
    void barajarMazo();
    void prepararMazo();
    void inicializarFilas();
    void mostrarEstadoJuego();
    void tomarYPonerCarta();
    void tomarFila();
    int calcularPuntuacion(Jugador& jugador);
    int calcularPuntosPorColor(int numCartas);

public:
    Colorette(int numJugadores, int numPartidas);
    void jugarPartida();
    void mostrarResultadoFinal();
};

#endif
