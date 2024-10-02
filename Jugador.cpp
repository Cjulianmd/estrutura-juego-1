#include "Jugador.h"
#include "Carta.h"
#include "Carta.cpp"
#include <iostream>
#include <map>
#include <algorithm>

Jugador::Jugador(std::string n) : nombre(n), activo(true), puntuacion(0) {}

void Jugador::agregarCarta(Carta c) {
    mano.push_back(c);
}

void Jugador::mostrarCartasPorColor() {
    std::map<std::string, int> conteoColores;
    for (const auto& carta : mano) {
        if (!carta.esComodin) {
            conteoColores[carta.color]++;
        }
    }

    std::cout << nombre << " tiene las siguientes cartas:" << std::endl;
    for (const auto& par : conteoColores) {
        std::string colorANSI = obtenerColorANSI(par.first);
        std::cout << colorANSI << par.first << ": " << par.second << " cartas" << restablecerColorANSI() << std::endl;
    }
}

void Jugador::contarPuntos() {
    std::map<std::string, int> conteoColores;
    for (const auto& carta : mano) {
        if (!carta.esComodin) {
            conteoColores[carta.color]++;
        }
    }

    // Ordenar los colores por cantidad de cartas en orden descendente
    std::vector<std::pair<std::string, int>> conteoVec(conteoColores.begin(), conteoColores.end());
    std::sort(conteoVec.begin(), conteoVec.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return a.second > b.second;
    });

    int puntosTotales = 0;
    std::cout << "\nPuntaje de " << nombre << ":" << std::endl;

    // Asignar puntos positivos a los tres primeros colores y negativos a los demás
    for (size_t i = 0; i < conteoVec.size(); i++) {
        std::string color = conteoVec[i].first;
        int cantidad = conteoVec[i].second;

        int puntos = 0;
        if (i < 3) { // Los tres colores con más cartas dan puntos positivos
            if (cantidad == 1) puntos = 1;
            else if (cantidad == 2) puntos = 3;
            else if (cantidad == 3) puntos = 6;
            else if (cantidad == 4) puntos = 10;
            else if (cantidad == 5) puntos = 15;
            else if (cantidad >= 6) puntos = 21;
        } else { // Los demás colores dan puntos negativos
            puntos = -cantidad;
        }

        std::cout << color << ": " << puntos << " puntos" << std::endl;
        puntosTotales += puntos;
    }

    puntuacion = puntosTotales;
    std::cout << "Puntuación total de " << nombre << ": " << puntuacion << " puntos\n";
}
