#include <iostream>
#include <winsock2.h>
#include "Juego.h"
#pragma comment(lib, "Ws2_32.lib")

#define PORT      8080
#define SERVER_IP "192.168.1.9"

int main() {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "WinSock init failed: " << WSAGetLastError() << "\n";
        return 1;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serv{};
    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);
    serv.sin_addr.s_addr = inet_addr(SERVER_IP);  // IP fija

    if (connect(sock, (sockaddr*)&serv, sizeof(serv)) == SOCKET_ERROR) {
        std::cerr << "Connect failed: " << WSAGetLastError() << "\n";
        return 1;
    }
    std::cout << "Conectado al servidor.\n";

    std::vector<std::string> nombres = { "Servidor", "Cliente" };
    Juego juego(nombres);
    juego.jugarSocketClient(sock);

    closesocket(sock);
    WSACleanup();
    return 0;
}