#ifndef ACC_SOCKET
#define ACC_SOCKET

#include "error.h"
#include "acc.h"

void acc_setup(void);
ssize_t acc_socket_read(int fd, char *ptr);
ssize_t acc_socket_readline(int sockfd, void* vptr, size_t maxlen);
ssize_t acc_socket_write(int fd, const void *vptr, size_t n);
int acc_listen_daemon(int port, char* returnIp);

#endif