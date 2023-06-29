#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

void ErrorHandling(char* message);

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        ErrorHandling("WSAStartup() error");

    // 문자열을 이진 주소로 변환 (inet_addr 대체)
    {
        const char* addr = "127.212.124.78";
        struct in_addr ipv4Addr;
        if (inet_pton(AF_INET, addr, &ipv4Addr) <= 0)
            printf("Error occurred!\n");
        else
            printf("Network ordered integer addr: %#lx\n", ipv4Addr.s_addr);
    }

    // 이진 주소를 문자열로 변환 (inet_ntoa 대체)
    {
        struct sockaddr_in addr;
        char strArr[INET_ADDRSTRLEN];

        addr.sin_addr.s_addr = htonl(0x1020304);
        if (inet_ntop(AF_INET, &(addr.sin_addr), strArr, sizeof(strArr)) == NULL)
            printf("Error occurred!\n");
        else
            printf("Dotted-Decimal notation: %s\n", strArr);
    }

    WSACleanup();

    return 0;
}

void ErrorHandling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
