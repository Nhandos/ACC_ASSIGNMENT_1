#ifndef STORAGE_CLIENT_H
#define STORAGE_CLIENT_H

#include "acc.h"

#define MAX_COMMAND_LEN
#define MAX_COMMAND_ARGS

enum command
{
    STORE,
    GET,
    DELETE,
    HISTORY,
    QUIT,
    INVALID
};

typedef struct payload
{
    enum command command;
    int argc;
    char* argv[MAX_COMMAND_ARGS];
    FILE* fp;

} srv_payload;

void start_storage_cli(FILE *fp, int sockfd);

#endif