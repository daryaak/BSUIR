#ifndef LAB08_HEADER_H
#define LAB08_HEADER_H
#define _GNU_SOURCE
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <pthread.h>
#include <dirent.h>
#include <ctype.h>
#include <signal.h>
#include <stdbool.h>

#define SERVER_FTP_PORT 1231
#define MAX_CLIENTS 11

#define h_addr h_addr_list[0]

#define SERVER_FTP_PORT 1231
#define DATA_CONNECTION_PORT SERVER_FTP_PORT +1

#define GOOD 0                                       
#define ERROR_INVALID_HOST_NAME -1
#define ERROR_CREATE_SOCKET_FAILED -2
#define ERROR_BIND_FAILED -3
#define ERROR_CONNECT_FAILED -4
#define ERROR_SEND_FAILED -5
#define ERROR_RECEIVE_FAILED -6

void lower(char *str)
{
    int i = 0;

    for (; i < (int) strlen(str); i++)
    {
        str[i] = tolower(str[i]);
    }
}

#endif //LAB08_HEADER_H