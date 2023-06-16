#ifndef LAB07_HEADER_H
#define LAB07_HEADER_H
#define _XOPEN_SOURCE 700
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
#include <time.h>
#include <pthread.h>

#define SIZE 256
#define DATA (((SIZE + 3) / 4) * 4)
#define THREADS 4096
#define RANGE 512

typedef struct message{
  uint8_t type;
  uint16_t hash;
  uint8_t size;
  uint8_t data[DATA];
} message;                       

typedef struct queue{
  int inc;
  int dec;
  int head;                     
  int tail;
  message buffer[RANGE + 1];
} queue;                         

queue q;                       

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t items = PTHREAD_COND_INITIALIZER;  
pthread_cond_t free_space = PTHREAD_COND_INITIALIZER;

pthread_t tid;                            
int q_size = 10;
int num = 0;
int amount_of_producers;                    
int amount_of_consumers;                       

pthread_t producers[THREADS];           
pthread_t consumers[THREADS];          

bool prod_bool[THREADS] = {0};
bool con_bool[THREADS] = {0};


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
#endif //LAB07_HEADER_H