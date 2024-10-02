#ifndef MAZO_H
#define MAZO_H

#include "Carta.h"
#include <vector>

class Mazo {
public:
    Mazo();
    void barajar();
    Carta tomarCarta();
    int obtenerCantidadCartas() const;
    bool estaVacio() const;

private:
    std::vector<Carta> cartas;
    void crearMazo();
};

#endif
