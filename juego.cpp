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
    
    cout << "\n[ Ronda ] Servidor jugo "; serv.mostrar();
    cout << " | Cliente jugo "; cli.mostrar();
    cout << "\n";

    
    if (serv.getColor() == cli.getColor() && cli.getValor() > serv.getValor()) {
        cout << "Resultado: Cliente gana la ronda\n";
        jugadores[1].agregarCartaGanada(serv);
        jugadores[1].agregarCartaGanada(cli);
        string msg = "CLIENTE_GANA";
        send(sock, msg.c_str(), (int)msg.size() + 1, 0);
    }
    else if (serv.getColor() == cli.getColor() && cli.getValor() == serv.getValor()) {
        cout << "Resultado: Empate en la ronda\n";
        string msg = "EMPATE";
        send(sock, msg.c_str(), (int)msg.size() + 1, 0);
    }
    else {
        cout << "Resultado: Servidor gana la ronda\n";
        jugadores[0].agregarCartaGanada(serv);
        jugadores[0].agregarCartaGanada(cli);
        string msg = "SERVIDOR_GANA";
        send(sock, msg.c_str(), (int)msg.size() + 1, 0);
    }
}

void Juego::jugarSocketServer(SOCKET sock, uint64_t /*puerto*/) {
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
        
        Jugador& serv = jugadores[0];
        cout << "\n MANO (SERVIDOR) " << endl;
        for (int i = 0; i < serv.getNumeroCartas(); ++i) {
            cout << "[" << i << "] "; serv.getCartaEnMano(i).mostrar(); cout << endl;
        }
        int idx;
        do {
            cout << "Servidor, elige indice de carta: "; cin >> idx;
        } while (cin.fail() || idx < 0 || idx >= serv.getNumeroCartas());

        Carta cartaServ = serv.getCartaEnMano(idx);
        serv.quitarCarta(idx);
        int scol = static_cast<int>(cartaServ.getColor());
        int sval = cartaServ.getValor();
        send(sock, reinterpret_cast<char*>(&scol), sizeof(scol), 0);
        send(sock, reinterpret_cast<char*>(&sval), sizeof(sval), 0);
        cout << "-> Servidor juega: "; cartaServ.mostrar(); cout << endl;

        
        int ccol, cval;
        if (recv(sock, reinterpret_cast<char*>(&ccol), sizeof(ccol), 0) <= 0) break;
        recv(sock, reinterpret_cast<char*>(&cval), sizeof(cval), 0);
        Carta cartaCli(static_cast<Color>(ccol), cval);
        cout << "-> Cliente juega: "; cartaCli.mostrar(); cout << endl;

        
        resolverRonda(cartaServ, cartaCli, sock);
    }

    
    int servGan = jugadores[0].getCartasGanadas();
    int cliGan = jugadores[1].getCartasGanadas();
    cout << "\n=== Fin de la partida ===" << endl;
    cout << "Servidor cartas ganadas: " << servGan << endl;
    cout << "Cliente cartas ganadas: " << cliGan << endl;
    if (servGan > cliGan) cout << "¡Servidor gana la partida!" << endl;
    else if (servGan < cliGan) cout << "¡Cliente gana la partida!" << endl;
    else cout << "La partida termina en empate." << endl;
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

    int servGan = 0, cliGan = 0;
    
    while (jugadores[1].getNumeroCartas() > 0) {
        
        int scol, sval;
        if (recv(sock, reinterpret_cast<char*>(&scol), sizeof(scol), 0) <= 0) break;
        recv(sock, reinterpret_cast<char*>(&sval), sizeof(sval), 0);
        Carta cartaServ(static_cast<Color>(scol), sval);
        cout << "\n-> Servidor juega: "; cartaServ.mostrar(); cout << endl;

        
        Jugador& cli = jugadores[1];
        cout << " MANO (CLIENTE) " << endl;
        for (int i = 0; i < cli.getNumeroCartas(); ++i) {
            cout << "[" << i << "] "; cli.getCartaEnMano(i).mostrar(); cout << endl;
        }
        int idx;
        do {
            cout << "Cliente, elige indice de carta: "; cin >> idx;
        } while (cin.fail() || idx < 0 || idx >= cli.getNumeroCartas());

        Carta cartaCli = cli.getCartaEnMano(idx);
        cli.quitarCarta(idx);
        int ccol = static_cast<int>(cartaCli.getColor());
        int cval = cartaCli.getValor();
        send(sock, reinterpret_cast<char*>(&ccol), sizeof(ccol), 0);
        send(sock, reinterpret_cast<char*>(&cval), sizeof(cval), 0);
        cout << "-> Cliente juega: "; cartaCli.mostrar(); cout << endl;

        
        char buf[32];
        recv(sock, buf, sizeof(buf), 0);
        string result(buf);
        if (result == "CLIENTE_GANA") {
            cout << "Resultado: Cliente gana la ronda" << endl;
            
            cliGan += 2;
        }
        else if (result == "SERVIDOR_GANA") {
            cout << "Resultado: Servidor gana la ronda" << endl;
            servGan += 2;
        }
        else {
            cout << "Resultado: Empate en la ronda" << endl;
        }
    }

    
    cout << "\n=== Fin de la partida ===" << endl;
    cout << "Servidor cartas ganadas: " << servGan << endl;
    cout << "Cliente cartas ganadas: " << cliGan << endl;
    if (servGan > cliGan) cout << "¡Servidor gana la partida!" << endl;
    else if (servGan < cliGan) cout << "¡Cliente gana la partida!" << endl;
    else cout << "La partida termina en empate." << endl;
}
