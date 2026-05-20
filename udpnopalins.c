#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int serversocket, port;
    int num, temp, rev = 0, rem;

    char result[50];

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
             &num,
             sizeof(num),
             0,
             (struct sockaddr*)&clientaddr,
             &len);

    printf("Number from client: %d\n", num);

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

    sendto(serversocket,
           result,
           strlen(result) + 1,
           0,
           (struct sockaddr*)&clientaddr,
           len);

    close(serversocket);

    return 0;
}
