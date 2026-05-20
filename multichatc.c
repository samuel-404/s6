#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUF_SIZE 2000

int main(int argc,char *argv[])
{
    int sockfd,port;
    struct sockaddr_in addr;
    char buffer[BUF_SIZE];

    sockfd = socket(AF_INET,SOCK_STREAM,0);

    printf("Enter port number: ");
    scanf("%d",&port);

    memset(&addr,0,sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET,argv[1],&addr.sin_addr);

    connect(sockfd,(struct sockaddr*)&addr,sizeof(addr));

    printf("Connected to server\n");

    getchar();

    while(1)
    {
        memset(buffer,0,BUF_SIZE);

        printf("Enter message: ");
        fgets(buffer,BUF_SIZE,stdin);

        send(sockfd,buffer,BUF_SIZE,0);

        memset(buffer,0,BUF_SIZE);

        recv(sockfd,buffer,BUF_SIZE,0);

        printf("Server: %s",buffer);
    }
}
