#include <string.h>
#include "acc.h"
#include "acc_socket.h"
#include "storage_client.h"

int main(int argc, char** argv)
{
    int                sockfd;
    struct sockaddr_in servaddr;

    if (argc != 2){
        fprintf(stderr, "usage: client <IPAddress>\n");
        exit(0);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        fprintf(stderr, "socket error\n");
        exit(1);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_TCP_PORT);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    if ((connect(sockfd, (SA *) &servaddr, sizeof(servaddr))) < 0){
        fprintf(stderr, "connect error\n");
        exit(1);
    }

    start_storage_cli(stdin, sockfd); /* run storage client */

    return 0;
}