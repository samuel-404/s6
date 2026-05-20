#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int serversocket, clientsocket, port;
    int num, temp, rev = 0, rem;

    char result[50];

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

    temp = num;

    while(num > 0)
    {
        rem = num % 10;
        rev = rev * 10 + rem;
        num = num / 10;
    }

    if(temp == rev)
        strcpy(result, "Palindrome Number");
    else
        strcpy(result, "Not Palindrome Number");

    write(clientsocket, result, sizeof(result));

    close(clientsocket);
    close(serversocket);

    return 0;
}
