#ifndef LAB04_HEADER_H
#define LAB04_HEADER_H

#define _GNU_SOURCE
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <inttypes.h>

#define SIZE 256
#define DATA (((SIZE + 3) / 4) * 4)
#define MAX_AMOUNT 111
#define BUFFER_SIZE 8

typedef struct{
    uint8_t type;
    uint16_t hash;
    uint8_t size;
    uint8_t data[DATA];
} message;                   

typedef struct{
    int inc;
    int dec;
    int head;
    int tail;
    message buffer[BUFFER_SIZE + 1];
} queue;                   


queue *q;
sem_t *mutex;
sem_t *free_space;
sem_t *items;

bool check = false;


void end()
{
    if(sem_close(mutex) == -1 || sem_close(free_space)== -1 || sem_close(items) == -1)                   
    {
        perror("sem_close");
        exit(errno);
    }
    if(munmap(q, sizeof(queue)) == -1)             
    {
        perror("munmap");
        exit(errno);
    }
}

void signalhandler(int signal)
{
    if(signal == SIGUSR1)
    {
        int value;
        sem_getvalue(free_space, &value);
        if(value)
        { 
            check = true;
        }
        else 
        {
            end();
        }
    }
}

void *sharemem()
{
    int f = shm_open("que", O_RDWR, (S_IRUSR | S_IWUSR));
    if(f == -1)
    {
        perror("shm_open");
        exit(errno);
    }
    void *pointer = mmap(NULL, sizeof(queue), PROT_READ | PROT_WRITE, MAP_SHARED, f, 0);
    if(!pointer)
    {
        perror("mmap");
        exit(errno);
    }
    return pointer;
}

void begin()
{
    struct sigaction action = {0};
    sigset_t set;                                     
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    action.sa_flags = 0;                              
    action.sa_mask = set;      	                      
    action.sa_handler = signalhandler;
    sigaction(SIGUSR1, &action, NULL);

    q = (queue*) sharemem();

    if (((mutex = sem_open("mutex", O_RDWR)) == SEM_FAILED) || ((free_space = sem_open("free_space", O_RDWR)) == SEM_FAILED) || ((items = sem_open("items", O_RDWR)) == SEM_FAILED)) 
    {
        perror("sem_open");
        exit(errno);
    }
}

uint16_t check_hash(message *message)       
{
    uint16_t hash = 0;
    int length = sizeof(*message);
    char *tmp = (char*) message;
    for (int i = 0; i < length; tmp++, i++)
    {
        hash = (*tmp) + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}



#endif //LAB04_HEADER_H
