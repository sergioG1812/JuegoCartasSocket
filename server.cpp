#include <iostream>
#include <vector>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "Juego.h"

#pragma comment(lib, "Ws2_32.lib")

void printLocalIPs() {
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        std::cerr << "Error obteniendo hostname\n";
        return;
    }

    addrinfo hints{}, * res = nullptr;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(hostname, nullptr, &hints, &res) != 0) {
        std::cerr << "Error en getaddrinfo\n";
        return;
    }

    std::cout << "IP(s) locales:\n";
    for (auto p = res; p; p = p->ai_next) {
        auto* sa = reinterpret_cast<sockaddr_in*>(p->ai_addr);
        std::cout << "  " << inet_ntoa(sa->sin_addr) << "\n";
    }
    freeaddrinfo(res);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <puerto>\n";
        return 1;
    }
    int PORT = std::stoi(argv[1]);

    WSADATA w;
    WSAStartup(MAKEWORD(2,2), &w);

    SOCKET listenSock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in sa{};
    sa.sin_family      = AF_INET;
    sa.sin_port        = htons(PORT);
    sa.sin_addr.s_addr = INADDR_ANY;       // escucha en todas las interfaces

    bind(listenSock, (sockaddr*)&sa, sizeof(sa));
    listen(listenSock, 1);
    std::cout << "Esperando cliente en puerto " << PORT << "...\n";

    SOCKET clientSock = accept(listenSock, nullptr, nullptr);

    if (clientSock == INVALID_SOCKET) {
        std::cerr << "Error en accept: " << WSAGetLastError() << "\n";
        closesocket(listenSock);
        WSACleanup();
        return 1;
    }
    std::cout << "Cliente conectado.\n";

    // Iniciar el juego
    std::vector<std::string> nombres = { "Servidor", "Cliente" };
    Juego juego(nombres);
    juego.jugarSocketServer(clientSock, static_cast<uint64_t>(PORT));

    // Cerrar sockets y limpiar Winsock
    closesocket(clientSock);
    closesocket(listenSock);
    WSACleanup();
    return 0;
}