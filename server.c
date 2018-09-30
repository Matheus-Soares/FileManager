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
int create_socket(){
    struct sockaddr_in socketAddr;

    //Configuracao do socket
	socketAddr.sin_family = AF_INET;						// Familia do endereço
	socketAddr.sin_port = htons(7000);						// Porta escolhida (htons converte o valor na ordem de bytes da rede)
	socketAddr.sin_addr.s_addr = inet_addr("127.0.0.1");	// Endereço IP, localhost (inet_addr converte o endereço para binario em bytes)
	bzero(&(socketAddr.sin_zero), 8);						// Estrutura com zeros sem utilidade (Para propositos futuros)?

	int socketR = socket(AF_INET, SOCK_STREAM, 0);  	// Inicializa o socket. 	(Dominio da comunicacao (AF_NET p/ TCP/IP),
														// 							Tipo de comunicacao (TCP/UDP) (SOCK_STREAM p/ TCP)
														//							Protocolo (0))

	if(socketR == -1){	// A funcao socket() retorna -1 se ocorrer algum erro
		printf ("Error creating the socket");
		return -1;
	}

	int bindR = bind(socketR, (struct sockaddr *)&socketAddr, sizeof(socketAddr));	// Associa o socket criado com a porta do SO

	if(bindR == -1){	// A funcao bind() retorna -1 se ocorrer algum erro e 0 caso contrario
		printf("Error in function bind\n");
		return -1;
	}

	int listenR = listen(socketR, 10); 		// Habilita o socket pra receber as conexoes através do descritor (socketR) do socket

	if(listenR == -1){
		printf("Error in function listen\n");
		return -1;
	}

	return socketR;
}

void* menu(void* acceptR_){
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


        /* Primeiro mkdir feito:

        if (strncmp(recvBuffer, "mkdir ", 6) == 0){

            recvBuffer[recvR] = '\0';

            memmove(recvBuffer, recvBuffer+6, strlen(recvBuffer)); //Copia pro recvBuffer, iniciando no indice recvBuffer+6, indo ate o final do recvBuffer.
            printf("Palavra final %s\n", recvBuffer);

            status = mkdir(recvBuffer, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

            if(status == 0){
                printf("Pasta criada com sucesso!\n");
            }
        }
        */


        if (strncmp(recvBuffer, "mkdir ", 6) == 0){      //criar (sub)diretorio
            pthread_mutex_lock(&cadeado);
            system(recvBuffer);
            pthread_mutex_unlock(&cadeado);
        }

        if (strncmp(recvBuffer, "rm -r ", 6) == 0){      //remover (sub)diretorio
            pthread_mutex_lock(&cadeado);
            system(recvBuffer);
            pthread_mutex_unlock(&cadeado);
        }

        if (strncmp(recvBuffer, "cd ", 3) == 0){         //entrar em (sub)diretorio
            pthread_mutex_lock(&cadeado);
            system(recvBuffer);
            pthread_mutex_unlock(&cadeado);
        }

        if (strcmp(recvBuffer, "ls\n") == 0){            //mostrar conteudo do diretorio
            pthread_mutex_lock(&cadeado);
            system(recvBuffer);

            system("ls > a.txt");
            //system("ls > a.txt");
            pthread_mutex_unlock(&cadeado);

            //send(*acceptR, , strlen(RESULTADO DO LS), 0);
        }

        if (strncmp(recvBuffer, "touch ", 6) == 0){      //criar arquivo
            pthread_mutex_lock(&cadeado);
            system(recvBuffer);
            pthread_mutex_unlock(&cadeado);
        }

        if (strncmp(recvBuffer, "rm ", 3) == 0){         //remover arquivo
            pthread_mutex_lock(&cadeado);
            system(recvBuffer);
            pthread_mutex_unlock(&cadeado);
        }

        if (strncmp(recvBuffer, "echo ", 5) == 0){       //escrever um sequencia de caracteres em um arquivo
            pthread_mutex_lock(&cadeado);
            system(recvBuffer);
            pthread_mutex_unlock(&cadeado);
        }

        if (strncmp(recvBuffer, "cat ", 4) == 0){        //mostrar conteudo do arquivo
            pthread_mutex_lock(&cadeado);
            system(recvBuffer);
            pthread_mutex_unlock(&cadeado);
        }
    }
}


int main(){

    int socketR = create_socket();

	while(1){

		int acceptR = accept(socketR, (struct sockaddr*)NULL, NULL); 	// Aceita conexoes

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

    //pthread_mutex_destroy(&cadeado); ????????????

	return 0;
}
