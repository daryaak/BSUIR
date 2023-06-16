#include "header.h"


char input[1024];	    
char reply[4096];  
char current[1024];
bool broken = false;

int make_connection (char *name, int *a)
{
    int socketnumber;	                            		
    struct sockaddr_in adress_of_client;  			
    struct sockaddr_in adress_of_service;	    		
    struct hostent	   *struct_of_id_server;

    if((struct_of_id_server = gethostbyname(name)) == NULL)    
    {
        printf("THIS SERVER: %s NOT FOUND!!!\n\n", name);
        return (ERROR_INVALID_HOST_NAME);
    }

    if((socketnumber = socket(AF_INET, SOCK_STREAM, 0)) < 0)                
    {
        fprintf(stderr, "CAN'T CREATE SOCKET\n\n");
        return (ERROR_CREATE_SOCKET_FAILED);
    }

    memset((char *) &adress_of_client, 0, sizeof(adress_of_client));    

    adress_of_client.sin_family = AF_INET;
    adress_of_client.sin_addr.s_addr = htonl(INADDR_ANY);     
    adress_of_client.sin_port = 0;                           

    int flag = 1;

    setsockopt(socketnumber, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(int));
    if(bind(socketnumber, (struct sockaddr *)&adress_of_client, sizeof(adress_of_client)) < 0)  
    {   
        fprintf(stderr, "CAN'T CONNECT SOCKET WITH ID AND PORT OF CLEINT\n\n");
        close(socketnumber);                                                  
        return(ERROR_BIND_FAILED);
    }

    memset((char *) &adress_of_service, 0, sizeof(adress_of_service)); 

    adress_of_service.sin_family = AF_INET;
    memcpy((char *) &adress_of_service.sin_addr, struct_of_id_server->h_addr, struct_of_id_server->h_length);
    adress_of_service.sin_port = htons(SERVER_FTP_PORT);

    if (connect(socketnumber, (struct sockaddr *) &adress_of_service, sizeof(adress_of_service)) < 0) 
    {
        fprintf(stderr, "CAN'T CONNECT TO SERVER\n\n");
        close(socketnumber); 	                        
        return(ERROR_CONNECT_FAILED);
    }

    *a = socketnumber; 

    return(GOOD);
}
void sigpipe_handler()
{
    printf("SERVER BROKE THE CONNECTION!!!\n");
    broken= true;
}



int send_message(int s, char *message, int size_of_message)
{
    if((send(s, message, size_of_message, 0)) < 0)            
    {
        fprintf(stderr, "COULD NOT SEND A MESSAGE!!!\n\n");
        return(ERROR_SEND_FAILED);
    }

    return(GOOD);
}

int receive_message(int s, char *tmp, int tmpsize, int *size_of_message)
{
    *size_of_message = recv(s, tmp, tmpsize, 0);         

    if(*size_of_message <= 0)
    {
        fprintf(stderr, "COULD NOT RECIEVE A MESSAGE!!!\n\n");
        return(ERROR_RECEIVE_FAILED);
    }

    return (GOOD);
}

void print_message(char *message, int size_of_message)
{
    int i = 0;
    char tmp[4];

    strncpy(tmp, message, 3);

    if (strcmp(tmp, "cmd") == 0)
    {
        printf("LOG: ");
    }

    for(i = 0; i < size_of_message; i++)
    {                     
        printf("%c", message[i]);
    }
    printf("\n");
}

void change_directory(char *input)
{
    
    char arg[1024];
    char tmp[1024];
    char *str;
    //int len = strlen(current);
    int i = 0;

    memset(arg, '\0', 1024);
    memset(tmp, '\0', 1024);
     
    strcpy(arg, input + 3);
    arg[strcspn(arg, "\n")+1] = '\0'; 
    strcpy(tmp, current);
    i = strlen(tmp);

    /*if (strlen(tmp))
    {
        strcat(tmp, "/");
    }*/

    if (!strlen(arg))
    {
        return;
    }

    str = strtok(arg, "/\n");

    if (strcmp(str, "..") == 0)
    {
        tmp[i - 1] = '\0';
        i--;
        for (;tmp[i] != '/' && i > 0; i--)
        {
            tmp[i] = '\0';
        }
        tmp[i] = '\0';
    }
     else if (strcmp(str, ".") != 0 )
    {
        if (strlen(tmp))
            strcat(tmp, "/");
        strcat(tmp, str);
    }


    while ((str = strtok(NULL, "/\n")) != NULL)
    {
        i = strlen(tmp);
        if (strcmp(str, ".") == 0)
        {
            continue;
        }

        if (strcmp(str, "..") == 0)
        {
            tmp[i - 1] = '\0';
            i--;
            for (;tmp[i] != '/' && i > 0; i--)
            {
                tmp[i] = '\0';
            }
            tmp[i] = '\0';
            continue;
        } else 
        {
            if (strlen(tmp))
            {
                strcat(tmp, "/");
            }
            strcat(tmp, str);
        }
    }
    strcpy(current, tmp);

}



