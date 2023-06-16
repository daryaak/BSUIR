#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

struct struct_for_child
{
    int first;
    int second;
};

bool output_allow = true;
bool is_there_signal = false;

int amount_of_00 = 0;
int amount_of_01 = 0;
int amount_of_10 = 0;
int amount_of_11 = 0;

int count = 0;

struct struct_for_child stat;

struct struct_for_child increase_stat(struct struct_for_child stat);

void func_for_alarm();

void func_for_usr(int signal);

int main()
{

srand(time(NULL));

signal(SIGUSR1, func_for_usr);

signal(SIGUSR2, func_for_usr);

signal(SIGALRM, func_for_alarm);  

alarm(1 + rand() % 5);

while(1)
{
    sleep(1);

    stat=increase_stat(stat);

    if(count>=11)
    {
        if(output_allow==true)
        {
            is_there_signal=false;

            alarm(0);

            union sigval data;

            data.sival_int = getpid();

            while (!is_there_signal) 
            {       
                sigqueue(getppid(), SIGUSR1, data);      
                sleep(2);
            }

            alarm(1 + rand() % 5);

            if(!output_allow)
            {
                count=0;
                output_allow=true;
                continue;
            }

            printf("\nPPID is %d PID is %d ", (int)getppid(), (int)getpid());

            printf("{0,0} - %d ", amount_of_00);          
            printf("{0,1} - %d ", amount_of_01);  
            printf("{1,0} - %d ", amount_of_10);  
            printf("{1,1} - %d \n", amount_of_11);  

            count=0;

            sigqueue(getppid(), SIGUSR2, data);

            
        }
    }
    count++;
}

exit(0);
}


struct struct_for_child increase_stat(struct struct_for_child stat)
{
    static int check;

    if(check==0)
    {
        stat.first=0;
        stat.second=0;
        check++;
            
    }
    else if(check==1)
    {
        stat.first=0;
        stat.second=1;
        check++;
            
    }
    else if(check==2)
    {
        stat.first=1;
        stat.second=0;
        check++;
        
    }
    else if(check==3)
    {
        stat.first=1;
        stat.second=1;
        check++;
            
    }
    else
    {
        check=0;
    }
    

    return stat;
}

void func_for_alarm()
{
    if(stat.first==0)
    {
        if(stat.second==0) amount_of_00++;
        if(stat.second==1) amount_of_01++;
    }
    if(stat.first==1)
    {
        if(stat.second==0) amount_of_10++;
        if(stat.second==1) amount_of_11++;
    }
    alarm(1 + rand() % 5);
}

void func_for_usr(int signal)
{
    if(signal==SIGUSR1)
    {
        output_allow =false;
        is_there_signal = true;
    }

    if(signal==SIGUSR2)
    {
        output_allow = true;
        is_there_signal = true;
    }
}








