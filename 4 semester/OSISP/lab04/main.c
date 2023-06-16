#include "header.h"

pid_t producers[MAX_AMOUNT]; 
pid_t consumers[MAX_AMOUNT]; 
int count_producers;       
int count_consumers;        

static pid_t ppid;       

void show_processes()
{
    printf("\n       PROCESSES(PID)          \n");
    printf("             MAIN      \n");
    printf("              %d\n", ppid);
    printf("           PRODUCERS \n");
    for(int i = 0; i < count_producers; i++)
    {
    printf("              %d\n", producers[i]);
    }
    printf("          CONSUMERS\n");
    for(int i = 0; i < count_consumers; i++)
    {
    printf("              %d\n", consumers[i]);
    }
    printf("\n");
}

void create_prod()
{
    if(count_producers == MAX_AMOUNT - 1)
    {
        fprintf(stderr, "YOU REACHED MAX AMOUNT OF PRODUCERS:  %d\n", MAX_AMOUNT);
        return;
    }
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(errno);
    }
    if (pid == 0)
    {
        char producer_path[] = "./producer";
        execl(producer_path, producer_path, NULL);
    }
    producers[count_producers++] = pid;
    printf("PRODUCER CREATED. PID: %d\n", pid);
    printf("\n");
}

void del_prod()
{
    if(count_producers == 0)
    {
        fprintf(stderr, "NO PRODUCERS FOUND\n");
        return;
    }
    pid_t pid = producers[--count_producers];
    kill(pid, SIGUSR1);
    waitpid(pid, NULL, 0);
    printf("PRODUCER DELETED. PID: %d\n", pid);
    printf("\n");
}

void create_con()
{
    if(count_consumers == MAX_AMOUNT - 1)
    {
        fprintf(stderr, "YOU REACHED MAX AMOUNT OF CONSUMERS:  %d\n", MAX_AMOUNT);
        return;
    }
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(errno);
    }
    if (pid == 0)
    {
        char consumer_path[] = "./consumer";
        execl(consumer_path, consumer_path, NULL);
    }
    consumers[count_consumers++] = pid;
    printf("CONSUMER CREATED. PID: %d\n", pid);
    printf("\n");
}

void del_con()
{
    if(count_consumers == 0)
    {
        fprintf(stderr, "NO CONSUMERS FOUND\n");
        return;
    }
    pid_t pid = consumers[--count_consumers];
    kill(pid, SIGUSR1);
    waitpid(pid, NULL, 0);
    printf("CONSUMER DELETED. PID: %d\n", pid);
    printf("\n");
}

void start_programm()
{
    ppid = getpid();
    int fd = shm_open("que", (O_RDWR | O_CREAT | O_TRUNC), (S_IRUSR | S_IWUSR));
    if (fd == -1)
    {
        perror("shm_open");
        exit(errno);
    }
    if (ftruncate(fd, sizeof(queue)))
    {
        perror("ftruncate");
        exit(errno);
    }
    void *tmp = mmap(NULL, sizeof(queue), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (tmp == MAP_FAILED)
    {
        perror("mmap");
        exit(errno);
    }
    q = (queue*) tmp;
    memset(q, 0, sizeof(queue));                   
    if (close(fd))
    {
        perror("close");
        exit(errno);
    }
    if ((mutex = sem_open("mutex", (O_RDWR | O_CREAT | O_TRUNC), (S_IRUSR | S_IWUSR), 1)) == SEM_FAILED || 
        (free_space = sem_open("free_space", (O_RDWR | O_CREAT | O_TRUNC), (S_IRUSR | S_IWUSR), BUFFER_SIZE)) == SEM_FAILED ||
        (items = sem_open("items", (O_RDWR | O_CREAT | O_TRUNC ), (S_IRUSR | S_IWUSR), 0)) == SEM_FAILED) 
    {
        perror("sem_open");
        exit(errno);
    }

}

void finish_programm()
{
    if(sem_close(mutex) == -1 || sem_close(free_space)== -1 || sem_close(items) == -1)                    
    {
        perror("sen_close");
        exit(errno);
    }
    if(sem_unlink("mutex") == -1 || sem_unlink("free_space")== -1 || sem_unlink("items") == -1)
    {
        perror("sem_unlink");
        exit(errno);
    }
    if(munmap(q, sizeof(queue)) == -1)             
    {
        perror("munmap");
        exit(errno);
    }
    if(shm_unlink("que") == -1)
    {
        perror("shm_unlink");
        exit(errno);
    }
    for (int i = 0; i < count_producers; ++i)      
    {
        kill(producers[i], SIGTERM);
        wait(NULL);
    }
    for (int i = 0; i < count_consumers; ++i)
    {
        kill(consumers[i], SIGTERM);
        wait(NULL);
    }
    exit(0);
}

void menu()
{
    printf("\n              MENU             \n");
    printf("        1  CREATE PRODUCER\n");
    printf("        2  DELETE PRODUCER\n");
    printf("        3  CREATE CONSUMER\n");
    printf("        4  DELETE CONSUMER\n");
    printf("        m  SHOW MENU\n");
    printf("        l  SHOW PROCESSES INFO\n");
    printf("        q  EXIT PROGRAMM\n");
    printf("\n");
}

void choose_opt(char *opt)
{
    while(1)
    {
        scanf("%c", opt);
        if((*opt >= '1' && *opt <= '4') || *opt == 'm' || *opt == 'l' || *opt == 'q') break;
    }
    printf("\n");
}

int main()
{
    start_programm();
    printf("\n");
    menu();
    char option;
    while(1)
    {
        choose_opt(&option);
        switch(option)
        {
            case 'm':
            {
                menu();
                break;
            }
            case 'l':
            {
                show_processes();
                break;
            }
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
            case 'q':
            {
                finish_programm();
            }
        }
    }
}





