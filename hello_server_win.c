#include<stdio.h>
#include<stdlib.h>
#include<WinSock2.h>
//server side
void ErrorHandling(char* message);

int main(int argc, char* argv) {
	WSADATA wsaData;
	SOCKET hserverSock, hClntSock;
	SOCKADDR_IN servAddr, clntAddr;

	int szClntAddr;
	char message[] = "Hello World1";
	if (argc != 2) {
		print("Usage : %s <port >\n", argv[0]);		//string 을 통째로 가져오는 것 같음!
		exit(1);//?
	}

	//winsock2 라이브러리 초기화 진행
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	hserverSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hserverSock == INVALID_SOCKET)
		ErrorHandling("socket() Error!");
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(argv[1]));

	//(SOCKADDR*) &servAddr 해당 구문은 강제 형 변환이다.
	if (bind(hserverSock,(SOCKADDR*) &servAddr,sizeof(servAddr)) == SOCKET_ERROR)
		ErrorHandling("socket() Error!");
	if (listen(hserverSock, 5) == SOCKET_ERROR)
		Errorhandling("listen() error");

	szClntAddr = sizeof(clntAddr);
	hClntSock = accept(hserverSock, (SOCKADDR*)&clntAddr, &szClntAddr);
	if (hClntSock == INVALID_SOCKET)
		ErrorHandling("accept() error");
	
	//서버측에서 클라이언트로 정보 전송하는 코드
	send(hClntSock, message, sizeof(message), 0);
	closesocket(hClntSock);
	closesocket(hserverSock);

	WSACleanup();//초기화된 라이브러리의 해제방법

	return 0;
}
void ErrorHandling(char* message) {
	fputs(message, stderr);
	//fputs(message, stderr);는 message 문자열을 터미널에 오류 메시지로 출력합니다.
	fputc('\n', stderr);
	exit(1);
}
