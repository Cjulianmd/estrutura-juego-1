#ifndef JUGADOR_H
#define JUGADOR_H

#include "Carta.h"
#include <vector>
#include <string>
#include <map>

class Jugador {
public:
    std::string nombre;
    std::vector<Carta> mano;
    bool activo;
    int puntuacion;

    Jugador(std::string n);
    void agregarCarta(Carta c);
    void mostrarCartasPorColor();
    void contarPuntos();
};

#endif
