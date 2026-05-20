#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int serversocket, port;
    int n, a = 0, b = 1, c, i;

    char fib[200] = "";

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
             &n,
             sizeof(n),
             0,
             (struct sockaddr*)&clientaddr,
             &len);

    char temp[20];

    for(i = 0; i < n; i++)
    {
        sprintf(temp, "%d ", a);
        strcat(fib, temp);

        c = a + b;
        a = b;
        b = c;
    }

    sendto(serversocket,
           fib,
           sizeof(fib),
           0,
           (struct sockaddr*)&clientaddr,
           len);

    close(serversocket);

    return 0;
}
