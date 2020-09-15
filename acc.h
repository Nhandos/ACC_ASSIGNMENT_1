#ifndef ACC_H
#define ACC_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <netdb.h>
#include <sys/uio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/wait.h>

#define __IPV4_STR_LEN 16

#define	MAXLINE	4096
#define	LISTENQ	1024
#define	SERV_TCP_PORT	52001
#define	SA	struct sockaddr
#define	min(a,b)	((a) < (b) ? (a) : (b))
#define	max(a,b)	((a) > (b) ? (a) : (b))
typedef void    Sigfunc(int);

#endif