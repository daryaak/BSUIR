#include "header.h"

void print_consumer_message(message *mess)
{
    printf("PROCESS (TID): %ld CONSUMED MESSAGE: \nTYPE: %d\nHASH: %04X\nSIZE: %d\n", pthread_self(), mess->type, mess->hash, mess->size);
    printf("AMOUNT OF EXTRACTED MESSAGES: %d\n", q.dec);
    printf("\n");
}

int pop(message *msg)
{
    if (q.head == q_size) q.head = 0;
    *msg = q.buffer[q.head];
    q.head++;
    return ++q.dec;
}


void checkmes(message *mess) 
{
    uint16_t messhash = mess->hash; 
    mess->hash = 0;
    uint16_t sum = check_hash(mess);
    if(sum != messhash)
    {
        fprintf(stderr, "SUM IS %04X != MESSHASH = %04X\n", sum, messhash);
    }
    mess->hash = messhash;  
}

void *extract_message(void *arg) 
{
    message mess;
    int a;
    while(true)
    {
        sleep(3);
        sem_getvalue(items, &a);
        if(!a)
        {
            fprintf(stderr, "!NO SPACE IN QUEUE! CONSUMER(PID): %ld WAITING\n", pthread_self());
        }
        sem_wait(items);            
        pthread_mutex_lock(&mutex);  

        pop(&mess);
        checkmes(&mess);
        print_consumer_message(&mess);

        pthread_mutex_unlock(&mutex);
        sem_post(free_space);       
    }
}

void create_con()
{
    if(amount_of_consumers == THREADS - 1)
    {
        fprintf(stderr, "YOU REACHED MAX AMOUNT OF CONSUMERS\n");
        return;
    }
    if(pthread_create(&consumers[amount_of_consumers], NULL, extract_message, NULL))
    {
        perror("pthread_create");
        exit(errno);
    }
    printf("CONSUMER CREATED. PID: %ld\n", consumers[amount_of_consumers]);
    printf("\n");
    amount_of_consumers++;
}

void del_con()
{
    if(amount_of_consumers == 0)
    {
        fprintf(stderr, "NO CONSUMERS FOUND\n");
        return;
    }
    amount_of_consumers--;
    pthread_cancel(consumers[amount_of_consumers]);
    if(pthread_join(consumers[amount_of_consumers], NULL))
    {
        perror("pthread_join");
        exit(errno);
    }
    printf("CONSUMER DELETED. PID: %ld\n", consumers[amount_of_consumers]);
    printf("\n");
}