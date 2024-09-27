#include "juego.h"
//Constructor 
Colorette::Colorette(int numJugadores, int numPartidas) : numPartidas(numPartidas), partidaActual(1) {
    for (int i = 0; i < numJugadores; i++) {
        std::cout << "Ingrese el nombre del Jugador " << i + 1 << ": ";
        std::string nombre;
        std::cin >> nombre;
        jugadores.push_back({nombre, {}, true, 0});
    }
    crearMazo();
    prepararMazo();
    inicializarFilas();
    jugadorActual = 0;
    ultimaRonda = false;
}
//crea el mazo de cartas
void Colorette::crearMazo() {
    std::vector<std::string> colores = {"Rojo", "Azul", "Verde", "Amarillo", "Naranja", "Violeta", "Gris"};
    for (const auto& color : colores) {
        for (int i = 0; i < 9; i++) {
            mazo.push_back({color, 1, false, false});
        }
    }
    for (int i = 0; i < 10; i++) {
        mazo.push_back({"+2", 2, false, false});
    }
    for (int i = 0; i < 3; i++) {
        mazo.push_back({"Comodín", 0, false, true});
    }
    mazo.push_back({"Última Ronda", 0, true, false});
}
//crea el mazo
void Colorette::barajarMazo() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(mazo.begin(), mazo.end(), g);
}
//coloca la carta final en el punto adecuado
void Colorette::prepararMazo() {
    barajarMazo();
    std::vector<Carta> mazoTemporal;
    for (int i = 0; i < 15; i++) {
        mazoTemporal.push_back(mazo.back());
        mazo.pop_back();
    }
    auto it = std::find_if(mazo.begin(), mazo.end(), [](const Carta& c) { return c.esUltimaRonda; });
    if (it != mazo.end()) {
        mazoTemporal.push_back(*it);
        mazo.erase(it);
    }
    barajarMazo();
    mazo.insert(mazo.end(), mazoTemporal.begin(), mazoTemporal.end());
}
//crea las filas segun el numero de jugadores
void Colorette::inicializarFilas() {
    filas.clear();
    for (size_t i = 0; i < jugadores.size(); i++) {
        filas.push_back({});
    }
}
//imprimir las filas
void Colorette::mostrarEstadoJuego() {
    std::cout << "\nEstado actual del juego:" << std::endl;
    for (size_t i = 0; i < filas.size(); i++) {
        std::cout << "Fila " << i + 1 << ": ";
        for (const auto& carta : filas[i]) {
            std::cout << carta.color << " ";
        }
        std::cout << std::endl;
    }
}
//gestiona como actuar segun se toma las cartas
void Colorette::tomarYPonerCarta() {
    if (mazo.empty()) {
        //si no hay cartas en el mazo
        std::cout << "El mazo está vacío. No se pueden tomar más cartas." << std::endl;
        return;
    }

    Carta cartaTomada = mazo.back();
    mazo.pop_back();

    if (cartaTomada.esUltimaRonda) {
        //si se toma la ultima ronda
        std::cout << "¡Se ha tomado la carta de Última Ronda! Esta será la última ronda del juego." << std::endl;
        ultimaRonda = true;
        if (!mazo.empty()) {
            cartaTomada = mazo.back();
            mazo.pop_back();
        } else {
            std::cout << "No quedan más cartas en el mazo." << std::endl;
            return;
        }
    }

    std::cout << jugadores[jugadorActual].nombre << " ha tomado una carta " << cartaTomada.color << std::endl;

    mostrarEstadoJuego();
    int filaElegida;
    do {
        //seleccionar fila a dejar la carta
        std::cout << "Elige una fila para poner la carta (1-" << filas.size() << "): ";
        std::cin >> filaElegida;
        filaElegida--;
    } while (filaElegida < 0 || filaElegida >= filas.size() || filas[filaElegida].size() >= 3);

    filas[filaElegida].push_back(cartaTomada);
}
//sirve para tomar las cartas de una fila
void Colorette::tomarFila() {
    mostrarEstadoJuego();
    int filaElegida;
    do {
        //Elegir fila al robar
        std::cout << "Elige una fila para tomar (1-" << filas.size() << "): ";
        std::cin >> filaElegida;
        filaElegida--;
    } while (filaElegida < 0 || filaElegida >= filas.size() || filas[filaElegida].empty());
    //sumar las cartas
    jugadores[jugadorActual].mano.insert(jugadores[jugadorActual].mano.end(), filas[filaElegida].begin(), filas[filaElegida].end());
    filas[filaElegida].clear();
    jugadores[jugadorActual].activo = false;
}
//calcular los puntos
int Colorette::calcularPuntuacion(Jugador& jugador) {
    std::map<std::string, int> conteoColores;
    int puntosMasDos = 0;
    int puntosPositivos = 0;
    int puntosNegativos = 0;

    for (const auto& carta : jugador.mano) {
        if (carta.color == "+2") {
            puntosMasDos += 2;
        } else if (carta.color != "Comodín") {
            conteoColores[carta.color]++;
        }
    }

    std::cout << jugador.nombre << ", elige los colores de tus comodines:" << std::endl;
    for (auto& carta : jugador.mano) {
        if (carta.esComodin) {
            std::cout << "Elige un color para el comodín: ";
            std::cin >> carta.color;
            conteoColores[carta.color]++;
        }
    }

    std::vector<std::pair<std::string, int>> coloresOrdenados(conteoColores.begin(), conteoColores.end());
    std::sort(coloresOrdenados.begin(), coloresOrdenados.end(), 
              [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) { return a.second > b.second; });

    std::cout << jugador.nombre << ", elige 3 colores para puntos positivos:" << std::endl;
    for (int i = 0; i < 3 && i < coloresOrdenados.size(); i++) {
        std::cout << coloresOrdenados[i].first << ": " << coloresOrdenados[i].second << " cartas" << std::endl;
        puntosPositivos += calcularPuntosPorColor(coloresOrdenados[i].second);
    }

    for (size_t i = 3; i < coloresOrdenados.size(); i++) {
        puntosNegativos += coloresOrdenados[i].second;
    }

    return puntosPositivos + puntosMasDos - puntosNegativos;
}
//gestiona segun la cantidad de cartas los puntos que se tiene
int Colorette::calcularPuntosPorColor(int numCartas) {
    switch(numCartas) {
        case 1: return 1;
        case 2: return 3;
        case 3: return 6;
        case 4: return 10;
        case 5: return 15;
        default: return 21;  // 6 o más cartas
    }
}
//controla el orden de la partida
void Colorette::jugarPartida() {
    std::cout << "\n--- Partida " << partidaActual << " de " << numPartidas << " ---" << std::endl;
    
    while (!ultimaRonda || !std::all_of(jugadores.begin(), jugadores.end(), [](const Jugador& j) { return !j.activo; })) {
        if (jugadores[jugadorActual].activo) {
            std::cout << "\nTurno de " << jugadores[jugadorActual].nombre << std::endl;
            mostrarEstadoJuego();

            char accion;
            if (std::all_of(filas.begin(), filas.end(), [](const std::vector<Carta>& fila) { return fila.size() >= 3; })) {
                std::cout << "Todas las filas están llenas. Debes tomar una fila." << std::endl;
                accion = 'B';
            } else {
                std::cout << "¿Qué acción quieres realizar? (A: Tomar y poner carta, B: Tomar fila): ";
                std::cin >> accion;
            }

            if (accion == 'A') {
                tomarYPonerCarta();
            } else if (accion == 'B') {
                tomarFila();
            }
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

    std::cout << "\nFin de la partida. Calculando puntuaciones..." << std::endl;
    for (auto& jugador : jugadores) {
        int puntos = calcularPuntuacion(jugador);
        jugador.puntuacion += puntos;
        std::cout << jugador.nombre << " ha obtenido " << puntos << " puntos en esta partida." << std::endl;
    }

    partidaActual++;
}
//Muestra los resultados finales del juego
void Colorette::mostrarResultadoFinal() {
    std::cout << "\n--- Resultado Final ---" << std::endl;
    for (const auto& jugador : jugadores) {
        std::cout << jugador.nombre << ": " << jugador.puntuacion << " puntos" << std::endl;
    }
    auto ganador = std::max_element(jugadores.begin(), jugadores.end(),
                                     [](const Jugador& a, const Jugador& b) { return a.puntuacion < b.puntuacion; });
    std::cout << "\n¡El ganador es " << ganador->nombre << " con " << ganador->puntuacion << " puntos!" << std::endl;
}