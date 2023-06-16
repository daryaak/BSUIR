#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include <unistd.h>

struct info_child_proc
{
    pid_t pid;          //pid
    char name_of_proc[80];      //имя
    bool block_or_not;    //блокировка
};

struct info_child_proc *child_processes = NULL;

int amount_of_children =0;

bool is_out_available = true;

int my_atoi(char *str);

char *my_itoa(int number);

void my_strcat(char *str1, char *str2, char *res);

void func_for_signal(int signal, siginfo_t *data, void *ucontext);

void set();

void create_child(pid_t pid);

void delete_one_proc(struct info_child_proc *child_processes, int number);

int delete_all_procs(struct info_child_proc *child_processes, int number);

int main()
{
    set();

    char opt[11];
    pid_t temp_pid;

    while(true)
    {
        opt[0]='\0';

        fgets(opt, 11, stdin);

        if (strcmp(opt, "+\n") == 0) 
        {           
            temp_pid = fork();      
            amount_of_children++;
            child_processes = realloc(child_processes, amount_of_children * sizeof(struct info_child_proc)); 
            create_child(temp_pid);

            if (temp_pid < 0) 
            {
                fprintf(stderr,"%s\n" ,strerror(errno));
                exit(1);
            } 
            if (temp_pid == 0) 
            {
                execl("./child", "child", NULL);
            }
             else 
            {
                printf("%s IS CREATED WITH PID: %d\n", child_processes[amount_of_children-1].name_of_proc, temp_pid);
                printf("TOTAL NUMBER OF CHILDREN: %d\n", amount_of_children);
            }
        }

        if (strcmp(opt, "-\n") == 0 ) 
        {  
            if(amount_of_children!=0)
            {
            delete_one_proc(child_processes, amount_of_children-1);        //удалить процесс
            amount_of_children--;
            child_processes = realloc(child_processes, amount_of_children * sizeof(struct info_child_proc));      //перераспределение памяти
            printf("TOTAL NUMBER OF CHILDREN: %d\n", amount_of_children);
            }
            if(amount_of_children==0)
            {
                printf("NO CHILDREN AVAILABLE TO DELETE");

            }
        }

        if (strcmp(opt, "l\n") == 0) 
        {    
            printf("PARENT PID IS: %d\n", (int)getpid());
            if(amount_of_children!=0)
            {
            printf("CHILD:\n");
            for (int i=0;i<amount_of_children;i++) 
            {
                printf("%s:\t%d\t", child_processes[i].name_of_proc,child_processes[i].pid);        //вывод информации о дочерних процессах
                if (child_processes[i].block_or_not) 
                {
                    printf("BLOCK\n");
                }
                else
                    printf("AVAILABLE\n");
            }
            }
            if(amount_of_children==0)
            {
                printf("NO CHILDREN AVAILABLE");

            }
        }

        if (strcmp(opt, "k\n") == 0) 
        {      
            if (amount_of_children!=0) 
            {
                amount_of_children = delete_all_procs(child_processes, amount_of_children);
            }
            if (amount_of_children==0)
            {
                printf("NO CHILDREN AVAILABLE");
            }
        }

        if (strcmp(opt, "s\n") == 0) 
        {      
            if (amount_of_children!=0) 
            {
                for (int i=0;i<amount_of_children;i++) 
                {

                kill(child_processes[i].pid, SIGUSR1);   

                child_processes[i].block_or_not=true;

                }
            }
            if (amount_of_children==0)
            {
                printf("NO CHILDREN AVAILABLE");
            }
        }

        if (strcmp(opt, "g\n") == 0) 
        {      
            if (amount_of_children!=0) 
            {
                for (int i=0;i<amount_of_children;i++) 
                {

                kill(child_processes[i].pid, SIGUSR2);   

                child_processes[i].block_or_not=false;

                }
            }
            if (amount_of_children==0)
            {
                printf("NO CHILDREN AVAILABLE");
            }
        }

        if (strstr(opt,"<") && strstr(opt,">")) 
        {       
            int number_pid=my_atoi(opt);
            if (number_pid>=amount_of_children)
            {
                printf("WRONG NUBER!!! NUMBER OF CHILDREN IS  %d\n",amount_of_children);
                continue;
            }
            if (opt[0]=='s') 
            {      
                kill(child_processes[number_pid].pid, SIGUSR1);
                child_processes[number_pid].block_or_not=true;
                printf("%s WAS BLOCKED\n",child_processes[number_pid].name_of_proc);
            }
            if (opt[0]=='g') 
            {      
                kill(child_processes[number_pid].pid, SIGUSR2);
                child_processes[number_pid].block_or_not=false;
                printf("%s NOW AVAILABLE\n",child_processes[number_pid].name_of_proc);
            }
            if (opt[0]=='p')
             {      
                for (int i=0;i<amount_of_children;i++) 
                {
                    kill(child_processes[i].pid, SIGUSR1);
                    child_processes[i].block_or_not = true;
                }
                sleep(2);
                kill(child_processes[number_pid].pid, SIGUSR2);
                child_processes[number_pid].block_or_not = false;      
            }
        }

        if (strcmp(opt, "q\n") == 0) 
        {     
            if(amount_of_children!=0) 
            {
                amount_of_children= delete_all_procs(child_processes, amount_of_children);
            }
            break;
            if(amount_of_children==0)
            {
                printf("NO CHILDREN AVAILABLE");
                break;
            }
        }
    }
    return 0;

}

