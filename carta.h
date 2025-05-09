#ifndef CARTA_H
#define CARTA_H

#include <iostream>

enum Color { Amarillo, Azul, Rojo, Negro };

class Carta {
public:

    Carta() : color(Amarillo), valor(0) {}

    
    Carta(Color color, int valor);

    Color getColor() const;
    int   getValor() const;

    
    void mostrar() const;

    bool operator==(const Carta& o) const;
    bool operator>(const Carta& o)  const;

private:
    Color color;
    int   valor;
};

#endif 
