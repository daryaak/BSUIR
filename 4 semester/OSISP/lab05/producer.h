#include "header.h"

void print_producer_message(message *mess)
{
    printf("PROCESS (TID): %ld CREATED MESSAGE: \nTYPE: %d\nHASH: %04X\nSIZE: %d\n", pthread_self(), mess->type, mess->hash, mess->size);
    printf("AMOUNT OF PUSHED MESSAGES: %d\n", q.inc);
    printf("\n");
}

int push(message *mess)
{
    if (q.tail == q_size) q.tail = 0;
    q.buffer[q.tail] = *mess;
    q.tail++;
    return ++q.inc;
}

void create(message *mess)
{
    int size = 0;
    mess->type = 0;
    while(!size)
    {
        size = rand() % 257;
        if(size == 256)
        {
            mess->type = 1;
            mess->size = 0;
            break;
        }
        mess->size = size;
    }
    uint8_t tmp_data;
    for(int i = 0; i < size; i++)
    {
        tmp_data = ((rand() % (127 - 32)) + 32);
        mess->data[i] = tmp_data;           
    }
    mess->hash = 0;
    mess->hash = check_hash(mess);
}

void *add_message(void *arg)
{
    message mess;
    int a;
    while (true) 
    {
        sleep(3);
        create(&mess);
        sem_getvalue(free_space, &a);
        if(!a)
        {
            fprintf(stderr, "!NO SPACE IN QUEUE! PRODUCER(TID): %ld WAITING\n", pthread_self());
        }
        sem_wait(free_space);      
        pthread_mutex_lock(&mutex); 

        push(&mess);
        print_producer_message(&mess);

        pthread_mutex_unlock(&mutex);
        sem_post(items);       
    }
}

void create_prod()
{
    if(amount_of_producers == THREADS - 1)
    {
        fprintf(stderr, "YOU REACHED MAX AMOUNT OF PRODUCERS\n");
        return;
    }
    if(pthread_create(&producers[amount_of_producers], NULL, add_message, NULL))
    {
        perror("pthread_create");
        exit(errno);
    }
    printf("PRODUCER CREATED. PID: %ld\n", producers[amount_of_producers]);
    printf("\n");
    amount_of_producers++;
}

void del_prod()
{
    if(amount_of_producers == 0)
    {
        fprintf(stderr, "NO PRODUCERS FOUND\n");
        return;
    }
    amount_of_producers--;
    pthread_cancel(producers[amount_of_producers]);
    if(pthread_join(producers[amount_of_producers], NULL))
    {
        perror("pthread_join");
        exit(errno);
    }
    printf("PRODUCER DELETED. PID: %ld\n", producers[amount_of_producers]);
    printf("\n");
}







