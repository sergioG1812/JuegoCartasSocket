#include <iostream>
#include <vector>
#include <string>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include "Juego.h"

#pragma comment(lib, "Ws2_32.lib")

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

    SOCKET listenSock = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSock == INVALID_SOCKET) {
        cerr << "Error al crear socket: " << WSAGetLastError() << "\n";
        WSACleanup();
        return 1;
    }

    sockaddr_in sa{};
    sa.sin_family = AF_INET;
    sa.sin_port = htons(PORT);
    sa.sin_addr.s_addr = inet_addr("127.0.0.1");

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

    cout << "Esperando cliente en localhost en el puerto: " << PORT << " \n";

    SOCKET clientSock = accept(listenSock, nullptr, nullptr);
    if (clientSock == INVALID_SOCKET) {
        cerr << "Error en accept: " << WSAGetLastError() << "\n";
        closesocket(listenSock);
        WSACleanup();
        return 1;
    }

    cout << "Cliente conectado en localhost. \n";

    vector<string> nombres = { "Servidor", "Cliente" };
    Juego juego(nombres);
    juego.jugarSocketServer(clientSock, static_cast<uint64_t>(PORT));
    closesocket(clientSock);
    closesocket(listenSock);
    WSACleanup();
    return 0;
}
