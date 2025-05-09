#pragma once
#include <vector>
#include <string>
#include <winsock2.h>
#include "Carta.h"
#include "Jugador.h"

using namespace std;

class Juego {
public:
    explicit Juego(const vector<string>& nombres);

    void repartirCartas();
    void jugarSocketServer(SOCKET sock, uint64_t puerto);
    void jugarSocketClient(SOCKET sock);

private:
    vector<Jugador> jugadores;
    vector<Carta>   mazo;

    void resolverRonda(const Carta& serv, const Carta& cli, SOCKET sock);
};
