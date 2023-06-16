#ifndef _HEADER_H
#define _HEADER_H

#define _GNU_SOURCE
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>

#define BUFFER_FILENAME "buffer.bin"
#define SORTED_FILENAME "sorted.bin"
#define N 8192

typedef struct index_s {
    double time_mark;       
    uint64_t recno;         
} index_s;

typedef struct index_hdr_s {
    uint64_t records;     
    index_s idx[];         
} index_hdr_s;

void print(char *filename, long num) 
{
    index_s index;
    index_hdr_s header;
    size_t read_size;
    long rec_count = 0;
    FILE *f = fopen(filename, "rb");

    if (num == 0 && (read_size = fread(&header, sizeof(index_hdr_s), 1, f)) > 0) 
    {
        printf("\nAMOUNT OF RECORDS: %lu\n", header.records);
        printf("\n");
    }

    while ((read_size = fread(&index, sizeof(index_s), 1, f)) > 0) 
    {
        printf("TIME MARK IS \"%f\" INDEX IS %lu\n", index.time_mark, index.recno);
        ++rec_count;
    }
    printf("\n");

    if(num == 1)
        printf("AMOUNT OF RECORDS: %lu\n", rec_count);
    
    fclose(f); 
}

#endif