char *get_current_directory(char *buffer)
{
    int size = (int) strlen(current);

    if (size > 0)
    {
        strncpy(buffer, current, size );
    }
    else
    {
        memset(buffer, '\0', 1024);
    }
        
    return buffer;
}


int main()
{

    int size_of_message;	        
    int main_socket;	   
    int status = GOOD;
    char tmp[1024];

    signal(SIGPIPE, sigpipe_handler);
    memset(current, '\0', sizeof(current));
    printf("CLIENT STARTED WORK\n");

    do
    {
        printf("\nENTER NAME OR IP-ADRESS OF SERVER (quit TO EXIT): ");
        scanf("%s", input);
        getc(stdin);

        if (strcmp(input,"quit") == 0)
        {
            return(GOOD);
        }
        printf("CONNECTING TO SERVER\n");
        status = make_connection(input, &main_socket);  		
    } while (status != GOOD);

    status = receive_message(main_socket, reply, sizeof(reply), &size_of_message);

    if(status == GOOD && size_of_message > 0)
    {
        print_message(reply, size_of_message);
    }

    while (true)
    {
        memset(tmp, '\0', sizeof(tmp));
        printf("%s> ", get_current_directory(tmp));
        memset(input, '\0', sizeof(input));
        fgets(input, 1024, stdin);
        
        if (strlen(input) <= 1)
        {
            continue;
        }

        if (input[0] != '@')
        {
            status = send_message(main_socket, input, strlen(input) + 1);
            if(status != GOOD)
            {
                if (broken == true)
                {
                    break;
                }
                fprintf(stderr, "ERROR WHILE SENDING COMMAND!!!\n\n");
                continue;
            }

            status = receive_message(main_socket, reply, sizeof(reply), &size_of_message);
            if(status != GOOD)
            {
                fprintf(stderr, "ERROR WITH GETTING REPLY FROM SERVER!!!\n\n");
            }
            else
            {
                print_message(reply, size_of_message);
            }
        }
        else
        {
            FILE *script;
            input[strcspn(input, "\n")] = '\0'; 

            if((script = fopen(input + 1, "r")) == NULL)
            {
                fprintf(stderr, "FILE DOES NOT EXIST\n\n");
                continue;
            }

            while (!feof(script))
            {
                fgets(input, 1024, script);
                printf("%s> %s", current, input);

                status = send_message(main_socket, input, strlen(input) + 1);
                if(status != GOOD)
                {
                    if (broken == true)
                    {
                        break;
                    }
                    fprintf(stderr, "ERROR WHILE SENDING COMMAND!!!\n\n");
                    continue;
                }

                status = receive_message(main_socket, reply,sizeof(reply), &size_of_message);
                if(status != GOOD)
                {
                    fprintf(stderr, "ERROR WITH GETTING REPLY FROM SERVER!!!\n\n");
                }
                else
                {
                    print_message(reply, size_of_message);
                }

                lower(input);

                if (strncmp(input, "cd", 2) == 0&& 
                        !strcmp(reply, "cmd 250 ok\n"))
                {
                    change_directory(input);
                }
                if (strcmp(input, "quit\n") == 0)
                {
                    break;
                }
            }
            fclose(script);
        }   

        lower(input);

        if (strncmp(input, "cd", 2) == 0 && !strcmp(reply, "cmd 250 ok\n"))
        {
            change_directory(input);
        }
        if (strcmp(input, "quit\n") == 0)
        {
            break;
        }
        if (broken == true)
        {
            break;
        }
    }

    close(main_socket);

    printf("CLIENT FINISHED WORK.\n");

    return (status);
}

