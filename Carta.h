#ifndef CARTA_H
#define CARTA_H

#include <string>

class Carta {
public:
    std::string color;
    int valor;
    bool esComodin;

    Carta(std::string c, int v, bool comodin = false);
};

// Función para obtener el código de color ANSI según el color de la carta
std::string obtenerColorANSI(const std::string& color);

// Función para restablecer el color al valor predeterminado
std::string restablecerColorANSI();

#endif