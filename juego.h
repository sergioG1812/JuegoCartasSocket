#pragma once
#include <vector>
#include <string>
#include <winsock2.h>
#include "Carta.h"
#include "Jugador.h"

using namespace std;

class Juego {
public:
    Juego(const vector<string>& nombres);

    void jugarSocketServer(SOCKET sock, uint64_t puerto);
    void jugarSocketClient(SOCKET sock);

private:
    vector<Jugador> jugadores;
    vector<Carta>   mazo;

    void repartirCartas();
    bool juegoTerminado() const;
    void jugarTurnoLocal(int idxJugador);
};
