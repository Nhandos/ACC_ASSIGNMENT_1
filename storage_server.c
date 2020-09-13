#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "acc.h"
#include "acc_socket.h"
#include "storage_server.h"

/*
 * Remove trailing white space characters from string
 * cite: https://codeforwin.org/2016/04/c-program-to-trim-trailing-white-space-characters-in-string.html
 */
static void trim_trailing(char * str)
{
    int index, i;

    /* Set default index */
    index = -1;

    /* Find last index of non-white space character */
    i = 0;
    while(str[i] != '\0')
    {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            index= i;
        }

        i++;
    }

    /* Mark next character to last non-white space character as NULL */
    str[index + 1] = '\0';
}

/* converts to upper using pointer reference */
static void to_upper(char* str)
{
    char *p;
    for(p=str; *p; p++) 
    {
        *p=toupper(*p);
    }
}

/* Asserts the correct number of arguments for a command. 
 * Return (0) if pass else (-1)
 */
int assert_command_args(int command, int argc, char** argv)
{
    if (( command == STORE && argc != 2 ) ||
        ( command == GET && argc != 3 ) ||
        ( command == DELETE && argc != 1 ) ||
        ( command == HISTORY && argc != 2))
    {
        return -1;
    }

    return 0;
}

/* Waits for a command from the client. Arguments will be stored in an array of
 * strings
 */
int await_cli_command(int sockfd, int* argc, char** argv)
{

    char        buffer[MAX_COMMAND_LEN];
    ssize_t     n;
    char*       token;
    int         n_token;
    
    if ((n = acc_socket_read(sockfd, buffer, MAXLINE)) < 0)
    {
        fprintf(stderr, "socket read error\n");
        return INVALID;
    }

    /* Check if EOF was sent */
    if (n == 0)
    {
        return QUIT;
    }

    /* Tokenize */
    n_token = 0;
    token = strtok(buffer, " ");
    while( token != NULL && n_token < MAX_COMMAND_ARGS) /* count token */
    {
        argv[n_token] = token;
        trim_trailing(argv[n_token++]);
        token = strtok(NULL, " "); /* get next token */
    }

    /* converts first argument which is the command to upper */
    to_upper(argv[0]);

    if( strcmp(argv[0], "STORE") == 0 )
    {
        return STORE;
    }
    else if( strcmp(argv[0], "GET" ) == 0 )
    {
        return GET;
    }
    else if( strcmp(argv[0], "DELETE" ) == 0 )
    {
        return DELETE;
    }
    else if( strcmp(argv[0], "HISTORY" ) == 0 )
    {
        return HISTORY;
    }
    else if( strcmp(argv[0], "QUIT" ) == 0 )
    {
        return QUIT;
    }
    else 
    {
        return INVALID;
    }
}

