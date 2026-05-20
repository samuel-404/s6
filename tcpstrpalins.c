#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int serversocket, clientsocket, port;
    int i, j = 0;

    char str[100], rev[100], result[50];

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

    read(clientsocket, str, sizeof(str));

    for(i = strlen(str) - 1; i >= 0; i--)
    {
        rev[j] = str[i];
        j++;
    }

    rev[j] = '\0';

    if(strcmp(str, rev) == 0)
        strcpy(result, "Palindrome String");
    else
        strcpy(result, "Not Palindrome String");

    write(clientsocket, result, sizeof(result));

    close(clientsocket);
    close(serversocket);

    return 0;
}
