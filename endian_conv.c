#include <stdio.h>
#include <winsock2.h>

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Failed to initialize Winsock.\n");
        return 1;
    }
    //notification : WSAStartup and WSACleanup 은 windows에서
    // socket 과 file을 구분하기 때문에 필요한 구문이다

    unsigned short host_port = 0x1234;
    unsigned short net_port;
    unsigned long host_addr = 0x12345678;
    unsigned long net_addr;

    net_port = htons(host_port);
    net_addr = htonl(host_addr);

    printf("Host ordered port: %#x\n", host_port);
    printf("Network ordered port: %#x\n", net_port);
    printf("Host ordered address: %#lx\n", host_addr);
    printf("Network ordered address: %#lx\n", net_addr);

    WSACleanup();

    return 0;
}

/*
[Linux code]

#include<stdio.h>
#include<arpa/inet.h>

int main()
{
    unsigned short host_port = 0x1234;
    unsigned short net_port;
    unsigned long host_addr = 0x12345678;
    unsigned long net_addr;


    net_port = htons(host_port);
    net_addr = htonl(host_addr);

    printf("Host ordered port : %#x \n", host_port);
    printf("Network ordered port : %#x \n", net_port);
    printf("Host ordered address : %#x \n", host_addr);
    printf("Network ordered address : %#x \n", net_addr);
    return 0;
}

*/
