#include "acc_socket.h"
#include "storage_server.h"


int main(void)
{

    int     connfd;
    char    ip[__IPV4_STR_LEN];
    ssize_t n;
    char    line[MAXLINE];
    int     command;
    void	sig_chld(int);

    int     argc;
    char*   argv[MAX_COMMAND_ARGS]; 

	signal(SIGCHLD, sig_chld);	/* must call waitpid() */

    if ((connfd = acc_listen_daemon(SERV_TCP_PORT, ip)) < 0)
    {
        fprintf(stderr, "Failed to connect to socket\n");
        exit(0);
    }

    printf("Accepted a connection from %s\n", ip);

    for ( ;; )
    {
        command = await_cli_command(connfd, &argc, argv);
        printf("Command = %d\n", command);

        if (command == QUIT)
        {
            close(connfd);
            printf("Exiting...");
            exit(0);
        }
    }

    return 0;
}
