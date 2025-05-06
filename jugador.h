#pragma once
#include <vector>
#include <string>
#include <stdexcept>
#include "Carta.h"

using namespace std;

class Jugador {
public:
    explicit Jugador(const string& nombre);

    // Marca local/remoto
    void setLocal(bool esLocal);
    bool esJugadorLocal() const;

    // Para el reparto: limpia estado previo
    void vaciarMano();
    void vaciarCartasGanadas();
    void agregarCarta(const Carta& c);

    // Lógica de juego
    Carta jugarCarta();
    int   getUltimaCartaJugadaIndice() const;

    // Consultas
    int   getNumeroCartas() const;
    Carta getCartaEnMano(int idx) const;
    void  quitarCarta(int idx);

    // Cartas ganadas
    void agregarCartaGanada(const Carta& c);
    int  getCartasGanadas() const;

private:
    string        nombre;
    vector<Carta> mano;
    vector<Carta> cartasGanadas;
    bool          local;
    int           ultimaJugadaIdx;
};
