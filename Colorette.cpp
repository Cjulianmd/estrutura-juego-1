#include "Colorette.h"
#include "Jugador.h"
#include "Carta.h"
#include <iostream>
#include <algorithm>
#include <random>

Colorette::Colorette(int numJugadores) : jugadorActual(0), ultimaRonda(false) {
    for (int i = 0; i < numJugadores; i++) {
        std::cout << "Ingrese el nombre del Jugador " << i + 1 << ": ";
        std::string nombre;
        std::cin >> nombre;
        jugadores.emplace_back(nombre);
    }
    inicializarFilas();
}

void Colorette::inicializarFilas() {
    filas.clear();
    filasDisponibles.clear();
    for (size_t i = 0; i < jugadores.size(); i++) {
        filas.push_back({});
        filasDisponibles.push_back(true); // Todas las filas comienzan disponibles
    }
}

void Colorette::mostrarEstadoJuego() {
    std::cout << "\nEstado actual del juego:" << std::endl;
    for (size_t i = 0; i < filas.size(); i++) {
        std::cout << "Fila " << i + 1 << " (" << (filasDisponibles[i] ? "Disponible" : "No disponible") << "): ";
        for (const auto& carta : filas[i]) {
            std::cout << carta.color << " ";
        }
        std::cout << std::endl;
    }
}

void Colorette::tomarYPonerCarta() {
    if (mazo.estaVacio()) {
        std::cout << "El mazo está vacío. No se pueden tomar más cartas." << std::endl;
        return;
    }

    if (mazo.obtenerCantidadCartas() == 14 && !ultimaRonda) {
        std::cout << "¡Se ha activado la carta de Última Ronda! Esta será la última ronda del juego." << std::endl;
        ultimaRonda = true;
    }

    Carta cartaTomada = mazo.tomarCarta();
    std::cout << jugadores[jugadorActual].nombre << " ha tomado una carta " << cartaTomada.color << std::endl;

    mostrarEstadoJuego();
    int filaElegida;
    do {
        std::cout << "Elige una fila para poner la carta (1-" << filas.size() << "): ";
        std::cin >> filaElegida;
        filaElegida--;
    } while (filaElegida < 0 || filaElegida >= filas.size() || filas[filaElegida].size() >= 3 || !filasDisponibles[filaElegida]);

    filas[filaElegida].push_back(cartaTomada);
}

void Colorette::tomarFila() {
    mostrarEstadoJuego();
    int filaElegida;
    do {
        std::cout << "Elige una fila para tomar (1-" << filas.size() << "): ";
        std::cin >> filaElegida;
        filaElegida--;
        if (filas[filaElegida].empty()) {
            std::cout << "La fila elegida está vacía. No se pueden tomar más cartas." << std::endl;
            jugarPartida();
        }
        
    } while (filaElegida < 0 || filaElegida >= filas.size() || filas[filaElegida].empty() || !filasDisponibles[filaElegida]);

    jugadores[jugadorActual].mano.insert(jugadores[jugadorActual].mano.end(), filas[filaElegida].begin(), filas[filaElegida].end());
    filas[filaElegida].clear();
    filasDisponibles[filaElegida] = false; // Marcar la fila como no disponible
    jugadores[jugadorActual].activo = false;
}

void Colorette::contarPuntosJugadores() {
    std::cout << "\n--- Conteo de puntos final ---\n";
    for (auto& jugador : jugadores) {
        jugador.contarPuntos();
    }

    // Determinar el jugador con mayor puntuación
    auto ganador = std::max_element(jugadores.begin(), jugadores.end(), [](const Jugador& a, const Jugador& b) {
        return a.puntuacion < b.puntuacion;
    });

    std::cout << "\nEl ganador es: " << ganador->nombre << " con " << ganador->puntuacion << " puntos!" << std::endl;
}

void Colorette::jugarPartida() {
    while (!ultimaRonda || !mazo.estaVacio()) {
        if (jugadores[jugadorActual].activo) {
            std::cout << "\nTurno de " << jugadores[jugadorActual].nombre << std::endl;
            mostrarEstadoJuego();

            char accion;
             int prueba = 1;
            do{
            if (std::all_of(filas.begin(), filas.end(), [](const std::vector<Carta>& fila) { return fila.size() >= 3; })) {
                std::cout << "Todas las filas están llenas. Debes tomar una fila." << std::endl;
                accion = 'B';
            } else {
                std::cout << "¿Qué acción quieres realizar? (A: Tomar y poner carta, B: Tomar fila): ";
                std::cin >> accion;
            }

            if (accion == 'A') {
                tomarYPonerCarta();
                prueba = 0;
            } else if (accion == 'B') {
                tomarFila();
                prueba = 0;
            }
            else{
                std::cout << "Acción invalida intenta de nuevo \n";
            }
            }while(prueba = 1);

            jugadores[jugadorActual].mostrarCartasPorColor(); // Mostrar el conteo de cartas por color después del turno.
        }

        jugadorActual = (jugadorActual + 1) % jugadores.size();

        if (std::all_of(jugadores.begin(), jugadores.end(), [](const Jugador& j) { return !j.activo; })) {
            std::cout << "Fin de la ronda. Iniciando nueva ronda." << std::endl;
            for (auto& jugador : jugadores) {
                jugador.activo = true;
            }
            inicializarFilas();
        }
    }

    // Cuando el juego termina, realizar el conteo de puntos
    contarPuntosJugadores();
}
