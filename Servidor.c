/*
 * Servidor.c
 *
 *  Created on: 22/02/2017
 *      Author: Carlos
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>



char* concat(const char *s1, const char *s2){
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void write_client(int socketfd, char* line) {
	char *tosend = concat(line,"\n");
	send(socketfd, tosend, strlen(tosend),0);
	free(tosend);
}



int main(int argc, char *argv[]){
  /* Estruturas de dados */
  int sockfd, newsockfd, port = 6752;
  socklen_t client_addr_length;
  struct sockaddr_in serv_addr, cli_addr;
  char buf[1024];

  /* Inicializar o socket
     AF_INET - para indicar que queremos usar IP
     SOCK_STREAM - para indicar que queremos usar TCP
     Protocolo =0
	 sockfd - id do socket principal do servidor
     Se retornar < 0 ocorreu um erro */
  sockfd = socket(PF_INET, SOCK_STREAM, 0);

  if (sockfd < 0) {
    printf("Error creating socket\n");
     //exit(-1);
  }

  /* Criar a estrutura que guarda o endereço do servidor
     PF_INET - endereço IP
     INADDR_ANY - aceitar pedidos para qualquer IP */
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);
  serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
  memset(serv_addr.sin_zero, '\0', sizeof(serv_addr.sin_zero));

  /* Fazer bind do socket. Apenas nesta altura é que o socket fica ativo
     mas ainda não estamos a tentar receber ligações.
     Se retornar < 0 ocorreu um erro */
  int res = bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

  if (res < 0) {
    printf("Error binding to socket");
    //exit(-1);
  }

 /* Indicar que queremos escutar no socket com um backlog de 5 (podem
     ficar até 5 ligações pendentes antes de fazermos accept */
  listen(sockfd, 5);


    /* Aceitar uma nova ligação. O endereço do cliente fica guardado em
       cli_addr - endereço do cliente
       newsockfd - id do socket que comunica com este cliente */
    client_addr_length = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &client_addr_length);
	//write_client(newsockfd, "welcome");


	while(1){
		recv(newsockfd,buf,sizeof(buf),0);
		
		send(newsockfd,buf,sizeof(buf),0);
		memset(buf, '\0', sizeof(buf));
	}



	close(sockfd);
	close(newsockfd);

	shutdown(sockfd,2);
	shutdown(newsockfd,2);

  return 0;
}
