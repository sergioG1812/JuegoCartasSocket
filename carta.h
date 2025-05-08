#pragma once
#include <string>
#include <iostream>

using namespace std;

enum Color { Amarillo, Azul, Rojo, Negro };

class Carta {
public:
    Carta(Color color, int valor);
    Color getColor() const;
    int   getValor() const;
    void  mostrar() const;

    bool operator==(const Carta& o) const { return color == o.color && valor == o.valor; }
    bool operator>(const Carta& o)  const { return valor > o.valor; }

private:
    Color color;
    int   valor;
};
