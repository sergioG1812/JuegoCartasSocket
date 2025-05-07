#include <iostream>
#include <vector>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "Juego.h"

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

void printLocalIPs() {
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        cerr << "Error obteniendo hostname\n";
        return;
    }

    addrinfo hints{}, *res = nullptr;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(hostname, nullptr, &hints, &res) != 0) {
        cerr << "Error en getaddrinfo\n";
        return;
    }

    cout << "IP(s) locales:\n";
    for (auto p = res; p; p = p->ai_next) {
        auto* sa = reinterpret_cast<sockaddr_in*>(p->ai_addr);
        cout << "  " << inet_ntoa(sa->sin_addr) << "\n";
    }
    freeaddrinfo(res);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Uso: " << argv[0] << " <puerto>\n";
        return 1;
    }

    int PORT = stoi(argv[1]);

    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        cerr << "Error inicializando WinSock: " << WSAGetLastError() << "\n";
        return 1;
    }

    printLocalIPs();

    SOCKET listenSock = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSock == INVALID_SOCKET) {
        cerr << "Error al crear socket: " << WSAGetLastError() << "\n";
        WSACleanup();
        return 1;
    }

    sockaddr_in sa{};
    sa.sin_family = AF_INET;
    sa.sin_port = htons(PORT);
    sa.sin_addr.s_addr = INADDR_ANY; // todas las interfaces

    if (bind(listenSock, (sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR) {
        cerr << "Error en bind: " << WSAGetLastError() << "\n";
        closesocket(listenSock);
        WSACleanup();
        return 1;
    }

    if (listen(listenSock, 1) == SOCKET_ERROR) {
        cerr << "Error en listen: " << WSAGetLastError() << "\n";
        closesocket(listenSock);
        WSACleanup();
        return 1;
    }

    cout << "Esperando cliente en puerto " << PORT << "...\n";

    SOCKET clientSock = accept(listenSock, nullptr, nullptr);
    if (clientSock == INVALID_SOCKET) {
        cerr << "Error en accept: " << WSAGetLastError() << "\n";
        closesocket(listenSock);
        WSACleanup();
        return 1;
    }

    cout << "Cliente conectado.\n";

    vector<string> nombres = { "Servidor", "Cliente" };
    Juego juego(nombres);
    juego.jugarSocketServer(clientSock, static_cast<uint64_t>(PORT));

    closesocket(clientSock);
    closesocket(listenSock);
    WSACleanup();
    return 0;
}
