#include <stdio.h>

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32")

int main(int argc, char* argv[])
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;

    addr.sin_addr.s_addr = inet_addr(argv[1]);

    unsigned short port = (unsigned short)strtoul(argv[2], NULL, 0);

    addr.sin_port = htons(port);

    int ret = connect(client, (SOCKADDR*)&addr, sizeof(addr));
    if (ret == SOCKET_ERROR)
    {
        ret = WSAGetLastError();
        printf("Connect failed: %d\n", ret);
        return 1;
    }

    char msg[256];

    while (1)
    {
        printf("Nhap xau ky tu: ");
        fgets(msg, sizeof(msg), stdin);
        if (strcmp(msg, "exit") == 0) break;
        send(client, msg, strlen(msg), 0);
    }
    

    closesocket(client);
    WSACleanup();
}