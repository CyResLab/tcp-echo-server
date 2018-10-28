
/* Sample TCP server */

#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>

#define WELCOME_MSG "Welcome to TCP echo!\n"

int perform_action(struct sockaddr_in cliaddr, int connfd,
socklen_t clilen) {
	int n;
	char mesg[1000];
    sendto(connfd,WELCOME_MSG,strlen(WELCOME_MSG),0,
        (struct sockaddr *)&cliaddr,sizeof(cliaddr));
	n = recvfrom(connfd,mesg,1050,0,(struct sockaddr *)&cliaddr,&clilen);
	sendto(connfd,mesg,n,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
	printf("-------------------------------------------------------\n");
	//mesg[n] = 0;
	printf("Received the following:\n%p\n",mesg);
	printf("%s",mesg);
	printf("-------------------------------------------------------\n");
	return 0;   
}

int main(int argc, char**argv)
{
	int listenfd,connfd;
	struct sockaddr_in servaddr,cliaddr;
	socklen_t clilen;
	pid_t	 childpid;

	listenfd=socket(AF_INET,SOCK_STREAM,0);
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int));

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_LOOPBACK);
	servaddr.sin_port=htons(5000);
	bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

	listen(listenfd,1024);

	for(;;)
	{
		clilen=sizeof(cliaddr);
		connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen);

		perform_action(cliaddr, connfd, clilen);
		
		close(connfd);
	}

	close (listenfd);
}
