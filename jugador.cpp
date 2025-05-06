#include "Jugador.h"
#include <iostream>
#include <limits>

using namespace std;

Jugador::Jugador(const string& nombre_)
  : nombre(nombre_), local(true), ultimaJugadaIdx(-1) {}

void Jugador::setLocal(bool esLocal) {
    local = esLocal;
}

bool Jugador::esJugadorLocal() const {
    return local;
}

void Jugador::vaciarMano() {
    mano.clear();
    ultimaJugadaIdx = -1;
}

void Jugador::vaciarCartasGanadas() {
    cartasGanadas.clear();
}

void Jugador::agregarCarta(const Carta& c) {
    mano.push_back(c);
}

Carta Jugador::jugarCarta() {
    if (mano.empty())
        throw out_of_range("No hay cartas para jugar");

    cout << "Mano de " << nombre << ":\n";
    for (int i = 0; i < (int)mano.size(); ++i) {
        cout << (i+1) << ": ";
        mano[i].mostrar();
        cout << "\n";
    }

    int opcion;
    cout << "Elige número de carta [1-" << mano.size() << "]: ";
    while (!(cin >> opcion) || opcion < 1 || opcion > (int)mano.size()) {
        cout << "Índice inválido. Intenta de nuevo: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int idx = opcion - 1;
    ultimaJugadaIdx = idx;
    Carta c = mano[idx];
    mano.erase(mano.begin() + idx);
    return c;
}

int Jugador::getUltimaCartaJugadaIndice() const {
    return ultimaJugadaIdx;
}

int Jugador::getNumeroCartas() const {
    return (int)mano.size();
}

Carta Jugador::getCartaEnMano(int idx) const {
    if (idx < 0 || idx >= (int)mano.size())
        throw out_of_range("Índice de carta fuera de rango");
    return mano[idx];
}

void Jugador::quitarCarta(int idx) {
    if (idx < 0 || idx >= (int)mano.size())
        throw out_of_range("Índice de carta fuera de rango");
    ultimaJugadaIdx = idx;
    mano.erase(mano.begin() + idx);
}

void Jugador::agregarCartaGanada(const Carta& c) {
    cartasGanadas.push_back(c);
}

int Jugador::getCartasGanadas() const {
    return (int)cartasGanadas.size();
}
