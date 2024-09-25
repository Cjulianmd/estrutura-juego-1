#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

struct Carta {
    string color;
    bool esComodin;
};

class Jugador {
public:
    map<string, int> cartasRecoleccion; // Contador de cartas por color
    int puntos;

    Jugador() {
        puntos = 0;
    }

    void agregarCarta(Carta carta) {
        if (!carta.esComodin) {
            cartasRecoleccion[carta.color]++;
        }
    }

    void calcularPuntos() {
        vector<int> puntajesPositivos;
        vector<int> puntajesNegativos;

        // Recorre los colores y calcula puntos
        for (auto const& par : cartasRecoleccion) {
            int cantidad = par.second;
            int puntosColor = calcularPuntaje(cantidad);

            if (puntajesPositivos.size() < 3) {
                puntajesPositivos.push_back(puntosColor);
            } else {
                puntajesNegativos.push_back(-puntosColor);
            }
        }

        // Sumar puntos positivos
        for (int puntosPos : puntajesPositivos) {
            puntos += puntosPos;
        }

        // Restar puntos negativos
        for (int puntosNeg : puntajesNegativos) {
            puntos += puntosNeg;
        }
    }

    void mostrarPuntuacion() {
        cout << "Puntuacion final: " << puntos << " puntos." << endl;
    }

private:
    int calcularPuntaje(int cantidad) {
        if (cantidad == 1) return 1;
        else if (cantidad == 2) return 3;
        else if (cantidad == 3) return 6;
        else if (cantidad == 4) return 10;
        else if (cantidad == 5) return 15;
        else return 21;
    }
};

class Juego {
public:
    vector<Carta> mazo;
    vector<Jugador> jugadores;
    int rondaActual;

    Juego(int numJugadores) {
        rondaActual = 1;
        jugadores = vector<Jugador>(numJugadores);
        inicializarMazo();
    }

    void inicializarMazo() {
        string colores[7] = {"Rojo", "Azul", "Verde", "Amarillo", "Naranja", "Marron", "Rosa"};
        for (int i = 0; i < 9; i++) {
            for (string color : colores) {
                mazo.push_back(Carta{color, false});
            }
        }
        // Agregar comodines
        mazo.push_back(Carta{"Comodin", true});
        mazo.push_back(Carta{"Comodin", true});
    }

    void repartirCartas() {
        // Ejemplo simple de repartir cartas
        for (int i = 0; i < 3; i++) {
            for (auto& jugador : jugadores) {
                Carta carta = mazo.back();
                mazo.pop_back();
                jugador.agregarCarta(carta);
            }
        }
    }

    void finalizarJuego() {
        for (auto& jugador : jugadores) {
            jugador.calcularPuntos();
            jugador.mostrarPuntuacion();
        }
    }
};

int main() {
    int numJugadores;
    cout << "Ingrese el numero de jugadores: ";
    cin >> numJugadores;

    Juego coloretto(numJugadores);
    coloretto.repartirCartas();
    coloretto.finalizarJuego();

    return 0;
}
