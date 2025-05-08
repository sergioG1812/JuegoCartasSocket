#include "Jugador.h"
#include <iostream>
#include <limits>

using namespace std;

Jugador::Jugador(const string& nombre_)
    : nombre(nombre_), local(true), ultimaJugadaIdx(-1) {
}

void Jugador::setLocal(bool esLocal) {
    local = esLocal;
}

bool Jugador::esJugadorLocal() const {
    return local;
}

void Jugador::vaciarMano() {
    mano.clear();
}

void Jugador::agregarCarta(const Carta& c) {
    mano.push_back(c);
}

int Jugador::getNumeroCartas() const {
    return static_cast<int>(mano.size());
}

Carta Jugador::getCartaEnMano(int idx) const {
    if (idx < 0 || idx >= static_cast<int>(mano.size()))
        throw out_of_range("Índice de carta fuera de rango");
    return mano[idx];
}

void Jugador::quitarCarta(int idx) {
    if (idx < 0 || idx >= static_cast<int>(mano.size()))
        throw out_of_range("Índice de carta fuera de rango");
    ultimaJugadaIdx = idx;
    mano.erase(mano.begin() + idx);
}

void Jugador::agregarCartaGanada(const Carta& c) {
    cartasGanadas.push_back(c);
}

int Jugador::getCartasGanadas() const {
    return static_cast<int>(cartasGanadas.size());
}
