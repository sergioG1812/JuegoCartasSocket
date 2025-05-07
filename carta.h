#pragma once
#include <string>
#include <iostream>

enum Color { Amarillo, Azul, Rojo, Negro };

class Carta {
public:
    Carta(Color color, int valor);
    Color getColor() const;
    int   getValor() const;
    void  mostrar() const;

private:
    Color color;
    int   valor;
};
