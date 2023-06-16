#include "header.h"

void head()
{
    printf("NUMBER        NAME              ADDRESS         SEMESTER\n");
    printf("---------------------------------------------------------\n");
}

void menu()
{
    printf("\n");
    printf("MENU:\n");
    printf("MENU - SHOW MENU\n"); 
    printf("LST - AHOW ALL RECORDS\n");
    printf("GET - GET RECORD\n"); 
    printf("MOD - EDIT RECORD\n");
    printf("PUT - PUT LAST USED RECORD TO FILE\n"); 
    printf("QUIT - FINISH PROGRAMM\n"); 
    printf("\n");
}

void input_option(char *option)
{
    while(true)                                            
    {
        memset(option, '\0', 1024);
        fflush(stdin);
        fgets(option, 1024, stdin);

        option[strlen(option) - 1] = '\0';

        if(!strcmp(option, "MENU") || !strcmp(option, "LST") || !strcmp(option, "GET") ||
            !strcmp(option, "MOD") || !strcmp(option, "PUT") || !strcmp(option, "QUIT")) break;
    }
}

void validation_int(int *number, int min, int max)
{
    do 
    {
        if(!scanf("%d", number))
        {
            printf("INPUT YOUR CHOICE\n");
            (void) getchar();
            continue;
        }
        if(*number < min || *number > max) 
        {
            printf("YOUR NUMBER SHOULD BE BETWWEN %d AND %d!!!\n", min, max);
            continue;
        }
        (void) getchar();

        break;
    }while(true);
}

void get_record_by_number(int number, record_s *record)
 {
    off_t offset = (number-1) * sizeof(*record);
    lseek(fd, offset, SEEK_SET);
    if(read(fd, record, sizeof(*record)) == -1)
    {
        perror("read");
        exit(1);
    }
}

void print_by_number(int number) 
{   
    get_record_by_number(number, &current);
    printf("%4d %14s %20s %11d\n", number, current.name, current.address, current.semester);
}

void print_record_by_value(record_s *record)
{
    printf("%4d %14s %20s %11d\n", number, record->name, record->address, record->semester);
    printf("\n");
}

void put_record_by_number(int number, record_s *record) 
{
    off_t offset = (number-1) * sizeof(*record);
    lseek(fd, offset, SEEK_SET);
    if(write(fd, record, sizeof(*record)) == -1)
    {
        perror("write");
        exit(1);
    }
}

void lock_()
{
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = number * sizeof(record_s);
    lock.l_len = sizeof(record_s);
    while (fcntl(fd, F_SETLK, &lock) == -1) 
    {
        if (errno == EAGAIN) 
        {
            printf("RECORDS [%d] LOCKED. WAIT FOR RELEASE...\n", number);
            sleep(1);
        } 
        else 
        {
            perror("fcntl");
            exit(errno);
        }
    }
}

void change_current_record()
{
    int option;
    while(true)
    {
        printf("CURRENT RECORD:\n");
        printf("NUMBER: %d\nNAME: %s\nADDRESS: %s\nSEMESTER: %d\n\n", number, current.name, current.address, current.semester);
        printf("INPUT WHAT TO EDIT:\n1 - NAME\n2 - ADDRESS\n3 - SEMESTER\n0 - EXIT\n\n");
        validation_int(&option, 0, 3);
        switch(option)
        {
            case 1:
            {
                printf("INPUT NAME:\n");
                fgets(current.name, LENGHT, stdin);
                current.name[strlen(current.name) - 1] = '\0';
                break;
            }
            case 2:
            {
                printf("INPUT ADDRESS:\n");
                fgets(current.address, LENGHT, stdin);
                current.address[strlen(current.address) - 1] = '\0';
                break;
            }
            case 3:
            {
                printf("INPUT SEMESTER:\n");
                validation_int((int *)&current.semester, 1, 8);
                break;
            }
            case 0:
            {
                get_record_by_number(number, &tmp_rec);
                return;
            }
        }
    }
}

void save_record_to_file()
{
    record_s rec_sav = {0};
    bool flag = false;
    int pick;
    get_record_by_number(number, &rec_sav);
    if(memcmp(&rec_sav,&current,sizeof(rec_sav))!=0)
    {
  
        fprintf(stdout,"RECORD NEMBER %d WAS EDITED\n", number);
        lock_();
        if(memcmp(&tmp_rec,&rec_sav,sizeof(rec_sav)))
        {
            while(!flag)
            {
                printf("RECORD WAS CHANGED WHILE YOU WORKED WITH IT!!!\n");
                printf("THIS RECORD FROM FILE:\n");
                print_by_number(number);
                printf("PICK AN ACTION:\n1. ACCEPT CHANGES \n0. EDIT RECORD AGAIN\n");
                validation_int(&pick,0,1);
                switch (pick)
                {
                case 1:
                {
                    get_record_by_number(number,&current);
                    flag = true;
                    break;
                    
                }
                case 0:
                {
                    get_record_by_number(number,&current);
                    change_current_record();
                    put_record_by_number(number,&current);
                    flag = true;
                    break;
                }
                default:
                {
                    continue;
                }
                }
            }
            lock.l_type = F_UNLCK;
            fcntl(fd, F_SETLK,&lock);
            return;    
                
        }
         put_record_by_number(number,&current);
         lock.l_type = F_UNLCK;
         fcntl(fd,F_SETLK, &lock);
         fprintf(stdout, "RECORD[%d] IS SAVED IN FILE\n", number);
         return;
    }
    printf("RECORD[%d] IS NOT CHANGED!!!\n", number);
}





int main() 
{
    fd = open(file, O_RDWR);
    if (fd == -1) 
    {
        perror("open");
        exit(errno);
    }
    int temp;
    menu();
    char option[1024];
    while (true) 
    {
        if(number != 0) 
        {
            printf("CURRENT RECORD:\n");
            head();
            printf("%4d %14s %20s %11d\n\n", number, current.name, current.address, current.semester);
            printf("\n");
        }
        input_option(option);

        if (!strcmp(option, "MENU"))
        {
            menu();
        }
        else if (!strcmp(option, "LST"))
        {
            printf("RECORDS:\n");
            head();
            for (number = 1; number < AMOUNT_OF_RECORDS; number++)
            {
                print_by_number(number);
            }
            number--;
            printf("\n");
        }
        else if (!strcmp(option, "GET"))
        {
            printf("WHAT RECORD WOULD YOU LIKE (INPUT):\n");
            validation_int(&number, 1, AMOUNT_OF_RECORDS - 1);
            print_by_number(number);

        }
        else if (!strcmp(option, "MOD"))
        {
            if(number == 0)
            {
                printf("PICK A RECORD TO WORK WITH\n");
                continue;
            }
            change_current_record();
        }
        else if (!strcmp(option, "PUT"))
        {
            if(number == 0)
            {
                printf("READ OR CHANGE RECORD FIRST\n");
                continue;
            }
            save_record_to_file();
        }
        else if (!strcmp(option, "QUIT"))
        {
            printf("PROGRAMM FINISHED\n");
            break;
        }
    }
    close(fd);
    return 0;
}

















