#include "producer.h"
#include "consumer.h"

void menu()
{
    printf("\n              MENU             \n");
    printf("        1  CREATE PRODUCER\n");
    printf("        2  DELETE PRODUCER\n");
    printf("        3  CREATE CONSUMER\n");
    printf("        4  DELETE CONSUMER\n");
    printf("        i  INCREASE SIZE OF QUEUE\n");
    printf("        d  DECREASE SIZE OF QUEUE\n");
    printf("        m  SHOW MENU\n");
    printf("        l  SHOW THREADS INFO\n");
    printf("        s  SHOW SIZE OF QUEUE\n");
    printf("        q  EXIT PROGRAMM\n");
    printf("\n");
}


void show_threads()
{
    printf("\n       PROCESSES(PID)          \n");
    printf("             MAIN      \n");
    printf("        %ld\n", tid);
    printf("           PRODUCERS \n");
    for(int i = 0; i < amount_of_producers; i++)
    {
    printf("        %ld\n", producers[i]);
    }
    printf("          CONSUMERS\n");
    for(int i = 0; i < amount_of_consumers; i++)
    {
    printf("        %ld\n", consumers[i]);
    }
    printf("\n");
}
void handler(int signo)
{
}

void start_programm()
{
     signal(SIGUSR1, handler);
    tid = pthread_self();   
    memset(&q, 0, sizeof(queue));
    if(pthread_mutex_init(&mutex, NULL))
    {
        perror("pthread_mutex_init");
        exit(errno);
    }
    if(pthread_cond_init(&free_space, NULL) || pthread_cond_init(&items, NULL))
    {
        perror("pthread_cond_init");
        exit(errno);
    }
}

void finish_programm()
{
    while(amount_of_consumers)
    {
         del_con();
    }
    while(amount_of_producers)
    { 
        del_prod();
    }
    if(pthread_cond_destroy(&free_space) || pthread_cond_destroy(&items))
    {
        perror("pthread_cond_destroy");
        exit(errno);
    }
    if(pthread_mutex_destroy(&mutex))
    {
        perror("pthread_mutex_destroy");
        exit(errno);
    }
    printf("PROGRAMM FINISHED\n");
    exit(0);
}


void choose_opt(char *option)
{
    char tmp; 
    while(true)                                            
    {
        scanf("%c", &tmp);
        if((tmp >= '0' && tmp <= '4') || tmp == 'm' ||
            tmp == 'l' || tmp == 'i' || tmp == 'd' || tmp == 's'||tmp == 'q') break;
    }
    *option = tmp;
    printf("\n");
}

int main()
{
    start_programm();
    printf("\n");
    menu();
    char option;
    while(true)
    {
        choose_opt(&option);
        switch(option)
        {
            
            case '1':
            {
                create_prod();
                break;
            }
            case '2':
            {
                del_prod();
                break;
            }
            case '3':
            {
                create_con();
                break;
            }
            case '4':
            {
                del_con();
                break;
            }
            case 'i':
            {
                if(q_size == RANGE)
                {
                    fprintf(stderr, "max ring size is %d\n", RANGE);
                    break;
                }   
                q_size++;
                printf("INCREASED SIZE OF QUEUE. NOW IT IS %d\n", q_size);
                printf("\n");
                break;
            }
            case 'd':
            {
                
                if(!q_size)
                {
                     fprintf(stderr, "CAN'T DECREASE ANYMORE\n");
                }
                else if (q_size == num)
                {
                    fprintf(stderr, "QUEUE IS FULL! EXTRACT MESSAGES!\n");
                }
                else
                {
                printf("DECREASED SIZE OF QUEUE. NOW IT IS %d\n", --q_size);
                }
                printf("\n");
                break;
            }
            case 'm':
            {
                menu();
                break;
            }
            case 'l':
            {
                show_threads();
                break;
            }
            case 's':
            {
                printf("SIZE OF QUEUE %d\n", q_size);
                printf("\n");
                break;
            }
            case 'q':
            {
                finish_programm();
            }
        }
    }
}