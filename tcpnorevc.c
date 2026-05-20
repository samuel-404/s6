#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int clientsocket, port;
    int num, rev;

    struct sockaddr_in serveraddr;

    clientsocket = socket(AF_INET, SOCK_STREAM, 0);

    memset(&serveraddr, 0, sizeof(serveraddr));

    printf("Enter Port Number: ");
    scanf("%d", &port);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(clientsocket,
            (struct sockaddr*)&serveraddr,
            sizeof(serveraddr));

    printf("Enter Number: ");
    scanf("%d", &num);

    write(clientsocket, &num, sizeof(num));

    read(clientsocket, &rev, sizeof(rev));

    printf("Reversed Number = %d\n", rev);

    close(clientsocket);

    return 0;
}
