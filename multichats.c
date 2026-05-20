#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUF_SIZE 2000

int main()
{
    int sockfd, newsockfd, port;
    struct sockaddr_in addr, cl_addr;
    socklen_t len;
    char buffer[BUF_SIZE];
    pid_t pid;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    printf("Enter port number: ");
    scanf("%d",&port);

    memset(&addr,0,sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));

    listen(sockfd,5);

    printf("Server waiting for connection...\n");

    while(1)
    {
        len = sizeof(cl_addr);
        newsockfd = accept(sockfd,(struct sockaddr*)&cl_addr,&len);

        printf("Client connected\n");

        pid = fork();

        if(pid==0)
        {
            close(sockfd);

            while(1)
            {
                memset(buffer,0,BUF_SIZE);

                recv(newsockfd,buffer,BUF_SIZE,0);
                printf("Client: %s",buffer);

                send(newsockfd,buffer,BUF_SIZE,0);
            }
        }

        close(newsockfd);
    }
}
