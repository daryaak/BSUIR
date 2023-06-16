#include "header.h"

void print_message(message *mess)
{
    printf("PROCESS (PID): %d CONSUMED MESSAGE:\nTYPE: %d\nHASH: %04X\nSIZE: %d\n", getpid(), mess->type, mess->hash, mess->size);
    printf("AMOUNT OF EXTRACTED MESSAGES: %d\n", q->dec);
    printf("\n");
}

int pop(message *mess)
{
    if (q->head == BUFFER_SIZE) q->head = 0;
    *mess = q->buffer[q->head];
    q->head++;
    return ++q->dec;
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

int main()
{
    begin();
    message mess;
    int count = 0;
    while(!check)
    {
        sleep(2);
        sem_getvalue(items, &count);
        if(!count)
        {
            fprintf(stderr, "!NO SPACE IN QUEUE! CONSUMER(PID): %d WAITING\n", getpid());
        }
        sem_wait(items);          
        sem_wait(mutex);            

        pop(&mess);
        checkmes(&mess);
        print_message(&mess);

        sem_post(mutex);         
        sem_post(free_space);       

    }
    end();
    return 0;
}