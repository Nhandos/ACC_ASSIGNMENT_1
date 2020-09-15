#include 	<string.h>
#include    "acc_socket.h"

/* systems signal handler for SIGCHLD */
void sig_chld(int signo)
{
	pid_t pid;
	int stat;

	while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0) {
 #ifdef DEBUG /* avoid using I/O in system call, only for debug */
		printf("%d > terminated %d\n", getpid(), pid);
 #endif   
	}

	return;
}

/* Reads a message from a socket until an EOF character is reached */
ssize_t acc_socket_read(int fd, char *ptr)
{
	static int	read_cnt = 0;
	static char	*read_ptr;
	static char	read_buf[MAXLINE];

	if (read_cnt <= 0) {
again:
		if ( (read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0) {
			if (errno == EINTR)
				goto again;
			return(-1);
		} else if (read_cnt == 0)
			return(0);
		read_ptr = read_buf;
	}

	read_cnt--;
	*ptr = *read_ptr++;
	return(1);
}

ssize_t acc_socket_readline(int sockfd, void* vptr, size_t maxlen)
{
	int		n, rc;
	char	c, *ptr;

	ptr = vptr;
	for (n = 1; n < maxlen; n++) {
		if ( (rc = acc_socket_read(sockfd, &c)) == 1) {
			*ptr++ = c;
			if (c == '\n')
				break;	/* newline is stored, like fgets() */
		} else if (rc == 0) {
			if (n == 1)
				return(0);	/* EOF, no data read */
			else
				break;		/* EOF, some data was read */
		} else
			return(-1);		/* error, errno set by read() */
	}

	*ptr = 0;	/* null terminate like fgets() */
	return(n);
}

ssize_t						/* Write "n" bytes to a descriptor. */
acc_socket_write(int fd, const void *vptr, size_t n)
{
	size_t		nleft;
	ssize_t		nwritten;
	const char	*ptr;

	ptr = vptr;
	nleft = n;
	while (nleft > 0) {
		if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
			if (errno == EINTR)
				nwritten = 0;		/* and call write() again */
			else
				return(-1);			/* error */
		}

		nleft -= nwritten;
		ptr   += nwritten;
	}
	return(n);
}
/* end writen */

/* Daemon process to listen to a socket */
int acc_listen_daemon(int port, char* returnIp)
{
	int					listenfd, connfd;
	char				buff[__IPV4_STR_LEN];
	pid_t				childpid;
	socklen_t			clilen;
	const char			*ptr;
	struct sockaddr_in	cliaddr, servaddr;


	if ( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		fprintf(stderr, "socket error\n");
		return -1;
	}

	/* Allows bind() to resuse local address */
	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
	{
		fprintf(stderr, "setsockopt failed\n");
		return -1;
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_TCP_PORT); /* daytime server */

	if ( bind(listenfd, (SA *) &servaddr, sizeof(servaddr)) < 0){
		fprintf(stderr, "bind error\n");
		return -1;
	}

	if ( listen(listenfd, LISTENQ) < 0 ){
		fprintf(stderr, "listen error\n");
		return -1;
	}

	printf("%d > Listening on port %d\n", getpid(), port);
	for ( ; ; ) {
		/* signal should not be inside the loop, but I can't get it to work otherwise */
		signal(SIGCHLD, sig_chld);
		
		clilen = sizeof(cliaddr);
		if ( (connfd = accept(listenfd, (SA *) &cliaddr, &clilen)) < 0) {
			if (errno == EINTR) /* If a system interrupt occur */
			{
				continue;	/* back to fork() */
			}	
			else
			{
				fprintf(stderr, "accept error\n");
				return -1;
			}
		}

		/* Retrieve IP in text form */
		ptr = inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff));
		if ( ptr  == NULL ) {
			if (errno == EINTR) /* If a interrupt occured */
			{
				continue; /* back to fork() */
			}
			else
			{
				fprintf(stderr, "inet_ntop error\n");
				return -1;
			}
		}

		if ( (childpid = fork()) == 0) {	/* child process */
			close(listenfd);
			break;
		}
	}

	strncpy(returnIp, buff, __IPV4_STR_LEN);
	printf("%d > connected with IP: %s\n", getpid(), returnIp);
	return connfd;
} /* acc_listen_daemon() */
