#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int clientsocket, port, n;

    char fib[200];

    struct sockaddr_in serveraddr;
    socklen_t len;

    clientsocket = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&serveraddr, 0, sizeof(serveraddr));

    printf("Enter Port Number: ");
    scanf("%d", &port);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter Limit: ");
    scanf("%d", &n);

    sendto(clientsocket,
           &n,
           sizeof(n),
           0,
           (struct sockaddr*)&serveraddr,
           sizeof(serveraddr));

    len = sizeof(serveraddr);

    recvfrom(clientsocket,
             fib,
             sizeof(fib),
             0,
             (struct sockaddr*)&serveraddr,
             &len);

    printf("Fibonacci Series: %s\n", fib);

    close(clientsocket);

    return 0;
}
