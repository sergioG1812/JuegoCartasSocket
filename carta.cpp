#include "Carta.h"

static const char* nombresColor[] = { "Amarillo", "Azul", "Rojo", "Negro" };

Carta::Carta(Color color_, int valor_)
    : color(color_), valor(valor_) {
}

Color Carta::getColor() const { return color; }
int   Carta::getValor() const { return valor; }

void Carta::mostrar() const {
    std::cout << nombresColor[color] << " " << valor;
}
