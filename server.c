#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include <string.h>
#include <dirent.h>
//#include <pthread.h>

int main(){

	struct sockaddr_in socketAddr;

	socketAddr.sin_family = AF_INET;						// Familia do endere�o
	socketAddr.sin_port = htons(7000);						// Porta escolhida (htons converte o valor na ordem de bytes da rede)
	socketAddr.sin_addr.s_addr = inet_addr("127.0.0.1");	// Endere�o IP, localhost (inet_addr converte o endere�o para binario em bytes)
	bzero(&(socketAddr.sin_zero), 8);						// Estrutura com zeros sem utilidade (Para prop�sitos futuros)?

	int socketR = socket(AF_INET, SOCK_STREAM, 0);  	// Inicializa o socket. 	(Dom�nio da comunica��o (AF_NET p/ TCP/IP),
														// 							Tipo de comunica��o (TCP/UDP) (SOCK_STREAM p/ TCP)
														//							Protocolo (0))

	if(socketR == -1){	// A fun��o socket() retorna -1 se ocorrer algum erro
		printf ("Error creating the socket");
		return -1;
	}

	int bindR = bind(socketR, (struct sockaddr *)&socketAddr, sizeof(socketAddr));	// Associa o socket criado com a porta do SO

	if(bindR == -1){	// A fun��o bind() retorna -1 se ocorrer algum erro e 0 caso contr�rio
		printf("Error in function bind\n");
		return -1;
	}

	int listenR = listen(socketR, 10); 		// Habilita o socket pra receber as conex�es atrav�s do descritor (socketR) do socket

	if(listenR == -1){
		printf("Error in function listen\n");
		return -1;
	}

	while(1){

		int acceptR = accept(socketR, (struct sockaddr*)NULL, NULL); 	// Aceita conex�es

		if(acceptR == -1){
			printf("Error in function accept\n");
			return -1;
		}

		printf("Socket criado: %d\n", acceptR);
	}


	return 0;
}
