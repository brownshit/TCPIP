#include<stdio.h>
#include<stdlib.h>
#include<WinSock2.h>

//by deprecated
#include<ws2tcpip.h>

//notify : tcp server parts are same as previous server example

void error_handling(char* message);
int main(int argc, char* argv[]) {//argv 같은 경우, 문자형을 입력으로 받는다.

	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAddr;

	char message[30];
	int strlen = 0;
	int idx = 0, readLen = 0;
	if (argc != 3) {//원래 argc는 main함수의 기본 전달인자이다.
		printf("Usage : %s <IP> <PORT>\n", argv[0]);
	}
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)//WSAStartup 함수가 0을 반환하지 않는다는것은 실패한 것.
		error_handling("WSAStartup() error");//notify error..!
	hSocket = socket(PF_INET, SOCK_STREAM, 0);//IPv4 internet protocol sys with stream type socket
	//위의 socket generate procedure에서 왜 3rd인자가 0일까?
	//ㄴ그냥 dafault status의 socket example로 consist하자
	if (hSocket == INVALID_SOCKET)
		error_handling("hSocket() error");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	//InetPton : 주어진 문자열 형식의 IP 주소를 네트워크 바이트 순서로 된 이진 형태로 변환
	if (InetPton(AF_INET, argv[1], &(servAddr.sin_addr.s_addr)) != 1) {
		error_handling("InetPton() error");
	}

	//what are these use for?
	/*
	* [deprecated code]
	* 
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(argv[1]);
	servAddr.sin_port = htons(atoi(argv[2]));

	*/
	if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)//SOCKET_ERROR have -1 value,
		error_handling("connect() error!");
	
	while (readLen = recv(hSocket, &message[idx++], 1, 0)) {
		//recv함수 호출을 통해 수신된 데이터를 1Byte씩 읽고있다.
		if (readLen == -1)
			error_handling("read() error!");

		strlen += readLen;
		//1 Byte 씩 데이터를 읽기 때문에 문장에서 strlen에 실제로 더해지는 값은 1, 최종 strlen은 recv함수 호출횟수와 같다.
	}
	printf("Message from server : %s\n", message);
	printf("Function read call count : %d\n", strlen);//함수의 호출 횟수 반환
	
	closesocket(hSocket);
	WSACleanup();
	
	return 0;
}

void error_handling(char* message) {
	fputs(message, stderr, _TRUNCATE);
	fputc('\n', stderr);
	_Exit(1);
}
