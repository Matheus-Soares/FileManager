/*
O sistema deve permitir que arquivos locais sejam acessados por usuarios remotos simultaneamente.
As operacoes permitidas pelo sistema devem incluir:
criar (sub)diretorio
remover (sub)diretorio
entrar em (sub)diretorio
mostrar conteudo do diretorio
criar arquivo
remover arquivo
escrever um sequencia de caracteres em um arquivo
mostrar conteudo do arquivo

Etapa 1:
Desenvolver a estrutura de acesso do servidor de arquivos.
Ele devera sera acessado via socket TCP. Cada conexao devera ser gerida por uma thread.
Condicoes de corrida deverao ser tratadas por meio de semaforos ou mutexes.
Nesta etapa voce nao precisa implementar as operacoes sobre arquivos listadas acima.
Ao inves disso, use as operacoes diretamente do sistema de arquivos do seu sistema operacional.
Recomenda-se que o servidor imprima mensagens na tela para demonstrar o funcionamento ao professor.

Observações:
Não e necessario autenticacao dos usuarios.
Não e necessario criar um aplicativo cliente. Voce pode usar o aplicativo netcat disponivel para Linux e Windows.
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

//Criar variavel do mutex. Deve ser global.
pthread_mutex_t cadeado;

//Definição das funcoes
int create_socket();
void* menu(void* acceptR_);


int main(){

    int socketR = create_socket();

	while(1){
        // Aceita conexoes
		int acceptR = accept(socketR, (struct sockaddr*)NULL, NULL);

		if(acceptR == -1){
			printf("Error in function accept\n");
			return -1;
		}

		//Inicia o mutex
        //pthread_mutex_init(&cadeado, NULL);

        pthread_t tid;

        printf("\nCriando thread.\n");
        pthread_create(&tid, NULL, menu, &acceptR);
	}

	return 0;
}



int create_socket(){
    struct sockaddr_in socketAddr;

    //Configuracao do socket
	socketAddr.sin_family = AF_INET;						// Familia do endereço
	socketAddr.sin_port = htons(7000);						// Porta escolhida (htons converte o valor na ordem de bytes da rede)
	socketAddr.sin_addr.s_addr = inet_addr("127.0.0.1");	// Endereço IP, localhost (inet_addr converte o endereço para binario em bytes)
	bzero(&(socketAddr.sin_zero), 8);						// Prevencao de bug para arquiteturas diferentes


	/* Inicializa o socket:
    Dominio da comunicacao (AF_NET p/ TCP/IP),
    Tipo de comunicacao (TCP/UDP) (SOCK_STREAM p/ TCP)
    Protocolo (0) */
	int socketR = socket(AF_INET, SOCK_STREAM, 0);
	if(socketR == -1){
		printf ("Erro ao criar o socket.\n");
		exit(0);
	}

	//Associa o socket criado com a porta do SO
	int bindR = bind(socketR, (struct sockaddr *)&socketAddr, sizeof(socketAddr));
	if(bindR == -1){
		printf("Erro na funcao bind.\n");
		exit(0);
	}

    //Habilita o socket pra receber as conexoes atraves do descritor (socketR) do socket
	int listenR = listen(socketR, 10);
	if(listenR == -1){
		printf("Erro na funcao listen.\n");
		exit(0);
	}

	return socketR;
}


void* menu(void* acceptR_){
    int* conexao = (int*)acceptR_;
    char sendBuffer[1024], recvBuffer[1024];

    memset(sendBuffer, 0, sizeof(sendBuffer));

    strcpy(sendBuffer, "Conexao realizada com sucesso!\n\n");
    send(*conexao, sendBuffer, strlen(sendBuffer), 0);

    while (strcmp(recvBuffer, "exit\n") != 0){

        //Retorna o tamanho da String que o cliente escreveu
        int recvR = recv(*conexao, recvBuffer, 100, 0);

        //Adiciona um \0 ao final da string para indicar seu termino
        recvBuffer[recvR] = '\0';

        //criar (sub)diretorio
        if (strncmp(recvBuffer, "mkdir ", 6) == 0){
            pthread_mutex_lock(&cadeado);
            system(recvBuffer);
            pthread_mutex_unlock(&cadeado);
        }

        //remover (sub)diretorio
        if (strncmp(recvBuffer, "rm -r ", 6) == 0){
            pthread_mutex_lock(&cadeado);
            system(recvBuffer);
            pthread_mutex_unlock(&cadeado);
        }

        //entrar em (sub)diretorio
        if (strncmp(recvBuffer, "cd ", 3) == 0){
            pthread_mutex_lock(&cadeado);
            system(recvBuffer);
            pthread_mutex_unlock(&cadeado);
        }

        //mostrar conteudo do diretorio
        if (strcmp(recvBuffer, "ls\n") == 0){
            pthread_mutex_lock(&cadeado);
            system(recvBuffer);
            pthread_mutex_unlock(&cadeado);
            //system("ls > a.txt");
        }

        //criar arquivo
        if (strncmp(recvBuffer, "touch ", 6) == 0){
            pthread_mutex_lock(&cadeado);
            system(recvBuffer);
            pthread_mutex_unlock(&cadeado);
        }

        //remover arquivo
        if (strncmp(recvBuffer, "rm ", 3) == 0){
            pthread_mutex_lock(&cadeado);
            system(recvBuffer);
            pthread_mutex_unlock(&cadeado);
        }

        //escrever um sequencia de caracteres em um arquivo
        if (strncmp(recvBuffer, "echo ", 5) == 0){
            pthread_mutex_lock(&cadeado);
            system(recvBuffer);
            pthread_mutex_unlock(&cadeado);
        }

        //mostrar conteudo do arquivo
        if (strncmp(recvBuffer, "cat ", 4) == 0){
            pthread_mutex_lock(&cadeado);
            system(recvBuffer);
            pthread_mutex_unlock(&cadeado);
        }
    }
}
