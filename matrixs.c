#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {

    int serversocket, clientsocket;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t addrsize;

    int a[2][2], b[2][2], sum[2][2];

    serversocket = socket(AF_INET, SOCK_STREAM, 0);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(9001);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    bind(serversocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    listen(serversocket, 5);

    printf("Waiting for connection...\n");

    addrsize = sizeof(clientaddr);

    clientsocket = accept(serversocket, (struct sockaddr*)&clientaddr, &addrsize);

    read(clientsocket, a, sizeof(a));
    read(clientsocket, b, sizeof(b));

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            sum[i][j] = a[i][j] + b[i][j];
        }
    }

    write(clientsocket, sum, sizeof(sum));

    printf("Matrix addition completed.\n");

    close(clientsocket);
    close(serversocket);

    return 0;
}