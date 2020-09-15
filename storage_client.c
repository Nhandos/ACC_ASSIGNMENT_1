#include    "acc.h"
#include    "acc_socket.h"

void start_storage_cli(FILE *fp, int sockfd)
{
	int		maxfdp1;
	fd_set		rset;
	char		sendline[MAXLINE], recvline[MAXLINE];

	FD_ZERO(&rset);
	for ( ; ; ) {
		FD_SET(fileno(fp), &rset);
		FD_SET(sockfd, &rset);
		maxfdp1 = max(fileno(fp), sockfd) + 1;
		select(maxfdp1, &rset, NULL, NULL, NULL);

		if (FD_ISSET(sockfd, &rset)) {	/* socket is readable */
			if (acc_socket_readline(sockfd, recvline, MAXLINE) == 0)
            {
                fprintf(stderr, "server terminated prematurely\n");
                return;
            }
			fputs(recvline, stdout);
		}

		if (FD_ISSET(fileno(fp), &rset)) {  /* input is readable */
			if (fgets(sendline, MAXLINE, fp) == NULL)
				return;		/* all done */
			acc_socket_write(sockfd, sendline, strlen(sendline));
		}
	}
}


