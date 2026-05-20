#include <stdio.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    int clientsocket, port, num;
    struct sockaddr_in serveraddr;
    socklen_t len;
    char buffer[256];

    clientsocket = socket(AF_INET, SOCK_DGRAM, 0);

    bzero((char*)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;

    printf("Enter the port number: ");
    scanf("%d",&port);

    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    printf("Enter number: ");
    scanf("%d",&num);

    sprintf(buffer,"%d",num);

    sendto(clientsocket, buffer, sizeof(buffer), 0,
           (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    len = sizeof(serveraddr);

    recvfrom(clientsocket, buffer, sizeof(buffer), 0,
            (struct sockaddr*)&serveraddr, &len);

    printf("Result from server: %s\n",buffer);

    close(clientsocket);
}
