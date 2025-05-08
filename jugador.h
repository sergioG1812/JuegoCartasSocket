#pragma once
#include <vector>
#include <string>
#include <stdexcept>
#include "Carta.h"

using namespace std;

class Jugador {
public:
    explicit Jugador(const string& nombre);

    void setLocal(bool esLocal);
    bool esJugadorLocal() const;

    void vaciarMano();
    void agregarCarta(const Carta& c);
    int  getNumeroCartas() const;
    Carta getCartaEnMano(int idx) const;
    void  quitarCarta(int idx);

    void agregarCartaGanada(const Carta& c);
    int  getCartasGanadas() const;

private:
    string        nombre;
    vector<Carta> mano;
    vector<Carta> cartasGanadas;
    bool          local;
    int           ultimaJugadaIdx;
};
