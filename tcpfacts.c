#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int serversocket, clientsocket, port;
    int num, fact = 1, i;

    struct sockaddr_in serveraddr, clientaddr;
    socklen_t len;

    serversocket = socket(AF_INET, SOCK_STREAM, 0);

    memset(&serveraddr, 0, sizeof(serveraddr));

    printf("Enter Port Number: ");
    scanf("%d", &port);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    bind(serversocket,
         (struct sockaddr*)&serveraddr,
         sizeof(serveraddr));

    listen(serversocket, 5);

    len = sizeof(clientaddr);

    clientsocket = accept(serversocket,
                          (struct sockaddr*)&clientaddr,
                          &len);

    read(clientsocket, &num, sizeof(num));

    for(i = 1; i <= num; i++)
    {
        fact = fact * i;
    }

    write(clientsocket, &fact, sizeof(fact));

    close(clientsocket);
    close(serversocket);

    return 0;
}
