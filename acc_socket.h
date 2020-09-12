#ifndef ACC_SOCKET
#define ACC_SOCKET

#include "error.h"
#include "acc.h"

ssize_t acc_socket_read(int sockfd, void* vptr, size_t maxlen);
int acc_listen_daemon(int port, char* returnIp);

#endif