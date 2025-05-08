#include "Juego.h"
#include <algorithm>
#include <random>
#include <iostream>

using namespace std;

Juego::Juego(const vector<string>& nombres) {
    if (nombres.size() != 2) {
        throw invalid_argument("Se requieren exactamente 2 nombres de jugador");
    }
    jugadores.emplace_back(nombres[0]);
    jugadores.emplace_back(nombres[1]);
    jugadores[0].setLocal(true);
    jugadores[1].setLocal(false);
}

void Juego::repartirCartas() {
    mazo.clear();
    for (int c = Amarillo; c <= Negro; ++c) {
        for (int v = 0; v < 10; ++v) {
            mazo.emplace_back(static_cast<Color>(c), v);
        }
    }
    mt19937 rng(random_device{}());
    shuffle(mazo.begin(), mazo.end(), rng);
    size_t turno = 0;
    while (!mazo.empty()) {
        jugadores[turno].agregarCarta(mazo.back());
        mazo.pop_back();
        turno = (turno + 1) % jugadores.size();
    }
}

void Juego::resolverRonda(const Carta& serv, const Carta& cli, SOCKET sock) {
    if (serv == cli) {
        string msg = "EMPATE";
        send(sock, msg.c_str(), (int)msg.size() + 1, 0);
    }
    else if (serv > cli) {
        jugadores[0].agregarCartaGanada(serv);
        jugadores[0].agregarCartaGanada(cli);
        string msg = "SERVIDOR_GANA";
        send(sock, msg.c_str(), (int)msg.size() + 1, 0);
    }
    else {

        jugadores[1].agregarCartaGanada(serv);
        jugadores[1].agregarCartaGanada(cli);
        string msg = "CLIENTE_GANA";
        send(sock, msg.c_str(), (int)msg.size() + 1, 0);
    }
}

void Juego::jugarSocketServer(SOCKET sock, uint64_t /*puerto*/) {
    // Reparto inicial
    repartirCartas();

    int numCliente = jugadores[1].getNumeroCartas();
    send(sock, reinterpret_cast<char*>(&numCliente), sizeof(numCliente), 0);
    for (int i = 0; i < numCliente; ++i) {
        Carta c = jugadores[1].getCartaEnMano(i);
        int col = static_cast<int>(c.getColor());
        int val = c.getValor();
        send(sock, reinterpret_cast<char*>(&col), sizeof(col), 0);
        send(sock, reinterpret_cast<char*>(&val), sizeof(val), 0);
    }
    
    while (jugadores[0].getNumeroCartas() > 0 && jugadores[1].getNumeroCartas() > 0) {
       
        Carta serv = jugadores[0].getCartaEnMano(0);
        jugadores[0].quitarCarta(0);
        int scol = serv.getColor(), sval = serv.getValor();
        send(sock, reinterpret_cast<char*>(&scol), sizeof(scol), 0);
        send(sock, reinterpret_cast<char*>(&sval), sizeof(sval), 0);

       
        int ccol, cval;
        recv(sock, reinterpret_cast<char*>(&ccol), sizeof(ccol), 0);
        recv(sock, reinterpret_cast<char*>(&cval), sizeof(cval), 0);
        Carta cli(static_cast<Color>(ccol), cval);

    
        resolverRonda(serv, cli, sock);
    }
}


void Juego::jugarSocketClient(SOCKET sock) {

    int num;
    recv(sock, reinterpret_cast<char*>(&num), sizeof(num), 0);
    jugadores[1].vaciarMano();
    for (int i = 0; i < num; ++i) {
        int col, val;
        recv(sock, reinterpret_cast<char*>(&col), sizeof(col), 0);
        recv(sock, reinterpret_cast<char*>(&val), sizeof(val), 0);
        jugadores[1].agregarCarta(Carta(static_cast<Color>(col), val));
    }
    
    cout << "-- MANO CLIENTE (" << num << " cartas) --\n";
    for (int i = 0; i < jugadores[1].getNumeroCartas(); ++i) {
        jugadores[1].getCartaEnMano(i).mostrar();
        cout << "\n";
    }
    cout << "\n";
   
    while (jugadores[1].getNumeroCartas() > 0) {
       
        int scol, sval;
        if (recv(sock, reinterpret_cast<char*>(&scol), sizeof(scol), 0) <= 0) break;
        recv(sock, reinterpret_cast<char*>(&sval), sizeof(sval), 0);
        Carta serv(static_cast<Color>(scol), sval);
        cout << "Servidor juega: "; serv.mostrar(); cout << "\n";

       
        Carta cli = jugadores[1].getCartaEnMano(0);
        jugadores[1].quitarCarta(0);
        int ccol = cli.getColor(), cval = cli.getValor();
        send(sock, reinterpret_cast<char*>(&ccol), sizeof(ccol), 0);
        send(sock, reinterpret_cast<char*>(&cval), sizeof(cval), 0);
        cout << "Cliente juega: "; cli.mostrar(); cout << "\n";

     
        char buf[32];
        recv(sock, buf, sizeof(buf), 0);
        string result(buf);
        if (result == "EMPATE") cout << "-> Empate\n\n";
        else if (result == "SERVIDOR_GANA") cout << "-> Servidor gana\n\n";
        else if (result == "CLIENTE_GANA") cout << "-> Cliente gana\n\n";
    }
    cout << ">> Fin del juego <<\n";
}
