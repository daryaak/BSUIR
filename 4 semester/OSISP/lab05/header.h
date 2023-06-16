#ifndef LAB05_HEADER_H
#define LAB05_HEADER_H
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


void println();                             // функция для вывода линии, состоящей из '-'

typedef struct message{
  uint8_t type;
  uint16_t hash;
  uint8_t size;
  uint8_t data[DATA];
} message;                       // структура сообщения

typedef struct queue{
  int inc;
  int dec;
  int head;                     
  int tail;
  message buffer[RANGE + 1];
} queue;                         // структура кольцевого буфера

queue q;                       

pthread_mutex_t mutex;                      // мьютекс для монопольного доступа к очереди и два семафора для заполнения и извлечения сообщений
sem_t *items;                               // семафоры для количества сообщений и свободных мест в очереди 
sem_t *free_space;

pthread_t tid;                              // id потока родительского процесса
int q_size = 10;
int amount_of_producers;                        // количество производителей
int amount_of_consumers;                        // количество потребителей

pthread_t producers[THREADS];           // id потоков производителей
pthread_t consumers[THREADS];           // id потоков потребителей


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
#endif //LAB05_HEADER_H