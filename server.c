/*
O sistema deve permitir que arquivos locais sejam acessados por usu�rios remotos simultaneamente.
As opera��es permitidas pelo sistema devem incluir:
criar (sub)diret�rio
remover (sub)diret�rio
entrar em (sub)diret�rio
mostrar conte�do do diret�rio
criar arquivo
remover arquivo
escrever um sequ�ncia de caracteres em um arquivo
mostrar conte�do do arquivo

Etapa 1:
Desenvolver a estrutura de acesso do servidor de arquivos.
Ele dever� ser� acessado via socket TCP. Cada conex�o dever� ser gerida por uma thread.
Condi��es de corrida dever�o ser tratadas por meio de sem�foros ou mutexes.
Nesta etapa voc� n�o precisa implementar as opera��es sobre arquivos listadas acima.
Ao inv�s disso, use as opera��es diretamente do sistema de arquivos do seu sistema operacional.
Recomenda-se que o servidor imprima mensagens na tela para demonstrar o funcionamento ao professor.

Observa��es:
N�o � necess�rio autentica��o dos usu�rios.
N�o � necess�rio criar um aplicativo cliente. Voc� pode usar o aplicativo netcat dispon�vel para Linux e Windows.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include <string.h>
#include <dirent.h>
#include <pthread.h>
#include <sys/stat.h>

//Criar vari�vel do mutex. Deve ser global.
pthread_mutex_t cadeado;


//Defini��o das fun��es
int create_socket(){
    struct sockaddr_in socketAddr;

    //Configura��o do socket
	socketAddr.sin_family = AF_INET;						// Famil�a do endere�o
	socketAddr.sin_port = htons(7000);						// Porta escolhida (htons converte o valor na ordem de bytes da rede)
	socketAddr.sin_addr.s_addr = inet_addr("127.0.0.1");	// Endere�o IP, localhost (inet_addr converte o endere�o para bin�rio em bytes)
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

	return socketR;
}

void* menu(void* acceptR_){
    /*
    criar (sub)diret�rio
    remover (sub)diret�rio
    entrar em (sub)diret�rio
    mostrar conte�do do diret�rio
    criar arquivo
    remover arquivo
    escrever um sequ�ncia de caracteres em um arquivo
    mostrar conte�do do arquivo
    */

    int option = 1;
    int* acceptR = (int*)acceptR_;
    char buffer[1000], recvBuffer[1000];
    int status;

    memset(buffer, 0, sizeof(buffer));

    strcpy(buffer, "Conexao realizada com sucesso!\n\n");

    send(*acceptR, buffer, strlen(buffer), 0);


    while (strcmp(buffer, "exit\n") != 0){

        int recvR = recv(*acceptR, recvBuffer, 100, 0);  //Retorna o tamanho da String que o cliente escreveu
        recvBuffer[recvR] = '\0';                        //Adiciona um \0 ao final da string para indicar seu termino

        /*
        if (strncmp(recvBuffer, "mkdir ", 6) == 0){

            recvBuffer[recvR] = '\0';

            memmove(recvBuffer, recvBuffer+6, strlen(recvBuffer)); //Copia pro recvBuffer, iniciando no indice recvBuffer+6, indo at� o final do recvBuffer.
            printf("Palavra final %s\n", recvBuffer);

            status = mkdir(recvBuffer, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

            if(status == 0){
                printf("Pasta criada com sucesso!\n");
            }
        }
        */

        if (strncmp(recvBuffer, "mkdir ", 6) == 0)
            system(recvBuffer);

        if (strncmp(recvBuffer, "rm -r ", 6) == 0)
            system(recvBuffer);

        if (strncmp(recvBuffer, "cd ", 3) == 0)
            system(recvBuffer);

        if (strcmp(recvBuffer, "ls\n") == 0)
            system(recvBuffer);

        if (strncmp(recvBuffer, "touch ", 6) == 0)
            system(recvBuffer);

        if (strncmp(recvBuffer, "rm ", 3) == 0)
            system(recvBuffer);

        if (strncmp(recvBuffer, "echo ", 5) == 0)
            system(recvBuffer);

        if (strncmp(recvBuffer, "cat ", 4) == 0)
            system(recvBuffer);
    }
}



int main(){

    int socketR = create_socket();

	while(1){

		int acceptR = accept(socketR, (struct sockaddr*)NULL, NULL); 	// Aceita conex�es

		if(acceptR == -1){
			printf("Error in function accept\n");
			return -1;
		}

		//Inicia o mutex
        pthread_mutex_init(&cadeado, NULL);

        pthread_t tid;

        printf("\nCriando thread.\n");
        pthread_create(&tid, NULL, menu, &acceptR);

		printf("Socket criado: %d\n", acceptR);
	}


	return 0;
}
