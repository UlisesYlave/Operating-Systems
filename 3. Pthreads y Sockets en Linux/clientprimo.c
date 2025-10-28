#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
    int sockfd;
    int len;
    struct sockaddr_in address;
    int num = 3;
    bool server_result;
    int connect_result;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(1);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(9734);
    len = sizeof(address);

    connect_result = connect(sockfd, (struct sockaddr *)&address, len);
    if (connect_result == -1){
        perror("connect");
        close(sockfd);
        exit(1);
    }

    // Enviar número
    if (write(sockfd, &num, sizeof(num)) != sizeof(num)) {
        perror("write");
        close(sockfd);
        exit(1);
    }

    // Recibir resultado
    if (read(sockfd, &server_result, sizeof(server_result)) != sizeof(server_result)) {
        perror("read");
        close(sockfd);
        exit(1);
    }

    if (server_result == true) printf("NUM: %d, RESULT SERVER: Es primo\n", num);
    else printf("NUM: %d, RESULT SERVER: No es primo\n", num);

    close(sockfd);
    exit(0);
}