int my_atoi(char *str)
{
    char *number = NULL;
    int len = 0;

    for(int i=0;str[i]!='\0';i++)
    {
        if (str[i]>'0' && str[i]<'9')
        {
            len++;
            number = realloc(number, len);
            number[len-1]=str[i];
        }
    }

    if(len) 
    {
        return atoi(number);
    }
     return 0;
}

char *my_itoa(int number)
{

    int i = 0;
    int len = 0;
    int a;
    char *str;
    int temp=number;
    while(temp != 0) 
    { 
        len++;
        temp = temp/10;
    }

    str = (char*) malloc((len + 1) * sizeof(char));     

    
    do 
    {
        a = number % 10;
        str[i++] = a + '0';
        number/= 10;

    }while(number!=0);

    str[i] = '\0';

    for(i = 0; i < len / 2; i++) 
    {
        char s = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = s;       
    }
    return str;
}

void func_for_signal(int signal, siginfo_t *data, void *ucontext)
{
    if(signal==SIGUSR1)
    {
        if(!is_out_available)
        {
             kill((*data).si_value.sival_int, SIGUSR1);
        }
        else
        {
            is_out_available = false;
            kill((*data).si_value.sival_int,SIGUSR2);
        }
    }
    if(signal==SIGALRM)
    {
        for (int i=0;i<amount_of_children;i++) 
        {
            kill(child_processes[i].pid, SIGUSR2);
        }
    }
    if(signal==SIGUSR2) is_out_available=true;
}

void set()
{
   struct sigaction temp;

   memset(&temp,0,sizeof(temp));

   temp.sa_sigaction = func_for_signal;
   temp.sa_flags = SA_SIGINFO;

    sigset_t check;

    sigemptyset(&check);
    sigaddset(&check, SIGUSR1);
    sigaddset(&check, SIGUSR2);
    sigaddset(&check, SIGALRM);

    temp.sa_mask = check;

    sigaction(SIGUSR1, &temp, 0);
    sigaction(SIGUSR2, &temp, 0);
    sigaction(SIGALRM, &temp, 0);
}

void my_strcat(char *str1, char *str2, char *res) 
{
    strcpy(res, str1);   
    strcat(res, str2);   
}

void create_child(pid_t pid)
{
    my_strcat("C_",my_itoa(amount_of_children-1),child_processes[amount_of_children-1].name_of_proc);
    child_processes[amount_of_children-1].pid = pid;
    child_processes[amount_of_children-1].block_or_not=false;
}

void delete_one_proc(struct info_child_proc *child_processes, int number)
{
    printf("DELETE PROCCES %d \n", child_processes[number].pid);
    kill(child_processes[number].pid, SIGTERM);
}

int delete_all_procs(struct info_child_proc *child_processes, int number)
{
    while (number) 
    {
        delete_one_proc(child_processes,number-1);
        number--;
    }
    if(child_processes!=NULL)
    {
        free(child_processes);
        child_processes=NULL;
    }

    return number;
}

