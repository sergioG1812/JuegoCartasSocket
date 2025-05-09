#include "carta.h"
using namespace std;
Carta::Carta(Color c, int v)
    : color(c), valor(v) {
}
Color Carta::getColor() const { return color; }
int   Carta::getValor() const { return valor; }

void Carta::mostrar() const {
    static const char* nombres[] = { "Amarillo", "Azul", "Rojo", "Negro" };
    cout << "[" << nombres[color] << " " << valor << "]";
}

bool Carta::operator==(const Carta& o) const {
    return color == o.color && valor == o.valor;
}

bool Carta::operator>(const Carta& o) const {
    
    if (color != o.color) return color > o.color;
    return valor > o.valor;
}
