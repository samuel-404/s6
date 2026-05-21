#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {

    int clientsocket;
    struct sockaddr_in serveraddr;

    int a[2][2], b[2][2], sum[2][2];

    clientsocket = socket(AF_INET, SOCK_STREAM, 0);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(9001);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(clientsocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    printf("Enter elements of first 2x2 matrix:\n");

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    printf("Enter elements of second 2x2 matrix:\n");

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            scanf("%d", &b[i][j]);
        }
    }

    write(clientsocket, a, sizeof(a));
    write(clientsocket, b, sizeof(b));

    read(clientsocket, sum, sizeof(sum));

    printf("Sum Matrix:\n");

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            printf("%d ", sum[i][j]);
        }
        printf("\n");
    }

    close(clientsocket);

    return 0;
}