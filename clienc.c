#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define BUF_LEN 1000

int main(void){
	int sockfd, len, port=6752;
	struct sockaddr_in serv;
	socklen_t addlen= sizeof(serv);
	char buf[BUF_LEN];
	
	sockfd = socket(PF_INET,SOCK_STREAM,0);
	if (sockfd < 0) {
    printf("Error creating socket\n");
     //exit(-1);
	}
	
	
	serv.sin_family=PF_INET;
	serv.sin_port=htons(port);
	inet_aton("127.0.0.1",&serv.sin_addr);
	
	int i =connect(sockfd,(struct sockaddr *) &serv,addlen);
	
	if(i<0){
		printf("Erro no connect \n");
		return 1;
	}
	
	printf("Mensagem a ser enviada: ");
	scanf("%s", buf);
	strcat(buf,"\n");
	len=send(sockfd,buf,strlen(buf)+1,0);

	len=recv(sockfd,buf,strlen(buf),0);
	printf("resposta do servidor : %s\n", buf);
	
	
	close(sockfd);
	shutdown(sockfd,2);
	
}