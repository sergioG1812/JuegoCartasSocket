#include "Juego.h"
#include <algorithm>
#include <random>
#include <iostream>

using namespace std;

Juego::Juego(const vector<string>& nombres) {
    for (auto& n : nombres)
        jugadores.emplace_back(n);
    jugadores[0].setLocal(true);
    jugadores[1].setLocal(false);
}

void Juego::repartirCartas() {
    
    mazo.clear();
    for (int c = 0; c < 4; ++c)
        for (int v = 0; v < 10; ++v)
            mazo.emplace_back(static_cast<Color>(c), v);

    mt19937 rng(random_device{}());
    shuffle(mazo.begin(), mazo.end(), rng);

    for (auto& j : jugadores) {
        j.vaciarMano();
        j.vaciarCartasGanadas();
    }

    int turno = 0, nJ = jugadores.size();
    for (auto& carta : mazo) {
        jugadores[turno].agregarCarta(carta);
        turno = (turno + 1) % nJ;
    }
}

bool Juego::juegoTerminado() const {
    for (const auto& j : jugadores)
        if (j.getNumeroCartas() == 0)
            return true;
    return false;
}

void Juego::jugarTurnoLocal(int idxJugador) {
    jugadores[idxJugador].jugarCarta();
}

