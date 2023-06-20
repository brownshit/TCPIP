#include<stdio.h>
#include<stdlib.h>
#include<WinSock2.h>
void ErrorHandling(char* message);
int main(int argc, char* argv[]) {//argv 같은 경우, 문자형을 입력으로 받는다.
	WSADATA wsaData;
	SOCKET hsock;
	SOCKADDR_IN servAddr;

	char message[30];
	int strLen;
	if (argc != 3) {
		printf("Usage : %s <IP> <PORT>\n", argv[0]);
		exit(1);
	}
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error");

	hsock = socket(PF_INET, SOCK_STREAM, 0);
	if (hsock == INVALID_SOCKET)
		ErrorHandling("socket() error");
	
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(argv[1]);
	servAddr.sin_port = htons(atoi(argv[2]));

	if (connect(hsock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorHandling("connect() error");

	strLen = recv(hsock, message, sizeof(message) - 1, 0);
	if (strLen == -1)
		ErrorHandling("read() error");
	printf("Message from server : %s \n", message);

	closesocket(hsock);
	WSACleanup();//이걸로 winsock 을 초기화 한내용 해제한다.

	return 0;
}
void ErrorHandling(char* message) {
	fputs(message, stderr);
	fputc("\n", stderr);
	exit(1);
}
