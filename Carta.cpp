#include "Carta.h"

Carta::Carta(std::string c, int v, bool comodin) : color(c), valor(v), esComodin(comodin) {}

std::string obtenerColorANSI(const std::string& color) {
    if (color == "Rojo") return "\033[1;31m";
    else if (color == "Azul") return "\033[1;34m";
    else if (color == "Verde") return "\033[1;32m";
    else if (color == "Amarillo") return "\033[1;33m";
    else if (color == "Naranja") return "\033[38;5;208m";
    else if (color == "Violeta") return "\033[1;35m";
    else if (color == "Gris") return "\033[1;37m";
    else if (color == "+2") return "\033[1;36m";
    else if (color == "Comodín") return "\033[1;95m";
    else return "\033[0m";
}

std::string restablecerColorANSI() {
    return "\033[0m";
}