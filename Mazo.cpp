#include "Mazo.h"
#include <algorithm>
#include <random>

Mazo::Mazo() {
    crearMazo();
    barajar();
}

void Mazo::barajar() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cartas.begin(), cartas.end(), g);
}

Carta Mazo::tomarCarta() {
    Carta cartaTomada = cartas.back();
    cartas.pop_back();
    return cartaTomada;
}

int Mazo::obtenerCantidadCartas() const {
    return cartas.size();
}

bool Mazo::estaVacio() const {
    return cartas.empty();
}

void Mazo::crearMazo() {
    std::vector<std::string> colores = {"Rojo", "Azul", "Verde", "Amarillo", "Naranja", "Violeta", "Gris"};
    for (const auto& color : colores) {
        for (int i = 0; i <= 9; i++) {
            cartas.push_back(Carta(color, 1));
        }
    }
    for (int i = 0; i <= 10; i++) {
        cartas.push_back(Carta("+2", 2));
    }
    for (int i = 0; i <= 3; i++) {
        cartas.push_back(Carta("Comodín", 0, true));
    }
}
