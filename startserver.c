#include "acc_socket.h"
#include "storage_server.h"
#include "signal.h"

int main(void)
{

    int     connfd;
    char    ip[__IPV4_STR_LEN];
    ssize_t n;
    void    sig_chld(int);

    /* a child process returns a connection */
    if ((connfd = acc_listen_daemon(SERV_TCP_PORT, ip)) < 0)
    {
        fprintf(stderr, "Failed to connect to socket\n");
        exit(0);
    }

    start_storage_srv(stdout, connfd);
    return 0;
}
