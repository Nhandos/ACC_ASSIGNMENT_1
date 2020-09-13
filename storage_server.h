#ifndef STORAGE_SERVER_H
#define STORAGE_SERVER_H

#define MAX_COMMAND_LEN 4096
#define MAX_COMMAND_ARGS 10

enum command
{
    STORE,
    GET,
    DELETE,
    HISTORY,
    QUIT,
    INVALID
};

int assert_command_args(int command, int argc, char** argv);
int await_cli_command(int socketfd, int* argc, char** argv);

#endif