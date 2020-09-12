#include "acc_socket.h"


int main(int argc, char** argv)
{

    int connfd;
    char ip[__IPV4_STR_LEN];
    ssize_t n;
    char    line[MAXLINE];

    if ((connfd = acc_listen_daemon(SERV_TCP_PORT, ip)) < 0)
    {
        fprintf(stderr, "Failed to connect to socket\n");
        exit(0);
    }

    for ( ;; )
    {
        if ((n = acc_socket_read(connfd, line, MAXLINE)) == 0)
        {
            printf("Connection closed by other end\n");
            exit(0);
        }        
        
        printf("Received message:\n%s", line);
    }
}