#include "header.h"
#include <time.h>


void print_message(message *mess)
{
    printf("PROCESS (PID): %d CREATED MESSAGE: \nTYPE: %d\nHASH: %04X\nSIZE: %d\n", getpid(), mess->type, mess->hash, mess->size);
    printf("AMOUNT OF PUSHED MESSAGES: %d\n", q->inc);
    printf("\n");
}

int push(message *mess)
{
    if (q->tail == BUFFER_SIZE) q->tail = 0;
    q->buffer[q->tail] = *mess;
    q->tail++;
    return ++q->inc;
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

int main()
{
    begin();
    message mess;
    int a = 0;
    while (!check)
    {
        sleep(2);
        sem_getvalue(free_space, &a);
        if(!a)
        {
            fprintf(stderr, "!NO SPACE IN QUEUE! PRODUCER(PID): %d WAITING\n", getpid());
        }
        create(&mess);

        sem_wait(free_space);  
        sem_wait(mutex);      

        push(&mess);
        print_message(&mess);

        sem_post(mutex);       
        sem_post(items);      
    }
    end();
    return 0;
}

