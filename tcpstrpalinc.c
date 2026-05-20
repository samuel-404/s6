#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int clientsocket, port;

    char str[100], result[50];

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

    printf("Enter String: ");
    scanf("%s", str);

    write(clientsocket, str, sizeof(str));

    read(clientsocket, result, sizeof(result));

    printf("%s\n", result);

    close(clientsocket);

    return 0;
}
