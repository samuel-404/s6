#include <stdio.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>

int factorial(int n)
{
    if(n==0 || n==1)
        return 1;
    return n * factorial(n-1);
}

int main()
{
    int serversocket, port, num, result;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t len;
    char buffer[256];

    serversocket = socket(AF_INET, SOCK_DGRAM, 0);

    bzero((char*)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;

    printf("Enter the port number: ");
    scanf("%d",&port);

    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    bind(serversocket,(struct sockaddr*)&serveraddr,sizeof(serveraddr));

    printf("Waiting for client message...\n");

    len = sizeof(clientaddr);

    recvfrom(serversocket, buffer, sizeof(buffer), 0,
            (struct sockaddr*)&clientaddr, &len);

    sscanf(buffer,"%d",&num);

    result = factorial(num);

    sprintf(buffer,"Factorial of %d is %d",num,result);

    sendto(serversocket, buffer, sizeof(buffer), 0,
           (struct sockaddr*)&clientaddr, len);

    close(serversocket);
}
