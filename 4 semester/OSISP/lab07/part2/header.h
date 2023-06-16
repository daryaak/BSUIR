#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>

#define LENGHT 80
#define AMOUNT_OF_RECORDS 11

typedef struct record_s{
    char name[LENGHT];
    char address[LENGHT];
    uint8_t semester;
}record_s;

int fd;
struct flock lock;
const char *file = "file.txt";
record_s current = {0};
int number = 0;
record_s tmp_rec = {0};