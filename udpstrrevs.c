#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int serversocket, port, i, j;

    char str[100], rev[100];

    struct sockaddr_in serveraddr, clientaddr;
    socklen_t len;

    serversocket = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&serveraddr, 0, sizeof(serveraddr));

    printf("Enter Port Number: ");
    scanf("%d", &port);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    bind(serversocket,
         (struct sockaddr*)&serveraddr,
         sizeof(serveraddr));

    printf("Waiting for client...\n");

    len = sizeof(clientaddr);

    recvfrom(serversocket,
             str,
             sizeof(str),
             0,
             (struct sockaddr*)&clientaddr,
             &len);

    printf("String from client: %s\n", str);

    j = 0;

    for(i = strlen(str) - 1; i >= 0; i--)
    {
        rev[j] = str[i];
        j++;
    }

    rev[j] = '\0';

    sendto(serversocket,
           rev,
           strlen(rev) + 1,
           0,
           (struct sockaddr*)&clientaddr,
           len);

    close(serversocket);

    return 0;
}
